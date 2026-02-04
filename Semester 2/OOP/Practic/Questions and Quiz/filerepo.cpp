#include "filerepo.h"
#include <fstream>
#include <sstream>

std::vector<User> FileRepo::loadUsers() {
    std::vector<User> users;
    std::ifstream fin(userFile);
    std::string name;
    while (getline(fin, name)) {
        if (!name.empty()) users.emplace_back(name);
    }
    return users;
}

std::vector<Question> FileRepo::loadQuestions() {
    std::vector<Question> questions;
    std::ifstream fin(questionFile);
    std::string line;
    while (getline(fin, line)) {
        std::istringstream iss(line);
        int id; std::string text, user;
        iss >> id; iss.ignore();
        getline(iss, text, '|');
        getline(iss, user);
        questions.emplace_back(id, text, user);
    }
    return questions;
}

std::vector<Answer> FileRepo::loadAnswers() {
    std::vector<Answer> answers;
    std::ifstream fin(answerFile);
    std::string line;
    while (getline(fin, line)) {
        std::istringstream iss(line);
        int id, qid, votes;
        std::string user, text;
        iss >> id >> qid >> votes; iss.ignore();
        getline(iss, user, '|');
        getline(iss, text);
        answers.emplace_back(id, qid, user, text, votes);
    }
    return answers;
}

void FileRepo::saveQuestions(const std::vector<Question>& questions) {
    std::ofstream fout(questionFile);
    for (const auto& q : questions)
        fout << q.getId() << " " << q.getText() << "|" << q.getUserName() << "\n";
}

void FileRepo::saveAnswers(const std::vector<Answer>& answers) {
    std::ofstream fout(answerFile);
    for (const auto& a : answers)
        fout << a.getId() << " " << a.getQuestionId() << " " << a.getVotes()
             << "|" << a.getUserName() << "|" << a.getText() << "\n";
}