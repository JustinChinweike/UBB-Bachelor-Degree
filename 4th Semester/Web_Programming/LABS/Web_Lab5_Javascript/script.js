const input = document.getElementById('combo-input'); //input
const select = document.getElementById('combo-select'); // dropdown
const suggestionList = document.getElementById('suggestion-list'); // list

const bulkInput = document.getElementById('bulk-input');
const addBulkBtn = document.getElementById('add-bulk');

function selectToInput() {
  input.value = select.value;
  filterSuggestions();
}

function filterSuggestions() {
  const value = input.value.toLowerCase();
  suggestionList.innerHTML = '';
  let matches = 0;

  Array.from(select.options).forEach(option => {
    if (option.value.toLowerCase().includes(value)) {
      const li = document.createElement('li');
      li.textContent = option.value;
      li.onclick = () => {
        input.value = option.value;
        suggestionList.style.display = 'none'; 
      };
      suggestionList.appendChild(li);
      matches++;
    }
  });

  suggestionList.style.display = matches ? 'block' : 'none';
}

input.addEventListener('input', filterSuggestions);

input.addEventListener('keydown', (e) => {
  if (e.key === 'Enter') {
    let exists = Array.from(select.options).some(opt => opt.value === input.value);

    if (!exists && input.value.trim()) {
      const newOption = document.createElement('option');
      newOption.value = input.value;
      newOption.text = input.value;
      select.appendChild(newOption);
    }

    select.value = input.value;
    suggestionList.style.display = 'none';
    input.classList.add('added');
    setTimeout(() => input.classList.remove('added'), 1000);
  }
});




addBulkBtn.addEventListener('click', () => {
  const names = bulkInput.value.split(',').map(name => name.trim()).filter(name => name !== '');
  let newAdded = false;

  names.forEach(name => {
    const exists = Array.from(select.options).some(opt => opt.value === name);
    if (!exists) {
      const newOption = document.createElement('option');
      newOption.value = name;
      newOption.text = name;
      select.appendChild(newOption);
      newAdded = true;
    }
  });

  if (newAdded) {
    input.classList.add('added');
    setTimeout(() => input.classList.remove('added'), 1000);
  }

  bulkInput.value = '';
});

 