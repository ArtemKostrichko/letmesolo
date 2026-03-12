#pragma once

#include "io/matrix_print.h"
#include "util/value.h"

#include <iosfwd>
#include <memory>

namespace util {

    void printValue(
        std::ostream& out,
        const Value& value,
        std::shared_ptr<const io::MatrixPrinter> printer);

} // namespace util