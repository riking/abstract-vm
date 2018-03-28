//
// Created by Kane York on 1/9/18.
//

#include "WrappedError.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace {
const std::string escape_nul(const std::string& s) {
    std::string::const_iterator it = std::find(s.begin(), s.end(), '\0');
    if (it == s.end()) {
        return s;
    }
    const std::string replacement = "\uFFFD";
    const std::string nul_find("\0", 1);
    std::string dest(s);
    size_t start_pos = 0;
    while ((start_pos = dest.find(nul_find, start_pos)) != std::string::npos) {
        dest.replace(start_pos, /* length */ 1, replacement);
        start_pos += replacement.length();
    }
    return dest;
}
}  // namespace

WrappedError::WrappedError() : msg("Empty WrappedError") {
    msg = "Empty WrappedError";
    inner_msg = "";
}

WrappedError::~WrappedError() {}

WrappedError::WrappedError(const std::exception& wrapped) {
    std::stringstream ss;
    const char* inner = wrapped.what();
    this->inner_msg = inner;
    ss << "Error: " << this->inner_msg;
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
        ss << "\033[1;30m";
        ss << std::setw(4) << tok.GetLine();
        ss << "\033[0m " << escape_nul(tok.GetSource()) << std::endl;
    };

    for (int i = -3; i <= 3; i++) {
        ssize_t idx = (static_cast<ssize_t>(lineno) + i) - 1;
        if (idx < 0) {
            continue;
        }
        if (idx >= static_cast<ssize_t>(context.size())) {
            continue;
        }
        const Line& v = context.at(static_cast<size_t>(idx));
        if (i == 0) {
            ss << "\033[1;31m";  // red
        }
        print_line(v.GetSource());
        if (i == 0) {
            ss << "\033[0m";
        }
    }
    const char* inner = wrapped.what();
    this->inner_msg = inner;
    ss << inner;
    this->msg = ss.str();
}

WrappedError::WrappedError(const std::string& what, const Token& line_token, const Token& phrase,
                           const std::vector<Line>& context) {
    std::stringstream ss;
    size_t lineno = line_token.GetLine();

    ss << "Error on line " << lineno << ":" << std::endl;

    // lambdas are fun!
    auto print_line = [&ss](const Token& tok) {
        ss << "\033[1;30m";
        ss << std::setw(4) << tok.GetLine();
        ss << "\033[0m " << escape_nul(tok.GetSource()) << std::endl;
    };

    // Pre-context lines
    for (int i = -3; i <= -1; i++) {
        ssize_t idx = (static_cast<ssize_t>(lineno) + i) - 1;
        if (idx < 0) {
            continue;
        }
        if (idx >= static_cast<ssize_t>(context.size())) {
            continue;
        }
        const Line& v = context.at(static_cast<size_t>(idx));
        print_line(v.GetSource());
    }

    // Print erroring line
    ssize_t col = phrase.GetColumn();
    if (col < 0) {
        print_line(line_token);
    } else {
        size_t len = phrase.GetLength();
        // Print line with colorized token
        const std::string& error_line = line_token.GetSource();
        ss << "\033[1;30m";
        ss << std::setw(4) << phrase.GetLine();
        ss << "\033[0m ";
        ss << escape_nul(error_line.substr(0, (unsigned long)col));
        ss << "\033[1;31m";  // red
        ss << escape_nul(error_line.substr((unsigned long)col, len));
        ss << "\033[0m";
        ss << escape_nul(error_line.substr(col + len, std::string::npos));
        ss << std::endl;

        ss << std::setw(4) << "";
        ss << " ";
        for (ssize_t i = 0; i < col; i++) {
            ss << " ";
        }
        ss << "\033[1;34m";  // blue
        ss << "^";
        for (size_t i = 0; (len > 0) && (i < len - 1); i++) {
            ss << "~";
        }
        ss << "\033[0m";
        ss << std::endl;
    }

    // Post-context lines
    for (int i = 1; i <= 3; i++) {
        ssize_t idx = (static_cast<ssize_t>(lineno) + i) - 1;
        if (idx < 0) {
            continue;
        }
        if (idx >= static_cast<ssize_t>(context.size())) {
            continue;
        }
        const Line& v = context.at(static_cast<size_t>(idx));
        print_line(v.GetSource());
    }
    this->inner_msg = what;
    ss << what;
    this->msg = ss.str();
}

WrappedError::WrappedError(WrappedError const& src) { *this = src; }

WrappedError& WrappedError::operator=(WrappedError const& rhs) {
    this->msg = rhs.msg;
    this->inner_msg = rhs.inner_msg;
    return *this;
}

const char* WrappedError::what() const throw() { return msg.c_str(); }

std::string WrappedError::GetInnerMessage() const { return inner_msg; }
