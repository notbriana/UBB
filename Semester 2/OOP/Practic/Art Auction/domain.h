#pragma once
#include <string>
#include <vector>
#include <tuple>

enum class UserType { Collector, Administrator };

struct User {
    int id;
    std::string name;
    UserType type;
};

struct Offer {
    int userId;
    double offeredSum;
    std::string date;
};

struct Item {
    std::string name;
    std::string category;
    int currentPrice;
    std::vector<Offer> offers;
};