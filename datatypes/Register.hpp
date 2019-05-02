#pragma once

/* Register represents one of the Caltech10 CPU's two registers. */
class Register {
public:
    Register(bool isX);
    bool getIsX();
private:
    bool isX;
};