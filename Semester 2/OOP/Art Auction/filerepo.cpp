#include "filerepo.h"
#include <fstream>
#include <sstream>
#include <algorithm>

static UserType parseUserType(const std::string& str) {
    return (str == "collector" ? UserType::Collector : UserType::Administrator);
}

FileRepo::FileRepo(const std::string& u, const std::string& i) : usersFile(u), itemsFile(i) {}

std::vector<User> FileRepo::loadUsers() {
    std::vector<User> users;
    std::ifstream fin(usersFile);
    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string name, typeStr;
        int id;
        ss >> name >> id >> typeStr;
        users.push_back(User{ id, name, parseUserType(typeStr) });
    }
    return users;
}

std::vector<Item> FileRepo::loadItems() {
    std::vector<Item> items;
    std::ifstream fin(itemsFile);
    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string itemName, category;
        int currentPrice;
        ss >> itemName >> category >> currentPrice;
        Item item;
        item.name = itemName;
        item.category = category;
        item.currentPrice = currentPrice;
        item.offers.clear();

        // Read the rest of the line for offers
        std::string offersPart;
        std::getline(ss, offersPart); // get the rest after currentPrice
        if (!offersPart.empty()) {
            std::stringstream oss(offersPart);
            std::string offerToken;
            // Offers are separated by '|'
            while (std::getline(oss, offerToken, '|')) {
                std::stringstream offerStream(offerToken);
                int userId;
                double offeredSum;
                std::string date;
                offerStream >> userId >> offeredSum >> date;
                if (offerStream) {
                    item.offers.push_back(Offer{ userId, offeredSum, date });
                }
            }
        }

        items.push_back(item);
    }
    return items;
}

void FileRepo::saveItems(const std::vector<Item>& items) {
    std::ofstream fout(itemsFile);
    for (const auto& item : items) {
        fout << item.name << " " << item.category << " " << item.currentPrice;
        for (const auto& offer : item.offers) {
            fout << " | " << offer.userId << " " << offer.offeredSum << " " << offer.date;
        }
        fout << "\n";
    }
}