<?php

$servername = "localhost";

// REPLACE with your Database name
$dbname = "Your db";
// REPLACE with Database user
$username = "DB username";
// REPLACE with Database user password
$password = "DB password";

$api_key_value = "Your API key same as used in ESP side";

$api_key= $sensor = $location = $temperature = $humidity = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $sensor = test_input($_POST["sensor"]);
        $location = test_input($_POST["location"]);
        $temperature = test_input($_POST["Temperature"]);
        $humidity = test_input($_POST["Humidity"]);
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO Temp_humid (sensor, location, Temperature, Humidity)
        VALUES ('" . $sensor . "', '" . $location . "', '" . $temperature . "', '" . $humidity . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
