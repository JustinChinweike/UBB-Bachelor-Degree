<?php

session_start(); 
header('Content-Type: application/json'); // Set the content type to JSON
require 'config.php'; // Include the database connection file

if (!isset($_SESSION['user_id'])) {
    echo json_encode(['error' => 'User not logged in']);
    exit;
}

$category = trim($_GET['category'] ?? '');
$keyword = trim($_GET['keyword'] ?? ''); // Get the keyword from the request

$sql = 'SELECT title content, category, created_at FROM news';
$conditions = []; // Initialize an array to hold the conditions
$params = []; // Initialize an array to hold the parameters

if ($category !== '') {
    $conditions[] = 'category = :category'; // Add category condition
    $params[':category'] = $category; // Bind the category parameter
}

if ($keyword !== '') {
    $conditions[] = 'title LIKE :keyword OR content LIKE :keyword'; // Add keyword condition
    $params[':keyword'] = '%' . $keyword . '%'; // Bind the keyword parameter
}

if ($conditions) {
    $sql .= ' WHERE ' . implode(' AND ', $conditions); // Append conditions to the SQL query
}
$sql .= ' ORDER BY created_at DESC'; // Order by created_at in descending order

$stmt = $pdo->prepare($sql); // Prepare the SQL statement
$stmt->execute($params); // Execute the statement with the parameters
$newsList = $stmt->fetchAll(PDO::FETCH_ASSOC); // Fetch all results as an associative array

echo json_encode($newsList); // Return the results as JSON



