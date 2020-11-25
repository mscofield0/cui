#ifndef CUI_CT_SCENE_HPP
#define CUI_CT_SCENE_HPP

#include <tuple>

#include <compile_time/scenes/block.hpp>
#include <compile_time/string/string_view.hpp>
#include <containers/static_vector.hpp>
#include <utils/as_const.hpp>

namespace cui::ct {

/// \brief Scene class that holds the GUI tree structure
template <std::size_t BlockAmount>
class Scene
{
public:
	using size_type = std::size_t;
	using block_t = scenes::Block;
	using children_t = StaticVector<size_type, BlockAmount>;
	using depth_t = size_type;

	using blocks_t = StaticVector<block_t, BlockAmount>;
	using family_t = StaticVector<children_t, BlockAmount>;
	using depths_t = StaticVector<depth_t, BlockAmount>;

	using tuple_t = std::tuple<block_t&, children_t&, depth_t&>;
	using const_tuple_t = std::tuple<const block_t&, const children_t&, const depth_t&>;

	constexpr Scene() : blocks_{}, children_{}, depths_{} {}

	[[nodiscard]] constexpr auto length() const noexcept -> size_type {
		return blocks_.size();
	}

	[[nodiscard]] constexpr auto blocks() noexcept -> blocks_t& {
		return blocks_;
	}

	[[nodiscard]] constexpr auto blocks() const noexcept -> const blocks_t& {
		return blocks_;
	}

	[[nodiscard]] constexpr auto children() noexcept -> family_t& {
		return children_;
	}

	[[nodiscard]] constexpr auto children() const noexcept -> const family_t& {
		return children_;
	}

	[[nodiscard]] constexpr auto depths() noexcept -> depths_t& {
		return depths_;
	}

	[[nodiscard]] constexpr auto depths() const noexcept -> const depths_t& {
		return depths_;
	}

	[[nodiscard]] constexpr auto index_of_last() const noexcept -> size_type {
		return length() - 1;
	}

	[[nodiscard]] constexpr auto get(const size_type idx) noexcept -> tuple_t {
		return std::tie(blocks_[idx], children_[idx], depths_[idx]);
	}

	[[nodiscard]] constexpr auto get(const size_type idx) const noexcept -> const_tuple_t {
		return std::tie(as_const(blocks_[idx]), as_const(children_[idx]), as_const(depths_[idx]));
	}

	constexpr void add_child_to(const size_type to, const size_type child_idx) {
		children_[to].push_back(child_idx);
	}

private:
	blocks_t blocks_;
	family_t children_;
	depths_t depths_;
};

}	 // namespace cui::ct

#endif	  // CUI_CT_SCENE_HPP