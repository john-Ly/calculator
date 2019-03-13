//
// Created by john on 2018/5/10.
//

#include "parser.h"
#include "lexer.h"  // to be able to set ts
#include "error.h"
#include "table.h" // to be able to predefine names
#include <sstream> // to be able to put main()’s arguments into a string stream

namespace Parser {
    using Lexer::ts;
    using Lexer::Kind;
    using Error::error;
    using Table::table;

    // handle primaries
    double prim(bool get) {
        if (get) ts.get(); // read next token
        switch (ts.current().kind) {

            case Kind::number: { // floating-point constant
                double v = ts.current().number_value;
                ts.get();
                return v;
            } case Kind::name: {
                // & means sync/share the value between table and v
                double& v = table[ts.current().string_value];  // find the corresponding
                if (ts.get().kind == Kind::assign) v = expr(true);  // '=' seen: assignment
                return v;
            } case Kind::minus:  // unar y minus
                return -prim(true);
            case Kind::lp: {
                double e = expr(true);
                if (ts.current().kind != Kind::rp) return error("')' expected");
                ts.get(); // eat ')'
                return e;
            } default:
                return error("primary expected");
        }
    }

    double expr(bool get) {
        double left = term(get);
        for (;;) {
            switch (ts.current().kind) {
                case Kind::plus:
                    left += term(true);
                    break;
                case Kind::minus:
                    left -= term(true);
                    break;
                default:
                    return left;
            }
        }
    }

    double term(bool get) {
        double left = prim(get);
        for (;;) {
            switch (ts.current().kind) {
                case Kind::mul:
                    left *= prim(true);
                    break;
                case Kind::div:
                    if (auto d = prim(true)) {
                        left /= d;
                        break;
                    }
                    return error("divide by 0");
                default:
                    return left;
            }
        }
    }
} // namespace parser