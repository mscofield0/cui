#ifndef CUI_CT_STYLES_LOOKUP_FUNCTION_HPP
#define CUI_CT_STYLES_LOOKUP_FUNCTION_HPP

#include <compile_time/format/fmt.hpp>
#include <compile_time/format/format.hpp>
#include <compile_time/styles/data_with_rule.hpp>
#include <compile_time/styles/detail/constants.hpp>
#include <compile_time/styles/detail/helper_macros.hpp>
#include <compile_time/styles/detail/values/function_argument_list.hpp>
#include <compile_time/styles/detail/values/functions/rgb.hpp>
#include <compile_time/styles/detail/values/functions/rgba.hpp>
#include <compile_time/styles/detail/values/functions/vec.hpp>
#include <compile_time/variant/variant.hpp>

namespace cui::ct::styles::detail {

constexpr auto lookup_function(size_t fn_name_idx, const detail::FunctionArgumentList& fal) -> Variant<DataWithRule, Format<256>> {
	switch (function_ids[fn_name_idx]) {
		case FunctionId::RGB: {
			return rgb(fal);
		}
		case FunctionId::RGBA: {
			return rgba(fal);
		}
		case FunctionId::Vec: {
			return vec(fal);
		}
		default: {
			break;
		}
	}

	CUI_RETURN_ERROR("ERROR: Invalid function index.");
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_LOOKUP_FUNCTION_HPP