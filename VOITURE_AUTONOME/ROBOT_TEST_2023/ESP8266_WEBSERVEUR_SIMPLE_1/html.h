#ifndef html_H
#define html_H

// Page html
const char html[] PROGMEM = R"=====(
<!doctype html>
<html lang="fr">
    <head>
        <meta http-equiv="content-type" content="text/html; charset=utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Parcours du Véhicule</title>
        <style>
        body, html {
            height: 100%;
            margin: 0;
            overflow: hidden;
          background-color: black;
        }

        #map {
            position: absolute;
            top: 40%;
            left: 40%;
            transform: translate(-50%, -50%);
            /*border: 1px solid #ccc;*/
            /*overflow: hidden; *//* Empêche les points de déborder du cadre visible */
        }

        #vehicle {
            position: absolute;
            width: 20px;
            height: 20px;
            background-color: #3498db;
            border-radius: 50%;
        }

        .point {
            position: absolute;
            width: 5px;
            height: 5px;
            background-color: #e74c3c;
            border-radius: 50%;
        }     
        </style>
    </head>
    <body>
    <div id="map">
        <div id="vehicle"></div>
    </div>
    </body>
    <script>
var vehicle = document.getElementById('vehicle');
var map = document.getElementById('map');

var currentPosition = { x: 0, y: 0 };
var direction = 0; // 0: vers le haut, 1: vers la droite, 2: vers le bas, 3: vers la gauche

var vehicleWidth = 20;
var vehicleHeight = 20;

function moveVehicle(instruction) {
    var step = 20;

    function moveForward() {
        switch (direction) {
            case 0:
                currentPosition.y = Math.max(currentPosition.y - step, 0);
                break;
            case 1:
                currentPosition.x = currentPosition.x + step;
                break;
            case 2:
                currentPosition.y = currentPosition.y + step;
                break;
            case 3:
                currentPosition.x = Math.max(currentPosition.x - step, 0);
                break;
        }
    }

    function moveBackward() {
        switch (direction) {
            case 0:
                currentPosition.y = currentPosition.y + step;
                break;
            case 1:
                currentPosition.x = Math.max(currentPosition.x - step, 0);
                break;
            case 2:
                currentPosition.y = Math.max(currentPosition.y - step, 0);
                break;
            case 3:
                currentPosition.x = currentPosition.x + step;
                break;
        }
    }

    function turnLeft() {
        direction = (direction - 1 + 4) % 4; // Mettez à jour la direction vers la gauche
    }

    function turnRight() {
        direction = (direction + 1) % 4; // Mettez à jour la direction vers la droite
    }

    switch (instruction) {
        case 'avancer':
            moveForward();
            break;
        case 'reculer':
            moveBackward();
            break;
        case 'gauche':
            turnLeft();
            break;
        case 'droite':
            turnRight();
            break;
        case 'arreter':
            // Ne rien faire pour l'instruction 'arrêter'
            break;
        default:
            console.error('Instruction non reconnue:', instruction);
            return;
    }

    createPoint(currentPosition.x, currentPosition.y);
    adjustMapSize(currentPosition.x + vehicleWidth, currentPosition.y + vehicleHeight);

    vehicle.style.left = currentPosition.x + 'px';
    vehicle.style.top = currentPosition.y + 'px';
}

function createPoint(x, y) {
    var point = document.createElement('div');
    point.className = 'point';
    point.style.left = x + 'px';
    point.style.top = y + 'px';
    map.appendChild(point);
}

function adjustMapSize(newWidth, newHeight) {
    map.style.width = newWidth + 'px';
    map.style.height = newHeight + 'px';
}

    setInterval(function(){ 
        fetch("/direction") 
        .then(response => response.text()) 
        .then((response) => {
            moveVehicle(response.trim());
            })
        .catch(err => console.log(err))
    }, 150)
    </script>    
</html> 
)=====";

#endif