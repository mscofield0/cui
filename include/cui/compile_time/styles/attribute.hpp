#ifndef CUI_CT_STYLES_ATTRIBUTE_HPP
#define CUI_CT_STYLES_ATTRIBUTE_HPP

#include <compile_time/string/string_view.hpp>

namespace cui::ct::styles {

class Attribute
{
public:
	constexpr Attribute() : type_(), value_() {}
	constexpr Attribute(const StringView p_type, const StringView p_value) : type_(p_type), value_(p_value) {}

	[[nodiscard]] constexpr auto type() noexcept -> StringView& {
		return type_;
	}

	[[nodiscard]] constexpr auto type() const noexcept -> StringView {
		return type_;
	}

	[[nodiscard]] constexpr auto value() noexcept -> StringView& {
		return value_;
	}

	[[nodiscard]] constexpr auto value() const noexcept -> StringView {
		return value_;
	}

private:
	StringView type_, value_;
};

}	 // namespace cui::ct::styles

#endif	  // CUI_CT_STYLES_ATTRIBUTE_HPP