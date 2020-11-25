#ifndef CUI_CT_STYLES_VALID_ATTRIBUTE_TYPES_HPP
#define CUI_CT_STYLES_VALID_ATTRIBUTE_TYPES_HPP

#include <aliases.hpp>

namespace cui::ct::styles {

class ValidAttributeType
{
public:
	constexpr ValidAttributeType(u64 p_x = 0) : x(p_x) {}

	constexpr operator u64() const {
		return x;
	}

	static const ValidAttributeType Invalid, RGBA, Vec2, Vec3, Vec4, Float, Int, Instruction, String;

private:
	u64 x;
};

// clang-format off
constexpr const ValidAttributeType ValidAttributeType::Invalid    {1 << 0},
                                   ValidAttributeType::RGBA       {1 << 1},
                                   ValidAttributeType::Vec2       {1 << 2},
                                   ValidAttributeType::Vec3       {1 << 3},
                                   ValidAttributeType::Vec4       {1 << 4},
                                   ValidAttributeType::Float      {1 << 5},
                                   ValidAttributeType::Int        {1 << 6},
                                   ValidAttributeType::Instruction{1 << 7},
                                   ValidAttributeType::String	  {1 << 8};
// clang-format on

constexpr auto operator|(const ValidAttributeType& a, const ValidAttributeType& b) -> u64 {
	return static_cast<u64>(a) | static_cast<u64>(b);
}

constexpr auto operator|(const u64 a, const ValidAttributeType& b) -> u64 {
	return a | static_cast<u64>(b);
}

constexpr auto operator|(const ValidAttributeType& a, const u64 b) -> u64 {
	return static_cast<u64>(a) | b;
}

}	 // namespace cui::ct::styles

#endif	  // CUI_CT_STYLES_VALID_ATTRIBUTE_TYPES_HPP