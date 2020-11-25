#ifndef CUI_NARY_TREE_NODE_HPP
#define CUI_NARY_TREE_NODE_HPP

#include <vector>

#include <aliases.hpp>

namespace cui::nary {

template <typename T>
class Node
{
public:
	using data_type = T;
	using size_type = std::size_t;
	using vec_t = std::vector<size_type>;

	Node() = default;
	Node(const data_type& val) : data_(val), depth_(0) {}
	Node(const data_type& val, const vec_t& p_children, const size_type p_depth)
		: data_(val), children_(p_children), depth_(p_depth) {}

	[[nodiscard]] auto data() noexcept -> data_type& {
		return data_;
	}

	[[nodiscard]] auto data() const noexcept -> const data_type& {
		return data_;
	}

	[[nodiscard]] auto children() noexcept -> vec_t& {
		return children_;
	}

	[[nodiscard]] auto children() const noexcept -> const vec_t& {
		return children_;
	}

	[[nodiscard]] auto depth() noexcept -> size_type& {
		return depth_;
	}

	[[nodiscard]] auto depth() const noexcept -> size_type {
		return depth_;
	}

	void add_child(const size_type index) {
		children_.push_back(index);
	}

private:
	data_type data_;
	vec_t children_;
	size_type depth_;
};

}	 // namespace cui::nary

#endif	  // CUI_NARY_TREE_NODE_HPP