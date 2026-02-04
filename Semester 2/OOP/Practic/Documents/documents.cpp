#include "documents.h"

float Document::similarityScore(const std::string& query) const {
    size_t maxLen = 0;
    for (size_t i = 0; i < query.size(); ++i) {
        for (size_t j = i + 1; j <= query.size(); ++j) {
            std::string sub = query.substr(i, j - i);
            if (name.find(sub) != std::string::npos) {
                maxLen = std::max(maxLen, sub.size());
            }
        }
    }
    return name.empty() ? 0.0f : (float)maxLen / name.size();
}
