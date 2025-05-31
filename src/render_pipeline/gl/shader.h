#pragma once
#include "core/bindable.h"
#include "util/macro.h"
#include <cstdint>
#include <filesystem>
#include <string_view>

namespace gl {

enum class ShaderType : uint16_t {
	UNKNOWN	 = 0x0000,
	VERTEX	 = 0x8B31,
	FRAGMENT = 0x8B30,
	GEOMETRY = 0x8DD9
};

class Shader : public Bindable {
private:
	uint32_t   program_;
	ShaderType type_;

public:
	DEFAULT_MOVE_CTOR(Shader);
	~Shader() noexcept override;

	static Result<Shader> New(uint32_t program, const std::filesystem::path& shader_path);
	static Result<Shader> New(uint32_t program, ShaderType type,
			const std::string_view& shader_src);

	Result<void> Bind() noexcept final;
	void		 Destroy() noexcept;

private:
	Result<void> InitFromFile(const std::filesystem::path& shader_path);
	Result<void> InitFromSrc(const std::string_view& shader_src) noexcept;

private:
	Shader() noexcept = default;
	DEL_COPY_CTOR(Shader);
};

} // namespace gl
