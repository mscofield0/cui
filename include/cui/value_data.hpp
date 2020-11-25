#ifndef CUI_VALUE_DATA_HPP
#define CUI_VALUE_DATA_HPP

#include <string>

#include <compile_time/value_data.hpp>
#include <data_types/color.hpp>
#include <data_types/data_types.hpp>
#include <data_types/instruction.hpp>
#include <data_types/vec.hpp>

namespace cui {

struct Empty
{};

/// \brief Variant container containing CUI data types
/// \details May throw on invalid type access
/// Union members are pointers in order to result in less memory being stored in the instance itself
class ValueData
{
public:
	ValueData() : active_(DataTypes::None), none_(nullptr) {}
	ValueData(const Color& color) : active_(DataTypes::Color), rgba_(new Color(color)) {}
	ValueData(const float val) : active_(DataTypes::Float), float_value_(new float(val)) {}
	ValueData(const int val) : active_(DataTypes::Int), integer_value_(new int(val)) {}
	ValueData(const Vec2f& v2) : active_(DataTypes::Vec2), vec2_(new Vec2f(v2)) {}
	ValueData(const Vec3f& v3) : active_(DataTypes::Vec3), vec3_(new Vec3f(v3)) {}
	ValueData(const Vec4f& v4) : active_(DataTypes::Vec4), vec4_(new Vec4f(v4)) {}
	ValueData(const Instruction& instr) : active_(DataTypes::Instruction), instruction_(new Instruction(instr)) {}
	ValueData(const std::string& instr) : active_(DataTypes::String), string_(new std::string(instr)) {}

	ValueData(const ValueData& other);

	ValueData(const ct::ValueData& other);

	ValueData& operator=(const ValueData& a);

	ValueData& operator=(const ct::ValueData& a);

	ValueData& operator=(const Color& color);

	ValueData& operator=(const float val);

	ValueData& operator=(const int val);

	ValueData& operator=(const Vec2f& p_vec2);

	ValueData& operator=(const Vec3f& p_vec3);

	ValueData& operator=(const Vec4f& p_vec4);

	ValueData& operator=(const Instruction& instr);

	ValueData& operator=(const std::string& str);

	// Checker functions
	[[nodiscard]] bool is_none() const noexcept;

	[[nodiscard]] bool is_rgba() const noexcept;

	[[nodiscard]] bool is_float() const noexcept;

	[[nodiscard]] bool is_int() const noexcept;

	[[nodiscard]] bool is_vec2() const noexcept;

	[[nodiscard]] bool is_vec3() const noexcept;

	[[nodiscard]] bool is_vec4() const noexcept;

	[[nodiscard]] bool is_instruction() const noexcept;

	[[nodiscard]] bool is_string() const noexcept;

	[[nodiscard]] auto rgba() noexcept -> Color&;

	[[nodiscard]] auto rgba() const noexcept -> const Color&;

	[[nodiscard]] auto float_value() noexcept -> float&;

	[[nodiscard]] auto float_value() const noexcept -> float;

	[[nodiscard]] auto integer_value() noexcept -> int&;

	[[nodiscard]] auto integer_value() const noexcept -> int;

	[[nodiscard]] auto vec2() noexcept -> Vec2f&;

	[[nodiscard]] auto vec2() const noexcept -> const Vec2f&;

	[[nodiscard]] auto vec3() noexcept -> Vec3f&;

	[[nodiscard]] auto vec3() const noexcept -> const Vec3f&;

	[[nodiscard]] auto vec4() noexcept -> Vec4f&;

	[[nodiscard]] auto vec4() const noexcept -> const Vec4f&;

	[[nodiscard]] auto instruction() noexcept -> Instruction&;

	[[nodiscard]] auto instruction() const noexcept -> const Instruction&;

	[[nodiscard]] auto string() noexcept -> std::string&;

	[[nodiscard]] auto string() const noexcept -> const std::string&;

	[[nodiscard]] auto active() const noexcept -> DataTypes;

private:
	void delete_current_active();

	DataTypes active_;

	union
	{
		Empty* none_;
		Color* rgba_;
		float* float_value_;
		int* integer_value_;
		Vec2f* vec2_;
		Vec3f* vec3_;
		Vec4f* vec4_;
		Instruction* instruction_;
		std::string* string_;
	};
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// \brief Copy constructs the \sa cui::ValueData with \sa cui::ValueData
ValueData::ValueData(const ValueData& other) {
	active_ = other.active_;
	switch (other.active_) {
		case DataTypes::Color: {
			rgba_ = new Color(other.rgba());
			break;
		}
		case DataTypes::Float: {
			float_value_ = new float(other.float_value());
			break;
		}
		case DataTypes::Int: {
			integer_value_ = new int(other.integer_value());
			break;
		}
		case DataTypes::Vec2: {
			vec2_ = new Vec2f(other.vec2());
			break;
		}
		case DataTypes::Vec3: {
			vec3_ = new Vec3f(other.vec3());
			break;
		}
		case DataTypes::Vec4: {
			vec4_ = new Vec4f(other.vec4());
			break;
		}
		case DataTypes::Instruction: {
			instruction_ = new Instruction(other.instruction());
			break;
		}
		case DataTypes::String: {
			string_ = new std::string(other.string());
			break;
		}
		default: {
			break;
		}
	}
}

/// \brief Copy constructs the \sa cui::ValueData with \sa cui::ct::ValueData
ValueData::ValueData(const ct::ValueData& other) {
	active_ = other.active();
	switch (active_) {
		case DataTypes::Color: {
			rgba_ = new Color(other.rgba());
			break;
		}
		case DataTypes::Float: {
			float_value_ = new float(other.float_value());
			break;
		}
		case DataTypes::Int: {
			integer_value_ = new int(other.integer_value());
			break;
		}
		case DataTypes::Vec2: {
			vec2_ = new Vec2f(other.vec2());
			break;
		}
		case DataTypes::Vec3: {
			vec3_ = new Vec3f(other.vec3());
			break;
		}
		case DataTypes::Vec4: {
			vec4_ = new Vec4f(other.vec4());
			break;
		}
		case DataTypes::Instruction: {
			instruction_ = new Instruction(other.instruction());
			break;
		}
		case DataTypes::String: {
			string_ = new std::string(other.string().begin(), other.string().end());
			break;
		}
		default: {
			// Do nothing
			break;
		}
	}
}

/// \brief Copy assigns the \sa cui::ValueData with \sa cui::ValueData
ValueData& ValueData::operator=(const ValueData& a) {
	this->delete_current_active();
	active_ = a.active_;
	switch (a.active_) {
		case DataTypes::Color: {
			rgba_ = new Color(a.rgba());
			return (*this);
		}
		case DataTypes::Float: {
			float_value_ = new float(a.float_value());
			return (*this);
		}
		case DataTypes::Int: {
			integer_value_ = new int(a.integer_value());
			return (*this);
		}
		case DataTypes::Vec2: {
			vec2_ = new Vec2f(a.vec2());
			return (*this);
		}
		case DataTypes::Vec3: {
			vec3_ = new Vec3f(a.vec3());
			return (*this);
		}
		case DataTypes::Vec4: {
			vec4_ = new Vec4f(a.vec4());
			return (*this);
		}
		case DataTypes::Instruction: {
			instruction_ = new Instruction(a.instruction());
			return (*this);
		}
		case DataTypes::String: {
			string_ = new std::string(a.string());
			return (*this);
		}
		default: {
			return (*this);
		}
	}
}

/// \brief Copy assigns the \sa cui::ValueData with \sa cui::ct::ValueData
ValueData& ValueData::operator=(const ct::ValueData& a) {
	this->delete_current_active();
	active_ = a.active();
	switch (active_) {
		case DataTypes::Color: {
			rgba_ = new Color(a.rgba());
			return (*this);
		}
		case DataTypes::Float: {
			float_value_ = new float(a.float_value());
			return (*this);
		}
		case DataTypes::Int: {
			integer_value_ = new int(a.integer_value());
			return (*this);
		}
		case DataTypes::Vec2: {
			vec2_ = new Vec2f(a.vec2());
			return (*this);
		}
		case DataTypes::Vec3: {
			vec3_ = new Vec3f(a.vec3());
			return (*this);
		}
		case DataTypes::Vec4: {
			vec4_ = new Vec4f(a.vec4());
			return (*this);
		}
		case DataTypes::Instruction: {
			instruction_ = new Instruction(a.instruction());
			return (*this);
		}
		case DataTypes::String: {
			string_ = new std::string(a.string().begin(), a.string().end());
			return (*this);
		}
		default: {
			return (*this);
		}
	}
}

/// \brief Assigns a \sa cui::Color to \sa cui::ValueData
/// \param color The color to be assigned
/// \returns The instance of \sa cui::ValueData that was assigned to
ValueData& ValueData::operator=(const Color& color) {
	this->delete_current_active();
	active_ = DataTypes::Color;
	rgba_ = new Color(color);
	return (*this);
}

/// \brief Assigns a \sa float to \sa cui::ValueData
/// \param val The float to be assigned
/// \returns The instance of \sa cui::ValueData that was assigned to
ValueData& ValueData::operator=(const float val) {
	this->delete_current_active();
	active_ = DataTypes::Float;
	float_value_ = new float(val);
	return (*this);
}

/// \brief Assigns an \sa int to \sa cui::ValueData
/// \param val The int to be assigned
/// \returns The instance of \sa cui::ValueData that was assigned to
ValueData& ValueData::operator=(const int val) {
	this->delete_current_active();
	active_ = DataTypes::Int;
	integer_value_ = new int(val);
	return (*this);
}

/// \brief Assigns a \sa cui::Vec2f to \sa cui::ValueData
/// \param p_vec2 The Vec2f to be assigned
/// \returns The instance of \sa cui::ValueData that was assigned to
ValueData& ValueData::operator=(const Vec2f& p_vec2) {
	this->delete_current_active();
	active_ = DataTypes::Vec2;
	vec2_ = new Vec2f(p_vec2);
	return (*this);
}

/// \brief Assigns a \sa cui::Vec3f to \sa cui::ValueData
/// \param p_vec3 The Vec3f to be assigned
/// \returns The instance of \sa cui::ValueData that was assigned to
ValueData& ValueData::operator=(const Vec3f& p_vec3) {
	this->delete_current_active();
	active_ = DataTypes::Vec3;
	vec3_ = new Vec3f(p_vec3);
	return (*this);
}

/// \brief Assigns a \sa cui::Vec4f to \sa cui::ValueData
/// \param p_vec4 The Vec4f to be assigned
/// \returns The instance of \sa cui::ValueData that was assigned to
ValueData& ValueData::operator=(const Vec4f& p_vec4) {
	this->delete_current_active();
	active_ = DataTypes::Vec4;
	vec4_ = new Vec4f(p_vec4);
	return (*this);
}

/// \brief Assigns a \sa cui::Instruction to \sa cui::ValueData
/// \param instr The instruction to be assigned
/// \returns The instance of \sa cui::ValueData that was assigned to
ValueData& ValueData::operator=(const Instruction& instr) {
	this->delete_current_active();
	active_ = DataTypes::Instruction;
	instruction_ = new Instruction(instr);
	return (*this);
}

/// \brief Assigns a \sa std::string to \sa cui::ValueData
/// \param str The string to be assigned
/// \returns The instance of \sa cui::ValueData that was assigned to
ValueData& ValueData::operator=(const std::string& str) {
	this->delete_current_active();
	active_ = DataTypes::String;
	string_ = new std::string(str);
	return (*this);
}

/// \brief Checks if the variant is empty
/// \returns Boolean indicating whether or not the variant is empty
[[nodiscard]] bool ValueData::is_none() const noexcept {
	return active_ == DataTypes::None;
}

/// \brief Checks if the variant is set to a \sa cui::Color value
/// \returns Boolean indicating whether or not the variant is set to a \sa cui::Color value
[[nodiscard]] bool ValueData::is_rgba() const noexcept {
	return active_ == DataTypes::Color;
}

/// \brief Checks if the variant is set to a float value
/// \returns Boolean indicating whether or not the variant is set to a float value
[[nodiscard]] bool ValueData::is_float() const noexcept {
	return active_ == DataTypes::Float;
}

/// \brief Checks if the variant is set to a int value
/// \returns Boolean indicating whether or not the variant is set to a int value
[[nodiscard]] bool ValueData::is_int() const noexcept {
	return active_ == DataTypes::Int;
}

/// \brief Checks if the variant is set to a \sa cui::Vec2 value
/// \returns Boolean indicating whether or not the variant is set to a \sa cui::Vec2 value
[[nodiscard]] bool ValueData::is_vec2() const noexcept {
	return active_ == DataTypes::Vec2;
}

/// \brief Checks if the variant is set to a \sa cui::Vec3 value
/// \returns Boolean indicating whether or not the variant is set to a \sa cui::Vec3 value
[[nodiscard]] bool ValueData::is_vec3() const noexcept {
	return active_ == DataTypes::Vec3;
}

/// \brief Checks if the variant is set to a \sa cui::Vec4 value
/// \returns Boolean indicating whether or not the variant is set to a \sa cui::Vec4 value
[[nodiscard]] bool ValueData::is_vec4() const noexcept {
	return active_ == DataTypes::Vec4;
}

/// \brief Checks if the variant is set to an \sa cui::Instruction value
/// \returns Boolean indicating whether or not the variant is set to a \sa cui::Instruction value
[[nodiscard]] bool ValueData::is_instruction() const noexcept {
	return active_ == DataTypes::Instruction;
}

/// \brief Checks if the variant is set to a \sa std::string value
/// \returns Boolean indicating whether or not the variant is set to a \sa std::string value
[[nodiscard]] bool ValueData::is_string() const noexcept {
	return active_ == DataTypes::String;
}

///////////
// Getters
///////////

/// \brief Gets a mutable rgba value or throws in case of an invalid variant member access
/// \returns The mutable RGBA color value
[[nodiscard]] auto ValueData::rgba() noexcept -> Color& {
	return *rgba_;
}

/// \brief Gets an immutable rgba value or throws in case of an invalid variant member access
/// \returns The immutable RGBA value
[[nodiscard]] auto ValueData::rgba() const noexcept -> const Color& {
	return *rgba_;
}

/// \brief Gets a mutable float value or throws in case of an invalid variant member access
/// \returns The mutable float value
[[nodiscard]] auto ValueData::float_value() noexcept -> float& {
	return *float_value_;
}

/// \brief Gets an immutable float value or throws in case of an invalid variant member access
/// \returns The immutable float value
[[nodiscard]] auto ValueData::float_value() const noexcept -> float {
	return *float_value_;
}

/// \brief Gets a mutable int value or throws in case of an invalid variant member access
/// \returns The mutable int value
[[nodiscard]] auto ValueData::integer_value() noexcept -> int& {
	return *integer_value_;
}

/// \brief Gets an immutable int value or throws in case of an invalid variant member access
/// \returns The immutable int value
[[nodiscard]] auto ValueData::integer_value() const noexcept -> int {
	return *integer_value_;
}

/// \brief Gets a mutable \sa cui::Vec2f value or throws in case of an invalid variant member access
/// \returns The mutable \sa cui::Vec2f value
[[nodiscard]] auto ValueData::vec2() noexcept -> Vec2f& {
	return *vec2_;
}

/// \brief Gets an immutable \sa cui::Vec2f value or throws in case of an invalid variant member access
/// \returns The immutable \sa cui::Vec2f value
[[nodiscard]] auto ValueData::vec2() const noexcept -> const Vec2f& {
	return *vec2_;
}

/// \brief Gets a mutable \sa cui::Vec3f value or throws in case of an invalid variant member access
/// \returns The mutable \sa cui::Vec3f value
[[nodiscard]] auto ValueData::vec3() noexcept -> Vec3f& {
	return *vec3_;
}

/// \brief Gets an immutable \sa cui::Vec3f value or throws in case of an invalid variant member access
/// \returns The immutable \sa cui::Vec3f value
[[nodiscard]] auto ValueData::vec3() const noexcept -> const Vec3f& {
	return *vec3_;
}

/// \brief Gets a mutable \sa cui::Vec4f value or throws in case of an invalid variant member access
/// \returns The mutable \sa cui::Vec4f value
[[nodiscard]] auto ValueData::vec4() noexcept -> Vec4f& {
	return *vec4_;
}

/// \brief Gets an immutable \sa cui::Vec4f value or throws in case of an invalid variant member access
/// \returns The immutable \sa cui::Vec4f value
[[nodiscard]] auto ValueData::vec4() const noexcept -> const Vec4f& {
	return *vec4_;
}

/// \brief Gets a mutable \sa cui::Instruction value or throws in case of an invalid variant member access
/// \returns The mutable \sa cui::Instruction value
[[nodiscard]] auto ValueData::instruction() noexcept -> Instruction& {
	return *instruction_;
}

/// \brief Gets an immutable \sa cui::Instruction value or throws in case of an invalid variant member access
/// \returns The immutable \sa cui::Instruction  value
[[nodiscard]] auto ValueData::instruction() const noexcept -> const Instruction& {
	return *instruction_;
}

/// \brief Gets a mutable \sa std::string value or throws in case of an invalid variant member access
/// \returns The mutable \sa std::string value
[[nodiscard]] auto ValueData::string() noexcept -> std::string& {
	return *string_;
}

/// \brief Gets an immutable \sa std::string value or throws in case of an invalid variant member access
/// \returns The immutable \sa std::string value
[[nodiscard]] auto ValueData::string() const noexcept -> const std::string& {
	return *string_;
}

/// \brief Gets the \sa cui::DataTypes set indicating which variant member is active
/// \returns The \sa cui::DataTypes set indicating which variant member is active
[[nodiscard]] auto ValueData::active() const noexcept -> DataTypes {
	return active_;
}

/// \brief Deletes the current active variant member
/// \details Used when assigning a new value
void ValueData::delete_current_active() {
	switch (active_) {
		case DataTypes::Color: {
			delete rgba_;
			break;
		}
		case DataTypes::Float: {
			delete float_value_;
			break;
		}
		case DataTypes::Int: {
			delete integer_value_;
			break;
		}
		case DataTypes::Vec2: {
			delete vec2_;
			break;
		}
		case DataTypes::Vec3: {
			delete vec3_;
			break;
		}
		case DataTypes::Vec4: {
			delete vec4_;
			break;
		}
		case DataTypes::Instruction: {
			delete instruction_;
			break;
		}
		case DataTypes::String: {
			delete string_;
			break;
		}
		default: {
			// Do nothing
			break;
		}
	}
}

}	 // namespace cui

#endif	  // #define CUI_CT_VALUE_DATA_HPP
