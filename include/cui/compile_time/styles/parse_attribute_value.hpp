#ifndef CUI_CT_STYLES_PARSE_ATTRIBUTE_VALUE_HPP
#define CUI_CT_STYLES_PARSE_ATTRIBUTE_VALUE_HPP

#include <compile_time/format/fmt.hpp>
#include <compile_time/format/fmt_string_view.hpp>
#include <compile_time/format/format.hpp>
#include <compile_time/stream/stream.hpp>
#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/data_with_rule.hpp>
#include <compile_time/styles/detail/helper_macros.hpp>
#include <compile_time/styles/detail/values/char_checks.hpp>
#include <compile_time/styles/detail/values/function_argument_list.hpp>
#include <compile_time/styles/detail/values/index_of_function_name.hpp>
#include <compile_time/styles/detail/values/lookup_function.hpp>
#include <compile_time/styles/detail/values/lookup_string.hpp>
#include <compile_time/styles/detail/values/parse_float.hpp>
#include <compile_time/styles/detail/values/parse_int.hpp>
#include <compile_time/styles/detail/values/parse_percentage.hpp>
#include <compile_time/value_data.hpp>
#include <compile_time/variant/variant.hpp>

#define CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(msg, val) fmt_s<256>("ERROR: {}. Attribute value provided: {}", msg, val);

namespace cui::ct::styles::detail {

constexpr auto parse_attribute_value(const StringView str) -> Variant<DataWithRule, Format<256>> {
	enum class States : u8
	{
		None = 0,
		Int,
		Minus,
		Float,
		Percentage,
		String,
		Function,
		FunctionEnd
	} state = States::None;

	constexpr const char missing_end_fn_parenthesis[] = "Missing end parenthesis to the function";
	constexpr const char expected_end_of_value[] = "End of value expected";
	constexpr const char expected_minus_at_beginning[] = "Minus expected at the beginning of the value";
	constexpr const char expected_int_or_float_before_percent[] = "Expected int or float value before percent sign";
	constexpr const char expected_int_or_point_at_beginning[] = "Expected int value or point starting the value";
	constexpr const char missing_fn_name[] = "Expected function name";
	constexpr const char expected_fn[] = "Expected a function";
	constexpr const char expected_char_or_int[] = "Expected a char or an int";
	constexpr const char invalid_char[] = "Invalid char in value";

	CharStream stream{str};

	while (stream.good()) {
		const auto ch = *stream.current();
		if (is_digit(ch)) {
			switch (state) {
				case States::None:
				case States::Minus: {
					state = States::Int;
					break;
				}
				case States::Int:
				case States::Float:
				case States::String: {
					break;
				}
				case States::Function: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(missing_end_fn_parenthesis, str);
				}
				default: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(expected_end_of_value, str);
				}
			}
		} else if (is_minus(ch)) {
			switch (state) {
				case States::None: {
					state = States::Minus;
					break;
				}
				default: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(expected_minus_at_beginning, str);
				}
			}
		} else if (is_percent(ch)) {
			switch (state) {
				case States::Int:
				case States::Float: {
					state = States::Percentage;
					break;
				}
				case States::Function: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(missing_end_fn_parenthesis, str);
				}
				default: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(expected_int_or_float_before_percent, str);
				}
			}
		} else if (is_point(ch)) {
			switch (state) {
				case States::None:
				case States::Int: {
					state = States::Float;
					break;
				}
				case States::Function: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(missing_end_fn_parenthesis, str);
				}
				default: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(expected_int_or_point_at_beginning, str);
				}
			}
		} else if (is_open_parenthesis(ch)) {
			switch (state) {
				case States::String: {
					state = States::Function;
					if (str.find_last_of(',') != StringView::npos) {
						state = States::FunctionEnd;
					}

					while (stream.good()) stream.next();

					break;
				}
				case States::Function: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(missing_end_fn_parenthesis, str);
				}
				default: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(missing_fn_name, str);
				}
			}
		} else if (is_closed_parenthesis(ch)) {
			switch (state) {
				case States::Function: {
					state = States::FunctionEnd;
					break;
				}
				default: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(expected_fn, str);
				}
			}
		} else if (is_valid_char(ch)) {
			switch (state) {
				case States::None: {
					state = States::String;
					break;
				}
				case States::String: {
					break;
				}
				case States::Function: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(expected_fn, str);
				}
				default: {
					return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(expected_char_or_int, str);
				}
			}
		} else {
			return CUI_CT_RETURN_ATTR_VALUE_PARSING_ERROR(invalid_char, str);
		}

		stream.next();
	}

	switch (state) {
		case States::Int: {
			return DataWithRule{parse_int(str), ValueType::Int};
		}
		case States::Float: {
			return DataWithRule{parse_float(str), ValueType::Float};
		}
		case States::Percentage: {
			return DataWithRule{parse_percentage(str), ValueType::Percentage};
		}
		case States::String: {
			return DataWithRule{lookup_string(str), ValueType::String};
		}
		case States::FunctionEnd: {
			const auto open_parenthesis_idx = str.find_first_of('(');
			auto fn_name = str.substr(0, open_parenthesis_idx);
			const auto fn_name_idx = index_of_function_name(fn_name);
			if (fn_name_idx == styles::function_names.size()) {
				CUI_RETURN_ERROR("ERROR: Function name invalid.\nName: {}.", fn_name);
			}
			const auto closed_parenthesis_idx = str.find_last_of(')');
			const auto args_variant = FunctionArgumentList::parse(str.substr(open_parenthesis_idx + 1, closed_parenthesis_idx - open_parenthesis_idx - 1));
			if (args_variant.is_type_b()) {
				return args_variant.type_b();
			}

			const auto fn_processed_val = lookup_function(fn_name_idx, args_variant.type_a());
			if (fn_processed_val.is_type_b()) {
				return fn_processed_val.type_b();
			}

			return fn_processed_val.type_a();
		}
		default: {
			CUI_RETURN_ERROR("ERROR: Unexpected error.");
		}
	}
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_PARSE_ATTRIBUTE_VALUE_HPP