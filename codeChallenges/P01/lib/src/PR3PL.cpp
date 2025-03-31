/**
   @author:
   @id:
*/

#include <PR3PL.hpp>

Unit::Unit() noexcept
{
    // empty
}

std::shared_ptr<Expression> Unit::eval(Environment&) const
{
    // TODO
    return nullptr;
}

std::string Unit::to_string() const noexcept
{
    return "()";
}

Int::Int(int _value) noexcept
    : value{_value}
{
    // empty
}

std::shared_ptr<Expression> Int::eval(Environment&) const
{
    // TODO
    return nullptr;
}

std::string Int::to_string() const noexcept
{
    return "(" + std::to_string(value) + ")";
}

int Int::get_value() const noexcept
{
    return value;
}

Id::Id(const std::string& _value) noexcept
    : value{_value}
{
    // empty
}

std::shared_ptr<Expression> Id::eval(Environment&) const
{
    // TODO
    return nullptr;
}

std::string Id::to_string() const noexcept
{
    return "(" + value + ")";
}

const std::string& Id::get_value() const noexcept
{
    return value;
}

std::shared_ptr<Expression> IsUnit::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string IsUnit::to_string() const noexcept
{
    return "(isunit" + UnaryExpression::get_expression()->to_string() + ")";
}

std::shared_ptr<Expression> Pair::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Pair::to_string() const noexcept
{
    return "(pair"
        + BinaryExpression::get_left_expression()->to_string()
        + BinaryExpression::get_right_expression()->to_string() + ")";
}

std::shared_ptr<Expression> Fst::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Fst::to_string() const noexcept
{
    return "(fst" + UnaryExpression::get_expression()->to_string() + ")";
}

std::shared_ptr<Expression> Snd::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Snd::to_string() const noexcept
{
    return "(snd" + UnaryExpression::get_expression()->to_string() + ")";
}

std::shared_ptr<Expression> Neg::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Neg::to_string() const noexcept
{
    return "(-" + UnaryExpression::get_expression()->to_string() + ")";
}

std::shared_ptr<Expression> Add::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Add::to_string() const noexcept
{
    return "(+" +
        BinaryExpression::get_left_expression()->to_string() +
        BinaryExpression::get_right_expression()->to_string() + ")";
}

std::shared_ptr<Expression> Mul::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Mul::to_string() const noexcept
{
    return "(*" +
        BinaryExpression::get_left_expression()->to_string() +
        BinaryExpression::get_right_expression()->to_string() + ")";
}

std::shared_ptr<Expression> Div::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Div::to_string() const noexcept
{
    return "(/" +
        BinaryExpression::get_left_expression()->to_string() +
        BinaryExpression::get_right_expression()->to_string() + ")";
}

std::shared_ptr<Expression> Mod::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Mod::to_string() const noexcept
{
    return "(%" +
        BinaryExpression::get_left_expression()->to_string() +
        BinaryExpression::get_right_expression()->to_string() + ")";
}

IfLesser::IfLesser(std::shared_ptr<Expression> _left_expression, std::shared_ptr<Expression> _right_expression, std::shared_ptr<Expression> _true_expression, std::shared_ptr<Expression> _false_expression) noexcept
    : BinaryExpression{_left_expression, _right_expression}, true_expression{_true_expression}, false_expression{_false_expression}
{
    // empty
}
    
std::shared_ptr<Expression> IfLesser::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string IfLesser::to_string() const noexcept
{
    return "(iflesser"
        + BinaryExpression::get_left_expression()->to_string()
        + BinaryExpression::get_right_expression()->to_string()
        + true_expression->to_string()
        + false_expression->to_string() + ")";
}

std::shared_ptr<Expression> Val::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Val::to_string() const noexcept
{
    return "(val"
        + BinaryExpression::get_left_expression()->to_string()
        + BinaryExpression::get_right_expression()->to_string() + ")";
}

std::shared_ptr<Expression> Var::eval(Environment& env) const
{  
    // TODO
    return nullptr;
}

std::string Var::to_string() const noexcept
{
    return "(var" + UnaryExpression::get_expression()->to_string() + ")";
}

Let::Let(std::shared_ptr<Expression> _var_name, std::shared_ptr<Expression> _var_expression, std::shared_ptr<Expression> _body_expression) noexcept
    : BinaryExpression{_var_name, _var_expression}, body_expression{_body_expression}
{
    // empty
}

std::shared_ptr<Expression> Let::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Let::to_string() const noexcept
{
    return "(let"
        + BinaryExpression::get_left_expression()->to_string()
        + BinaryExpression::get_right_expression()->to_string()
        + body_expression->to_string() + ")";
}

Fun::Fun(std::shared_ptr<Expression> _function_name, std::shared_ptr<Expression>_parameter_name, std::shared_ptr<Expression> _body_expression) noexcept
    : UnaryExpression{_body_expression}, function_name{_function_name}, parameter_name{_parameter_name}
{
    // empty
}

std::shared_ptr<Expression> Fun::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Fun::to_string() const noexcept
{
    return "(fun"
        + function_name->to_string()
        + parameter_name->to_string()
        + UnaryExpression::get_expression()->to_string() + ")";
}

const std::string& Fun::get_name() const noexcept
{
    return std::dynamic_pointer_cast<Id>(function_name)->get_value();
}

const std::string Fun::get_parameter_name() const noexcept
{
    return std::dynamic_pointer_cast<Id>(parameter_name)->get_value();
}

std::shared_ptr<Expression> Fun::get_body_expression() const noexcept
{
    return UnaryExpression::get_expression();
}

std::shared_ptr<Expression> Call::eval(Environment& env) const
{
    // TODO
    return nullptr;
}

std::string Call::to_string() const noexcept
{
    return "(call"
        + BinaryExpression::get_left_expression()->to_string()
        + BinaryExpression::get_right_expression()->to_string() + ")";
}

std::shared_ptr<Expression> Parser::parse(std::string_view program)
{
    // TODO
    return nullptr;
}