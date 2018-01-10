//
// Created by Kane York on 1/9/18.
//

#include <sstream>
#include <iomanip>
#include "WrappedError.hpp"

WrappedError::WrappedError() : msg("Empty WrappedError") {
    msg = "Empty WrappedError";
}

WrappedError::~WrappedError() {}

WrappedError::WrappedError(std::exception wrapped) {
    std::stringstream ss;
    ss << "Error: " << wrapped.what();
    this->msg = ss.str();
}

WrappedError::WrappedError(std::exception wrapped, std::string error_line, int lineno) {
    std::stringstream ss;
    ss << "Error on line " << lineno << ":" << std::endl;
    ss << std::setw(4) << lineno;
    ss << " " << error_line << std::endl;
    ss << wrapped.what();
    this->msg = ss.str();
}

WrappedError::WrappedError(std::exception wrapped, std::string error_line, Token phrase) {
    std::stringstream ss;

    signed long col = phrase.GetColumn();
    if (col < 0) {
        ss << "Error on line " << phrase.GetLine() << " at '" << phrase.GetSource() << "':" << std::endl;
        ss << std::setw(4) << phrase.GetLine();
        ss << " " << error_line << std::endl;
    } else {
        unsigned long len = phrase.GetLength();
        ss << std::setw(4) << phrase.GetLine();
        ss << " ";
        ss << error_line.substr(0, (unsigned long)col);
        ss << "\027[1;31m"; // red
        ss << error_line.substr((unsigned long)col, len);
        ss << "\027[0m";
        ss << error_line.substr(col + len, std::string::npos);
        ss << std::endl;

        ss << std::setw(4) << "";
        ss << " ";
        for (int i = 0; i < col; i++) {
            ss << " ";
        }
        ss << "\027[1;34m"; // blue
        ss << "^";
        for (int i = 0; i < len - 1; i++) {
            ss << "~";
        }
        ss << "\027[0m";
        ss << std::endl;
    }
    ss << wrapped.what();
    this->msg = ss.str();
}

WrappedError::WrappedError(WrappedError const &src) {
    *this = src;
}

WrappedError &WrappedError::operator=(WrappedError const &rhs) {
    this->msg = rhs.msg;
    return *this;
}

const char *WrappedError::what() const throw() {
    return msg.c_str();
}
