<?php
session_start(); 
require_once 'config.php'; // Include the database connection file

// Redirect to the dashboard if the user is already logged in
if (isset($_SESSION['user_id'])) {
    header('Location: dashboard.php');
    exit;
}

$error = ''; // Initialize error variable

// Check if the form is submitted
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = trim($_POST['username']?? '');
    $password = trim($_POST['password']?? '');

    // Validate input
    if (empty($username) || empty($password)) {
        $error = 'Please enter both username and password.';
    } else {
        // Prepare and execute the SQL statement to check credentials
        $stmt = $pdo->prepare('SELECT * FROM users WHERE username = ? LIMIT 1');
        $stmt->execute([$username]);
        $user = $stmt->fetch(PDO::FETCH_ASSOC);

        // Verify password and set session variables if successful
        if ($user && password_verify($password, $user['password'])) {
            $_SESSION['user_id'] = $user['id'];
            $_SESSION['username'] = $user['username'];
            $_SESSION['role'] = $user['role']; 
            header('Location: dashboard.php');
            exit;
        } else {
            $error = 'Invalid username or password.';
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login - News Web App</title>
    <link rel="stylesheet" href="styles.css"> <!-- Link to the CSS file -->
</head>
<body>
    <h1>Login</h1>
    <?php if ($error): ?>
        <p class="error"><?php echo htmlspecialchars($error); ?></p> <!-- Display error message if any -->
    <?php endif; ?> 
    <form method="post" action="login.php"> <!-- Form for login -->
         <label>Username:<br> 
            <input type="text" name="username" required> <!-- Input for username -->
        </label><br><br>
        <label>Password:<br> 
            <input type="password" name="password" required> <!-- Input for password -->
        </label><br><br>
        <button type="submit">Login</button> <!-- Submit button -->
    </form>
    </body>
</html>