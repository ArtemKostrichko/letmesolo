#include "util/value_printer.h"

#include <ostream>
#include <variant>

namespace util {

    void printValue(
        std::ostream& out,
        const Value& value,
        std::shared_ptr<const io::MatrixPrinter> printer) {
        std::visit(
            [&out, &printer](const auto& current) {
                using T = std::decay_t<decltype(current)>;

                if constexpr (std::is_same_v<T, core::Matrix>) {
                    printer->print(out, current);
                } else {
                    out << current << '\n';
                }
            },
            value);
    }

} // namespace util