#include <stack>

#include <Parser.hpp>

#include <Scanner.hpp>
#include <Token.hpp>

Parser::Parser(std::string_view expression)
    : suffix_expression{build_suffix_expression(expression)}
{
    // Empty
}

long Parser::evaluate_integer(ArithmNode *node) noexcept
{
    return static_cast<long>(std::stoi(K(node).value));
}

long Parser::evaluate_addition(ArithmNode *node) noexcept
{
    return std::dynamic_pointer_cast<ArithmNode>(L(node))->eval() + std::dynamic_pointer_cast<ArithmNode>(R(node))->eval();
}

long Parser::evaluate_subtraction(ArithmNode *node) noexcept
{
    return std::dynamic_pointer_cast<ArithmNode>(L(node))->eval() - std::dynamic_pointer_cast<ArithmNode>(R(node))->eval();
}

long Parser::evaluate_multiplication(ArithmNode *node) noexcept
{
    return std::dynamic_pointer_cast<ArithmNode>(L(node))->eval() * std::dynamic_pointer_cast<ArithmNode>(R(node))->eval();
}

long Parser::evaluate_division(ArithmNode *node)
{
    if (std::dynamic_pointer_cast<ArithmNode>(R(node))->eval() == 0)
    {
        throw std::runtime_error{"Division by zero"};
    }
    return std::dynamic_pointer_cast<ArithmNode>(L(node))->eval() / std::dynamic_pointer_cast<ArithmNode>(R(node))->eval();
}

long Parser::evaluate_module(ArithmNode *node)
{
    if (std::dynamic_pointer_cast<ArithmNode>(R(node))->eval() == 0)
    {
        throw std::runtime_error{"Division by zero"};
    }
    return std::dynamic_pointer_cast<ArithmNode>(L(node))->eval() % std::dynamic_pointer_cast<ArithmNode>(R(node))->eval();
}

bool Parser::validate_parenthesis(std::string_view expression) noexcept
{
    int errors = 0;
    int opens = 0;
    for (auto c : expression)
    {
        if (c == '(')
        {
            ++opens;
        }
        if (c == ')')
        {
            if (opens > 0)
            {
                --opens;
            }
            else
            {
                ++errors;
            }
        }
    }

    errors += opens;
    return errors == 0;
}

std::vector<Token> Parser::Parser::build_suffix_expression(std::string_view expression)
{
    if (!validate_parenthesis(expression))
    {
        throw std::runtime_error{"Parenthesis don't match"};
    }

    Scanner scanner{expression};

    PrecedenceTable precedence{
        {"(", 0},
        {"+", 1},
        {"-", 1},
        {"*", 2},
        {"/", 2},
        {"%", 2}};

    std::vector<Token> suffix;
    std::stack<Token> operator_stack;

    for (Token token; (token = scanner.get_next_token()).first != TokenType::EoF;)
    {
        if (token.first == TokenType::Int)
        {
            suffix.push_back(token);
        }
        else if (token.first == TokenType::LParen)
        {
            operator_stack.push(token);
        }
        else if (token.first == TokenType::RParen)
        {
            while (operator_stack.top().first != TokenType::LParen)
            {
                suffix.push_back(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.pop();
        }
        else if (token.first != TokenType::Unknown)
        {
            while (!operator_stack.empty() && precedence.lookup(operator_stack.top().second) >= precedence.lookup(token.second))
            {
                suffix.push_back(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.push(token);
        }
    }

    while (!operator_stack.empty())
    {
        suffix.push_back(operator_stack.top());
        operator_stack.pop();
    }

    return suffix;
}

std::shared_ptr<ArithmNode> Parser::build_arithmetic_tree() const
{
    if (suffix_expression.empty())
    {
        return nullptr;
    }

    std::stack<std::shared_ptr<ArithmNode>> node_stack;

    for (auto token : suffix_expression)
    {
        if (token.first == TokenType::Int)
        {
            node_stack.push(std::make_shared<ArithmNode>(make_key(token.second, evaluate_integer)));
        }
        else
        {
            if (node_stack.size() < 2)
            {
                throw std::runtime_error{"Invalid Expression"};
            }

            std::shared_ptr<ArithmNode> operator_node;
            std::shared_ptr<ArithmNode> right_children = node_stack.top();
            node_stack.pop();
            std::shared_ptr<ArithmNode> left_children = node_stack.top();
            node_stack.pop();

            switch (token.first)
            {
            case TokenType::Add:
                operator_node = std::make_shared<ArithmNode>(make_key(token.second, evaluate_addition), left_children, right_children);
                break;
            case TokenType::Sub:
                operator_node = std::make_shared<ArithmNode>(make_key(token.second, evaluate_subtraction), left_children, right_children);
                break;
            case TokenType::Mul:
                operator_node = std::make_shared<ArithmNode>(make_key(token.second, evaluate_multiplication), left_children, right_children);
                break;
            case TokenType::Div:
                operator_node = std::make_shared<ArithmNode>(make_key(token.second, evaluate_division), left_children, right_children);
                break;
            case TokenType::Mod:
                operator_node = std::make_shared<ArithmNode>(make_key(token.second, evaluate_module), left_children, right_children);
                break;
            default:
                break;
            }

            node_stack.push(operator_node);
        }
    }

    if (node_stack.size() != 1)
    {
        throw std::runtime_error{"Invalid Expression"};
    }

    return node_stack.top();
}