#ifndef CUI_SCHEMATIC_HPP
#define CUI_SCHEMATIC_HPP

#include <exception>
#include <utils/print.hpp>

#include <aliases.hpp>
#include <compile_time/styles/attribute_data.hpp>
#include <compile_time/styles/detail/styles/get_attribute_index.hpp>
#include <compile_time/styles/detail/values/value_type.hpp>
#include <visual/attributes.hpp>
#include <visual/rules.hpp>

namespace cui {

/// \brief Class that contains attributes and rules for the GUI
class Schematic : public Attributes, public Rules
{
public:
	Schematic() noexcept = default;

	void assign(const ct::styles::AttributeData& attr_data);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// \brief Assigns the \sa cui::ValueData to attributes and sets the rules
/// \param attr_data The AttributeData that's used to populate the Schematic
void Schematic::assign(const ct::styles::AttributeData& attr_data) {
	using namespace ct::styles;
	using namespace ct::styles::detail;
	const auto i = get_attribute_index(attr_data.type());
	const auto pp_type = attr_data.preprocessed_type();
	const auto& value = attr_data.value();

	switch (static_cast<AttributeIndexes>(i)) {
		case AttributeIndexes::Background: {
			this->background_ = value;
			break;
		}
		case AttributeIndexes::X: {
			this->x_ = value;
			switch (pp_type) {
				case ValueType::Percentage:
				case ValueType::String:
				case ValueType::Instruction: {
					this->set_x_rule(true);
					break;
				}
				default: {
					break;
				}
			}
			break;
		}
		case AttributeIndexes::Y: {
			this->y_ = value;
			switch (pp_type) {
				case ValueType::Percentage:
				case ValueType::String:
				case ValueType::Instruction: {
					this->set_y_rule(true);
					break;
				}
				default: {
					break;
				}
			}
			break;
		}
		case AttributeIndexes::Width: {
			this->width_ = value;
			switch (pp_type) {
				case ValueType::Percentage: {
					this->set_width_rule(true);
					break;
				}
				default: {
					break;
				}
			}
			break;
		}
		case AttributeIndexes::Height: {
			this->height_ = value;
			switch (pp_type) {
				case ValueType::Percentage: {
					this->set_height_rule(true);
					break;
				}
				default: {
					break;
				}
			}
			break;
		}
		case AttributeIndexes::Font: {
			this->font_ = value;

			break;
		}
		case AttributeIndexes::FontSize: {
			this->font_size_ = value;

			break;
		}
		case AttributeIndexes::TextColor: {
			this->text_color_ = value;

			break;
		}
		case AttributeIndexes::TextPosition: {
			this->text_position_ = value;

			break;
		}
		default: {
			throw std::logic_error("Shouldn't happen");
		}
	}
}

}	 // namespace cui

#endif	  // CUI_SCHEMATIC_HPP