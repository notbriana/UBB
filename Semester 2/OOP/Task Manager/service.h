#pragma once
#include "domain.h"
#include "filerepo.h"
#include <vector>
#include <functional>

class Service {
    FileRepo& repo;
    std::vector<Task> tasks;
    std::vector<std::function<void()>> observers;
public:
    Service(FileRepo& repo);
    const std::vector<Task>& getTasks() const;
    void addTask(const std::string& desc);
    void removeTask(int index);
    void startTask(int index, int programmerId);
    void closeTask(int index, int programmerId);
    void addObserver(std::function<void()> obs);
    void notify();
    void save();
};