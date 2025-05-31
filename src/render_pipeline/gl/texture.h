#pragma once
#include "core/bindable.h"
#include "util/image_loader.h"
#include "util/macro.h"
#include <cstdint>
#include <vector>
namespace gl {
class Texture2D : public Bindable {
public:
    struct Filter {
        int name;
        int type;
    };

private:
    int32_t num_ = 0;

public:
    DEFAULT_MOVE_CTOR(Texture2D);
    static Result<Texture2D> New(int num = 1) noexcept;

    ~Texture2D() noexcept override;
    Result<void> Bind() noexcept override;
    Result<void> SetParam(const std::vector<Filter> &filters) noexcept;
    Result<void> SetData(const util::ImageLoader &loader) noexcept;
private:
    DEL_COPY_CTOR(Texture2D);
    Texture2D() noexcept = default;
};
} // namespace gl