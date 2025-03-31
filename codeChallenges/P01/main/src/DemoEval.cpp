#include <iostream>
#include <vector>

#include <PR3PL.hpp>

int main()
{
    std::vector<std::string> program{
        "()",
        "(10)",
        "(isunit ())",
        "(isunit (10))",
        "(pair (10) (20))",
        "(fst (pair (10) (20)))",
        "(snd (pair (10) (20)))",
        "(- (5))",
        "(+ (5) (2))",
        "(* (5) (2))",
        "(/ (5) (2))",
        "(% (5) (2))",
        "(val (x) (10))",
        "(var (x))",
        "(iflesser (var (x)) (18) (18) (var (x)))",
        "(let (x) (5) (+ (var (x)) (20)))",
        "(fun (pow2) (x) (* (var (x)) (var (x))))",
        "(call (pow2) (8))"
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