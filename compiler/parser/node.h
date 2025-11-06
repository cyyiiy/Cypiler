#pragma once
#include <string>

struct node
{
	virtual ~node() = default;
	
	[[nodiscard]] virtual std::string to_string(const int offset = 0) const = 0;

	static std::string to_string(const node& node, const int offset = 0)
	{
		return node.to_string(offset);
	}

protected:
	static std::string offset_to_string(const int offset)
	{
		std::string out;
    
		if (offset > 0)
		{
			for (int i = 0; i < offset - 1; i++)
			{
				out += "   ";
			}
			out += " > ";
		}

		return out;
	}
};