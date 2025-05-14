<?php

session_start(); 

if (!isset($_SESSION['user_id'])) {
    header('Location: login.php');
    exit;
}
require 'config.php'; // Include the database connection file

// Fetch distinct categories from the database
$stmt = $pdo->query("SELECT DISTINCT category FROM news ORDER BY category ASC");
$categories = $stmt->fetchAll(PDO::FETCH_COLUMN);
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>News Feed - News Web App</title>
    <link rel="stylesheet" href="../css/style.css"> <!-- Include your CSS file here -->
</head>
<body> 
    <h1> News Feed</h1>
    <p><a href="dashboard.php"> Back to Dashboard</a> | <a href="logout.php">Logout</a></p>
    <form id ="filterForm"> 
        <label> Category: 
            <select id = "category" name="category">
                <option value="">All Categories</option>
                <?php foreach ($categories as $cat): ?>
                    <option value="<?php echo htmlspecialchars($cat); ?>">
                        <?php echo htmlspecialchars($cat); ?>
                    </option>
                <?php endforeach; ?>
            </select>
        </label>
        <label> Keyword: 
            <input type="text" id="keyword" name="keyword" placeholder="Search by keyword">
        </label>
        <button type="submit">Filter</button>
    </form>
    <h3 id="criteria"></h3>
    <div id="newsResults"></div>   <!-- This div will hold the filtered news results -->
    <script src="../js/filter.js"></script> <!-- Include your JavaScript file here -->
</body>
</html>