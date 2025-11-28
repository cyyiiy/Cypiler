#pragma once
#include <memory>
#include <sstream>
#include <string>
#include <parser/parser.h>

class generator
{
public:
    explicit generator(parse_result parse_result);
    ~generator() = default;

    generator(const generator& other) = delete;
    generator(generator&& other) = delete;
    generator& operator=(const generator& other) = delete;
    generator& operator=(generator&& other) = delete;

    [[nodiscard]] std::string generate();

private:
    [[nodiscard]] std::vector<std::string> search_text_expressions() const;
    
    parse_result m_parse_result;
    std::stringstream m_assembly;
};
