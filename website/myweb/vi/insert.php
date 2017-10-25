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

$sql = "INSERT INTO PupilInfo (name, birthyear)
VALUES ('LinhTOHoang', '1989');";

if ($conn->multi_query($sql) === TRUE) {
    echo "New records created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

// Close connection
$conn->close();
?>