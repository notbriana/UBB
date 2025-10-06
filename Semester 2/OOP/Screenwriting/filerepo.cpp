#include "filerepo.h"
#include <fstream>
#include <sstream>

FileRepo::FileRepo(const std::string& wf, const std::string& ifile)
    : writersFile(wf), ideasFile(ifile) {}

void FileRepo::load() {
    writers.clear();
    ideas.clear();
    std::ifstream fin(writersFile);
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string name, expertise;
        if (std::getline(iss, name, ',') && std::getline(iss, expertise)) {
            writers.emplace_back(name, expertise);
        }
    }
    fin.close();

    std::ifstream fin2(ideasFile);
    while (std::getline(fin2, line)) {
        std::istringstream iss(line);
        std::string desc, status, creator, actStr;
        if (std::getline(iss, desc, ',') && std::getline(iss, status, ',') &&
            std::getline(iss, creator, ',') && std::getline(iss, actStr)) {
            int act = std::stoi(actStr);
            ideas.emplace_back(desc, status, creator, act);
        }
    }
    fin2.close();
}

void FileRepo::saveIdeas() {
    std::ofstream fout(ideasFile);
    for (const auto& idea : ideas) {
        fout << idea.getDescription() << "," << idea.getStatus() << ","
             << idea.getCreator() << "," << idea.getAct() << "\n";
    }
    fout.close();
}

const std::vector<Writer>& FileRepo::getWriters() const { return writers; }
const std::vector<Idea>& FileRepo::getIdeas() const { return ideas; }
void FileRepo::setIdeas(const std::vector<Idea>& newIdeas) { ideas = newIdeas; }