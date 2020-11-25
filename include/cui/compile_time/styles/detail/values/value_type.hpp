#ifndef CUI_CT_STYLES_VALUE_TYPE_HPP
#define CUI_CT_STYLES_VALUE_TYPE_HPP

#include <aliases.hpp>

namespace cui::ct::styles {

enum class ValueType : u8
{
	Int,
	Float,
	Percentage,
	String,
	Color,
	VectorInt,
	VectorFloat,
	Instruction
};

}	 // namespace cui::ct::styles

#endif	  // CUI_CT_STYLES_VALUE_TYPE_HPP