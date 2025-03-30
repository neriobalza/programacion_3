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
    return errors == 0 ? true : false;
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
    std::stack<Token> operatorStack;

    // std::cout << to_string(token.first) << ": " << token.second << std::endl;

    for (Token token; (token = scanner.get_next_token()).first != TokenType::EoF;)
    {
        if (token.first == TokenType::Int)
        {
            suffix.push_back(token);
        }
        else if (token.first == TokenType::LParen)
        {
            operatorStack.push(token);
        }
        else if (token.first == TokenType::RParen)
        {
            while (operatorStack.top().first != TokenType::LParen)
            {
                suffix.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        else if (token.first != TokenType::Unknown)
        {
            while (!operatorStack.empty() && precedence.lookup(operatorStack.top().second) >= precedence.lookup(token.second))
            {
                suffix.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
    }

    while (!operatorStack.empty())
    {
        suffix.push_back(operatorStack.top());
        operatorStack.pop();
    }

    return suffix;
}

std::shared_ptr<ArithmNode> Parser::build_arithmetic_tree() const
{
    if (suffix_expression.empty())
    {
        return nullptr;
    }

    std::stack<std::shared_ptr<ArithmNode>> nodeStack;

    for (auto token : suffix_expression)
    {
        if (token.first == TokenType::Int)
        {
            nodeStack.push(std::make_shared<ArithmNode>(make_key(token.second, evaluate_integer)));
        }
        else
        {
            if (nodeStack.size() < 2)
            {
                throw std::runtime_error{"Invalid Expression"};
            }

            std::shared_ptr<ArithmNode> operatorNode;
            std::shared_ptr<ArithmNode> rightChildren = nodeStack.top();
            nodeStack.pop();
            std::shared_ptr<ArithmNode> leftChildren = nodeStack.top();
            nodeStack.pop();

            switch (token.first)
            {
            case TokenType::Add:
                operatorNode = std::make_shared<ArithmNode>(make_key(token.second, evaluate_addition), leftChildren, rightChildren);
                break;
            case TokenType::Sub:
                operatorNode = std::make_shared<ArithmNode>(make_key(token.second, evaluate_subtraction), leftChildren, rightChildren);
                break;
            case TokenType::Mul:
                operatorNode = std::make_shared<ArithmNode>(make_key(token.second, evaluate_multiplication), leftChildren, rightChildren);
                break;
            case TokenType::Div:
                operatorNode = std::make_shared<ArithmNode>(make_key(token.second, evaluate_division), leftChildren, rightChildren);
                break;
            case TokenType::Mod:
                operatorNode = std::make_shared<ArithmNode>(make_key(token.second, evaluate_module), leftChildren, rightChildren);
                break;
            default:
                break;
            }

            nodeStack.push(operatorNode);
        }
    }

    if (nodeStack.size() != 1)
    {
        throw std::runtime_error{"Invalid Expression"};
    }

    return nodeStack.top();
}