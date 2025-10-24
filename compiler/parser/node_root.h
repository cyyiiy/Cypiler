#pragma once
#include <memory>
#include "node.h"
#include "node_expr.h"

struct node_root : node
{
};


struct node_root_exit : node_root
{
	explicit node_root_exit(const std::weak_ptr<node_expr_numeric>& expr_numeric) : m_expr_numeric(expr_numeric.lock()) {}

	[[nodiscard]] std::string to_string(const int offset = 0) const override;

	std::shared_ptr<node_expr_numeric> m_expr_numeric;
};