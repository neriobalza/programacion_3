#include <iostream>
#include <vector>

#include <PR3PL.hpp>

int main()
{
    std::vector<std::string> program{
        // Función que suma los elementos de una lista
        /*
        (fun 
            (sum)
            (xs)
            (iflesser
                (0)
                (isunit 
                    (var 
                        (xs)
                    )
                )
                (0)
                (+ (fst(var(xs))) (call (sum) (snd(var(xs)))))
            )
        )
        */
        "(fun (sum) (xs) (iflesser (0) (isunit (var (xs))) (0) (+ (fst(var(xs))) (call (sum) (snd(var(xs)))))))",
        "(val (lst) (pair (1) (pair (2) (pair (3) (pair (4) (pair (5) (pair (6) (pair (7) (pair (8) (pair (9) (pair (10) ())))))))))))",
        "(call (sum) (var (lst)))"
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