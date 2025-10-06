#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
    std::string programmersFile, tasksFile;
public:
    FileRepo(const std::string& progFile, const std::string& taskFile);
    std::vector<Programmer> loadProgrammers();
    std::vector<Task> loadTasks();
    void saveTasks(const std::vector<Task>& tasks);
};