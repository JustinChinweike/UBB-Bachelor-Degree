<?php
session_start();

if (!isset($_SESSION['user_id'])) {
    header('Location: login.php');
    exit;
}
$username = $_SESSION['username'];
$role = $_SESSION['role'];


?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard - News Web App</title>
    <link rel="stylesheet" href="style.css">
</head>
<body> 
    <h1>Dashboard</h1>
    <p>Welcome, <?php echo htmlspecialchars($username); ?>!</p>
    <p><a href="logout.php">Logout</a></p>
    <?php if ($role === 'admin') : ?>
        <p><a href="news_list.php">Manage News</a></p>
        <a href="add_user.php">Add user</a>
    <?php endif; ?>
    <p><a href="filter_news.php">View News</a></p>
</body>
</html>

