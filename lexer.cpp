#include "lexer.h"
#include "error.h"
#include <iostream>    // redundant: in lexer.h
#include <cctype>

Lexer::Token_stream Lexer::ts {std::cin};

namespace Lexer {

    Token Token_stream::get() {
        char ch = 0;
        // operator >>, automatically increase 'ip'
        //*ip>>ch;

        do {
            // get() does not skip whitespace, while >> does.
            // get() read a single character from the input stream *ip into 'ch'
            if (!ip->get(ch)) return ct={Kind::end};
        } while (ch!='\n' && isspace(ch));

        switch (ch) {
            // cases: end of input,  operator,  a punctuation character, a number
            //        default case-- name
            //
            //
            // By default, operator >> skips whitespace (that is, spaces, tabs, newlines, etc.)
            // and leaves the value of input stream
            // Consequently, ch==0 indicates end-of-input.
            case 0:
                return ct={Kind::end}; // assign and return

            case ';': // end of expression; print
            case '\n':
                return ct={Kind::print};

            case '*':
            case '/':
            case '+':
            case '-':
            case '(':
            case ')':
            case '=': // explicit convertion from 'char' to 'Kind'
                return ct={static_cast<Kind>(ch)};
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case '.':
                ip->putback(ch);  // put the first digit (or .) back into the input stream
                *ip >> ct.number_value;  // read number into ct
                ct.kind=Kind::number;
                return ct;
            default:  // name, name =, or error
                /*	if (isalpha(ch)) {
                        ip->putback(ch);  // put the first character back into the input stream
                        *ip>>ct.string_value;  // read string(until whitespace) into ct
                        ct.kind=Kind::name;
                        return ct;
                    }*/
                // >> will read the string until whitespace
                // but ch did not change
                if (isalpha(ch)) {
                    ct.string_value = ch;
                    while (ip->get(ch) && isalnum(ch))
                        // small string optimization
                        ct.string_value += ch; // append ch to end of string_value
                    ip->putback(ch);
                    return ct={Kind::name};
                }

                Error::error("bad token");
                return ct={Kind::print};
        }
    }

}