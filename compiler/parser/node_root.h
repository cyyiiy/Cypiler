#pragma once
#include <memory>
#include "node.h"
#include "node_expr.h"

struct node_root : node
{
	[[nodiscard]] virtual std::string to_assembly() const = 0;
};


struct node_root_exit : node_root
{
	explicit node_root_exit(const std::weak_ptr<node_expr_numeric>& expr_numeric) : m_expr_numeric(expr_numeric.lock()) {}

	[[nodiscard]] std::string to_string(const int offset = 0) const override;
	[[nodiscard]] std::string to_assembly() const override;

	std::shared_ptr<node_expr_numeric> m_expr_numeric;
};

struct node_root_print : node_root
{
	explicit node_root_print(const std::weak_ptr<node_expr_text>& expr_text) : m_expr_text(expr_text.lock()) {}

	[[nodiscard]] std::string to_string(const int offset = 0) const override;
	[[nodiscard]] std::string to_assembly() const override;

	std::shared_ptr<node_expr_text> m_expr_text;
};