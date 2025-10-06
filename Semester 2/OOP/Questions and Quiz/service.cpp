#include "service.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>

// Constructor: loads users, questions, and answers from the repository
Service::Service(FileRepo& r) : repo(r) {
    users = repo.loadUsers();
    questions = repo.loadQuestions();
    answers = repo.loadAnswers();
}

// Getters
const std::vector<User>& Service::getUsers() const {
    return users;
}

const std::vector<Question>& Service::getQuestions() const {
    return questions;
}

const std::vector<Answer>& Service::getAnswers() const {
    return answers;
}

// Observer pattern
void Service::addObserver(std::function<void()> obs) {
    observers.push_back(obs);
}

void Service::notify() {
    for (auto& obs : observers) {
        obs();
    }
}

// Add a new question
void Service::addQuestion(const std::string& text, const std::string& user) {
    if (text.empty()) throw std::runtime_error("Empty question");
    int id = questions.empty() ? 1 : questions.back().getId() + 1;
    questions.emplace_back(id, text, user);
    repo.saveQuestions(questions);
    notify();
}

// Add a new answer to a question
void Service::addAnswer(int qid, const std::string& text, const std::string& user) {
    if (text.empty()) throw std::runtime_error("Empty answer");
    int id = answers.empty() ? 1 : answers.back().getId() + 1;
    answers.emplace_back(id, qid, user, text, 0);
    repo.saveAnswers(answers);
    notify();
}

// Vote (up or down) an answer, but not your own
void Service::voteAnswer(int aid, int delta, const std::string& user) {
    for (auto& a : answers) {
        if (a.getId() == aid) {
            if (a.getUserName() == user) return; // Don't allow voting own answer
            a.setVotes(a.getVotes() + delta);
            notify();
            return;
        }
    }
}

void Service::increaseVote(int aid, const std::string& user) {
    for (auto& a : answers) {
        if (a.getId() == aid && a.getUserName() != user) {
            a.setVotes(a.getVotes() + 1);
            notify();
            break;
        }
    }
}

void Service::decreaseVote(int aid, const std::string& user) {
    for (auto& a : answers) {
        if (a.getId() == aid && a.getUserName() != user) {
            a.setVotes(a.getVotes() - 1);
            notify();
            break;
        }
    }
}

// Get all answers for a given question
std::vector<Answer> Service::getAnswersForQuestion(int qid) const {
    std::vector<Answer> res;
    for (const auto& a : answers) {
        if (a.getQuestionId() == qid)
            res.push_back(a);
    }
    return res;
}

// Save questions and answers to files
void Service::save() {
    repo.saveQuestions(questions);
    repo.saveAnswers(answers);
}

// Helper: similarity score (number of matching letters at identical positions)
static int similarityScore(const std::string& a, const std::string& b) {
    int score = 0;
    size_t len = std::min(a.size(), b.size());
    for (size_t i = 0; i < len; ++i)
        if (std::tolower(a[i]) == std::tolower(b[i]))
            ++score;
    return score;
}

std::vector<std::pair<Question, int>> Service::searchQuestionsByText(const std::string& text) const {
    std::vector<std::pair<Question, int>> result;
    for (const auto& q : questions) {
        int score = similarityScore(q.getText(), text);
        if (score > 0)
            result.emplace_back(q, score);
    }
    std::sort(result.begin(), result.end(),
        [](const std::pair<Question, int>& a, const std::pair<Question, int>& b) {
            return a.second > b.second;
        });
    return result;
}

std::vector<Question> Service::getQuestionsSortedByAnswerCount() const {
    std::vector<Question> sorted = questions;
    std::sort(sorted.begin(), sorted.end(), [this](const Question& a, const Question& b) {
        int countA = std::count_if(answers.begin(), answers.end(),
            [&a](const Answer& ans) { return ans.getQuestionId() == a.getId(); });
        int countB = std::count_if(answers.begin(), answers.end(),
            [&b](const Answer& ans) { return ans.getQuestionId() == b.getId(); });
        return countA > countB;
    });
    return sorted;
}