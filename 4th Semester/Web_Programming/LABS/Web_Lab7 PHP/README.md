# 📰 News Service Web Application

A full-stack PHP web application for managing and browsing news articles, built as part of a university lab assignment. This project demonstrates secure CRUD operations, user authentication, AJAX-powered filtering, and a clean, responsive UI.

---

## 🚀 Features

- **User Authentication:**  
  - Secure login system with role-based access (admin/user).
- **News Management:**  
  - Admins can add, edit, and delete news articles.
  - News articles include title, content, producer, date, and category.
- **News Browsing:**  
  - All users can view news.
  - Filter news by category and keyword using AJAX (no page reload).
  - Displays the last used filter criteria.
- **Responsive UI:**  
  - Clean, minimal CSS for a user-friendly experience.
- **Security:**  
  - Uses prepared statements to prevent SQL injection.
  - Session management for authentication.
- **Validation:**  
  - Server-side and client-side validation for all forms.
  - Confirmation prompts for delete/cancel actions.

---

## 📂 Project Structure

```
/News_Service
│
├── api/
│   ├── add_user.php
│   ├── config.php
│   ├── dashboard.php
│   ├── filter_news.php
│   ├── get_news.php
│   ├── login.php
│   ├── logout.php
│   ├── news_form.php
│   └── news_list.php
│
├── css/
│   └── style.css
│
├── js/
│   └── filter.js
│
└── index.php
```

---

## 🛠️ Requirements

- **PHP** (>= 7.4)
- **MySQL** (tested with 5.7+)
- **Web Server:** Apache (included in [XAMPP](https://www.apachefriends.org/))
- **Browser:** Modern browser with JavaScript enabled
- ## 🛠️ Requirements

> **Note:**  
> This project was developed and tested using [XAMPP](https://www.apachefriends.org/), which provides Apache, PHP, and MySQL in a single package.  
> Simply place the project folder inside your `htdocs` directory and access it via `http://localhost/News_Service`.

---

## ⚡ Setup Instructions

1. **Clone the Repository**
    ```bash
    git clone https://github.com/yourusername/news-service.git
    cd news-service
    ```

2. **Database Setup**
    - Create a MySQL database (e.g., `news_db`).
    - Import the provided SQL schema (if available) or create the following table:
      ```sql
      CREATE TABLE users (
          id INT AUTO_INCREMENT PRIMARY KEY,
          username VARCHAR(50) NOT NULL UNIQUE,
          password VARCHAR(255) NOT NULL,
          role ENUM('admin','user') NOT NULL
      );

      CREATE TABLE news (
          id INT AUTO_INCREMENT PRIMARY KEY,
          title VARCHAR(255) NOT NULL,
          content TEXT NOT NULL,
          producer VARCHAR(100) NOT NULL,
          category VARCHAR(50) NOT NULL,
          created_at DATETIME DEFAULT CURRENT_TIMESTAMP
      );
      ```
    - Update `api/config.php` with your database credentials.

3. **Run the Application**
    - Using PHP built-in server:
      ```bash
      php -S localhost:8000
      ```
    - Visit [http://localhost:8000](http://localhost:8000) in your browser.

---

## 🧑‍💻 Usage

- **Admins:**  
  - Log in with admin credentials.
  - Manage users and news articles.
- **Regular Users:**  
  - Log in to view and filter news.
  - Use the filter form to search by category or keyword (AJAX-powered).

---

## 📋 Assignment Requirements Checklist

- [x] **CRUD operations** (select, insert, update, delete) on MySQL tables
- [x] **AJAX** for asynchronous data fetching/filtering
- [x] **At least 5 web pages** (login, dashboard, news list, news form, filter news)
- [x] **SQL injection prevention** (prepared statements)
- [x] **User experience:**  
  - Input validation  
  - No manual ID entry for edit/delete  
  - Confirmation prompts  
  - Aligned input fields with CSS

---

## 📚 References

- [PHP Manual](http://www.php.net/manual/en)
- [W3Schools PHP Tutorial](http://www.w3schools.com/php)
- [W3Schools AJAX Tutorial](http://www.w3schools.com/ajax)
- [Lab Documentation](http://www.cs.ubbcluj.ro/~forest/wp)

