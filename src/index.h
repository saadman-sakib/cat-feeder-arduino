#include <Arduino.h>

String index_html = R"rawliteral(
    
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        body{font-family: sans-serif !important;}
    </style>
</head>
<body>
    <h2>Wifi Login</h2>
    <form action="/login" method="get">
        Wifi ssid:
        <input type="text"  name="ssid" >
        <br>
        Wifi password:
        <input type="password" name="password">
        <br>
        <input type="submit" >
    </form>
</body>
</html>

)rawliteral";

