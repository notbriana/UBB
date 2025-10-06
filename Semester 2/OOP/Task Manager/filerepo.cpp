#include "filerepo.h"
#include <fstream>
#include <sstream>

FileRepo::FileRepo(const std::string& progFile, const std::string& taskFile)
    : programmersFile(progFile), tasksFile(taskFile) {}

std::vector<Programmer> FileRepo::loadProgrammers() {
    std::vector<Programmer> result;
    std::ifstream fin(programmersFile);
    int id;
    std::string name;
    while (fin >> id) {
        std::getline(fin, name);
        if (!name.empty() && name[0] == ' ') name = name.substr(1);
        result.emplace_back(id, name);
    }
    return result;
}

std::vector<Task> FileRepo::loadTasks() {
    std::vector<Task> result;
    std::ifstream fin(tasksFile);
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string desc, statusStr, progIdStr;
        std::getline(iss, desc, '|');
        std::getline(iss, statusStr, '|');
        std::getline(iss, progIdStr, '|');
        int progId = progIdStr.empty() ? -1 : std::stoi(progIdStr);
        TaskStatus status = TaskStatus::Open;
        if (statusStr == "in progress") status = TaskStatus::InProgress;
        else if (statusStr == "closed") status = TaskStatus::Closed;
        result.emplace_back(desc, status, progId);
    }
    return result;
}

void FileRepo::saveTasks(const std::vector<Task>& tasks) {
    std::ofstream fout(tasksFile);
    for (const auto& t : tasks) {
        std::string statusStr = "open";
        if (t.status == TaskStatus::InProgress) statusStr = "in progress";
        else if (t.status == TaskStatus::Closed) statusStr = "closed";
        fout << t.description << "|" << statusStr << "|" << t.programmerId << "\n";
    }
}