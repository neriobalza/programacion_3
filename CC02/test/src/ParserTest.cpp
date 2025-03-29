#include <Parser.hpp>
#include <TestUtilities.hpp>

int main()
{
    std::cout << "Parser test\n";

    auto int_five = std::make_shared<ArithmNode>(make_key("5", Parser::evaluate_integer));
    auto int_three = std::make_shared<ArithmNode>(make_key("3", Parser::evaluate_integer));
    auto int_cero = std::make_shared<ArithmNode>(make_key("0", Parser::evaluate_integer));

    {
        std::cout << "Testing evaluate_integer\n";
        assert_equal(int_five->eval(), 5L);
    }

    {
        std::cout << "Testing evaluate_addition\n";
        auto tree = std::make_shared<ArithmNode>(make_key("+", Parser::evaluate_addition), int_five, int_three);
        assert_equal(tree->eval(), 8L);
    }

    {
        std::cout << "Testing evaluate_subtraction\n";
        auto tree = std::make_shared<ArithmNode>(make_key("-", Parser::evaluate_subtraction), int_five, int_three);
        assert_equal(tree->eval(), 2L);
    }
    {
        std::cout << "Testing evaluate_subtraction\n";
        auto tree = std::make_shared<ArithmNode>(make_key("-", Parser::evaluate_subtraction), int_cero, int_three);
        assert_equal(tree->eval(), -3L);
    }

    {
        std::cout << "Testing evaluate_multiplication\n";
        auto tree = std::make_shared<ArithmNode>(make_key("*", Parser::evaluate_multiplication), int_five, int_three);
        assert_equal(tree->eval(), 15L);
    }

    {
        std::cout << "Testing evaluate_division\n";
        auto tree = std::make_shared<ArithmNode>(make_key("/", Parser::evaluate_division), int_five, int_three);
        assert_equal(tree->eval(), 1L);
    }

    {
        std::cout << "Testing evaluate_module\n";
        auto tree = std::make_shared<ArithmNode>(make_key("%", Parser::evaluate_module), int_five, int_three);
        assert_equal(tree->eval(), 2L);
    }

    {
        std::cout << "Testing build_suffix_expression\n";
        std::vector<Token> expected{{TokenType::Int, "2"}, {TokenType::Int, "5"}, {TokenType::Int, "3"}, {TokenType::Add, "+"}, {TokenType::Mul, "*"}};
        assert_equal(Parser::build_suffix_expression("2 * (5 + 3)"), expected);
    }

    {
        std::cout << "Testing build_arithmetic_tree\n";
        auto int_two = std::make_shared<ArithmNode>(make_key("2", Parser::evaluate_integer));
        auto addition = std::make_shared<ArithmNode>(make_key("+", Parser::evaluate_addition), int_five, int_three);
        auto expected = std::make_shared<ArithmNode>(make_key("*", Parser::evaluate_multiplication), int_two, addition);
        assert_equal(Parser{"2 * (5 + 3)"}.build_arithmetic_tree(), expected);
    }

    {
        std::cout << "Tesing parsing result\n";
        assert_equal(Parser{"2 * 5 + 3"}.build_arithmetic_tree()->eval(), 13L);
        assert_equal(Parser{"2 * (5 + 3)"}.build_arithmetic_tree()->eval(), 16L);
        assert_equal(Parser{"(2 * (5) + 3)"}.build_arithmetic_tree()->eval(), 13L);
        assert_equal(Parser{"(2 * ((5) + 3))"}.build_arithmetic_tree()->eval(), 16L);
    }

    return EXIT_SUCCESS;
}