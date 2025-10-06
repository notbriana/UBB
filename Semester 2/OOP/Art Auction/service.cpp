#include "service.h"
#include <algorithm>
#include <stdexcept>

AuctionService::AuctionService(FileRepo& r) : repo(r) {
    users = repo.loadUsers();
    items = repo.loadItems();
}

const std::vector<User>& AuctionService::getUsers() const { return users; }
const std::vector<Item>& AuctionService::getItems() const { return items; }

std::vector<std::string> AuctionService::getCategories() const {
    std::vector<std::string> cats;
    for (const auto& item : items)
        if (std::find(cats.begin(), cats.end(), item.category) == cats.end())
            cats.push_back(item.category);
    return cats;
}

void AuctionService::addOffer(const std::string& itemName, int userId, double sum, const std::string& date) {
    auto it = std::find_if(items.begin(), items.end(), [&](const Item& i) { return i.name == itemName; });
    if (it == items.end()) throw std::runtime_error("Item not found");
    if (sum <= 0 || sum < it->currentPrice) throw std::runtime_error("Invalid offer");
    it->offers.push_back({ userId, sum, date });
    it->currentPrice = sum;
    notifyObservers();
    saveAll(); // Save after each offer
}

void AuctionService::addItem(const std::string& name, const std::string& category, double price) {
    if (name.empty()) throw std::runtime_error("Name cannot be empty.");
    if (price <= 0) throw std::runtime_error("Price must be positive.");
    items.push_back(Item{ name, category, static_cast<int>(price), {} });
    notifyObservers();
    saveAll(); // Save after each new item
}

UserType AuctionService::getUserType(int userId) const {
    auto it = std::find_if(users.begin(), users.end(), [userId](const User& u) { return u.id == userId; });
    if (it != users.end()) return it->type;
    return UserType::Collector;
}

void AuctionService::addObserver(Observer* obs) {
    observers.push_back(obs);
}
void AuctionService::removeObserver(Observer* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}
void AuctionService::notifyObservers() {
    for (auto obs : observers) obs->update();
}
void AuctionService::saveAll() {
    repo.saveItems(items);
}