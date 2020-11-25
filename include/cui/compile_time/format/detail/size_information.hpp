#ifndef CUI_SIZE_INFORMATION_HPP
#define CUI_SIZE_INFORMATION_HPP

#include <type_traits>

namespace cui::ct::detail {

template <typename T, typename Enabler = void>
struct SizeInformation
{
	static constexpr std::size_t size = 0;
};

template <typename T>
struct SizeInformation<T, std::enable_if_t<std::is_integral_v<T>>>
{
	static constexpr std::size_t size = std::numeric_limits<T>::digits10 + 1;
};

template <std::size_t N>
struct SizeInformation<const char (&)[N]>
{
	static constexpr std::size_t size = N - 1;
};

template <std::size_t StrSize, typename... Args>
static constexpr std::size_t calculate_buffer_size() {
	return (1 + StrSize + (SizeInformation<Args>::size + ... + 0));
}

}	 // namespace cui::ct::detail

#endif	  // CUI_SIZE_INFORMATION_HPP