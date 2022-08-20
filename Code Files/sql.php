<!DOCTYPE html>
<html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Compiled and minified CSS -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css">
    <!--Import Google Icon Font-->
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <!-- Compiled and minified JavaScript -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js"></script>
    <title>Document</title>
    <style>
        section{
            padding-top:4vw;
            padding-bottom: 4vw;
        }
    </style>
</head>



<body>
<body class="indigo lighten-5">

    <nav class="nav-wraper indigo">
        <div class="container">
            <div class="brand-logo right "><a href="https://weathermonitoringstationee.000webhostapp.com/home.html">Weather Station</a></div>
            <ul class="left-align">
                <li><a href="https://weathermonitoringstationee.000webhostapp.com/about.html">About</a></li>
            </ul>
        </div>
    </nav>


<div class="container center">
         <a href="https://weathermonitoringstationee.000webhostapp.com//graph.html" class="btn indigo lighten-3">Graph Data
         <i class="material-icons right">analytics</i></a>
       </div>




<?php
 
$servername = "localhost";
$dbname = "id18080426_weatheree";
$username = "id18080426_esp_board";
$password = "XU*6n){m4k4{%W{~";

 
 
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
 
$sql = "SELECT Temprature, Humidity, Pressure, Altitude, Light, Rain,AirQuality,RealFeel,DewPoint,reading_time FROM ESPData ORDER BY id DESC";
 
echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <td>Temprature</td> 
        <td>Humidity</td> 
        <td>Pressure</td> 
        <td>Altitude</td>
        <td>Light</td>
        <td>Rain</td>  
        <td>AirQuality</td> 
        <td>RealFeel</td> 
        <td>DewPoint</td> 
        <td>Timestamp</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_Temprature= $row["Temprature"];
        $row_Humidity = $row["Humidity"];
        $row_Pressure = $row["Pressure"];
        $row_Altitude = $row["Altitude"]; 
        $row_Light = $row["Light"]; 
        $row_Rain = $row["Rain"];
        $row_AirQuality = $row["AirQuality"];
        $row_RealFeel = $row["RealFeel"];
        $row_DewPoint = $row["DewPoint"];
        $row_reading_time = $row["reading_time"];
        
      
        echo '<tr> 
                <td>' . $row_Temprature . '</td> 
                <td>' . $row_Humidity . '</td> 
                <td>' . $row_Pressure . '</td>
                <td>' . $row_Altitude . '</td> 
                <td>' . $row_Light . '</td> 
                <td>' . $row_Rain . '</td> 
                <td>' . $row_AirQuality . '</td>
                <td>' . $row_RealFeel . '</td>
                <td>' . $row_DewPoint . '</td>
                <td>' . $row_reading_time . '</td> 
              </tr>';
    }
    $result->free();
}
 
$conn->close();
?> 
</table>
</body>
</html>