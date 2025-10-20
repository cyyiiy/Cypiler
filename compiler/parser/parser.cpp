#include "parser.h"
#include <iostream>


parser::parser(std::vector<token> tokens) : m_tokens(std::move(tokens))
{
}


std::optional<token> parser::peek_token() const
{
	if (m_token_index >= m_tokens.size())
		return {};

	return m_tokens.at(m_token_index);
}

token parser::consume_token()
{
	const token out = m_tokens.at(m_token_index);
	m_token_index++;
	return out;
}
