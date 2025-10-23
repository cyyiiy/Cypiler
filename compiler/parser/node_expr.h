#pragma once
#include <string>
#include "node.h"

struct node_expr : public node
{
};


struct node_expr_numeric : public node_expr
{
	explicit node_expr_numeric(std::string numeric_value) : m_numeric_value(std::move(numeric_value)) {}

	[[nodiscard]] std::string to_string() const override;

	std::string m_numeric_value;
};