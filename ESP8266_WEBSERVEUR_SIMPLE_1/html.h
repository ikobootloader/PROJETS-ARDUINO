#ifndef html_H
#define html_H

// Page html
const char html[] PROGMEM = R"=====(
<!doctype html>
<html lang="fr">
    <head>
        <meta http-equiv="content-type" content="text/html; charset=utf-8">
        <title>ROBOT</title>
    </head>
    <body>
        <p><h1>TEST : <span id="TEST"></span></h1></p>
    </body>
    <script>
        setInterval(function(){ 
            fetch("/TEST") 
            .then(response => response.text()) 
            .then((response) => {
                document.getElementById("TEST").textContent = response
                })
            .catch(err => console.log(err))
        }, 50)
    </script>    
</html> 
)=====";

#endif