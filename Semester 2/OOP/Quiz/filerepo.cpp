#include "filerepo.h"
#include <fstream>
#include <sstream>

FileRepo::FileRepo(const std::string& qf, const std::string& pf)
    : questionsFile(qf), participantsFile(pf) {}

std::vector<Question> FileRepo::loadQuestions() {
    std::vector<Question> qs;
    std::ifstream fin(questionsFile);
    int id, score;
    std::string text, answer, line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        iss >> id;
        iss.ignore();
        std::getline(iss, text, '|');
        std::getline(iss, answer, '|');
        iss >> score;
        qs.emplace_back(id, text, answer, score);
    }
    return qs;
}

void FileRepo::saveQuestions(const std::vector<Question>& qs) {
    std::ofstream fout(questionsFile);
    for (const auto& q : qs)
        fout << q.getId() << " " << q.getText() << "|" << q.getCorrectAnswer() << "|" << q.getScore() << "\n";
}

std::vector<Participant> FileRepo::loadParticipants() {
    std::vector<Participant> ps;
    std::ifstream fin(participantsFile);
    std::string name;
    int score;
    while (fin >> name >> score)
        ps.emplace_back(name, score);
    return ps;
}

void FileRepo::saveParticipants(const std::vector<Participant>& ps) {
    std::ofstream fout(participantsFile);
    for (const auto& p : ps)
        fout << p.getName() << " " << p.getScore() << "\n";
}