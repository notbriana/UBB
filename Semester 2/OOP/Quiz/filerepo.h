#pragma once
#include "domain.h"
#include <vector>
#include <string>

class FileRepo {
    std::string questionsFile, participantsFile;
public:
    FileRepo(const std::string& qf, const std::string& pf);
    std::vector<Question> loadQuestions();
    void saveQuestions(const std::vector<Question>&);
    std::vector<Participant> loadParticipants();
    void saveParticipants(const std::vector<Participant>&);
};