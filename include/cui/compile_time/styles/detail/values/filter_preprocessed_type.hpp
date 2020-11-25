#ifndef CUI_STYLES_FILTER_PREPROCESSED_TYPE
#define CUI_STYLES_FILTER_PREPROCESSED_TYPE

#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/detail/values/value_type.hpp>

namespace cui::ct::styles::detail {

auto filter_preprocessed_type(const StringView name, const ValueType type) -> ValueType {
	if (name.compare("x") == 0 && type == ValueType::String) return ValueType::Instruction;
	if (name.compare("y") == 0 && type == ValueType::String) return ValueType::Instruction;

	return type;
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_STYLES_FILTER_PREPROCESSED_TYPE