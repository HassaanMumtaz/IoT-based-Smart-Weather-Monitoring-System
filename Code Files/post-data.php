<?php
$servername = "localhost";
$dbname = "id18080426_weatheree";
$username = "id18080426_esp_board";
$password = "XU*6n){m4k4{%W{~";
 
$api_key_value = "12345";
$api_key= $Temprature = $Humidity = $Pressure = $Altitude = $Light = $Rain= $AirQuality= $RealFeel= $DewPoint = "";
 
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = $_POST["api_key"];
    if($api_key == $api_key_value) {
        $Temprature = $_POST["Temprature"];
        $Humidity = $_POST["Humidity"];
        $Pressure = $_POST["Pressure"];
        $Altitude = $_POST["Altitude"];
        $Light = $_POST["Light"];
        $Rain = $_POST["Rain"];
        $AirQuality= $_POST["AirQuality"];
        $RealFeel= $_POST["RealFeel"];
        $DewPoint= $_POST["DewPoint"];
        
        
        $conn = new mysqli($servername, $username, $password, $dbname);
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO ESPData (Temprature,Humidity ,Pressure , Altitude, Light,Rain, AirQuality, RealFeel, DewPoint)
        VALUES ('" . $Temprature . "', '" . $Humidity . "', '" . $Pressure . "', '" . $Altitude . "', '" . $Light . "', '" . $Rain . "',  '" . $AirQuality . "', '" . $RealFeel . "', '" . $DewPoint . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key";
    }
 
}
else {
    echo "No data posted HTTP POST.";
}
