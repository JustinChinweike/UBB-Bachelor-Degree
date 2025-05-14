<?php

session_start(); // Start the session
require 'config.php'; // Include the database configuration file

if (!isset($_SESSION['user_id']) || $_SESSION['role'] !== 'admin') {
    // Check if the user is logged in and has admin role
    header('Location: login.php'); // Redirect to login page if not logged in
    exit;
}

// Handle deletion of news articles
if (isset($_GET['delete_id']) ){
    $deleteId = (int)$_GET['delete_id'];
    $stmt = $pdo->prepare("DELETE FROM news WHERE id = ?");
    $stmt->execute([$deleteId]);
    header('Location: news_list.php'); // Redirect to the same page after deletion
    exit;
}

// Fetch news articles from the database
$stmt = $pdo->query("SELECT id, title, category, created_at FROM news ORDER BY created_at DESC");
$newsList = $stmt->fetchAll(PDO::FETCH_ASSOC); // Fetch all news articles
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Manage News - News Web App</title>
    <link rel="stylesheet" href="styles.css"> <!-- Include your CSS file here -->
</head>
<body>
    <h1>Manage News </h1>
    <p><a href="dashboard.php">Back to Dashboard</a> | <a href="logout.php">Logout</a></p>  
    <p><a href="news_form.php">Add New News</a></p> <!-- Link to add new news article -->
    <?php if ($newsList): ?> 
        <table> <!-- Table to display news articles -->
                <tr>
                    <th>ID</th>
                    <th>Title</th>
                    <th>Category</th>
                    <th>Date</th>
                    <th>Actions</th>
                </tr>
                <?php foreach ($newsList as $news): ?>
                    <tr>
                        <td><?php echo $news['id']; ?></td>
                        <td><?php echo htmlspecialchars($news['title']); ?></td>
                        <td><?php echo htmlspecialchars($news['category']); ?></td>
                        <td><?php echo $news['created_at']; ?></td>
                        <td>
                            <a href="news_form.php?id=<?php echo $news['id']; ?>">Edit</a> | 
                            <a href="news_list.php?delete_id=<?php echo $news['id']; ?>" 
                            onclick="return confirm('Are you sure you want to delete this news article?');">Delete</a>
                        </td> <!-- Link to edit and delete news article -->
                    </tr>
                <?php endforeach; ?>
                </table>
            <?php else: ?>
                <p>No news articles found.</p> <!-- Message if no news articles are found -->
            <?php endif; ?>
</body>
</html>

