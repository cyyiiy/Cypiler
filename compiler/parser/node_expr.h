#pragma once
#include <string>
#include "node.h"

struct node_expr : node
{
};


struct node_expr_numeric : node_expr
{
	explicit node_expr_numeric(std::string numeric_value) : m_numeric_value(std::move(numeric_value)) {}

	[[nodiscard]] std::string to_string(const int offset = 0) const override;

	std::string m_numeric_value;
};

struct node_expr_text : node_expr
{
	explicit node_expr_text(std::string text_value) : m_text_value(std::move(text_value)) {}

	[[nodiscard]] std::string to_string(const int offset = 0) const override;

	std::string m_text_value;
};