# 📂 Virtual File System (VFS) in C++

This project implements a **Virtual File System (VFS)** in C++ that simulates a hierarchical structure of **directories** and **files**.  

The design is based on **OOP principles** with **inheritance**, **polymorphism**, and **smart pointers (`shared_ptr`, `weak_ptr`)** to manage ownership and relationships between files and directories.

---

## 🚀 Features

- **FileSystemNode (Abstract Base Class)**
  - Represents a generic file system node.  
  - Provides interfaces for `getSize()`, `display()`, and `name()`.  
  - Maintains a reference to its parent (`weak_ptr<Directory>`).  

- **File**
  - Stores file content (`std::string`).  
  - Overrides `getSize()` to return file content size.  
  - Can be displayed with indentation.  

- **Directory**
  - Can contain both **Files** and other **Directories** (composite pattern).  
  - Implements `addChild()`, `removeChildByName()`, and `findByPath()`.  
  - Supports recursive **tree-like display** of contents.  
  - Calculates total size by summing up children sizes.  

---

## 📂 Project Structure
```
.
├── vfs.h # Class declarations for File, Directory, FileSystemNode
├── vfs.hpp # (Expected) method definitions/implementations
├── main.cpp # Example usage and test driver
└── README.md # Documentation
```


---

## 🏗️ Compilation

Compile with a C++17 (or later) compiler:

```bash
g++ -std=c++17 -o vfs main.cpp
```
