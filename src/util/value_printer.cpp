#include "util/value_printer.h"

#include <ostream>
#include <variant>

#include "io/matrix_print.h"

namespace util {

    void printValue(std::ostream& out, const Value& value) {
        std::visit(
            [&out](const auto& v) {
                using T = std::decay_t<decltype(v)>;

                if constexpr (std::is_same_v<T, core::Matrix>) {
                    io::MatrixPrinter printer;
                    printer.print(out, v);
                } else {
                    out << v << '\n';
                }
            },
            value
        );
    }

} // namespace util