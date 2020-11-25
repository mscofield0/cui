#ifndef CUI_CT_STYLES_ATTRIBUTE_DATA_HPP
#define CUI_CT_STYLES_ATTRIBUTE_DATA_HPP

#include <compile_time/string/string_view.hpp>
#include <compile_time/value_data.hpp>
#include <compile_time/styles/detail/values/value_type.hpp>

namespace cui::ct::styles {

class AttributeData
{
public:
	constexpr AttributeData() : type_(), value_(), preprocessed_type_() {}
	constexpr AttributeData(const StringView p_type, const ValueData& p_data, const ValueType p_pptype)
		: type_(p_type), value_(p_data), preprocessed_type_(p_pptype) {}

	[[nodiscard]] constexpr auto type() noexcept -> StringView& {
		return type_;
	}

	[[nodiscard]] constexpr auto type() const noexcept -> StringView {
		return type_;
	}

	[[nodiscard]] constexpr auto value() noexcept -> ValueData& {
		return value_;
	}

	[[nodiscard]] constexpr auto value() const noexcept -> const ValueData& {
		return value_;
	}

	[[nodiscard]] constexpr auto preprocessed_type() const noexcept -> ValueType {
		return preprocessed_type_;
	}

private:
	StringView type_;
	ValueData value_;
	ValueType preprocessed_type_;
};

}	 // namespace cui::ct::styles

#endif	  // CUI_CT_STYLES_ATTRIBUTE_DATA_HPP