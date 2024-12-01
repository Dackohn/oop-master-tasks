#ifndef DINEABLE_H
#define DINEABLE_H

#include <string>

class Dineable {
public:
    virtual void serveDinner(const std::string& carId) = 0;
    virtual ~Dineable() = default;
};

#endif
