#pragma once
#include "core/error.hpp"

namespace gl {
enum ERRORCODE : int8_t {
	SHADER_FILE_NOT_FOUND = -100,
	SHADER_ERROR,
	PROGRAM_ERROR,
};

void ClearError() noexcept;

class ErrorCat : public std::error_category {
public:
	static const ErrorCat& Get();

	std::string message(int code) const final;
	const char* name() const noexcept final;
};

Error MakeError(int64_t code, std::string extra = "");

template <typename Func, typename... Args,
		typename = std::enable_if_t<std::is_invocable_v<Func, Args...>>>
constexpr auto CheckError(Func&& GLFx, Args&&... FxArgs) -> Result<std::invoke_result_t<Func, Args...>> {
	using GLFxReturnType = std::invoke_result_t<Func, Args...>;
	ClearError();
	GLenum err = GL_NO_ERROR;
	if constexpr (std::is_void_v<GLFxReturnType>) {
		std::invoke(std::forward<Func>(GLFx), FxArgs...);
		while ((err = glGetError()) != GL_NO_ERROR) {
			return tl::unexpected(MakeError(err));
		}
		return {};
	} else {
		GLFxReturnType func_ret = std::invoke(std::forward<Func>(GLFx), FxArgs...);
		while ((err = glGetError()) != GL_NO_ERROR) {
			return tl::unexpected(MakeError(err));
		}
		return func_ret;
	}
}
} // namespace gl