#pragma once
#include <vector>
#include <optional>
#include <tokenizer/token.h>
// TODO: #include "node.h"


class parser
{
public:
    explicit parser(std::vector<token> tokens);
    ~parser() = default;

    parser(const parser& other) = delete;
    parser(parser&& other) = delete;
    parser& operator=(const parser& other) = delete;
    parser& operator=(parser&& other) = delete;

    // TODO: std::vector<node> parse();

private:
    [[nodiscard]] std::optional<token> peek_token() const;
    token consume_token();

    std::vector<token> m_tokens;
    size_t m_token_index{ 0 };
};

