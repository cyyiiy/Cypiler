#pragma once
#include <memory>
#include <vector>
#include <sstream>
#include <string>
#include <parser/node_root.h>

class generator
{
public:
    explicit generator(std::vector<std::shared_ptr<node_root>> root_nodes);
    ~generator() = default;

    generator(const generator& other) = delete;
    generator(generator&& other) = delete;
    generator& operator=(const generator& other) = delete;
    generator& operator=(generator&& other) = delete;

    [[nodiscard]] std::string generate();

private:
    [[nodiscard]] std::vector<std::string> search_text_expressions() const;
    
    std::vector<std::shared_ptr<node_root>> m_root_nodes;
    std::stringstream m_assembly;
};
