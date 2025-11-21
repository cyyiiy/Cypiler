#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <optional>
#include <utils/compiler_exception.h>
#include <tokenizer/token.h>
#include "node_root.h"
#include "node_expr.h"


class parser
{
public:
    explicit parser(std::vector<token> tokens);
    ~parser() = default;

    parser(const parser& other) = delete;
    parser(parser&& other) = delete;
    parser& operator=(const parser& other) = delete;
    parser& operator=(parser&& other) = delete;

    [[nodiscard]] std::vector<std::shared_ptr<node_root>> parse();

private:
    [[nodiscard]] std::optional<token> peek_token() const;
    token consume_token();
    void require_token_type(const token_type type) const;

    [[nodiscard]] std::shared_ptr<node_root_exit> construct_exit();
    [[nodiscard]] std::shared_ptr<node_root_print> construct_print();

    [[nodiscard]] std::shared_ptr<node_expr_numeric> search_numeric_expression();
    [[nodiscard]] std::shared_ptr<node_expr_text> search_text_expression();
    
    [[nodiscard]] std::pair<std::string, std::shared_ptr<node_expr>> construct_constant_declaration();
    
    template<typename T>
    [[nodiscard]] std::shared_ptr<T> retrieve_constant_by_name(const std::string& constant_name, const std::string& required_type)
    {
        if (m_constants.find(constant_name) == m_constants.end())
        {
            throw compiler_exception("Constant name \"" + constant_name + "\" is not registered!");
        }
        
        const std::shared_ptr<node_expr> base_constant = m_constants.at(constant_name);
        std::shared_ptr<T> derived_constant = std::dynamic_pointer_cast<T>(m_constants.at(constant_name));
        if (!derived_constant)
        {
            throw compiler_exception("Required constant of type <" + required_type + ">, got:\n" + base_constant->to_string());
        }
        
        return derived_constant;
    }


    std::vector<token> m_tokens;
    size_t m_token_index{ 0 };

    std::vector<std::shared_ptr<node_root>> m_root_nodes;
    std::unordered_map<std::string, std::shared_ptr<node_expr>> m_constants;
};