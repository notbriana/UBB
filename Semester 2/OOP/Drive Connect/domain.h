#pragma once
#include <string>
#include <vector>

struct Driver {
    std::string name;
    double latitude, longitude;
    int score;

    // Getters
    const std::string& getName() const { return name; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    int getScore() const { return score; }

    // Setters
    void setName(const std::string& n) { name = n; }
    void setLatitude(double lat) { latitude = lat; }
    void setLongitude(double lon) { longitude = lon; }
    void setScore(int s) { score = s; }
};

struct Report {
    std::string description;
    std::string reporter;
    double latitude, longitude;
    bool validated;
    std::vector<std::string> validators;

    // Getters
    const std::string& getDescription() const { return description; }
    const std::string& getReporter() const { return reporter; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    bool isValidated() const { return validated; }
    const std::vector<std::string>& getValidators() const { return validators; }

    // Setters
    void setDescription(const std::string& d) { description = d; }
    void setReporter(const std::string& r) { reporter = r; }
    void setLatitude(double lat) { latitude = lat; }
    void setLongitude(double lon) { longitude = lon; }
    void setValidated(bool v) { validated = v; }
    void setValidators(const std::vector<std::string>& v) { validators = v; }
};

struct Message {
    std::string sender;
    std::string text;
};