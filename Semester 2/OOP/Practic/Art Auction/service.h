#pragma once
#include "domain.h"
#include "filerepo.h"
#include <vector>
#include <string>
#include <functional>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class AuctionService {
    std::vector<User> users;
    std::vector<Item> items;
    std::vector<Observer*> observers;
    FileRepo& repo;
public:
    AuctionService(FileRepo& repo);

    const std::vector<User>& getUsers() const;
    const std::vector<Item>& getItems() const;
    std::vector<std::string> getCategories() const;

    void addOffer(const std::string& itemName, int userId, double sum, const std::string& date);
    void addItem(const std::string& name, const std::string& category, double price);
    UserType getUserType(int userId) const;
    void addObserver(Observer* obs);
    void removeObserver(Observer* obs);

    void notifyObservers();
    void saveAll();
};