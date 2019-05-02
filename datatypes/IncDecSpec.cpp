#include "IncDecSpec.hpp"

IncDecSpec::IncDecSpec(bool isDec, bool isPost) {
    this->isDec = isDec;
    this->isPost = isPost;
}

bool IncDecSpec::getIsDec() {
    return isDec;
}

bool IncDecSpec::getIsPost() {
    return isPost;
}
