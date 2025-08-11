#include "vfs.h"


//FileSystemNode
void FileSystemNode::setParent(std::weak_ptr<Directory> p) {
    m_parent = std::move(p);
}
std::shared_ptr<Directory> FileSystemNode::parent() const {
    return m_parent.lock();
}


//File
File::File(const std::string &name) {
    m_name = name;
}

std::size_t File::getSize() const {
    return content.size();
}

void File::display(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << m_name << " (file, " << getSize() << ")\n";
}

std::string File::name() const {
    return m_name;
}

void File::setContent(const std::string& s) {
    std::string str(s);
    content = std::move(str);
}



//Directory
Directory::Directory(const std::string &name) {
    m_name = name;
}

std::size_t Directory::getSize() const {
    std::size_t size = 0;
    for (const auto &child : children) {
        size += child ->getSize();
    }
    return size;
}

std::string Directory::name() const {
    return m_name;
}

void Directory::display(std::ostream& os, int intdent) const {
    os << std::string(intdent, ' ') << m_name << "/ (dir, " << getSize() << ")\n";
    for (const auto& c : children) {
        c->display(os, intdent + 2);
    }
}

void Directory::addChild (std::shared_ptr<FileSystemNode> child) {
    if (!child) return;
    if (child == m_parent.lock()) {
        return;
    }
    child->setParent(shared_from_this());
    children.push_back(std::move(child));
    return;
}

bool Directory::removeChildByName(const std::string &name)  {
    auto it = std::find_if(children.begin(), children.end(),[&](const std::shared_ptr<FileSystemNode>& p){ return p->name() == name; });
    if (it == children.end()) return false;
    (*it)->setParent(std::weak_ptr<Directory>{});
    children.erase(it);
    return true;
}


std::vector<std::string> Directory::split(const std::string& path) {
    int index = 0;
    int prev = 0;
    std::string tmp(path);
    std::vector<std::string> substrs;

    while ((index = tmp.find('/', index)) != std::string::npos) {
        tmp[index] = '.';
        substrs.push_back(tmp.substr(prev,index - prev));
        ++index;  
        prev = index;
    }

    substrs.push_back(tmp.substr(prev,path.size() - prev));
    return substrs;
} 

std::shared_ptr<FileSystemNode> Directory::findByPath(const std::string& path) {
    std::string tmp(path);
    auto names = split(tmp);
    if (path.empty()) return shared_from_this();
    std::shared_ptr<FileSystemNode> next = shared_from_this();

    for(auto &n : names) {
        for (const auto &child : std::dynamic_pointer_cast<Directory>(next) ->children) {
            if (n == child ->name()) {
                next = child;
                break;
            }
        }
    }
    std::cout<<next ->name()<<"\n";
    return next;
}



void Directory::tree(int indent = 0) {
    if (!indent) {
        std::cout<< m_name<<"\n|\n";
    }
    for (const auto& it : children) {
        std::cout<<std::string(indent, ' ')<<"|"<<"_"<<it ->name()<<"\n";
        if (typeid(*it) == typeid(Directory)) {
            ++indent;
            std::dynamic_pointer_cast<Directory>(it) ->tree(indent);
            --indent;
        }
    }
}