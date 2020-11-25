#ifndef CUI_DATA_TYPES_INSTRUCTION_HPP
#define CUI_DATA_TYPES_INSTRUCTION_HPP

#include <aliases.hpp>

namespace cui {

/// \brief Enum holding all instruction functions
enum class Instruction : u8
{
	TopLeft = 0,
	Top,
	TopRight,
	Left,
	Center,
	Right,
	BottomLeft,
	Bottom,
	BottomRight
};

}	 // namespace cui

#endif	  // CUI_DATA_TYPES_INSTRUCTION_HPP