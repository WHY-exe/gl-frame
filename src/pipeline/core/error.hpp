#pragma once
#include <system_error>
#include <tl/expected.hpp>


#include <spdlog/fmt/bundled/format.h>

struct Error {
	std::error_code code;
	std::string		extra_info;
};

template <typename T>
using Result = tl::expected<T, Error>;

template <>
class fmt::formatter<Error> {
public:
	constexpr auto parse(fmt::format_parse_context& context) {
		auto	   iter{ context.begin() };
		const auto end{ context.end() };
		if (iter != end && *iter != '}') {
			throw fmt::format_error{ "Invalid gl::Error format specifier." };
		}

		return iter;
	};

	auto format(const Error& gl_error, fmt::format_context& context) const {
		if (gl_error.extra_info.empty()) {
			return fmt::format_to(context.out(), "[{}]", gl_error.code.message());
		}
		return fmt::format_to(context.out(), "[{}] {}", gl_error.code.message(), gl_error.extra_info);
	}
};

#define RET_IF_ERROR(expected)                             \
	{                                                      \
		const auto& exp_ref = expected;                    \
		if (!(exp_ref)) {                                  \
			return tl::make_unexpected((exp_ref).error()); \
		}                                                  \
	}
