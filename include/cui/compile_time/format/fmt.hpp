#ifndef CUI_CT_FMT_HPP
#define CUI_CT_FMT_HPP

#include <utility>

#include <compile_time/format/detail/consume.hpp>
#include <compile_time/format/detail/size_information.hpp>
#include <compile_time/format/format.hpp>
#include <compile_time/exception/ct_exception.hpp>
#include <compile_time/stream/stream.hpp>
#include <compile_time/string/string_view.hpp>

namespace cui::ct {

template <std::size_t StrSize, typename... Args>
constexpr auto fmt(const char (&s)[StrSize], Args&&... args) -> Format<detail::calculate_buffer_size<StrSize, Args...>()> {
	constexpr auto size = detail::calculate_buffer_size<StrSize, Args...>();
	Format<size> buffer;
	StringView str{s};
	CharStream stream{str};
	((detail::consume_until(buffer, stream), buffer << std::move(args)), ...);
	detail::consume_all(buffer, stream);
	buffer.append('\0');
	return buffer;
}

template <std::size_t MaxSize, std::size_t StrSize, typename... Args>
constexpr auto fmt_s(const char (&s)[StrSize], Args&&... args) -> Format<MaxSize> {
	constexpr auto size = MaxSize;
	Format<size> buffer;
	StringView str{s};
	CharStream stream{str};
	((detail::consume_until(buffer, stream), buffer << std::move(args)), ...);
	detail::consume_all(buffer, stream);
	buffer.append('\0');
	return buffer;
}

template <std::size_t StrSize, typename... Args>
constexpr auto fmt_throw(const char (&s)[StrSize], Args&&... args) -> CTException<detail::calculate_buffer_size<StrSize, Args...>()> {
	constexpr auto size = detail::calculate_buffer_size<StrSize, Args...>();
	Format<size> buffer;
	StringView str{s};
	CharStream stream{str};
	((detail::consume_until(buffer, stream), buffer << std::move(args)), ...);
	detail::consume_all(buffer, stream);
	buffer.append('\0');
	return CTException<size>{buffer};
}

template <std::size_t MaxSize, std::size_t StrSize, typename... Args>
constexpr auto fmt_s_throw(const char (&s)[StrSize], Args&&... args) -> CTException<MaxSize> {
	constexpr auto size = MaxSize;
	Format<size> buffer;
	StringView str{s};
	CharStream stream{str};
	((detail::consume_until(buffer, stream), buffer << std::move(args)), ...);
	detail::consume_all(buffer, stream);
	buffer.append('\0');
	return CTException<size>{buffer};
}

}	 // namespace cui::ct

#endif	  // CUI_CT_FMT_HPP