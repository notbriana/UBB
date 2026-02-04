#include "service.h"
#include <algorithm>

std::vector<Document> Service::getAllDocumentsSorted() {
    auto docs = repository.getAllDocuments();
    std::sort(docs.begin(), docs.end());
    return docs;
}

std::vector<Document> Service::searchDocuments(const std::string& query) {
    std::vector<Document> results;
    for (const auto& doc : repository.getAllDocuments()) {
        if (doc.getName().find(query) != std::string::npos ||
            doc.getKeywords().find(query) != std::string::npos) {
            results.push_back(doc);
        }
    }
    return results;
}

Document Service::getBestMatch(const std::string& query) {
    auto docs = repository.getAllDocuments();
    float bestScore = -1.0f;
    Document bestDoc("", "", "");
    for (const auto& doc : docs) {
        float score = doc.similarityScore(query);
        if (score > bestScore) {
            bestScore = score;
            bestDoc = doc;
        }
    }
    return bestDoc;
}
