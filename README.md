# Auto Complete Search Engine

## Overview

This project is a web-based **Auto Complete Search Engine** that provides real-time word suggestions as users type. The underlying search algorithm is based on the **Trie (Prefix Tree)** data structure, enabling efficient prefix searching.

The core algorithm was originally implemented in **C++** as part of our academic project and later implemented in **JavaScript** to make it accessible through a web application.

---

## Features

- 🔍 Real-time autocomplete suggestions
- 🌳 Efficient Trie-based searching
- ❓ Wildcard search using `?`
- 📈 Frequency-based ranking of suggestions
- 🔤 Alphabetical sorting when frequencies are equal
- 💻 Simple and responsive web interface

---

## Technologies Used

- HTML5
- CSS3
- JavaScript (ES6)
- Trie (Prefix Tree) Data Structure

---

## Project Structure

```
AutoCompleteSearchEngine/
│
├── index.html        # Main webpage
├── styles.css        # Styling
├── script.js         # Trie implementation and search logic
├── words.txt         # Dictionary of searchable words
└── README.md
```

---

## How It Works

1. The application loads words from `words.txt`.
2. Every word is inserted into a Trie.
3. As the user types:
   - Prefix search returns matching words.
   - `?` can be used as a wildcard character.
4. When a suggestion is selected:
   - Its frequency increases.
   - Frequently selected words appear higher in future searches.

---

## Installation

1. Clone the repository.

```bash
git clone https://github.com/your-username/AutoCompleteSearchEngine.git
```

2. Open the project folder.

```bash
cd AutoCompleteSearchEngine
```

3. Run the project using any local web server.

For example:

- VS Code Live Server Extension
- Python HTTP Server

```bash
python -m http.server
```

Then open the displayed localhost URL in your browser.

---

## Usage

1. Launch the application.
2. Type a word in the search box.
3. Matching suggestions will appear instantly.
4. Click on a suggestion to autocomplete the word.
5. Use `?` in place of a character to perform wildcard searches.

Example:

```
Input: app
Suggestions:
apple
application
apply

Input: c?t
Suggestions:
cat
cot
cut
```

---

## Future Improvements

- Case-insensitive searching
- Fuzzy search for spelling mistakes
- Persistent frequency storage
- Mobile-friendly interface
- Dark/Light theme toggle
- Larger dictionary support

---

## Contributors

- Ravi Chandra Raaj
- Team Members

---

## Acknowledgements

This project was developed as part of our Summer Project to demonstrate the practical application of the Trie data structure in building efficient autocomplete systems.

---

## License

This project is intended for educational purposes.