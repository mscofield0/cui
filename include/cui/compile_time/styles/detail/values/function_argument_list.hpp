#ifndef CUI_CT_STYLES_FUNCTION_ARGUMENT_LIST_HPP
#define CUI_CT_STYLES_FUNCTION_ARGUMENT_LIST_HPP

#include <compile_time/format/fmt.hpp>
#include <compile_time/format/fmt_string_view.hpp>
#include <compile_time/format/format.hpp>
#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/data_with_rule.hpp>
#include <compile_time/styles/parse_attribute_value.hpp>
#include <compile_time/value_data.hpp>
#include <compile_time/variant/variant.hpp>
#include <containers/static_vector.hpp>

namespace cui::ct::styles::detail {

constexpr auto parse_attribute_value(const StringView str) -> Variant<DataWithRule, Format<256>>;

class FunctionArgumentList
{
public:
	using values_t = StaticVector<ValueData, 32>;
	using reference = values_t&;
	using const_reference = const values_t&;

	constexpr FunctionArgumentList() : list_{} {}

	[[nodiscard]] constexpr auto list() noexcept -> reference {
		return list_;
	}

	[[nodiscard]] constexpr auto list() const noexcept -> const_reference {
		return list_;
	}

	constexpr void add_argument(const ValueData& arg) {
		list().push_back(arg);
	}

	static constexpr auto parse(const StringView str) -> Variant<FunctionArgumentList, Format<256>> {
		FunctionArgumentList fal;
		if (str.empty()) return fal;

		std::size_t prev = 0;
		std::size_t pos = str.find(',');
		while (pos != StringView::npos) {
			if (prev == pos) {
				return fmt_s<256>("ERROR: Function argument list is invalid\n\tList: {}", str);
			}
			const auto substr = str.substr(prev, pos - prev);
			const auto trimmed = substr.trim();
			auto variant_val = parse_attribute_value(trimmed);
			if (variant_val.is_type_b()) {
				return variant_val.type_b();
			}
			fal.add_argument(variant_val.type_a().data());
			prev = pos + 1;
			pos = str.find(',', prev);
		}

		if (prev == pos) {
			return fmt_s<256>("ERROR: Function argument list is invalid\n\tList: {}", str);
		}
		const auto substr = str.substr(prev, pos - prev);
		const auto trimmed = substr.trim();
		auto variant_val = parse_attribute_value(trimmed);
		if (variant_val.is_type_b()) {
			return variant_val.type_b();
		}
		fal.add_argument(variant_val.type_a().data());
		return fal;
	}

private:
	values_t list_;
};

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_STYLES_DETAIL_FUNCTION_ARGUMENT_LIST_HPP