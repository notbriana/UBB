#include "domain.h"

Programmer::Programmer(const std::string& name, int revised, int total)
    : name(name), revised_files(revised), total_files_to_revise(total) {
}

SourceFile::SourceFile(const std::string& name, const std::string& status, const std::string& creator, const std::string& reviewer)
    : name(name), status(status), creator(creator), reviewer(reviewer) {
}
