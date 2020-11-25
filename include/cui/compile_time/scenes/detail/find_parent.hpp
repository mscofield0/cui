#ifndef CUI_CT_SCENES_FIND_PARENT_HPP
#define CUI_CT_SCENES_FIND_PARENT_HPP

#include <cstdint>

#include <containers/static_stack.hpp>

namespace cui::ct::scenes::detail {

template <std::size_t StackSize, typename Container>
constexpr auto find_parent(StaticStack<std::size_t, StackSize>& child_stack, Container& depths, std::size_t current_block_idx) -> std::size_t {
	while (!child_stack.empty()) {
		if (depths[child_stack.top()] == depths[current_block_idx] - 1) {
			return child_stack.top();
		} else {
			child_stack.pop();
		}
	}
	return depths.size();
}

}	 // namespace cui::ct::scenes::detail

#endif	  // CUI_CT_SCENES_FIND_PARENT_HPP