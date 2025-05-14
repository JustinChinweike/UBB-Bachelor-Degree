<?php          
session_start();
require 'config.php';

// Check if the user is logged in and has the admin role
if (!isset($_SESSION['user_id']) || $_SESSION['role'] !== 'admin') {
    header('Location: dashboard.php');
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $u   = trim($_POST['username']  ?? '');
    $p   = trim($_POST['password']  ?? '');
    $r   = $_POST['role'] === 'admin' ? 'admin' : 'user'; // Default to 'user' if not 'admin'   
    if ($u && $p) {
        try {
            $stmt = $pdo->prepare(
              "INSERT INTO users (username, password, role) VALUES (?, ?, ?)");
            $stmt->execute([$u, password_hash($p, PASSWORD_DEFAULT), $r]);
            $msg = "User $u created successfully!";
        } catch (PDOException $e) {
            if ($e->getCode() == 23000) {
                $msg = "Username already exists. Please choose another.";
            } else {
                $msg = "Database error: " . $e->getMessage();
            }
        }
    } else {
        $msg = "Both fields are required";
    }
}
?>
<div class="container">
    <h1>Add User</h1>
    <?php if(isset($msg)) echo "<p class='error'>$msg</p>"; ?>
    <form id="addUserForm" method="post">
        <label>Username:
            <input name="username" type="text" required>
        </label>
        <label>Password:
            <input name="password" type="password" required>
        </label>
        <label>Role:
            <select name="role">
                <option value="user">user</option>
                <option value="admin">admin</option>
            </select>
        </label>
        <button type="submit">Create</button>
    </form>
    <p style="text-align:center;"><a href="dashboard.php">← Back to Dashboard</a></p>
</div>