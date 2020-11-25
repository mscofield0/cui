#ifndef CUI_ATTRIBUTES_HPP
#define CUI_ATTRIBUTES_HPP

#include <data_types/color.hpp>
#include <data_types/instruction.hpp>
#include <value_data.hpp>

namespace cui {

/// \brief Holds the \sa cui::Schematic 's attributes
class Attributes
{
public:
	Attributes() noexcept;

	[[nodiscard]] auto x() noexcept -> ValueData&;

	[[nodiscard]] auto x() const noexcept -> const ValueData&;

	[[nodiscard]] auto y() noexcept -> ValueData&;

	[[nodiscard]] auto y() const noexcept -> const ValueData&;

	[[nodiscard]] auto width() noexcept -> ValueData&;

	[[nodiscard]] auto width() const noexcept -> const ValueData&;

	[[nodiscard]] auto height() noexcept -> ValueData&;

	[[nodiscard]] auto height() const noexcept -> const ValueData&;

	[[nodiscard]] auto background() noexcept -> ValueData&;

	[[nodiscard]] auto background() const noexcept -> const ValueData&;

	[[nodiscard]] auto text_color() noexcept -> ValueData&;

	[[nodiscard]] auto text_color() const noexcept -> const ValueData&;

	[[nodiscard]] auto font_size() noexcept -> ValueData&;

	[[nodiscard]] auto font_size() const noexcept -> const ValueData&;

	[[nodiscard]] auto font() noexcept -> ValueData&;

	[[nodiscard]] auto font() const noexcept -> const ValueData&;

	[[nodiscard]] auto text_position() noexcept -> ValueData&;

	[[nodiscard]] auto text_position() const noexcept -> const ValueData&;

protected:
	ValueData x_;
	ValueData y_;
	ValueData width_;
	ValueData height_;
	ValueData background_;
	ValueData text_color_;
	ValueData font_size_;
	ValueData font_;
	ValueData text_position_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// \brief Constructs a default Attributes
/// \details Default attributes are:
/// x: 0
/// y: 0
/// width: 0
/// height: 0
/// background: Transparent
/// text_color: Black
/// font_size: 30
/// font: None
/// text_position: Center
Attributes::Attributes() noexcept
	: x_(0), y_(0), width_(0), height_(0), background_(Color::transparent), text_color_(Color::black), font_size_(30),
	  font_(), text_position_(Instruction::Center) {}

/// \brief Gets a mutable x attribute
/// \returns The mutable x attribute
auto Attributes::x() noexcept -> ValueData& {
	return x_;
}

/// \brief Gets an immutable x attribute
/// \returns The immutable x attribute
auto Attributes::x() const noexcept -> const ValueData& {
	return x_;
}

/// \brief Gets a mutable y attribute
/// \returns The mutable y attribute
auto Attributes::y() noexcept -> ValueData& {
	return y_;
}

/// \brief Gets an immutable y attribute
/// \returns The immutable y attribute
auto Attributes::y() const noexcept -> const ValueData& {
	return y_;
}

/// \brief Gets a mutable width attribute
/// \returns The mutable width attribute
auto Attributes::width() noexcept -> ValueData& {
	return width_;
}

/// \brief Gets an immutable width attribute
/// \returns The immutable width attribute
auto Attributes::width() const noexcept -> const ValueData& {
	return width_;
}

/// \brief Gets a mutable height attribute
/// \returns The mutable height attribute
auto Attributes::height() noexcept -> ValueData& {
	return height_;
}

/// \brief Gets an immutable height attribute
/// \returns The immutable height attribute
auto Attributes::height() const noexcept -> const ValueData& {
	return height_;
}

/// \brief Gets a mutable background attribute
/// \returns The mutable background attribute
auto Attributes::background() noexcept -> ValueData& {
	return background_;
}

/// \brief Gets an immutable background attribute
/// \returns The immutable background attribute
auto Attributes::background() const noexcept -> const ValueData& {
	return background_;
}

/// \brief Gets a mutable text_color attribute
/// \returns The mutable text_color attribute
auto Attributes::text_color() noexcept -> ValueData& {
	return text_color_;
}

/// \brief Gets an immutable text_color attribute
/// \returns The immutable text_color attribute
auto Attributes::text_color() const noexcept -> const ValueData& {
	return text_color_;
}

/// \brief Gets a mutable font_size attribute
/// \returns The mutable font_size attribute
auto Attributes::font_size() noexcept -> ValueData& {
	return font_size_;
}

/// \brief Gets an immutable font_size attribute
/// \returns The immutable font_size attribute
auto Attributes::font_size() const noexcept -> const ValueData& {
	return font_size_;
}

/// \brief Gets a mutable font attribute
/// \returns The mutable font attribute
auto Attributes::font() noexcept -> ValueData& {
	return font_;
}

/// \brief Gets an immutable font attribute
/// \returns The immutable font attribute
auto Attributes::font() const noexcept -> const ValueData& {
	return font_;
}

/// \brief Gets a mutable text_position attribute
/// \returns The mutable text_position attribute
auto Attributes::text_position() noexcept -> ValueData& {
	return text_position_;
}

/// \brief Gets an immutable text_position attribute
/// \returns The immutable text_position attribute
auto Attributes::text_position() const noexcept -> const ValueData& {
	return text_position_;
}

}	 // namespace cui

#endif	  // CUI_ATTRIBUTES_HPP