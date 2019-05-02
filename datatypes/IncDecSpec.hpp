#pragma once

/**
 * IncDecSpec represents a flag for increment/decrement and a flag for pre/post.
 * It describes the possible increment or decrement during an indexed LD/ST
 * instruction.
 */
class IncDecSpec {
public:
    IncDecSpec(bool isDec, bool isPost);
    bool getIsDec();
    bool getIsPost();
private:
    bool isDec;
    bool isPost;
};