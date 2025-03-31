#pragma once

#include <Exceptions.hpp>
#include <Scanner.hpp>
#include <Types.hpp>

class Unit : public Expression
{
public:
    Unit() noexcept;

    std::shared_ptr<Expression> eval(Environment&) const override;

    std::string to_string() const noexcept override;
};

class Int : public Expression
{
public:
    Int(int _value) noexcept;

    std::shared_ptr<Expression> eval(Environment&) const override;

    std::string to_string() const noexcept override;

    int get_value() const noexcept;

private:
    int value;
};

class Id : public Expression
{
public:
    Id(const std::string& _value) noexcept;

    std::shared_ptr<Expression> eval(Environment&) const override;

    std::string to_string() const noexcept override;

    const std::string& get_value() const noexcept;

private:
    std::string value;
};

class IsUnit : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Pair : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Fst : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Snd : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Neg : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Add : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Mul : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Div : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Mod : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class IfLesser : public BinaryExpression
{
public:
    IfLesser(std::shared_ptr<Expression> _left_expression, std::shared_ptr<Expression> _right_expression, std::shared_ptr<Expression> _true_expression, std::shared_ptr<Expression> _false_expression) noexcept;
        
    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;

private:
    std::shared_ptr<Expression> true_expression;
    std::shared_ptr<Expression> false_expression;
};

class Val : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Var : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Let : public BinaryExpression
{
public:
    Let(std::shared_ptr<Expression> _var_name, std::shared_ptr<Expression> _var_expression, std::shared_ptr<Expression> _body_expression) noexcept;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;

private:
    std::shared_ptr<Expression> body_expression;
};

class Fun : public UnaryExpression
{
public:
    Fun(std::shared_ptr<Expression> _function_name, std::shared_ptr<Expression> _parameter_name, std::shared_ptr<Expression> _body_expression) noexcept;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;

    const std::string& get_name() const noexcept;

    const std::string get_parameter_name() const noexcept;

    std::shared_ptr<Expression> get_body_expression() const noexcept;

private:
    std::shared_ptr<Expression> function_name;
    std::shared_ptr<Expression> parameter_name;
};

class Call : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;

    std::string to_string() const noexcept override;
};

class Parser
{
public:
    static std::shared_ptr<Expression> parse(std::string_view program);
};
