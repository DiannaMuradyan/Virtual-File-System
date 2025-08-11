#ifndef VFS_H
#define VFS_H
#include <iostream>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include <ostream>
#include <algorithm>


class Directory;

class FileSystemNode {
public:
    virtual std::size_t getSize() const = 0;
    virtual void display(std::ostream& os, int indent = 0) const = 0;
    virtual std::string name() const = 0;
    void setParent(std::weak_ptr<Directory> p);
    std::shared_ptr<Directory> parent() const;
    ~FileSystemNode () = default;
protected:
    std::string m_name;
    std::weak_ptr<Directory> m_parent;
};

class File : public FileSystemNode{
public:
    explicit File (const std::string &name);
    std::size_t getSize() const override;
    void display(std::ostream& os, int indent = 0) const override;
    std::string name() const override;
    void setContent(const std::string& s);
private:
    std::string content;
};


class Directory : public FileSystemNode, public std::enable_shared_from_this<Directory> { 
public:
    explicit Directory (const std::string &name);
    std::size_t getSize() const override;
    void display(std::ostream& os, int intdent ) const override;
    std::string name() const override;
    void addChild(std::shared_ptr<FileSystemNode> child);
    bool removeChildByName(const std::string &name) ;
    std::shared_ptr<FileSystemNode> findByPath(const std::string& path);
    void tree(int indent);
private:
    std::vector<std::shared_ptr<FileSystemNode>> children;
    std::vector<std::string> split(const std::string& path); 
};

#include "vfs.hpp"
#endif  