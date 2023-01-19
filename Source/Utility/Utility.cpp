#include "Utility/Utility.h"
#include "Utility/Debug.h"
#include "Utility/Random.h"

namespace utility
{
	std::string get_uuid() // LOL make real later
	{
		static rngfr<int, 1, 2>		branch;
		static rngfr<int, 48, 57>	number;
		static rngfr<int, 65, 90>	letter;
		std::string					string;
	
		for (std::size_t iteration = 0; iteration < 128; iteration++)
		{
			switch (branch.value())
			{
				case 1:
				{
					string.push_back(char(number.value()));
				}
				break;
	
				case 2:
				{
					string.push_back(char(letter.value()));
				}
				break;
			}
		}
	
		return string;
	}

}