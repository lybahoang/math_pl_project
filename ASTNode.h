#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <vector>
#ifndef AST_NODE_H
#define AST_NODE_H

class ASTNode {
public:
    virtual void print(int indent = 0) = 0;
    virtual ~ASTNode() { };
};

/** ---------------------------------------------------------------------------
    The class to represent an abstract syntax tree for binary operators
    expression.
 ------------------------------------------------------------------------------*/
class BinaryOperationNode : public ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> left, right;

    BinaryOperationNode(const std::string &op,
                        std::unique_ptr<ASTNode> l,
                        std::unique_ptr<ASTNode> r)
        : op{ op }, left{ std::move(l) }, right{ std::move(r) } { }

    void print(int indent) override {
        std::cout << "BinaryOperationNode" << std::endl;
        left->print(indent + 5);
        std::cout << std::setw(indent) << op << std::endl;
        right->print(indent + 5);
    }
};

class UnaryOperationNode : public ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> operand;

    UnaryOperationNode(const std::string &op, std::unique_ptr<ASTNode> expr)
        : op{ op }, operand{ std::move(expr) } { }

    void print(int indent) override {
        std::cout << "UnaryOperationNode" << std::endl;
        std::cout << std::setw(indent) << op << std::endl;
        operand->print(indent + 5);
    }
};

class VariableDeclarationNode : public ASTNode {
    std::string name;
    std::unique_ptr<ASTNode> expr;

    VariableDeclarationNode(const std::string &name, std::unique_ptr<ASTNode> expr)
        : name{ name }, expr{ std::move(expr) } { }

    void print(int indent) override {
        std::cout << "VariableDeclarationNode" << std::endl;
        std::cout << std::setw(indent) << name << std::endl;
        std::cout << "=" << std::endl;
        expr->print(indent + 5);
    }
};

class AssignmentNode : public ASTNode {
    std::string name;
    std::unique_ptr<ASTNode> expr;

    AssignmentNode(const std::string &name, std::unique_ptr<ASTNode> expr)
        : name{ name }, expr{ std::move(expr) } { }

    void print(int indent) override {
        std::cout << "AssignmentNode" << std::endl;
        std::cout << std::setw(indent) << name << std::endl;
        std::cout << "=" << std::endl;
        expr->print(indent + 5);
    }
};


class FunctionDeclarationNode : public ASTNode {
    std::string name;
    std::string parameter;
    std::unique_ptr<ASTNode> expr;

    FunctionDeclarationNode(const std::string &name,
                            const std::string &para,
                            std::unique_ptr<ASTNode> expr)
        : name{ name }, parameter{ para }, expr{ std::move(expr) } { }

    void print(int indent) override {
        std::cout << "FunctionDeclarationNode" << std::endl;
        std::cout << std::setw(indent) << name << std::endl;
        std::cout << std::setw(indent) << parameter << std::endl;
        std::cout << "=" << std::endl;
        expr->print(indent + 5);
    }
};


class PrintNode : public ASTNode {
    std::unique_ptr<ASTNode> expr;

    PrintNode(std::unique_ptr<ASTNode> expr) : expr{ std::move(expr) } { }
    void print(int indent) override {
        std::cout << "PrintNode" << std::endl;
        expr->print(indent + 5);
    }
};

class VariableNode : public ASTNode {
    std::string name;

    VariableNode(const std::string &name) : name{ name } { }
    void print(int indent) override {
        std::cout << "VariableNode" << std::endl;
        std::cout << std::setw(indent) << name << std::endl;
    }
};

class NumberNode : public ASTNode {
    double value;
    NumberNode(double v) : value{ v } { }
    void print(int indent) override {
        std::cout << "NumberNode" << std::endl;
        std::cout << std::setw(indent) << value << std::endl;
    }
};

class FunctionCallNode : public ASTNode {
    std::string name;
    std::vector<std::unique_ptr<ASTNode>> arguments;

    FunctionCallNode(const std::string &name,
                     std::vector<std::unique_ptr<ASTNode>> args)
        : name{ name }, arguments{ std::move(args) } { }

    void print(int indent) override {
        std::cout << "FunctionCallNode" << std::endl;
        std::cout << std::setw(indent) << name << std::endl;
        for (const auto& arg : arguments)
            arg->print(indent);
    }
};
#endif