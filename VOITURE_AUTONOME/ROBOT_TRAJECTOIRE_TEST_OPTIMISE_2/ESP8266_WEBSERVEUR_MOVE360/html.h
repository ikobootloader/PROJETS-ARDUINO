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
              margin: 0;
              padding: 0;
              height: 100%;
          }

          #map {
              position: relative;
              border: 1px solid #ccc;
              overflow: hidden;
              width: 100vw; /* Utilise la largeur totale de la fenêtre */
              height: 100vh; /* Utilise la hauteur totale de la fenêtre */
          }

          #vehicle {
              position: absolute;
              width: 5px;
              height: 5px;
              background-color: #3498db;
              border-radius: 50%;
              left: 50%;
              top: 50%;
              transform: translate(-50%, -50%);
          }

          .point {
              position: absolute;
              width: 5px;
              height: 5px;
              background-color: #e74c3c;
              border-radius: 50%;
          }

          /* Ajoutez ces styles à votre fichier styles.css */

          #arrow {
              position: absolute;
              width: 0;
              height: 0;
              border-left: 10px solid transparent;
              border-right: 10px solid transparent;
              border-bottom: 20px solid #e74c3c; /* Couleur de la flèche */
              transform-origin: center top;
          }
        </style>
    </head>
    <body>
      <div id="map">
        <div id="vehicle"></div>
        <div id="arrow"></div>
        <div id="instructionDisplay">Déplacement en cours: </div>
      </div>
    </body>
    <script>
      var vehicle = document.getElementById('vehicle');
      var map = document.getElementById('map');
      var instructionDisplay = document.getElementById('instructionDisplay');
      var arrow = document.getElementById('arrow');

      var currentPosition = { x: window.innerWidth / 2, y: window.innerHeight / 2 };
      var direction = 0; // Rotation en degrés

      var vehicleWidth = 5;
      var vehicleHeight = 5;

      function moveVehicle(instruction, angle) {
        var step = 5;

        function moveForward() {
          var angleInRadians = (direction * Math.PI) / 180;
          currentPosition.x -= step * Math.sin(angleInRadians); // utilise Math.sin ici
          currentPosition.y -= step * Math.cos(angleInRadians); // ajuste pour que les points aillent vers le haut
        }

        function moveBackward() {
          var angleInRadians = ((direction + 180) * Math.PI) / 180;
          currentPosition.x += step * Math.sin(angleInRadians); // utilise Math.sin ici
          currentPosition.y += step * Math.cos(angleInRadians); // ajuste pour que les points aillent vers le haut
        }

        function turnLeft() {
          direction = (direction + angle) % 360;
        }

        function turnRight() {
          direction = (direction - angle + 360) % 360;
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
            break;
          default:
            console.error('Instruction non reconnue:', instruction);
            return;
        }

        createPoint(currentPosition.x, currentPosition.y);
        adjustMapSize(
          Math.max(currentPosition.x + vehicleWidth, window.innerWidth),
          Math.max(currentPosition.y + vehicleHeight, window.innerHeight)
        );

        // Met à jour la rotation de la flèche
        arrow.style.transform = 'rotate(' + angle + 'deg)';
        arrow.style.left = currentPosition.x + 'px';
        arrow.style.top = currentPosition.y + 'px';

        // Met à jour la position du véhicule
        vehicle.style.left = currentPosition.x + 'px';
        vehicle.style.top = currentPosition.y + 'px';

        instructionDisplay.textContent = 'Déplacement en cours: ' + instruction + ' à ' + angle + '°';
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

      setInterval(function () {
        fetch('/direction')
          .then((response) => response.text())
          .then((response) => {
            const [instruction, angle] = response.trim().split(',');
            moveVehicle(instruction, parseInt(angle));
          })
          .catch((err) => console.log(err));
      }, 150);
    </script>


</html> 
)=====";

#endif