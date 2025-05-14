<?php
session_start();

// If the user is already logged in, redirect to the dashboard
if (isset($_SESSION['user_id'])) {
    header('Location: api/dashboard.php');
    exit;
} else {
    // Otherwise, redirect to the login page
    header('Location: api/login.php');
    exit;
}