#include "parser.h"
#include <iostream>


parser::parser(std::vector<token> tokens) : m_tokens(std::move(tokens))
{
}


std::vector<std::shared_ptr<node_root>> parser::parse()
{
	// Reset potential previous parsing
	m_token_index = 0;
	m_root_nodes.clear();

	std::optional<token> next_token;
	while ((next_token = peek_token()).has_value())
	{
		if (next_token.value().m_type == token_type::istr_exit)
		{
			consume_token(); // Consume the exit token
			m_root_nodes.push_back(construct_exit());
			continue;
		}

		if (next_token.value().m_type == token_type::istr_print)
		{
			consume_token(); // Consume the print token
			m_root_nodes.push_back(construct_print());
			continue;
		}

		std::cerr << "Incorrect token placement: Isolated " << next_token.value().to_string() << "\n";
		exit(EXIT_FAILURE);
	}

	return m_root_nodes;
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

void parser::require_token_type(token_type type)
{
	std::optional<token> next_token = peek_token();
	if (!next_token.has_value())
	{
		std::cerr << "Syntax error: required <" << token_utils::to_string(type) << ">, got nothing!\n";
		exit(EXIT_FAILURE);
	}
	if (next_token.value().m_type != type)
	{
		std::cerr << "Syntax error: required <" << token_utils::to_string(type) << ">, got <" << next_token.value().to_string() << ">!\n";
		exit(EXIT_FAILURE);
	}
}

std::shared_ptr<node_root_exit> parser::construct_exit()
{
	// Check for opening parenthesis
	require_token_type(token_type::sntx_par_open);
	consume_token();

	// Retrieve numeric expression child node
	const std::shared_ptr<node_expr_numeric> expr_num = search_numeric_expression();

	// Check for closing parenthesis
	require_token_type(token_type::sntx_par_close);
	consume_token();

	// Check for semicolon
	require_token_type(token_type::sntx_semicolon);
	consume_token();

	return std::make_shared<node_root_exit>(expr_num);
}

std::shared_ptr<node_root_print> parser::construct_print()
{
	// Check for opening parenthesis
	require_token_type(token_type::sntx_par_open);
	consume_token();

	// Retrieve text expression child node
	const std::shared_ptr<node_expr_text> expr_text = search_text_expression();

	// Check for closing parenthesis
	require_token_type(token_type::sntx_par_close);
	consume_token();

	// Check for semicolon
	require_token_type(token_type::sntx_semicolon);
	consume_token();

	return std::make_shared<node_root_print>(expr_text);
}

std::shared_ptr<node_expr_numeric> parser::search_numeric_expression()
{
	std::optional<token> next_token = peek_token();
	if (!next_token.has_value())
	{
		std::cerr << "Syntax error: required numeric expression, got nothing!\n";
		exit(EXIT_FAILURE);
	}
	
	if (next_token.value().m_type == token_type::val_numeric)
	{
		return std::make_shared<node_expr_numeric>(consume_token().m_raw_value);
	}

	std::cerr << "Syntax error: required numeric expression, got <" << next_token.value().to_string() << ">!\n";
	exit(EXIT_FAILURE);
}

std::shared_ptr<node_expr_text> parser::search_text_expression()
{
	std::optional<token> next_token = peek_token();
	if (!next_token.has_value())
	{
		std::cerr << "Syntax error: required text expression, got nothing!\n";
		exit(EXIT_FAILURE);
	}

	if (next_token.value().m_type == token_type::val_text)
	{
		return std::make_shared<node_expr_text>(consume_token().m_raw_value);
	}

	std::cerr << "Syntax error: required numeric expression, got <" << next_token.value().to_string() << ">!\n";
	exit(EXIT_FAILURE);
}
