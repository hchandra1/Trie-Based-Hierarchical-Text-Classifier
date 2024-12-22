# 🌳 Trie-Based Hierarchical Text Classifier

A lightweight and efficient hierarchical text classification tool built using C++ and trie data structures. Inspired by the need to organize and classify text data into structured categories, this project implements a trie-based system that refines classifications at multiple levels.

## 🚀 Project Overview
Ever wondered how to classify "apple" as a fruit or "tiger" as a carnivore in a clean, structured way? This project allows you to build and manage a hierarchy of classifications using a trie (prefix tree). The trie stores categories like "living things," "animals," or "plants," and classifies new input based on existing structures.

This project is designed to:
- Insert and manage categories and subcategories.
- Classify text into the most relevant hierarchical category.
- Efficiently handle and traverse large classification trees.

## 🎯 Key Features
- **Hierarchical Text Classification:** Classify input text at multiple levels, refining categories dynamically.  
- **Trie Implementation:** Fast insertion, deletion, and search with trie data structures.  
- **Command-Based Interface:** Simple text commands to interact with the classifier.  
- **Dynamic Memory Management:** Efficiently handles large classification trees with minimal overhead.  

## 🛠️ Technologies Used
- **Language:** C++  
- **Data Structures:** Trie (N-ary Tree with up to 15 children per node)  
- **Platform:** Cross-platform (Windows/Linux/MacOS)  

---

## 📂 Project Structure
```
Trie-Text-Classifier/
│
├── src/
│   ├── Trie.cpp           # Trie implementation
│   ├── Trie.h             # Trie header file
│   ├── TrieNode.cpp       # Trie node implementation
│   ├── TrieNode.h         # Trie node header file
│   └── trietest.cpp       # Main entry point (CLI-based classifier)
│
├── data/
│   └── simple_classes.txt # Sample classification data
│
├── Makefile               # Compilation instructions
│
└── README.md              # This file
```

---

## ⚙️ How It Works
1. **Initialize the Trie:**  
   The trie starts empty. You can load data from a file or insert classifications manually.  

2. **Insert Classifications:**  
   Add new categories in the format:  
   ```
   living,animals,vertebrate,mammal,carnivore
   living,plants,food,fruit
   ```

3. **Classify Text:**  
   The program uses the trie to find the best matching category for input text by traversing the trie levels.

4. **Command Line Interface:**  
   Interact with the classifier using simple commands:  
   ```
   INSERT living,animals,vertebrate,bird
   CLASSIFY parrot
   PRINT
   ```

---

## 🚦 Running the Project
### 1. Clone and Navigate:
```bash
git clone <repo-link>
cd Trie-Text-Classifier
```

### 2. Compile the Project:
```bash
make
```

### 3. Run the Program:
```bash
./a.out
```

### 4. Example Commands:
```bash
LOAD data/simple_classes.txt
INSERT living,animals,vertebrate,reptile
CLASSIFY iguana
PRINT
EXIT
```

---

## 📜 Commands
| Command    | Description                                   |
|------------|-----------------------------------------------|
| **LOAD**   | Load classification data from a file.         |
| **INSERT** | Add a new classification to the trie.         |
| **ERASE**  | Remove a classification from the trie.        |
| **CLASSIFY**| Classify input text.                         |
| **PRINT**  | Print all classifications in the trie.        |
| **EMPTY**  | Check if the trie is empty.                   |
| **SIZE**   | Show the number of classifications.           |
| **CLEAR**  | Remove all classifications from the trie.     |
| **EXIT**   | Exit the program.                             |

---

## 🧪 Example Data (`simple_classes.txt`)
```text
living
nonliving
living,from plants
living,from animals
living,from plants,food
living,from animals,vertebrate,mammal
nonliving,technology
```

---

## 🎨 Why I Built This
I wanted to explore how hierarchical classification could be modeled using efficient data structures like tries. This project not only deepened my understanding of tree traversal and dynamic memory management but also gave me hands-on experience integrating C++.

---

## 🚧 Future Improvements
- **GUI Interface:** Build a graphical interface to interact with the trie visually.  
- **REST API:** Expose classification as a web service.  
- **Better NLP Models:** Integrate local NLP models for more advanced classification.  

---

## 📝 License
This project is open-source and available under the MIT License.
