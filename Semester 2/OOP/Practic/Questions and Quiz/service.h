#pragma once
#include "domain.h"
#include "filerepo.h"
#include <vector>
#include <functional>
#include <utility> // for std::pair

class Service {
    FileRepo& repo;
    std::vector<User> users;
    std::vector<Question> questions;
    std::vector<Answer> answers;
    std::vector<std::function<void()>> observers;
public:
    Service(FileRepo& r);
    const std::vector<User>& getUsers() const;
    const std::vector<Question>& getQuestions() const;
    const std::vector<Answer>& getAnswers() const;
    void addObserver(std::function<void()>);
    void notify();
    void addQuestion(const std::string& text, const std::string& user);
    void addAnswer(int qid, const std::string& text, const std::string& user);
    void voteAnswer(int aid, int delta, const std::string& user);
    void increaseVote(int aid, const std::string& user);
    void decreaseVote(int aid, const std::string& user);
    std::vector<Answer> getAnswersForQuestion(int qid) const;
    void save();

    // --- Added for search and sorting ---
    // Returns a vector of pairs: (Question, similarity score), sorted descending by score
    std::vector<std::pair<Question, int>> searchQuestionsByText(const std::string& text) const;

    // Returns questions sorted descending by number of answers
    std::vector<Question> getQuestionsSortedByAnswerCount() const;
};