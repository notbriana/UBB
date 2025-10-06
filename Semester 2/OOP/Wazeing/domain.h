#pragma once
#include <string>

enum class Status { Baby, GrownUp, Knight };

struct Location {
    double lat, lon;
    Location(double lat = 0, double lon = 0) : lat(lat), lon(lon) {}
};

struct Driver {
    std::string name;
    Status status;
    Location location;
    int score;

    Driver(const std::string& name = "", Status status = Status::Baby, Location loc = {}, int score = 0)
        : name(name), status(status), location(loc), score(score) {}

    std::string getName() const { return name; }
    std::string getStatus() const {
        switch (status) {
            case Status::Baby: return "baby";
            case Status::GrownUp: return "grown-up";
            case Status::Knight: return "knight";
        }
        return "";
    }
    double getLat() const { return location.lat; }
    double getLon() const { return location.lon; }
    int getScore() const { return score; }
};

struct Report {
    std::string description;
    std::string reporter;
    Location location;
    bool validated;
    int validations;

    Report(const std::string& desc = "", const std::string& reporter = "", Location loc = {}, bool validated = false, int validations = 0)
        : description(desc), reporter(reporter), location(loc), validated(validated), validations(validations) {}

    std::string getDescription() const { return description; }
    std::string getReporter() const { return reporter; }
    double getLat() const { return location.lat; }
    double getLon() const { return location.lon; }
    bool isValidated() const { return validated; }
};