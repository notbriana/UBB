#pragma once
#include <string>

class Programmer {
public:
    std::string name;
    int revised_files;
    int total_files_to_revise;

    Programmer(const std::string& name, int revised, int total);
};

class SourceFile {
public:
    std::string name;
    std::string status;
    std::string creator;
    std::string reviewer;

    SourceFile(const std::string& name, const std::string& status, const std::string& creator, const std::string& reviewer);
};