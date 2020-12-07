#ifndef STUDENT_RPN_CALCULATOR_H
#define STUDENT_RPN_CALCULATOR_H

#include <memory>
#include <queue>
#include <stack>


namespace s22612 { namespace rpn_calculator {
using stack_type = std::stack<double>;

struct Element {
    virtual auto evaluate(stack_type&) const -> void = 0;
    virtual ~Element();
};

struct Literal : public Element {
    double const value{0.0};

    auto evaluate(stack_type&) const -> void override;

    Literal(double const);
};

struct Print : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Addition : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Subtraction : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Multiplication : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Divide : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Divide_integers : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Divide_modulo : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Exponentiation : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Square_root : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Absolute_value : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Calculator {
    stack_type stack;
    std::queue<std::unique_ptr<Element>> ops;


    auto push(std::unique_ptr<Element>) -> void;

    auto push(std::string) -> void;

    auto evaluate() -> void;

    Calculator() = default;
    Calculator(stack_type);
};
}}  // namespace s22612::rpn_calculator

#endif
