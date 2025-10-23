#pragma once
#include <string>

struct node
{
	[[nodiscard]] virtual std::string to_string() const = 0;

	static std::string to_string(const node& node)
	{
		return node.to_string();
	}
};