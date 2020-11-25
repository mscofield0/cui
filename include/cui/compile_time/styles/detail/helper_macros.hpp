#ifndef CUI_CT_STYLES_FUNCTIONS_HELPER_MACROS_HPP
#define CUI_CT_STYLES_FUNCTIONS_HELPER_MACROS_HPP

#define CUI_IF_IN_SET(...) if (is_in_set(args.size(), {__VA_ARGS__}))
#define CUI_IF_NOT_IN_SET(...) if (!is_in_set(args.size(), {__VA_ARGS__}))

#define CUI_RETURN_VALUE(val, val_type) \
	return DataWithRule { \
		ValueData{val}, val_type \
	}

#define CUI_RETURN_ERROR(msg, ...) return fmt_s<256>(msg, ##__VA_ARGS__);

#define CUI_DEFINE_FUNCTION(name) constexpr auto name(const FunctionArgumentList& fal)->Variant<DataWithRule, Format<256>>

#endif	  //  CUI_CT_STYLES_FUNCTIONS_HELPER_MACROS_HPP