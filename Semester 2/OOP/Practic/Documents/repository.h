#include "documents.h"
#include <vector>
class Repository {
private:
    std::vector<Document> documents;

public:
    Repository();
    void loadFromFile();
    std::vector<Document> getAllDocuments();
};
