#include "parser.h"


parser::parser(std::vector<token> tokens) : m_tokens(std::move(tokens))
{
}


parse_result parser::parse()
{
	// Reset potential previous parsing
	m_token_index = 0;
	m_parse_result.m_root_nodes.clear();
	m_parse_result.m_text_literals.clear();

	std::optional<token> next_token;
	while ((next_token = peek_token()).has_value())
	{
		if (next_token.value().m_type == token_type::istr_exit)
		{
			consume_token(); // Consume the exit token
			m_parse_result.m_root_nodes.push_back(construct_exit());
			continue;
		}

		if (next_token.value().m_type == token_type::istr_print)
		{
			consume_token(); // Consume the print token
			m_parse_result.m_root_nodes.push_back(construct_print());
			continue;
		}
		
		if (next_token.value().m_type == token_type::istr_constant)
		{
			consume_token(); // Consume the constant declaration token
			auto constant_pair = construct_constant_declaration();
			if (m_constants.find(constant_pair.first) != m_constants.end())
			{
				// Constant list already registered this constant name
				throw compiler_exception("Duplicated constant declaration: name \"" + constant_pair.first + "\" is already registered!");
			}
			m_constants.insert(constant_pair);
			continue;
		}

		throw compiler_exception("Incorrect token placement: Isolated <" + next_token.value().to_string() + ">");
	}

	return m_parse_result;
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

void parser::require_token_type(const token_type type) const
{
	const std::optional<token> next_token = peek_token();
	if (!next_token.has_value())
	{
		throw compiler_exception("Syntax error: required <" + token_utils::to_string(type) + ">, got nothing");
	}
	if (next_token.value().m_type != type)
	{
		throw compiler_exception("Syntax error: required <" + token_utils::to_string(type) + ">, got <" + next_token.value().to_string() + ">");
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
	const std::optional<token> next_token = peek_token();
	if (!next_token.has_value())
	{
		throw compiler_exception("Syntax error: required numeric expression, got nothing");
	}
	
	if (next_token.value().m_type == token_type::val_numeric)
	{
		return std::make_shared<node_expr_numeric_literal>(consume_token().m_raw_value);
	}
	
	if (next_token.value().m_type == token_type::custom_name)
	{
		return retrieve_constant_by_name<node_expr_numeric_constant>(consume_token().m_raw_value, "int");
	}

	throw compiler_exception("Syntax error: required numeric expression, got <" + next_token.value().to_string() + ">");
}

std::shared_ptr<node_expr_text> parser::search_text_expression()
{
	const std::optional<token> next_token = peek_token();
	if (!next_token.has_value())
	{
		throw compiler_exception("Syntax error: required text expression, got nothing");
	}

	if (next_token.value().m_type == token_type::val_text)
	{
		// Creating a new node expression of type 'text_literal', insert it in the text literals list
		auto text_literal = std::make_shared<node_expr_text_literal>(consume_token().m_raw_value);
		m_parse_result.m_text_literals.push_back(text_literal);
		return text_literal;
	}
	
	if (next_token.value().m_type == token_type::custom_name)
	{
		return retrieve_constant_by_name<node_expr_text_constant>(consume_token().m_raw_value, "string");
	}

	throw compiler_exception("Syntax error: required text expression, got <" + next_token.value().to_string() + ">");
}

std::pair<std::string, std::shared_ptr<node_expr>> parser::construct_constant_declaration()
{
	const std::optional<token> next_token = peek_token();
	if (!next_token.has_value())
	{
		throw compiler_exception("Syntax error: required value type, got nothing");
	}
	
	switch (next_token.value().m_type)
	{
	case token_type::type_int:
	{
		consume_token();

		// Check for custom name
		require_token_type(token_type::custom_name);
		std::string constant_name = consume_token().m_raw_value;

		// Check for equal symbol
		require_token_type(token_type::sntx_equal);
		consume_token();

		// Retrieve constant value
		std::shared_ptr<node_expr_numeric> constant_value = search_numeric_expression();

		// Check for semicolon
		require_token_type(token_type::sntx_semicolon);
		consume_token();

		return {constant_name, std::make_shared<node_expr_numeric_constant>(constant_name, constant_value)};
	}
	
	case token_type::type_string:
	{
		consume_token();
			
		// Check for custom name
		require_token_type(token_type::custom_name);
		std::string constant_name = consume_token().m_raw_value;
			
		// Check for equal symbol
		require_token_type(token_type::sntx_equal);
		consume_token();
			
		// Retrieve constant value
		std::shared_ptr<node_expr_text> constant_value = search_text_expression();
			
		// Check for semicolon
		require_token_type(token_type::sntx_semicolon);
		consume_token();
			
		return {constant_name, std::make_shared<node_expr_text_constant>(constant_name, constant_value)};
	}
		
	default:
		throw compiler_exception("Syntax error: required value type, got <" + next_token.value().to_string() + ">");
	}
}