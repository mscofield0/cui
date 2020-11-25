#ifndef CUI_DATA_TYPES_COLOR_HPP
#define CUI_DATA_TYPES_COLOR_HPP

#include <aliases.hpp>

namespace cui {

/// \brief Class representing an RGBA color value
class Color
{
public:
	constexpr Color();
	constexpr Color(u32 data);
	constexpr Color(i32 r, i32 g, i32 b, i32 a);

	[[nodiscard]] constexpr auto data() noexcept -> u32&;
	[[nodiscard]] constexpr auto data() const noexcept -> u32;

	[[nodiscard]] constexpr auto red() const noexcept -> i32;

	[[nodiscard]] constexpr auto green() const noexcept -> i32;

	[[nodiscard]] constexpr auto blue() const noexcept -> i32;

	[[nodiscard]] constexpr auto alpha() const noexcept -> i32;

	static const Color transparent, black, white;

private:
	static constexpr auto to_color(i32 r, i32 g, i32 b, i32 a) -> u32;

	u32 data_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// \brief Default constructs the color, equivalent to transparent color
constexpr Color::Color() : data_(0) {}

/// \brief Constructs the color from a packed u32 value
constexpr Color::Color(u32 data) : data_{data} {}

/// \brief Constructs the value from red, green, blue and alpha values
constexpr Color::Color(i32 r, i32 g, i32 b, i32 a = 255) : data_{to_color(r, g, b, a)} {}

/// \brief Gets a mutable packed u32 value
/// \returns A mutable packed u32 value
constexpr auto Color::data() noexcept -> u32& {
	return data_;
}

/// \brief Gets an immutable packed u32 value
/// \returns An immutable packed u32 value
constexpr auto Color::data() const noexcept -> u32 {
	return data_;
}

/// \brief Gets the red color value from the packed u32 value
/// \returns The red color value
constexpr auto Color::red() const noexcept -> i32 {
	return (data() & (255 << 24)) >> 24;
}

/// \brief Gets the green color value from the packed u32 value
/// \returns The green color value
constexpr auto Color::green() const noexcept -> i32 {
	return (data() & (255 << 16)) >> 16;
}

/// \brief Gets the blue color value from the packed u32 value
/// \returns The blue color value
constexpr auto Color::blue() const noexcept -> i32 {
	return (data() & (255 << 8)) >> 8;
}

/// \brief Gets the alpha color value from the packed u32 value
/// \returns The alpha color value
constexpr auto Color::alpha() const noexcept -> i32 {
	return data() & 255;
}

/// \brief Converts red, green, blue and alpha value into a packed u32 value
constexpr auto Color::to_color(i32 r, i32 g, i32 b, i32 a) -> u32 {
	u32 data = a;
	data |= b << 8;
	data |= g << 16;
	data |= r << 24;
	return data;
}

constexpr Color Color::transparent = Color(0), Color::black = Color(0, 0, 0), Color::white = Color(255, 255, 255);

}	 // namespace cui

#endif	  // CUI_DATA_TYPES_COLOR_HPP