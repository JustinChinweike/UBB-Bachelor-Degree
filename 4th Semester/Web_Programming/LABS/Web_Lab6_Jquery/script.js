$(document).ready(function() {
    // Function to save table data to localStorage
    function saveTableData() {
        const tableData = [];
        $('#mainTable tbody tr').each(function() {
            const rowData = {
                cells: []
            };
            $(this).find('td:not(:first-child):not(:last-child)').each(function() {
                const cellText = $(this).find('input').length > 0 
                    ? $(this).find('input').val() 
                    : $(this).text();
                rowData.cells.push(cellText);
            });
            tableData.push(rowData);
        });
        localStorage.setItem('tableData', JSON.stringify(tableData));
    }


    function loadTableData() {
        const savedData = localStorage.getItem('tableData');
        if (savedData) {
            const tableData = JSON.parse(savedData);
            $('#mainTable tbody').empty(); // clear all the existing rows
            
            tableData.forEach(rowData => {
                const newRow = $('<tr></tr>');
                newRow.append('<td><button class="delete-btn">Delete</button></td>');
                
                rowData.cells.forEach(cellText => {
                    newRow.append(`<td>${cellText}</td>`);
                });
                
                newRow.append('<td><button class="add-btn">Add</button></td>');
                $('#mainTable tbody').append(newRow);
            });
        }
    }

    // Load saved data when page loads
    loadTableData();

    // Function to check if all cells in a row are filled
    function areAllCellsFilled(row) {
        let allFilled = true;
        $(row).find('td:not(:first-child):not(:last-child)').each(function() {
            if ($(this).find('input').length > 0) {
                if ($(this).find('input').val().trim() === '') {
                    allFilled = false;
                    return false;
                }
            }
        });
        return allFilled;
    }

    function makeRowEditable(row) {
        $(row).find('td:not(:first-child):not(:last-child)').each(function() {
            const currentText = $(this).text();
            $(this).html(`<input type="text" value="${currentText}">`);
        });
        $(row).addClass('editable');
        
    }

    // Function to make a row read-only
    function makeRowReadOnly(row) {
        $(row).find('td:not(:first-child):not(:last-child)').each(function() {
            const input = $(this).find('input');
            if (input.length > 0) {
                const value = input.val();
                $(this).html(value);
            }
        });
        $(row).removeClass('editable');
        saveTableData(); // Save after making read-only
    }

    // Make row editable when clicked
    $(document).on('click', '#mainTable tbody tr', function(e) {
        // Don't trigger if clicking on buttons
        if ($(e.target).is('button') || $(e.target).is('input')) {
            return;
        }
        
        const row = $(this);
        if (!row.hasClass('editable')) {
            makeRowEditable(row);
            // Focus the first input field
            row.find('input').first().focus();
        }
    });




    // Handle clicking outside to save changes
    $(document).on('click', function(e) {
        if (!$(e.target).closest('#mainTable tbody tr').length) {
            $('#mainTable tbody tr.editable').each(function() {
                makeRowReadOnly($(this));
            });
        }
    });

    // Handle pressing Enter to save changes
    $(document).on('keypress', 'input[type="text"]', function(e) {
        if (e.which === 13) { // Enter key
            const row = $(this).closest('tr');
            makeRowReadOnly(row);
        }
    });

    
    // Delete row functionality
    $(document).on('click', '.delete-btn', function(e) {
        e.stopPropagation(); // Prevent row click event
        const currentRow = $(this).closest('tr');
        const currentIndex = currentRow.index();
        
        // Remove the current row
        currentRow.remove();
        
        // Shift all rows above down
        $('#mainTable tbody tr').each(function(index) {
            if (index >= currentIndex) {
                $(this).find('td:first-child button').text('Delete');
            }
        });
        
        saveTableData(); // Save after deletion
    });

    // Add row functionality
    $(document).on('click', '.add-btn', function(e) {
        e.stopPropagation(); // Prevent row click event
        const currentRow = $(this).closest('tr');
        const newRow = $('<tr class="editable"></tr>');
        
        // Create delete button cell
        newRow.append('<td><button class="delete-btn">Delete</button></td>');
        
        // Create 5 editable cells
        for (let i = 0; i < 5; i++) {
            newRow.append('<td><input type="text" placeholder="Enter data"></td>');
        }
        
        // Create add button cell
        newRow.append('<td><button class="add-btn">Add</button></td>');
        
        // Insert the new row after the current row
        currentRow.after(newRow);
        
        // Focus the first input field
        newRow.find('input').first().focus();
        
        saveTableData(); // Save after adding new row
    });

    // Handle input changes in editable cells
    $(document).on('input', 'input[type="text"]', function() {
        const row = $(this).closest('tr');
        if (areAllCellsFilled(row)) {
            // Don't automatically make read-only for existing rows
            if (row.find('input[placeholder="Enter data"]').length > 0) {
                makeRowReadOnly(row);
            }
        }
    });
}); 