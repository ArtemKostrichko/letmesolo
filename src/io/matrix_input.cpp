#include "io/matrix_input.h"

#include <istream>

#include "core/errors.h"

namespace io {

    core::Matrix MatrixInput::read(std::istream& in) const {
        (void)in;
        throw core::ParseError("MatrixInput::read is not implemented yet");
    }

} // namespace io