# Virtual-File-System

A small C++17 demo of a simple virtual file system (VFS) with files and directories, built using smart pointers.  
You can add, remove, display, and find files or directories, as well as print the full tree structure.

---

## Features
- **Files** with content and size tracking
- **Directories** containing files and other directories
- **Find by path** (`dir/file.txt`)
- **Tree view** of the whole structure
- Uses modern C++17 features (`std::shared_ptr`, `std::weak_ptr`)

---

## Build & Run

### 1. Clone the repository
```bash
git clone https://github.com/yourusername/vfs_demo.git
cd vfs_demo
