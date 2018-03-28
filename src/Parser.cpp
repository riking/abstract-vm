//
// Created by Kane York on 1/10/18.
//

#include "Parser.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "Double.hpp"
#include "Float.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Int8.hpp"

Parser::Parser() : is_stdin(false), input(NULL) {}

Parser::Parser(Parser const &src) {
    this->is_stdin = src.is_stdin;
    this->input = src.input;
}

Parser::~Parser() {
    // do not delete input
}

Parser &Parser::operator=(Parser const &rhs) {
    this->is_stdin = rhs.is_stdin;
    this->input = rhs.input;
    return *this;
}

std::unique_ptr<std::vector<Line>> Parser::ParseProgram(std::istream &input,
                                                        bool is_stdin) throw(WrappedError) {
    this->input = &input;
    this->is_stdin = is_stdin;

    auto full_source = std::make_unique<std::vector<Line>>();
    std::string cur_line;
    size_t lineno = 0;

    while (std::getline(input, cur_line)) {
        lineno++;

        const Token line_token(lineno, cur_line);
        try {
            const Line &line = ParseLine(line_token);
            full_source->push_back(line);
        } catch (ParseError e) {
            std::cout << "Parse error. Message: " << e.GetMessage() << std::endl;
            throw WrappedError(e.GetMessage(), line_token, e.GetToken(), *(full_source.get()));
        } catch (std::exception e) {
            throw WrappedError(e, line_token, *(full_source.get()));
        }
    }
    if (input.bad()) {
        throw WrappedError(StaticError("I/O Error"));
    }
    return full_source;
}

Line Parser::ParseLine(const Token &line_token) throw(ParseError) {
    std::unique_ptr<const Token> trimmed = TrimCommentsAndSpaces(&line_token);
    if (trimmed->GetLength() == 0) {
        return Line(line_token);
    }
    std::unique_ptr<const Token> instr = GetFirstWord(trimmed.get());
    eInstructionType instr_type = RecognizeInstruction(instr.get());  // throws instr

    switch (instr_type) {
        case eInstructionType::ASSERT:
        case eInstructionType::PUSH: {
            const IOperand *op = ParseOperand(trimmed.get(), instr->GetLength());
            return Line(line_token, *trimmed, instr_type, op);
        }
        default:
            return Line(line_token, *trimmed, instr_type);
    }
}

const IOperand *Parser::ParseOperand(const Token *trimmed_line,
                                     size_t instr_len) throw(ParseError) {
    std::unique_ptr<const Token> second_part_notrim =
        trimmed_line->SubToken(instr_len, trimmed_line->GetLength() - instr_len);
    std::unique_ptr<const Token> second_part = TrimSpace(second_part_notrim.get());
    if (second_part->GetLength() == 0) {
        throw ParseError(second_part.get(), "Instruction requires an operand, none given");
    }

    const std::string &s = second_part->GetSource();
    std::string::const_iterator lparen = std::find(s.begin(), s.end(), '(');
    std::string::const_iterator rparen = std::find(s.begin(), s.end(), ')');
    if (lparen == s.end() || rparen == s.end()) {
        throw ParseError(second_part.get(), "Could not find operand, should be type(123.45)");
    }
    if (rparen != s.end() - 1) {
        std::unique_ptr<const Token> after_paren =
            second_part->SubToken(rparen - s.begin(), s.end() - rparen);
        throw ParseError(after_paren.get(), "Extra content after close parenthesis");
    }
    std::unique_ptr<const Token> type = second_part->SubToken(0, lparen - s.begin());
    std::unique_ptr<const Token> value =
        second_part->SubToken((lparen + 1) - s.begin(), rparen - (lparen + 1));
    if (type->GetLength() == 0) {
        throw ParseError(type.get(), "Missing operand type, should be type(123.45)");
    }
    if (value->GetLength() == 0) {
        throw ParseError(value.get(), "Missing operand value, should be type(123.45)");
    }

    eOperandType op_type = RecognizeOperand(type.get());
    const IOperand *op = MakeOperand(op_type, value.get());

    return op;
}

eOperandType Parser::RecognizeOperand(const Token *type) throw(ParseError) {
    const std::string &op_type_str = type->GetSource();
    if (op_type_str == "int8") {
        return eOperandType::INT_8;
    } else if (op_type_str == "int16") {
        return eOperandType::INT_16;
    } else if (op_type_str == "int32") {
        return eOperandType::INT_32;
    } else if (op_type_str == "float") {
        return eOperandType::FLOAT;
    } else if (op_type_str == "double") {
        return eOperandType::DOUBLE;
    } else {
        std::cerr << "RecognizeOperand parse error" << std::endl;
        throw ParseError(type,
                         "Unrecognized operand type, expecting: int8 int16 "
                         "int32 float double");
    }
}

const IOperand *Parser::MakeOperand(eOperandType op_type, const Token *value) throw(ParseError) {
    size_t val_end_idx = 0;

    switch (op_type) {
        case eOperandType::INT_8:
        case eOperandType::INT_16:
        case eOperandType::INT_32: {
            long long val_ll;
            try {
                val_ll = std::stoll(value->GetSource(), &val_end_idx);
            } catch (std::invalid_argument) {
                throw ParseError(value, "Failed to parse integer");
            } catch (std::out_of_range) {
                throw ParseError(value, "Value out of range for integer");
            }
            if (val_end_idx != value->GetLength()) {
                throw ParseError(value, "Extra content after numeric value");
            }
            switch (op_type) {
                case eOperandType::INT_8:
                    if (val_ll < std::numeric_limits<int8_t>::min() ||
                        val_ll > std::numeric_limits<int8_t>::max()) {
                        throw ParseError(value, "Value out of range for int8");
                    }
                    return new Int8((int8_t)val_ll);
                case eOperandType::INT_16:
                    if (val_ll < std::numeric_limits<int16_t>::min() ||
                        val_ll > std::numeric_limits<int16_t>::max()) {
                        throw ParseError(value, "Value out of range for int16");
                    }
                    return new Int16((int16_t)val_ll);
                case eOperandType::INT_32:
                    if (val_ll < std::numeric_limits<int32_t>::min() ||
                        val_ll > std::numeric_limits<int32_t>::max()) {
                        throw ParseError(value, "Value out of range for int32");
                    }
                    return new Int32((int32_t)val_ll);
                default:
                    assert(false);
            }
        }
        case eOperandType::FLOAT: {
            float val_f;
            try {
                val_f = std::stof(value->GetSource(), &val_end_idx);
            } catch (std::invalid_argument) {
                throw ParseError(value, "Failed to parse float");
            } catch (std::out_of_range) {
                throw ParseError(value, "Value out of range for float");
            }
            if (val_end_idx != value->GetLength()) {
                throw ParseError(value, "Extra content after numeric value");
            }
            return new Float(val_f);
        }
        case eOperandType::DOUBLE: {
            double val_d;
            try {
                val_d = std::stod(value->GetSource(), &val_end_idx);
            } catch (std::invalid_argument) {
                throw ParseError(value, "Failed to parse double");
            } catch (std::out_of_range) {
                throw ParseError(value, "Value out of range for double");
            }
            if (val_end_idx != value->GetLength()) {
                throw ParseError(value, "Extra content after numeric value");
            }
            return new Double(val_d);
        }
        default:
            throw ParseError(value, "Invalid enum for operand type");
    }
}

eInstructionType Parser::RecognizeInstruction(const Token *token) throw(ParseError) {
    const std::string &word = token->GetSource();
    if (this->is_stdin && word == ";;") {
        return eInstructionType::END_OF_FILE;
    } else if (word == "add") {
        return eInstructionType::ADD;
    } else if (word == "assert") {
        return eInstructionType::ASSERT;
    } else if (word == "div") {
        return eInstructionType::DIV;
    } else if (word == "dump") {
        return eInstructionType::DUMP;
    } else if (word == "exit") {
        return eInstructionType::EXIT;
    } else if (word == "mul") {
        return eInstructionType::MUL;
    } else if (word == "mod") {
        return eInstructionType::MOD;
    } else if (word == "pop") {
        return eInstructionType::POP;
    } else if (word == "print") {
        return eInstructionType::PRINT;
    } else if (word == "push") {
        return eInstructionType::PUSH;
    } else if (word == "sub") {
        return eInstructionType::SUB;
    }
    std::cerr << "RecognizeInstruction parse error" << std::endl;
    throw ParseError(token, "Unrecognized instruction");
}

std::unique_ptr<const Token> Parser::TrimSpace(const Token *token) {
    const std::string &s = token->GetSource();
    std::string::const_iterator left_bound =
        std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace)));
    std::string::const_iterator right_bound =
        std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base();
    ssize_t offset = left_bound - s.begin();
    ssize_t len = right_bound - left_bound;

    // e.g "  ", left_bound is on the right and right_bound is on the left
    if (len < 0) {
        return token->SubToken(offset, 0);
    }
    assert(offset >= 0);
    return token->SubToken(offset, len);
}

std::unique_ptr<const Token> Parser::TrimCommentsAndSpaces(const Token *token) {
    const std::string &s = token->GetSource();
    // find first non-space
    std::string::const_iterator left_bound =
        std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace)));
    // find first semicolon
    std::string::const_iterator comment_start = std::find(s.begin(), s.end(), ';');
    auto comment_start_r = std::make_reverse_iterator(comment_start);
    // find last non-space before comment start
    std::string::const_iterator right_bound =
        std::find_if(comment_start_r, s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace)))
            .base();

    ssize_t offset = left_bound - s.begin();
    ssize_t len = right_bound - left_bound;
    if (len <= 0) {
        // check for ;;
        if (this->is_stdin && *(comment_start) == ';' && *(comment_start + 1) == ';') {
            return token->SubToken(comment_start - s.begin(), 2);
        }
        return token->SubToken(offset, 0);
    }
    assert(offset >= 0);
    return token->SubToken(offset, len);
}

std::unique_ptr<const Token> Parser::GetFirstWord(const Token *token) {
    const std::string &s = token->GetSource();
    // find first space
    std::string::const_iterator right_bound =
        std::find_if(s.begin(), s.end(), std::ptr_fun<int, int>(std::isspace));

    // if (right_bound == s.end())
    // still need to make a copy

    ssize_t len = right_bound - s.begin();
    return token->SubToken(0, len);
}
