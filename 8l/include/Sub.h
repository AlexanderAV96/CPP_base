#pragma once

#include "astnode.hpp"

class Sub :
    public ASTNode
{
public:
   
    
    Sub(ASTNode* lhs, ASTNode* rhs) :ASTNode("-", lhs, rhs)
    {};
   // ~Sub();
  //  std::string repr() const { return "-"; }
    

};

class Add :
    public ASTNode
{
public:
    Add(ASTNode* lhs, ASTNode* rhs) :ASTNode("+", lhs, rhs)
    {};
   // ~Add();

   // std::string repr() const { return "+"; }

    

};
class Mul :
    public ASTNode
{
public:
    Mul(ASTNode* lhs, ASTNode* rhs) :ASTNode("*", lhs, rhs)
    {};
    //~Mul();

    std::string repr() const { return "*"; }

    

};
class Div :
    public ASTNode
{
public:
    Div(ASTNode* lhs, ASTNode* rhs) :ASTNode("/", lhs, rhs)
    {};
   // ~Div();

    std::string repr() const { return "/"; }

    

};