<?php

$servername = "localhost";
$username = "ifold_svc";
$password = "fourth-S3cr3t";
$dbname = "ifold";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
	die("Connection failed: " . $conn->connect_error);
}
echo "Connected successfully<br>";

$username = 'jianopt';
$password = md5('Kang1994$');
$level = 100;
$approved = 1;
$sql = "insert into users(username, password, level, emailConfirmed, approved) values('$username', '$password', $level, 1, $approved)";
$conn->query($sql);

$conn->close();

