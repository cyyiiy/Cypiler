#pragma once
#include "node.h"
#include "node_expr.h"

struct node_root : public node
{
};


struct node_root_exit : public node_root
{
	explicit node_root_exit(node_expr_numeric expr_numeric) : m_expr_numeric(std::move(expr_numeric)) {}

	[[nodiscard]] std::string to_string() const override;

	node_expr_numeric m_expr_numeric;
};