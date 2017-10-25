<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "tutorDB";
$tablename = "PupilInfo";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT no, name, birthyear FROM " . $tablename;
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "No: " . $row["no"]. " - Name: " . $row["name"]. " - BirthYear: " . $row["birthyear"]. "<br>";
    }
} else {
    echo "0 results";
}

// Close connection
$conn->close();
?>