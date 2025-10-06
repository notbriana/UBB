#include "domain.h"

Question::Question(int id, const std::string& text, const std::string& answer, int score)
    : id(id), text(text), correctAnswer(answer), score(score) {}

int Question::getId() const { return id; }
const std::string& Question::getText() const { return text; }
const std::string& Question::getCorrectAnswer() const { return correctAnswer; }
int Question::getScore() const { return score; }

Participant::Participant(const std::string& name, int score)
    : name(name), score(score) {}

const std::string& Participant::getName() const { return name; }
int Participant::getScore() const { return score; }
void Participant::addScore(int s) { score += s; }
bool Participant::hasAnswered(int qid) const { return answeredQuestions.count(qid) > 0; }
void Participant::markAnswered(int qid) { answeredQuestions.insert(qid); }