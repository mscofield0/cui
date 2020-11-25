#ifndef CUI_DATA_TYPES_HPP
#define CUI_DATA_TYPES_HPP

#include <aliases.hpp>

namespace cui {

/// \brief An enum containing all CUI data types
enum class DataTypes : u8
{
	None = 0,
	Color,
	Float,
	Int,
	Vec2,
	Vec3,
	Vec4,
	Instruction,
	String
};

}	 // namespace cui

#endif	  // CUI_DATA_TYPES_HPP