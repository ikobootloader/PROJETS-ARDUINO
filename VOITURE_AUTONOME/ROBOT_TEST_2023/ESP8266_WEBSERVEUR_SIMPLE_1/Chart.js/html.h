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
        <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    </head>
    <body>
        <canvas id="myChart" width="400" height="400"></canvas>
    </body>
    <script>
		var canvas = document.getElementById('myChart');
		var ctx = canvas.getContext('2d');
		var coordinates = [];
		var currentPosition = { x: 0, y: 0 };
		var myChart = new Chart(ctx, {
		   type: 'line',
		   data: {
			   datasets: [{
				   label: 'Parcours du Véhicule',
				   borderColor: 'rgb(75, 192, 192)',
				   data: coordinates,
			   }]
		   },
		   options: {
			   scales: {
				   x: { type: 'linear', position: 'bottom' },
				   y: { type: 'linear', position: 'left' }
			   }
		   }
		});
		function receiveData(instruction) {
		   switch (instruction) {
			   case 'avancer':
				   currentPosition.y += 1;
				   break;
			   case 'reculer':
				   currentPosition.y -= 1;
				   break;
			   case 'gauche':
				   currentPosition.x -= 1;
				   break;
			   case 'droite':
				   currentPosition.x += 1;
				   break;
			   case 'arreter':
				   break;
			   default:
				   console.error('Instruction non reconnue:', instruction);
				   return;
		   }
		   coordinates.push({ ...currentPosition });
		   if (coordinates.length > 1000) {
			   coordinates.shift();
		   }
		   myChart.update();
		}
    setInterval(function(){ 
        fetch("/direction") 
        .then(response => response.text()) 
        .then((response) => {
            receiveData(response.trim());
            })
        .catch(err => console.log(err))
    }, 50)
    </script>    
</html> 
)=====";

#endif