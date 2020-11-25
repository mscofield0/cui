#ifndef CUI_CT_STYLES_FUNCTIONS_VEC_HPP
#define CUI_CT_STYLES_FUNCTIONS_VEC_HPP

#include <compile_time/styles/detail/values/functions/dependencies.hpp>

namespace cui::ct::styles::detail {

CUI_DEFINE_FUNCTION(vec) {
	const auto& args = fal.list();
	CUI_IF_NOT_IN_SET(2, 3, 4) {
		CUI_RETURN_ERROR("ERROR: Invalid amount of arguments.\n\tSupplied {} arguments.vec() only supports 2 - 4 arguments ", args.size());
	}

	if (!validate_args(args, args.size(), all_int)) {
		switch (args.size()) {
			case 2: {
				const float a = args[0].integer_value();
				const float b = args[1].integer_value();
				CUI_RETURN_VALUE((Vec2f{a, b}), ValueType::VectorInt);
			}
			case 3: {
				const float a = args[0].integer_value();
				const float b = args[1].integer_value();
				const float c = args[2].integer_value();
				CUI_RETURN_VALUE((Vec3f{a, b, c}), ValueType::VectorInt);
			}
			case 4: {
				const float a = args[0].integer_value();
				const float b = args[1].integer_value();
				const float c = args[2].integer_value();
				const float d = args[3].integer_value();
				CUI_RETURN_VALUE((Vec4f{a, b, c, d}), ValueType::VectorInt);
			}
		}
	} else if (!validate_args(args, args.size(), all_float)) {
		switch (args.size()) {
			case 2: {
				const float a = args[0].float_value();
				const float b = args[1].float_value();
				CUI_RETURN_VALUE((Vec2f{a, b}), ValueType::VectorFloat);
			}
			case 3: {
				const float a = args[0].float_value();
				const float b = args[1].float_value();
				const float c = args[2].float_value();
				CUI_RETURN_VALUE((Vec3f{a, b, c}), ValueType::VectorFloat);
			}
			case 4: {
				const float a = args[0].float_value();
				const float b = args[1].float_value();
				const float c = args[2].float_value();
				const float d = args[3].float_value();
				CUI_RETURN_VALUE((Vec4f{a, b, c, d}), ValueType::VectorFloat);
			}
		}
	}

	CUI_RETURN_ERROR("ERROR: Expected the vector values to be int or float types.");
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_FUNCTIONS_VEC_HPP