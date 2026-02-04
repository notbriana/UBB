#include "service.h"
#include <algorithm>

Service::Service(FileRepo& repo) : repo(repo) {}

void Service::load() {
    questions = repo.loadQuestions();
    participants = repo.loadParticipants();
}

const std::vector<Question>& Service::getQuestions() const { return questions; }
const std::vector<Participant>& Service::getParticipants() const { return participants; }

bool Service::addQuestion(int id, const std::string& text, const std::string& answer, int score, std::string& error) {
    if (text.empty()) { error = "Text is empty."; return false; }
    for (const auto& q : questions)
        if (q.getId() == id) { error = "Duplicate id."; return false; }
    questions.emplace_back(id, text, answer, score);
    for (auto& cb : updateCallbacks) cb();
    return true;
}

bool Service::answerQuestion(const std::string& participant, int qid, const std::string& answer, bool& correct) {
    auto pit = std::find_if(participants.begin(), participants.end(),
        [&](const Participant& p) { return p.getName() == participant; });
    if (pit == participants.end()) return false;
    if (pit->hasAnswered(qid)) return false;
    auto qit = std::find_if(questions.begin(), questions.end(),
        [&](const Question& q) { return q.getId() == qid; });
    if (qit == questions.end()) return false;
    correct = (qit->getCorrectAnswer() == answer);
    pit->markAnswered(qid);
    if (correct) pit->addScore(qit->getScore());
    for (auto& cb : updateCallbacks) cb();
    return true;
}

void Service::addUpdateCallback(std::function<void()> cb) { updateCallbacks.push_back(cb); }
void Service::save() {
    repo.saveQuestions(questions);
    repo.saveParticipants(participants);
}

void Service::updateParticipantScore(const std::string& name, int delta) {
    for (auto& p : participants)
        if (p.getName() == name) { p.addScore(delta); break; }
    for (auto& cb : updateCallbacks) cb();
}