document.addEventListener('DOMContentLoaded', function () {
    const form = document.getElementById('filterForm');
    const newsResults = document.getElementById('newsResults');
    const criteriaDisplay = document.getElementById('criteria');

    function fetchNews() {
        const category = document.getElementById('category').value;
        const keyword = document.getElementById('keyword').value;
        const params = new URLSearchParams();
        if (category) params.append('category', category);
        if (keyword) params.append('keyword', keyword);  

        fetch(`get_news.php?${params.toString()}`)
            .then(Response => Response.json())
            .then(data => { 
                // Update criteria display
                let criteriaText = 'Showing ' ; 
                if (category) {
                    criteriaText += 'Category: "' + category + '" ';                 
                } else {
                    criteriaText += 'All Categories ';
                }
                if (keyword) {
                    criteriaText += 'with Keyword: "' + keyword + '" ';
                }
                criteriaDisplay.textContent = criteriaText.trim();
                // Check if data is empty
                if (data.length === 0) {
                    newsResults.innerHTML = '<p>No news found.</p>';
                    return;
                }
                let html =  '<table> <tr><th>Title</th><th>Category</th><th>Date</th><th>Snippet</th></tr>';
                data.forEach(item => { 
                    let snippet = item.content.length > 100 ? item.content.substring(0, 100) + '...' : item.content;
                    html += '<tr>';
                    html += '<td>' + item.title + '</td>';
                    html += '<td>' + item.category + '</td>';
                    html += '<td>' + item.created_at + '</td>';
                    html += '<td>' + snippet + '</td>';
                    html += '</tr>';
                }); 
                html += '</table>';
                newsResults.innerHTML = html;
            })
            .catch(error => {
                console.error('Error fetching news:', error);
                newsResults.innerHTML = '<p class="Error"> An errror occurred while fetching news.</p>';
            });
    }

    // Initial fetch (all news)
    fetchNews();

    // Event listener for form submission
    form.addEventListener('submit', function (event) {
        event.preventDefault(); // Prevent the default form submission
        fetchNews(); // Fetch news based on the selected criteria
    });

});