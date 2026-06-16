#include <pybind11/pybind11.h>

#include "twopow/twopow.hpp"

namespace py = pybind11;

PYBIND11_MODULE(pytwopow, m) {
    m.doc() = "Deterministic base-2 exponentiation (Python binding for twopow).";

    py::register_exception<twopow::overflow_error>(m, "OverflowError",
                                                   PyExc_OverflowError);

    m.def("two_pow", &twopow::two_pow, py::arg("n"),
          "Return 2 ** n as an integer, for 0 <= n <= 63. "
          "Raises OverflowError for n > 63.");

    m.attr("MAX_EXPONENT") = twopow::kMaxExponent;
    m.attr("DEFAULT_EXPONENT") = twopow::kDefaultExponent;
    m.attr("__version__") = "0.1.0";
}
