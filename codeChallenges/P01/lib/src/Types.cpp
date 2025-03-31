#include <Types.hpp>

Expression::~Expression()
{
    // empty
}

UnaryExpression::UnaryExpression(std::shared_ptr<Expression> _expression) noexcept
    : expression{_expression}
{
    // empty
}

std::shared_ptr<Expression> UnaryExpression::get_expression() const noexcept
{
    return expression;
}

BinaryExpression::BinaryExpression(std::shared_ptr<Expression> _left_expression, std::shared_ptr<Expression> _right_expression) noexcept
    : left_expression{_left_expression}, right_expression{_right_expression}
{
    // empty
}

std::shared_ptr<Expression> BinaryExpression::get_left_expression() const noexcept
{
    return left_expression;
}

std::shared_ptr<Expression> BinaryExpression::get_right_expression() const noexcept
{
    return right_expression;
}

const Environment& Closure::get_environment() const noexcept
{
    return env;
}

std::shared_ptr<Expression> Closure::get_function() const noexcept
{
    return UnaryExpression::get_expression();
}

void Environment::add(const std::string& identifier, std::shared_ptr<Expression> expression) noexcept
{
    this->push_front(std::make_pair(identifier, expression));
}

std::shared_ptr<Expression> Environment::lookup(const std::string& identifier) const noexcept
{
    for (const auto& t : *this)
    {
        if (t.first == identifier)
        {
            return t.second;
        }
    }

    return nullptr;
}

Closure::Closure(const Environment& _env, std::shared_ptr<Expression> _function) noexcept
    : UnaryExpression{_function}, env{_env}
{
    // empty
}

std::shared_ptr<Expression> Closure::eval(Environment&) const
{
    return std::make_shared<Closure>(env, UnaryExpression::get_expression());
}

std::string Closure::to_string() const noexcept
{
    return "(closure" + UnaryExpression::get_expression()->to_string() + ")";
}
