#pragma once
#include <memory>
#include <vector>
#include <optional>
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

    std::vector<std::shared_ptr<node_root>> parse();

private:
    [[nodiscard]] std::optional<token> peek_token() const;
    token consume_token();
    void require_token_type(token_type type);

    [[nodiscard]] std::shared_ptr<node_root_exit> construct_exit();
    [[nodiscard]] std::shared_ptr<node_root_print> construct_print();

    [[nodiscard]] std::shared_ptr<node_expr_numeric> search_numeric_expression();
    [[nodiscard]] std::shared_ptr<node_expr_text> search_text_expression();
    

    std::vector<token> m_tokens;
    size_t m_token_index{ 0 };

    std::vector<std::shared_ptr<node_root>> m_root_nodes;
};

