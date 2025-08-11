#include "vfs.h"

int main() {
    auto root = std::make_shared<Directory>(std::string("root"));

    auto file1 = std::make_shared<File>(std::string("file1.txt"));
    file1->setContent(std::string("hello world!"));

    auto file2 = std::make_shared<File>(std::string("file2.txt"));
    file2->setContent(std::string("picsart academy"));
  
    auto dir = std::make_shared<Directory>(std::string("dir"));

    root->addChild(file1);
    root->addChild(dir);

  
    dir->addChild(file2);

    std::cout << "Initial tree:\n";
    root->display(std::cout,0);

   
    std::cout << "\nTotal size of root: " << root->getSize() << " bytes\n";

  
    std::string path = "dir/file2.txt";
    auto found = root->findByPath(path);
    if (found) {
        std::cout << "\nFound node: " << found->name()<< " (size: " << found->getSize() << " bytes)\n";
    } else {
        std::cout << "\nNode not found\n";
    }

    std::string nameToRemove = "notes.txt";
    if (root->removeChildByName(nameToRemove)) {
        std::cout << "\nRemoved " << nameToRemove << "\n";
    }

    std::cout << "\nUpdated tree:\n";
    root->display(std::cout,0);

   root ->tree();
    return 0;
}
