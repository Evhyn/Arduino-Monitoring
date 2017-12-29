
/***************************************************************************************
*    Title: Insert_data_php
*    Author: Evi Andrianto
*    Date: 27-Jan-17
*    Code version: v1.0
*
***************************************************************************************/




<?php


    // Prepare variables for database connection
   
    $username = 'root';  // enter database username
    $password = '';  // enter database password
    $host = 'localhost'; 
    $dbname='data monitoring';

    // Connect to your database

    $con = mysqli_connect($host, $username, $password, $dbname);

    // Check connection
    if ($con->connect_error) {
    	die("Connection failed: " . $con->connect_error);
	}


    // Prepare the SQL statement

    $sql = "INSERT INTO dht11 (temp,humidity) VALUES ('".$_GET["value1"]."',".$_GET["value2"].")";    

    // Execute SQL statement

    if ($con->query($sql) === TRUE) {
    	echo "New record created successfully";
    } else {
    	echo "Error: " . $sql . "<br>" . $conn->error;
    }

$con->close();
?>