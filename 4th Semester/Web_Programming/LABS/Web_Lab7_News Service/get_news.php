<?php

session_start(); 
header('Content-Type: application/json'); // Set the content type to JSON
require 'config.php'; // Include the database connection file

if (!isset($_SESSION['user_id'])) {
    echo json_encode(['error' => 'User not logged in']);
    exit;
}


$category = trim($_GET['category'] ?? ''); // Get the category from the request
$keyword = trim($_GET['keyword'] ?? ''); // Get the keyword from the request
$fromDate = trim($_GET['fromDate'] ?? ''); // Get the from date from the request
$toDate = trim($_GET['toDate'] ?? ''); // Get the to date from the request


// JOIN users to get producer username
$sql = 'SELECT news.title, news.content, news.category, news.created_at, users.username AS producer FROM news LEFT JOIN users ON news.author_id = users.id';
$conditions = []; // Initialize an array to hold the conditions
$params = []; // Initialize an array to hold the parameters

// ───────────────────────────────────────────────────────── category 
 
if ($category !== '') {  // Check if category is not empty
    $conditions[]       = 'news.category = :category'; // Add condition for category
    $params['category'] = $category; // Add parameter for category
}


// ───────────────────────────────────────────────────────── keyword 
if ($keyword !== '') {
    /* use two distinct placeholders so PDO is happy */
    $conditions[] = '(news.title LIKE :kw1 OR news.content LIKE :kw2)';
    $params['kw1'] = "%{$keyword}%";
    $params['kw2'] = "%{$keyword}%";
}

// ───────────────────────────────────────────────────────── date range
if ($fromDate !== '') {
    $conditions[]        = 'news.created_at >= :fromDate';
    $params['fromDate']  = $fromDate;
}
if ($toDate   !== '') {
    $conditions[]        = 'news.created_at <= :toDate';
    $params['toDate']    = $toDate . ' 23:59:59';
}


// Add conditions to the SQL query if any exist
if ($conditions) {
    $sql .= ' WHERE ' . implode(' AND ', $conditions);   
}
$sql .= ' ORDER BY news.created_at DESC'; 

try {
    $stmt = $pdo->prepare($sql); // Prepare the SQL statement
    $stmt->execute($params); // Execute the statement with the parameters
    $newsList = $stmt->fetchAll(PDO::FETCH_ASSOC); // Fetch all results as an associative array
    echo json_encode($newsList); // Return the results as JSON
} catch (Exception $e) {
    echo json_encode(['error' => 'An error occurred while fetching news: ' . $e->getMessage()]);
}