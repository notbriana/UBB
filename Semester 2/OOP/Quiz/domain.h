#pragma once
#include <string>
#include <vector>
#include <set>

class Question {
    int id;
    std::string text;
    std::string correctAnswer;
    int score;
public:
    Question(int id, const std::string& text, const std::string& answer, int score);
    int getId() const;
    const std::string& getText() const;
    const std::string& getCorrectAnswer() const;
    int getScore() const;
};

class Participant {
    std::string name;
    int score;
    std::set<int> answeredQuestions;
public:
    Participant(const std::string& name, int score = 0);
    const std::string& getName() const;
    int getScore() const;
    void addScore(int s);
    bool hasAnswered(int qid) const;
    void markAnswered(int qid);
};