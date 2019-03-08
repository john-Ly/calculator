#include "error.h"
// any more #includes or declarations
#include <iostream>

namespace Error {
    int no_of_errors;

    double error(const std::string& s) {
        no_of_errors++;
        // stream cerr is an unbufferd output stream
        std::cerr << "error: " << s << '\n';
        return 1;
    }
}