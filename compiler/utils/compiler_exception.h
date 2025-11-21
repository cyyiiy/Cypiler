#pragma once
#include <string>

class compiler_exception : public std::exception
{
public:
    explicit compiler_exception(std::string msg) : m_msg(std::move(msg)) {}

    [[nodiscard]] const char* what() const noexcept override { return m_msg.c_str(); }
    
private:
    std::string m_msg;
};
