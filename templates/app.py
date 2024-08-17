from flask import Flask, request, jsonify
from flask_cors import CORS
import logging
import math


app = Flask(__name__)
CORS(app)

# Set up logging
logging.basicConfig(level=logging.DEBUG)

sensor_data = {
    "gas": 0,
    "ultrasonic1": 0,
    "ultrasonic2": 0
}

graph = {
    'MBPP': {'Trash1': 2, 'Trash2': 4},
    'Trash1': {'MBPP': 2, 'Trash2': 3, 'Trash3': 8},
    'Trash2': {'MBPP': 4, 'Trash1': 3, 'Trash4': 5, 'Trash3': 2},
    'Trash3': {'Trash1': 8, 'Trash2': 2, 'Trash4': 11, 'Trash5': 22},
    'Trash4': {'Trash2': 5, 'Trash3': 11, 'Trash5': 1},
    'Trash5': {'Trash3': 22, 'Trash4': 1},
}

def floyd_warshall(graph):
    nodes = list(graph.keys())
    dist = {node: {node: math.inf for node in nodes} for node in nodes}
    next_node = {node: {node: None for node in nodes} for node in nodes}

    for node in nodes:
        dist[node][node] = 0
        for neighbor, weight in graph[node].items():
            dist[node][neighbor] = weight
            next_node[node][neighbor] = neighbor

    for k in nodes:
        for i in nodes:
            for j in nodes:
                if dist[i][j] > dist[i][k] + dist[k][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    next_node[i][j] = next_node[i][k]

    return dist, next_node

# Function to reconstruct the path from next_node
def construct_path(next_node, u, v):
    if next_node[u][v] is None:
        return []
    path = [u]
    while u != v:
        u = next_node[u][v]
        path.append(u)
    return path

# Nearest Neighbor Algorithm using precomputed shortest paths
def nearest_neighbor_algorithm(graph, full_bins):
    dist, next_node = floyd_warshall(graph)

    # Start at the first full bin
    start_bin = full_bins[0]
    visited = [start_bin]
    current_bin = start_bin
    total_distance = 0
    path = []

    while len(visited) < len(full_bins):
        nearest_bin = None
        nearest_distance = float('inf')
        
        for bin in full_bins:
            if bin not in visited and dist[current_bin][bin] < nearest_distance:
                nearest_bin = bin
                nearest_distance = dist[current_bin][bin]

        # If no valid nearest bin is found, break the loop to avoid infinite loop
        if nearest_bin is None:
            break

        # Append the path to the nearest bin
        path.extend(construct_path(next_node, current_bin, nearest_bin)[:-1])
        visited.append(nearest_bin)
        total_distance += nearest_distance
        current_bin = nearest_bin

    # Optional: Return to the start bin to complete the cycle if possible
    if len(visited) == len(full_bins) and dist[current_bin][start_bin] < float('inf'):
        path.extend(construct_path(next_node, current_bin, start_bin))
        total_distance += dist[current_bin][start_bin]

    return path, total_distance

@app.route('/calculateRoute', methods=['POST'])
def nearest_neighbor():
    data = request.json
    full_bins = data.get('full_bins', [])

    if not full_bins:
        return jsonify({'error': 'No full bins provided'}), 400

    path, distance = nearest_neighbor_algorithm(graph, full_bins)
    return jsonify({'path': path, 'total_distance': distance})


@app.route('/postData', methods=['GET'])
def index():
    return jsonify(sensor_data)

# Endpoint to receive data
@app.route('/data', methods=['POST','GET'])
def data():
    global sensor_data
    if request.method == 'GET':
        gas = request.args.get('gas')
        ultrasonic1 = request.args.get('ultrasonic1')
        ultrasonic2 = request.args.get('ultrasonic2')

        # Log the received data
        app.logger.info(f"Received data - gas: {gas}, ultrasonic1: {ultrasonic1}, ultrasonic2: {ultrasonic2}")

        sensor_data["gas"] = float(gas)
        sensor_data["ultrasonic1"] = float(ultrasonic1)
        sensor_data["ultrasonic2"] = float(ultrasonic2)
        return "Data received", 200
    return jsonify(sensor_data)

# Run the Flask server
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
