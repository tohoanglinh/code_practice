<?php
$servername = "localhost";
$username = "root";
$password = "";
$databasename = "tutorDB";
$tablename = "PupilInfo";

// Create connection
$conn = new mysqli($servername, $username, $password, $databasename);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
echo "Connected successfully";

// Create database
$database = "CREATE DATABASE IF NOT EXISTS " . $databasename;
if ($conn->query($database) === TRUE) {
    echo "Database " . $databasename . " created successfully";
} else {
    echo "Error creating database: " . $conn->error;
}

// Create a table
$table = "CREATE TABLE IF NOT EXISTS " . $tablename . "(
no INT(2) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
name VARCHAR(30) NOT NULL,
birthyear INT(4)
)";
if ($conn->query($table) === TRUE) {
    echo "Table " . $tablename . " created successfully";
} else {
    echo "Error creating table: " . $conn->error;
}

// Close connection
$conn->close();
?>