# Smarties - Trash Disposal and shortest path finding using Floyd Warshall Algorithm

<h1>Items needed</h1>
<h3>1. Arduino Uno Rev3 X 2</h3>
<h3>2. Ultrasonic Sensor X 2</h3>
<h3>3. Gas Sensor </h3>
<h3>4. IR Sensor </h3>
<h3>5. Moisture Sensor </h3>
<h3>6. Servo Motor </h3>
<h3>7. ESP8266 Wifi Module </h3>
<h3>8. Breadboard X 2</h3>

<h1> Arduino Uno Rev3 1 setup </h1>
<h5> 1. Connect all the sensors based on the GPIO, VCC and GND mentioned below </h5>
<h5> . IR Sensor - GPIO - 4 VCC - 5V(Connected to breadboard) GND - GND(Connected to breadboard) </h5>
<h5> . Moisture Sensor - GPIO - A0  VCC - 5V (Connected to breadboard) GND - GND(Connected to breadboard)</h5>
<h5> . Servo Motor - GPIO - 9 VCC - 5V (Connected to breadboard) GND - GND(Connected to breadboard)</h5>
<h5> 2. Upload trash_disposing.uno file via Arduino IDE</h5>


<h1> Arduino Uno Rev3 2 setup </h1>
<h5> 1. Conect all the sensors based on the GPIO, VCC and GND mentioned below </h5>
<h5> . Ultrasonic Sensor 1 - GPIO - (Trig - 9, Echo - 8) VCC - 5V(Connected to breadboard) GND - GND(Breadboard) </h5>
<h5> . Ultrasonic Sensor 2 - GPIO - (Trig - 5, Echo - 4) VCC - 5V (Connected to breadboard) GND - GND(Connected to breadboard)</h5>
<h5> . Gas Sensor - GPIO - A0 VCC - 5V (Connected to Breadboard) GND - GND (Connected to Breadboard) </h5>
<h5> . Wifi Module - Please refer to the figure below for setup. Make sure it is connected to 3.3V from Arduino. </h5>

<img src="https://github.com/Divenesh/Smarties---Trash-Disposal-and-shortest-path-finding-using-Floyd-Warshall-/blob/main/Images/Wifi%20Module%20Setup.jpeg"> </img>

<h5> 2. Upload trash_status_sensing.ino file via Arduino IDE </h5>


<h1> Steps </h1>
<h4> 1. Connect the workstation with a wifi network </h4>
<h4> 2. Run the app.py file using "python app.py" command in terminal/cmd to intiate the flask server.</h4>
<h4> 3. Copy the IP address of the flask server displayed in the terminal/cmd </h4>
<h4> 4. Change the IP address in the trash_status_sensing.ino and script.js files as below. </h4>

<img src="https://github.com/Divenesh/Smarties---Trash-Disposal-and-shortest-path-finding-using-Floyd-Warshall-/blob/main/Images/Arduino%20IP%20update.png"> </img>
<img src="https://github.com/Divenesh/Smarties---Trash-Disposal-and-shortest-path-finding-using-Floyd-Warshall-/blob/main/Images/Postdata%20IP%20update.png"> </img>
<img src="https://github.com/Divenesh/Smarties---Trash-Disposal-and-shortest-path-finding-using-Floyd-Warshall-/blob/main/Images/CalculateRoute%20IP%20update.png"> </img>

<h4> 5. Run index.html in localhost and reupload the trash_status_sensing.ino in Arduino 2. </h4>

<h4> 6. Verify the values from the sensor updated in realtime in webpage. </h4>


<h1> How does the system works ? </h1>

<img src="https://github.com/Divenesh/Smarties---Trash-Disposal-and-shortest-path-finding-using-Floyd-Warshall-/blob/main/Images/Open%20System%20Architechture.jpeg.png"> </img>


<p> Based on the workflow above, the trash disposed will be separated as wet and dry trash using IR sensor and moisture sensor and servo motor is responsible to dispose the trash in respective bin. The ultrasonic sensor 1 and 2 is responsible to get the trash level while the gas sensor is used to determine the level of harmful gases in the bin. Then, the data collected from the trash can will be uploaded into flask server using ESP8266 wifi module. The webpage will get the data from flask server and display to the authority. The authority can use the calculate path option in the website to calculate the shortest path which uses the floyd warshall algorithm to determine the shortest route to all filled trash cans. The calculate path option will send filled cans data to the flask server again to calculate the shortest path and displayed in the webpage.</p>


<h1> Benefits </h1>
<h4> 1. Lower carbon emission released from the truck. </h4>
<h4> 2. Smaller truck can be used as non-filled trash cans are excluded from the garbage collection trip. </h4>
<h4> 3. Reduces release of harmful gases and carbon dioxide from the trash can. </h4>
<h4> 4. Dry trashes can be sent for recycling in order to reduce carbon footprint </h4>


<h1> Presentation video by Smarties </h1>
<p> Link :  
<a href="https://youtu.be/bxP4p65DpRE"> Pitching video - Net O Bin by SMARTIES SJKT MAK MANDIN </a>
</p>


















                                                                                                                      








