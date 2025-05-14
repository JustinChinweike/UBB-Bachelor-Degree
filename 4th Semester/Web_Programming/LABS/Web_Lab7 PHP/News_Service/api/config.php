<?php

// Database configuration
$host = 'localhost'; // Database host
$db_name = 'news_db'; // Database name   
$db_user = 'root'; // Database user
$db_pass = ''; // Database password
$charset = 'utf8mb4'; // Database charset


// Create a new PDO instance
$dsn = "mysql:host=$host;dbname=$db_name;charset=$charset";
$options = [
    PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
    PDO::ATTR_EMULATE_PREPARES => false,
];
try {
    $pdo = new PDO($dsn, $db_user, $db_pass, $options);
} catch (PDOException $e) {
    echo 'Database connection failed: ' . $e->getMessage();
    exit;
}
