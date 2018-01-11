//
// Created by Kane York on 1/9/18.
//

#include "WrappedError.hpp"
#include <iomanip>
#include <sstream>

WrappedError::WrappedError() : msg("Empty WrappedError") { msg = "Empty WrappedError"; }

WrappedError::~WrappedError() {}

WrappedError::WrappedError(const std::exception& wrapped) {
    std::stringstream ss;
    ss << "Error: " << wrapped.what();
    this->msg = ss.str();
}

WrappedError::WrappedError(const std::exception& wrapped, const Token& line_token,
                           const std::vector<Line>& context) {
    std::stringstream ss;
    size_t lineno = line_token.GetLine();

    ss << "Error on line " << lineno << ":" << std::endl;

    // lambdas are fun!
    // (this is to encapsulate repeated constructor code)
    auto print_line = [&ss](const Token& tok) {
        ss << std::setw(4) << tok.GetLine();
        ss << " " << tok.GetSource() << std::endl;
    };

    for (int i = -3; i < 0; i++) {
        ssize_t idx = (((ssize_t)lineno) + i) - 1;
        if (idx < 0) {
            continue;
        }
        const Line& v = context.at((size_t)idx);
        print_line(v.GetSource());
    }
    print_line(line_token);
    ss << wrapped.what();
    this->msg = ss.str();
}

WrappedError::WrappedError(const std::string& what, const Token& line_token, const Token& phrase,
                           const std::vector<Line>& context) {
    std::stringstream ss;
    size_t lineno = line_token.GetLine();

    ss << "Error on line " << lineno << ":" << std::endl;

    // lambdas are fun!
    auto print_line = [&ss](const Token& tok) {
        ss << std::setw(4) << tok.GetLine();
        ss << " " << tok.GetSource() << std::endl;
    };

    for (int i = -3; i < 0; i++) {
        ssize_t idx = (((ssize_t)lineno) + i) - 1;
        if (idx < 0) {
            continue;
        }
        const Line& v = context.at((size_t)idx);
        print_line(v.GetSource());
    }

    ssize_t col = phrase.GetColumn();
    if (col < 0) {
        print_line(line_token);
    } else {
        size_t len = phrase.GetLength();
        // Print line with colorized token
        const std::string& error_line = line_token.GetSource();
        ss << std::setw(4) << phrase.GetLine();
        ss << " ";
        ss << error_line.substr(0, (unsigned long)col);
        ss << "\027[1;31m";  // red
        ss << error_line.substr((unsigned long)col, len);
        ss << "\027[0m";
        ss << error_line.substr(col + len, std::string::npos);
        ss << std::endl;

        ss << std::setw(4) << "";
        ss << " ";
        for (int i = 0; i < col; i++) {
            ss << " ";
        }
        ss << "\027[1;34m";  // blue
        ss << "^";
        for (int i = 0; i < len - 1; i++) {
            ss << "~";
        }
        ss << "\027[0m";
        ss << std::endl;
    }
    ss << what;
    this->msg = ss.str();
}

WrappedError::WrappedError(WrappedError const& src) { *this = src; }

WrappedError& WrappedError::operator=(WrappedError const& rhs) {
    this->msg = rhs.msg;
    return *this;
}

const char* WrappedError::what() const throw() { return msg.c_str(); }
