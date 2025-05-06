<?php
session_start();
if (!isset($_SESSION['user_id'])) {
    header('Location: login.php');
    exit;
}
require 'config.php';

// Fetch distinct categories
$stmt = $pdo->query('SELECT DISTINCT category FROM news'); // Fetch all categories from the database
$categories = $stmt->fetchAll(PDO::FETCH_COLUMN); // Fetch all categories as an array
?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>News Feed - News Web App</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container"> <!-- Container for the page content -->
    <h1>News Feed</h1>
    <p><a href="dashboard.php">Back to Dashboard</a> | <a href="logout.php">Logout</a></p>
    <form id="filterForm">
        <label>Category:
            <select id="category" name="category">
                <option value="">All Categories</option>
                <?php foreach ($categories as $cat): ?>
                    <option value="<?php echo htmlspecialchars($cat); ?>">
                        <?php echo htmlspecialchars($cat); ?>
                    </option>
                <?php endforeach; ?>
            </select>
        </label>
        <label>Keyword:
            <input type="text" id="keyword" name="keyword" placeholder="Search keyword">
        </label>
        <label>From Date:
            <input type="date" id="fromDate" name="fromDate">
        </label>
        <label>To Date:
            <input type="date" id="toDate" name="toDate">
        </label>
        <button type="submit">Filter</button>
    </form>
    <h3 id="criteria"></h3>
    <div id="newsResults"></div>
    </div>
    <script src="filter.js"></script>
</body>
</html>
