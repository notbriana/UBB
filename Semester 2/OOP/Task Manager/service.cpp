#include "service.h"
#include <algorithm>
#include <stdexcept>

Service::Service(FileRepo& repo) : repo(repo), tasks(repo.loadTasks()) {}

const std::vector<Task>& Service::getTasks() const { return tasks; }

void Service::addTask(const std::string& desc) {
    tasks.emplace_back(desc, TaskStatus::Open, -1);
    save();
    notify();
}

void Service::removeTask(int index) {
    if (index < 0 || index >= (int)tasks.size()) throw std::runtime_error("Invalid index");
    tasks.erase(tasks.begin() + index);
    save();
    notify();
}

void Service::startTask(int index, int programmerId) {
    if (tasks[index].status != TaskStatus::Open)
        throw std::runtime_error("Task not open");
    tasks[index].status = TaskStatus::InProgress;
    tasks[index].programmerId = programmerId;
    save();
    notify();
}

void Service::closeTask(int index, int programmerId) {
    if (tasks[index].status != TaskStatus::InProgress || tasks[index].programmerId != programmerId)
        throw std::runtime_error("Cannot close task");
    tasks[index].status = TaskStatus::Closed;
    save();
    notify();
}
void Service::addObserver(std::function<void()> obs) { observers.push_back(obs); }
void Service::notify() { for (auto& obs : observers) obs(); }
void Service::save() { repo.saveTasks(tasks); }