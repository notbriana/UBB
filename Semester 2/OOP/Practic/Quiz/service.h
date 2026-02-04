#pragma once
#include "domain.h"
#include "filerepo.h"
#include <vector>
#include <string>
#include <functional>

class Service {
    FileRepo& repo;
    std::vector<Question> questions;
    std::vector<Participant> participants;
    std::vector<std::function<void()>> updateCallbacks;
public:
    Service(FileRepo& repo);
    void load();
    const std::vector<Question>& getQuestions() const;
    const std::vector<Participant>& getParticipants() const;
    bool addQuestion(int id, const std::string& text, const std::string& answer, int score, std::string& error);
    bool answerQuestion(const std::string& participant, int qid, const std::string& answer, bool& correct);
    //void setUpdateCallback(std::function<void()> cb);
    void addUpdateCallback(std::function<void()> cb);
    void save();
    void updateParticipantScore(const std::string& name, int delta);
};