#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
    std::string userFile, questionFile, answerFile;
public:
    FileRepo(const std::string& uf, const std::string& qf, const std::string& af)
        : userFile(uf), questionFile(qf), answerFile(af) {}
    std::vector<User> loadUsers();
    std::vector<Question> loadQuestions();
    std::vector<Answer> loadAnswers();
    void saveQuestions(const std::vector<Question>&);
    void saveAnswers(const std::vector<Answer>&);
};