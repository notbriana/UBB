#pragma once
#include <string>

enum class TaskStatus { Open, InProgress, Closed };

class Programmer {
public:
    int id;
    std::string name;
    Programmer(int id, const std::string& name) : id(id), name(name) {}
};

class Task {
public:
    std::string description;
    TaskStatus status;
    int programmerId; // -1 if unassigned

    Task(const std::string& desc, TaskStatus stat, int progId = -1)
        : description(desc), status(stat), programmerId(progId) {}
};