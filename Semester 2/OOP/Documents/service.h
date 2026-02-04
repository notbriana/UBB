#include "repository.h"
#include<vector>

class Service {
private:
    Repository repository;

public:
    std::vector<Document> getAllDocumentsSorted();
    std::vector<Document> searchDocuments(const std::string& query);
    Document getBestMatch(const std::string& query);
};
