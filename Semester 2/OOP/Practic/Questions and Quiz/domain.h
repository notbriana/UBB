#pragma once
#include <string>

class User {
    std::string name;
public:
    User(const std::string& name) : name(name) {}
    std::string getName() const { return name; }
};

class Question {
    int id;
    std::string text;
    std::string userName;
public:
    Question(int id, const std::string& text, const std::string& userName)
        : id(id), text(text), userName(userName) {}
    int getId() const { return id; }
    std::string getText() const { return text; }
    std::string getUserName() const { return userName; }
};

class Answer {
    int id, questionId, votes;
    std::string userName, text;
public:
    Answer(int id, int questionId, const std::string& userName, const std::string& text, int votes)
        : id(id), questionId(questionId), userName(userName), text(text), votes(votes) {}
    int getId() const { return id; }
    int getQuestionId() const { return questionId; }
    std::string getUserName() const { return userName; }
    std::string getText() const { return text; }
    int getVotes() const { return votes; }
    void setVotes(int v) { votes = v; }
};