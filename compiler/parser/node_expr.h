#pragma once
#include <string>
#include <memory>
#include "node.h"

struct node_expr : node
{
};

struct node_expr_numeric : node_expr
{
	[[nodiscard]] virtual std::string get_numeric_value() const = 0;
};


struct node_expr_numeric_literal : node_expr_numeric
{
	explicit node_expr_numeric_literal(std::string numeric_value) : m_numeric_value(std::move(numeric_value)) {}

	[[nodiscard]] std::string to_string(const int offset = 0) const override;
	[[nodiscard]] std::string get_numeric_value() const override;

	std::string m_numeric_value;
};

struct node_expr_numeric_constant : node_expr_numeric
{
	explicit node_expr_numeric_constant(std::string custom_name, const std::weak_ptr<node_expr_numeric>& expr_numeric) :
		m_custom_name(std::move(custom_name)), m_expr_numeric(expr_numeric.lock()) {}
	
	[[nodiscard]] std::string to_string(const int offset = 0) const override;
	[[nodiscard]] std::string get_numeric_value() const override;
	
	std::string m_custom_name;
	std::shared_ptr<node_expr_numeric> m_expr_numeric;
};


struct node_expr_text : node_expr
{
	explicit node_expr_text(std::string text_value) : m_text_value(std::move(text_value)) {}

	[[nodiscard]] std::string to_string(const int offset = 0) const override;

	std::string m_text_value;
	int m_assembly_text_index{ 0 };
};