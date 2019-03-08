#include "parser.h"
#include "lexer.h"  // to be able to set ts
#include "error.h"
#include "table.h" // to be able to predefine names
#include <sstream> // to be able to put main()’s arguments into a string stream
#include <vector>
#include <string>

namespace Driver {
    using std::vector;
    using std::string;
    vector<string> arguments(int argc, char* argv[]) {
        vector<string> res;
        for (int i = 0; i!=argc; ++i)
            res.push_back(argv[i]);
        return res;
    }

    void calculate() {
        using Lexer::ts;
        for (;;) {
            ts.get();

            using Lexer::Kind;
            if (ts.current().kind == Kind::end) break;
            if (ts.current().kind == Kind::print) continue;

            std::cout << Parser::expr(false) << '\n';
        }
    }
}

int main(int argc, char* argv[]) {
    //Lexer::Token_stream ts (std::cin);
    switch (argc) {
        // caculator quit from the cin is  Ctrl-C (naive) @TODO
        case 1:          // read from standard input
            break;
        case 2: {        // read from argument string
            //Lexer::ts = std::cin;
            //Lexer::Token_stream ts (std::cin);
            auto arg_vec = Driver::arguments(argc, argv);
            Lexer::ts.set_input(new std::istringstream{arg_vec[1]});
            break;
        }
        default:
            Error::error("too many arguments");
            return 1;
    }

    Table::table["pi"] = 3.1415926535897932385; // insert predefined names
    Table::table["e"] = 2.7182818284590452354;
    Driver::calculate();
    return Error::no_of_errors;
}