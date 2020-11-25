#ifndef CUI_RULES_HPP
#define CUI_RULES_HPP

#include <aliases.hpp>

namespace cui {

/// \brief Class holding active rules
class Rules
{
public:
	Rules() noexcept;

	void set_x_rule(bool val) noexcept;

	void set_y_rule(bool val) noexcept;

	void set_width_rule(bool val) noexcept;

	void set_height_rule(bool val) noexcept;

	void set_text_position_rule(bool val) noexcept;

	[[nodiscard]] bool x_rule() const noexcept;

	[[nodiscard]] bool y_rule() const noexcept;

	[[nodiscard]] bool width_rule() const noexcept;

	[[nodiscard]] bool height_rule() const noexcept;

	[[nodiscard]] bool text_position_rule() const noexcept;

protected:
	void set_nth_bit(bool val, int n) noexcept {
		if (val) {
			enabled_rules_ |= (1 << n);
			return;
		}
		enabled_rules_ &= ~(1 << n);
	}

	bool get_nth_bit(int n) const noexcept {
		return (enabled_rules_ & (1 << n));
	}

	enum ID : u32
	{
		X = 0,
		Y,
		Width,
		Height,
		TextPosition
	};

	u32 enabled_rules_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// \brief Default constructs the rule
Rules::Rules() noexcept : enabled_rules_(0) {}

/// \brief Sets the x rule
/// \param val The value to set the x rule to
void Rules::set_x_rule(bool val) noexcept {
	set_nth_bit(val, ID::X);
}

/// \brief Sets the y rule
/// \param val The value to set the y rule to
void Rules::set_y_rule(bool val) noexcept {
	set_nth_bit(val, ID::Y);
}

/// \brief Sets the width rule
/// \param val The value to set the width rule to
void Rules::set_width_rule(bool val) noexcept {
	set_nth_bit(val, ID::Width);
}

/// \brief Sets the height rule
/// \param val The value to set the height rule to
void Rules::set_height_rule(bool val) noexcept {
	set_nth_bit(val, ID::Height);
}

/// \brief Sets the text_position rule
/// \param val The value to set the text_position rule to
void Rules::set_text_position_rule(bool val) noexcept {
	set_nth_bit(val, ID::TextPosition);
}

/// \brief Reads if x rule is set
/// \returns Boolean indicating whether or not the rule is set
bool Rules::x_rule() const noexcept {
	return get_nth_bit(ID::X);
}

/// \brief Reads if y rule is set
/// \returns Boolean indicating whether or not the rule is set
bool Rules::y_rule() const noexcept {
	return get_nth_bit(ID::Y);
}

/// \brief Reads if width rule is set
/// \returns Boolean indicating whether or not the rule is set
bool Rules::width_rule() const noexcept {
	return get_nth_bit(ID::Width);
}

/// \brief Reads if height rule is set
/// \returns Boolean indicating whether or not the rule is set
bool Rules::height_rule() const noexcept {
	return get_nth_bit(ID::Height);
}

/// \brief Reads if text_position rule is set
/// \returns Boolean indicating whether or not the rule is set
bool Rules::text_position_rule() const noexcept {
	return get_nth_bit(ID::TextPosition);
}

}	 // namespace cui

#endif	  // CUI_RULES_HPP