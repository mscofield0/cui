#ifndef CUI_CT_STREAM_UTILS_HPP
#define CUI_CT_STREAM_UTILS_HPP

#include <utility>

#include <compile_time/stream/stream.hpp>
#include <compile_time/string/string_view.hpp>

namespace cui::ct {

constexpr StringView stream_substr(const CharStream& stream, typename CharStream::iterator from, typename CharStream::iterator to) {
	return stream.data().substr(std::distance(stream.begin(), from), std::distance(from, to));
}

constexpr std::pair<StringView, char> consume(CharStream& stream, StringView delims) {
	auto start_it = stream.current();
	char delim{0};
	while (stream.good()) {
		const auto it = stream.current();
		for (const auto ch : delims) {
			if (*it == ch) {
				delim = ch;
				break;
			}
		}
		if (delim != 0) {
			stream.next();
			return {stream_substr(stream, start_it, it), delim};
		}
		stream.next();
	}
	return {stream_substr(stream, start_it, stream.end()), 0};
}

constexpr StringView consume_line(CharStream& stream) {
	auto start_it = stream.current();
	enum class Newlines
	{
		NoNewline = 0,
		PlainNewline,
		NewlineCarriage,
		CarriageNewline
	};

	while (stream.good()) {
		const auto it = stream.current();

		Newlines sw = Newlines::NoNewline;
		if (*it == '\n') sw = Newlines::PlainNewline;
		if (stream.data().substr(stream.distance()).starts_with("\n\r")) sw = Newlines::NewlineCarriage;
		if (stream.data().substr(stream.distance()).starts_with("\r\n")) sw = Newlines::CarriageNewline;
		if (sw != Newlines::NoNewline) {
			if (sw == Newlines::PlainNewline) stream.next();
			else
			{
				stream.next();
				stream.next();
			}

			return stream_substr(stream, start_it, it);
		}
		stream.next();
	}
	return stream_substr(stream, start_it, stream.end());
}

}	 // namespace cui::ct

#endif	  // CUI_PARSE_UTILS_STREAM_UTILS_HPP