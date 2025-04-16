# Table Manipulation with jQuery

## Original Requirements

### Table Structure
- 5 initial rows
- 5 data columns
- 2 special columns (left and right) with buttons

### Left Column Button (Delete)
- When clicked, deletes the current row
- Rows above are shifted down

### Right Column Button (Add)
- When clicked, adds a new editable row below current row
- New row has input fields for editing

### Row Editing
- New rows start as editable
- When all cells are filled, row becomes read-only
- Read-only rows match the style of other rows

## Additional Functionalities

### 1. Row Click Editing
- Any row can be made editable by clicking on it
- Clicking outside the row saves changes
- Pressing Enter key saves changes
- Visual feedback with yellow background for editable rows

### 2. Data Persistence
- All table data is saved to localStorage
- Data persists after:
  - Page refresh
  - Browser close/reopen
  - System restart
- Automatic saving when:
  - Editing a row
  - Adding a new row
  - Deleting a row

### 3. Enhanced User Experience
- Focus automatically moves to first input field when:
  - Adding new row
  - Making existing row editable
- Visual feedback for:
  - Editable rows (yellow background)
  - Hover states for buttons
  - Input field states
- Smooth transitions between states

### 4. Input Validation
- Checks for empty cells
- Prevents saving incomplete rows
- Maintains data integrity
- Automatic conversion to read-only when complete

### 5. Event Handling
- Click events for:
  - Row editing
  - Button actions
  - Outside clicks
- Keyboard events:
  - Enter key to save
  - Input validation
- Event propagation control

##  Technical Implementation
- Pure jQuery implementation
- No additional libraries or plugins
- Responsive design
- Clean and maintainable code structure
