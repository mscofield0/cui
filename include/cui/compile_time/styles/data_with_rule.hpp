#ifndef CUI_CT_STYLES_DATA_WITH_RULE_HPP
#define CUI_CT_STYLES_DATA_WITH_RULE_HPP

#include <compile_time/value_data.hpp>
#include <compile_time/styles/detail/values/value_type.hpp>

namespace cui::ct::styles {

class DataWithRule
{
public:
	constexpr DataWithRule(const ValueData& p_data, const ValueType p_type) : data_(p_data), type_(p_type) {}

	constexpr auto data() noexcept -> ValueData& {
		return data_;
	}

	constexpr auto data() const noexcept -> const ValueData& {
		return data_;
	}

	constexpr auto preprocessed_type() noexcept -> ValueType& {
		return type_;
	}

	constexpr auto preprocessed_type() const noexcept -> ValueType {
		return type_;
	}

private:
	ValueData data_;
	ValueType type_;
};

}	 // namespace cui::ct::styles

#endif	  // CUI_CT_STYLES_DATA_WITH_RULE_HPP