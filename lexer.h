// For input, the parser uses a Token_stream that encapsulates the reading of characters and their composition into Tokens.
// That is, a Token_stream ‘‘tokenizes’’: it turns streams of characters, such as 123.45 , into Tokens.
// A Token is a {kind-of-token,value} pair, such as {number,123.45} , where the 123.45 has been turned into a floating point value.
// The main parts of the parser need only to know the name of the Token_stream , ts , and how to get Token s from it.
// In addition to providing tokenizing, the Token_stream hides the actual source of the characters. We’ll see that they can come directly from a user typing to cin , from a program command line, or from any other input stream.

#ifndef CACULATOR_LEXER_H
#define CACULATOR_LEXER_H

#include<string>
#include<iostream>

namespace Lexer {
    using std::string;
    using std::istream;

    // use char(underlying type) to represent Kind (scoped enum class)
    enum class Kind : char {
        name, number, end,
        plus='+', minus='-', mul='*', div='/', print=';', assign='=', lp='(', rp=')'
    };

    // @NOTE data_abstraction
    struct Token {
        Kind kind;
        string string_value;
        double number_value;
    };

    // reference semantics
    class noncopyable {
    protected:
        noncopyable() = default;
        ~noncopyable() = default;
    private:
        noncopyable( const noncopyable& ) = delete;
        const noncopyable& operator=( const noncopyable& ) = delete;
    };

    class Token_stream : noncopyable {
    public:
        // @TODO single-argument constructors must be marked explicit to avoid unintentional implicit conversions
        explicit Token_stream(istream& s) : ip{&s}, owns{false}, ct{Kind::end} { }
        explicit Token_stream(istream* p) : ip{p}, owns{true}, ct{Kind::end} { }
        ~Token_stream() { close(); }

        Token get();  // read and return next token
        Token& current(){ return ct; } // most recently read token

        // jump to another stream
        void set_input(istream& s) { close(); ip = &s; owns=false; }
        void set_input(istream* p) { close(); ip = p; owns = true; }

    private:
        // RAII @TODO can be replaced with shared_ptr
        void close() { if (owns) delete ip; }
        istream* ip;  // pointer to an input stream
        bool owns;  // does the Token_stream own the istream?  -- ownership
        Token ct {Kind::end}; // current_token
    };

    extern Token_stream ts;
}

#endif //CACULATOR_LEXER_H
