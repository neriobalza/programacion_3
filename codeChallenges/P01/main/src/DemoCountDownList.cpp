#include <iostream>
#include <vector>

#include <PR3PL.hpp>

int main()
{
    std::vector<std::string> program{
        // Función que genera una lista con los números desde n hasta 1
        "(fun (countdown) (n) (iflesser (var (n)) (1) () (pair (var (n)) (call (countdown) (+ (var (n)) (-(1)))))))",
        "(call (countdown) (0))",
        "(call (countdown) (1))",
        "(call (countdown) (2))",
        "(call (countdown) (3))",
        "(call (countdown) (4))",
        "(call (countdown) (5))"
    };

    Environment env;

    for (const auto& expression: program)
    {
        std::cout << "Expression: " << expression << '\n';
        auto result = Parser::parse(expression);
        if (result != nullptr)
        {
            auto eval_result = result->eval(env);

            if (eval_result != nullptr)
            {
                std::cout << "Result: " << eval_result->to_string() << "\n\n";
            }
            else
            {
                std::cout << "Failed to evaluate program\n\n";
            }
        }
        else
        {
            std::cout << "Failed to parse program\n\n";
        }
    }

    return EXIT_SUCCESS;
}