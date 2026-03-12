#pragma once

#include <iosfwd>

#include "util/value.h"

namespace util {

    void printValue(std::ostream& out, const Value& value);

} // namespace util