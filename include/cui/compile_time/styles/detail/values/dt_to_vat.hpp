#ifndef CUI_CT_STYLES_DT_TO_VAT_HPP
#define CUI_CT_STYLES_DT_TO_VAT_HPP

#include <compile_time/styles/detail/constants.hpp>
#include <compile_time/styles/detail/values/validate_attribute_type.hpp>
#include <data_types/data_types.hpp>

namespace cui::ct::styles::detail {

constexpr auto dt_to_vat(DataTypes data_type) -> ValidAttributeType {
	switch (data_type) {
		case DataTypes::Color: {
			return ValidAttributeType::RGBA;
		}
		case DataTypes::Float: {
			return ValidAttributeType::Float;
		}
		case DataTypes::Int: {
			return ValidAttributeType::Int;
		}
		case DataTypes::Instruction: {
			return ValidAttributeType::Instruction;
		}
		case DataTypes::Vec2: {
			return ValidAttributeType::Vec2;
		}
		case DataTypes::Vec3: {
			return ValidAttributeType::Vec3;
		}
		case DataTypes::Vec4: {
			return ValidAttributeType::Vec4;
		}
		case DataTypes::String: {
			return ValidAttributeType::String;
		}
		default: {
			// Impossible
			return ValidAttributeType::Invalid;
		}
	}
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_DT_TO_VAT_HPP