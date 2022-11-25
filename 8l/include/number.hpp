#pragma once

#include <string>
#include "lexer.hpp"
#include "astnode.hpp"

class Number : public ASTNode {
  public:
    Number(int val)
        : ASTNode(std::to_string(val))
        , val_(val) {}

    int value() const { return val_; }

  private:
    int val_;
};

class Variable : public ASTNode {
public:
    Variable(std::string ch)
        : ASTNode((ch))
        , ch_() {}

    std::string ch() const { return  ch_; }

private:
    std::string ch_;
};
