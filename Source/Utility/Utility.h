#pragma once

#include <string>
#include <vector>
#include <algorithm>

	
// combine vectors
template <typename T>
std::vector<T> operator + (const std::vector<T>& first, const std::vector<T>& second)
{
	std::vector<T> result = {};

	for (auto& element : first)
	{
		result.push_back(element);
	}

	for (auto& element : second)
	{
		result.push_back(element);
	}

	return result;
}

namespace utility
{
	// uuid
	std::string get_uuid();
	
	// remove duplicates
	template <typename T>
	void sort_and_remove_vector_duplicates(std::vector<T>& elements)
	{
		std::sort(elements.begin(), elements.end());
	
		for (std::size_t index = 0; index < elements.size(); index++)
		{
			if (index != elements.size() - 1)
			{
				if (elements[index] == elements[index + 1])
				{
					elements.erase(elements.begin() + index);
					index--;
				}
			}
		}
	}

}