#pragma once
#include <cstdint>
#include "error.hpp"
#include "util/macro.h"

class Bindable {
protected:
    uint32_t handle_  = 0;
    bool     is_init_ = false;

protected:
    inline uint32_t GetID() noexcept {
        return handle_;
    }

public:
    virtual Result<void> Bind() noexcept = 0;

    Bindable() noexcept          = default;
    virtual ~Bindable() noexcept = default;

    Bindable &operator=(Bindable &&rhs) noexcept {
        handle_      = rhs.handle_;
        is_init_     = rhs.is_init_;
        rhs.handle_  = 0;
        rhs.is_init_ = false;
        return *this;
    }
    Bindable(Bindable &&rhs) noexcept {
        *this = std::move(rhs);
    }

private:
    DEL_COPY_CTOR(Bindable);
};
