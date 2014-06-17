
#pragma once
#include <string>

class Error
{
public:
    Error(const char* errText)
        : text(errText)
    { }

    Error(std::string errText)
        : text(errText)
    { }

    std::string What() const { return text; }

private:
    std::string text;
};

