#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
    std::string usersFile;
    std::string itemsFile;
public:
    FileRepo(const std::string& usersFile, const std::string& itemsFile);

    std::vector<User> loadUsers();
    std::vector<Item> loadItems();
    void saveItems(const std::vector<Item>& items);
};