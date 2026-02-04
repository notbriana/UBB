#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Document {
private:
    std::string name;
    std::string keywords;
    std::string content;

public:
    Document(std::string name, std::string keywords, std::string content)
        : name(name), keywords(keywords), content(content) {
    }

    std::string getName() const { return name; }
    std::string getKeywords() const { return keywords; }
    std::string getContent() const { return content; }

    bool operator <(const Document& d) const { return name < d.name; }

    std::string toStdString() const {
        return name + " | " + keywords;
    }

    float similarityScore(const std::string& query) const;
};
