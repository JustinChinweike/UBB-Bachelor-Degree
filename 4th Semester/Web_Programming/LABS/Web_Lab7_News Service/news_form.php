<?php 

session_start(); // Start the session
require_once 'config.php'; // Include the database configuration file

// Check if the user is logged in
if (!isset($_SESSION['user_id']) || $_SESSION ['role'] != 'admin') {
    // User is not logged in or not an admin
    header('Location: login.php'); // Redirect to login page if not logged in
    exit;
}

$newsId = $_GET['id'] ?? null; // Get the news ID from the URL parameter
$title = $content = $category = ''; // Initialize variables
$errors = ''; // Initialize error message variable

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Form was submitted
    $title = trim($_POST['title'] ?? ''); // Get the title from the form
    $content = trim($_POST['content'] ?? ''); // Get the content from the form
    $category = trim($_POST['category'] ?? ''); // Get the category from the form
    if ($title === '' || $content === '' || $category === '') {
        // Check if any field is empty
        $errors = 'All fields are required.'; // Set error message
    } else {
        if (!empty ($_POST['id'])) {
            // Update existing news
            $stmt = $pdo->prepare('UPDATE news SET title = ?, content = ?, category = ? WHERE id = ?');
            $stmt->execute([$title, $content, $category, $_POST['id']]);       
        } else {
            // Insert new news
            $stmt = $pdo->prepare('INSERT INTO news (title, content, category, author_id) VALUES (?, ?, ?, ?)');
            $stmt->execute([$title, $content, $category, $_SESSION['user_id']]); // Use the logged-in user's ID as the author  
        }
       header ('Location: news_list.php'); // Redirect to the news list page after submission
        exit;
    }
  
 }  elseif ($newsId) {
        // Fetch existing news for editing
        $stmt = $pdo->prepare('SELECT * FROM news WHERE id = ?');
        $stmt->execute([$newsId]);
        $news = $stmt->fetch(PDO::FETCH_ASSOC);
        if ($news) {
            // Populate form fields with existing news data
            $title = $news['title'];
            $content = $news['content'];
            $category = $news['category'];
        } else {
            // News not found, redirect to the news list page
            header('Location: news_list.php');
            exit;
        }
    }

?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title><?php echo $newsId ? 'Edit News' : 'Add News'; ?> - News Web App</title>
        <link rel="stylesheet" href="style.css"> <!-- Include your CSS file here -->
    </head>
    <body> 
        <h1> <?php echo $newsId ? 'Edit News' : 'Add News'; ?></h1>
        <p> <a href="news_list.php">Back to Manage News</a> | <a href="dashboard.php"> Dashboard</a></p>
        <?php if ($errors): ?>
            <p class ="error"><?php echo htmlspecialchars($errors); ?></p> <!-- Display error message if any -->
        <?php endif; ?>

      <form method="post" action="news_form.php">    <!-- Form to Add/Edit News  -->
        <?php if ($newsId) : ?> <!-- If editing, include the news ID as a hidden field -->
            <input type="hidden" name="id" value="<?php echo $newsId; ?>">
        <?php endif; ?>
        <label > Title:<br>
            <input type="text" name="title" value="<?php echo htmlspecialchars($title); ?>" required> <!-- Title input field -->
        </label><br><br>
        <label > Category:<br>
            <input type="text" name="category" value="<?php echo htmlspecialchars($category); ?>" required> <!-- Category input field -->
        </label><br><br>
        <label > Content:<br>
            <textarea name="content" rows="8" cols="50" required><?php echo htmlspecialchars($content); ?></textarea> <!-- Content input field -->
        </label><br><br>
        <button type="submit"> <?php echo $newsId ? 'Update' : 'Save'; ?> </button> <!-- Submit button to save the news -->
        <button type="button" onclick="window.location.href='news_list.php'">Cancel</button> <!-- Cancel button to go back to news list -->
        
        </form>
    </body>
</html>
    