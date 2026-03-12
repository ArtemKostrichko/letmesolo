#pragma once

#include <string>
#include <variant>

#include "core/matrix.h"

namespace util {

    using Value = std::variant<core::Matrix, double, int, std::string>;

} // namespace util