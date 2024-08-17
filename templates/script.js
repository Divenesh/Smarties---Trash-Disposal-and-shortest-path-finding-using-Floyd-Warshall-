var gas1,
  wet1,
  dry1,
  gas2,
  wet2,
  dry2,
  gas3,
  wet3,
  dry3,
  gas4,
  wet4,
  dry4,
  gas5,
  wet5,
  dry5;
var trash1, trash2, trash3, trash4, trash5;
function updateSensorValues() {
  const Url = "http://192.168.100.17:5000/postData";
  fetch(Url) // Fetch data from the /data endpoint
    .then((response) => response.json())
    .then((data) => {
      document.getElementById("gasValue1").textContent = data.gas;
      gas1 = data.gas;
      document.getElementById("ultrasonic1Value1").textContent =
        data.ultrasonic1;
      wet1 = data.ultrasonic1;
      document.getElementById("ultrasonic2Value1").textContent =
        data.ultrasonic2;
      dry1 = data.ultrasonic2;
    })
    .catch((error) => {
      console.error("Error fetching data:", error);
    });
}

function updateDummyValues() {
  gas2 = 190;
  wet2 = 40;
  dry2 = 80;
  gas3 = 179;
  wet3 = 19;
  dry3 = 50;
  gas4 = 230;
  wet4 = 12;
  dry4 = 18;
  gas5 = 800;
  wet5 = 70;
  dry5 = 60;

  document.getElementById("gasValue2").innerText = gas2;
  document.getElementById("ultrasonic1Value2").innerText = wet2;
  document.getElementById("ultrasonic2Value2").innerText = dry2;
  document.getElementById("gasValue3").innerText = gas3;
  document.getElementById("ultrasonic1Value3").innerText = wet3;
  document.getElementById("ultrasonic2Value3").innerText = dry3;
  document.getElementById("gasValue4").innerText = gas4;
  document.getElementById("ultrasonic1Value4").innerText = wet4;
  document.getElementById("ultrasonic2Value4").innerText = dry4;
  document.getElementById("gasValue5").innerText = gas5;
  document.getElementById("ultrasonic1Value5").innerText = wet5;
  document.getElementById("ultrasonic2Value5").innerText = dry5;
}

function setFull() {
  if (wet1 < 20 || dry1 < 20) {
    trash1 = "full";
  } else if (gas1 > 400) {
    trash1 = "gasHigh";
  } else {
    trash1 = "free";
  }

  if (wet2 < 20 || dry2 < 20) {
    trash2 = "full";
  } else if (gas2 > 400) {
    trash2 = "gasHigh";
  } else {
    trash2 = "free";
  }
  if (wet3 < 20 || dry3 < 20) {
    trash3 = "full";
  } else if (gas3 > 400) {
    trash3 = "gasHigh";
  } else {
    trash3 = "free";
  }

  if (wet4 < 20 || dry4 < 20) {
    trash4 = "full";
  } else if (gas4 > 400) {
    trash4 = "gasHigh";
  } else {
    trash4 = "free";
  }

  if (wet5 < 20 || dry5 < 20) {
    trash5 = "full";
  } else if (gas5 > 400) {
    trash5 = "gasHigh";
  } else {
    trash5 = "free";
  }
}

function changeColour() {
  if (trash1 == "full") {
    document.getElementById("trash1_id").style.backgroundColor = "red";
  } else if (trash1 == "gasHigh") {
    document.getElementById("trash1_id").style.backgroundColor = "orange";
  } else {
    document.getElementById("trash1_id").style.backgroundColor = "green";
  }
  if (trash2 == "full") {
    document.getElementById("trash2_id").style.backgroundColor = "red";
  } else if (trash2 == "gasHigh") {
    document.getElementById("trash2_id").style.backgroundColor = "orange";
  } else {
    document.getElementById("trash2_id").style.backgroundColor = "green";
  }

  if (trash3 == "full") {
    document.getElementById("trash3_id").style.backgroundColor = "red";
  } else if (trash3 == "gasHigh") {
    document.getElementById("trash3_id").style.backgroundColor = "orange";
  } else {
    document.getElementById("trash3_id").style.backgroundColor = "green";
  }

  if (trash4 == "full") {
    document.getElementById("trash4_id").style.backgroundColor = "red";
  } else if (trash4 == "gasHigh") {
    document.getElementById("trash4_id").style.backgroundColor = "orange";
  } else {
    document.getElementById("trash4_id").style.backgroundColor = "green";
  }

  if (trash5 == "full") {
    document.getElementById("trash5_id").style.backgroundColor = "red";
  } else if (trash5 == "gasHigh") {
    document.getElementById("trash5_id").style.backgroundColor = "orange";
  } else {
    document.getElementById("trash5_id").style.backgroundColor = "green";
  }
}

function appendArray() {}

async function sendFullBinsData() {
  fullBins = ["MBPP"];

  if (trash1 == "full") {
    fullBins.push("Trash1");
  } else if (trash1 == "gasHigh") {
    fullBins.push("Trash1");
  }
  if (trash2 == "full") {
    fullBins.push("Trash2");
  } else if (trash2 == "gasHigh") {
    fullBins.push("Trash2");
  }

  if (trash3 == "full") {
    fullBins.push("Trash3");
  } else if (trash3 == "gasHigh") {
    fullBins.push("Trash3");
  }
  if (trash4 == "full") {
    fullBins.push("Trash4");
  } else if (trash4 == "gasHigh") {
    fullBins.push("Trash4");
  }

  if (trash5 == "full") {
    fullBins.push("Trash5");
  } else if (trash5 == "gasHigh") {
    fullBins.push("Trash5");
  }

  try {
    const response = await fetch("http://192.168.100.17:5000/calculateRoute", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ full_bins: fullBins }),
    });

    if (response.ok) {
      const data = await response.json();
      var path_calculated = data.path.join(" -> ");
      document.getElementById("calculated_path").innerText = path_calculated;
      document.getElementById("calculated_dist").innerText =
        data.total_distance;
    } else {
      console.error("Error:", response.statusText);
    }
  } catch (error) {
    console.error("Error:", error);
  }
}

window.addEventListener("load", updateDummyValues);
updateSensorValues();
setInterval(updateSensorValues, 5000);
setInterval(setFull, 5000);
setInterval(changeColour, 5000);
setInterval(appendArray, 5000);
