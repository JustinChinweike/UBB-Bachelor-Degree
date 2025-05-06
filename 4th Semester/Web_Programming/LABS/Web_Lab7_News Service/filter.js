// filter.js
document.addEventListener('DOMContentLoaded', function () {
    const form = document.getElementById('filterForm');
    const newsResults = document.getElementById('newsResults');
    const criteriaDisplay = document.getElementById('criteria');

    function fetchNews() {
        const category = document.getElementById('category').value;
        const keyword = document.getElementById('keyword').value;
        const fromDate = document.getElementById('fromDate').value;
        const toDate = document.getElementById('toDate').value;
        const params = new URLSearchParams();
        if (category) params.append('category', category);
        if (keyword) params.append('keyword', keyword);
        if (fromDate) params.append('fromDate', fromDate);
        if (toDate) params.append('toDate', toDate);

        fetch(`get_news.php?${params.toString()}`)
            .then(response => response.json())
            .then(data => {
                // Update criteria display
                let criteriaText = 'Showing ';
                if (category) {
                    criteriaText += 'Category: "' + category + '" ';
                } else {
                    criteriaText += 'All Categories ';
                }
                if (keyword) {
                    criteriaText += 'with Keyword: "' + keyword + '" ';
                }
                if (fromDate) {
                    criteriaText += 'from ' + fromDate + ' ';
                }
                if (toDate) {
                    criteriaText += 'to ' + toDate;
                }
                criteriaDisplay.textContent = criteriaText.trim();

                // Generate news list
                if (data.length === 0) {
                    newsResults.innerHTML = '<p>No news found.</p>';
                    return;
                }
                let html = '<table><tr><th>Title</th><th>Category</th><th>Date</th><th>Producer</th><th>Snippet</th></tr>';
                data.forEach(item => {
                    const body    = item.content ?? '';
                    const snippet = body.length > 100 ? body.slice(0, 100) + '…' : body;
                    html += '<tr>';
                    html += '<td>' + item.title + '</td>';
                    html += '<td>' + item.category + '</td>';
                    html += '<td>' + item.created_at + '</td>';
                    html += '<td>' + (item.producer ?? '') + '</td>';
                    html += '<td>' + snippet + '</td>';
                    html += '</tr>';
                });
                html += '</table>';
                newsResults.innerHTML = html;
            })
            .catch(error => {
                console.error('Error fetching news:', error);
                newsResults.innerHTML = '<p class="error">An error occurred while fetching news.</p>';
            });
    }

    // Initial fetch (all news)
    fetchNews();

    // Fetch on form submit
    form.addEventListener('submit', function (e) {
        e.preventDefault();
        fetchNews();
    });
});
