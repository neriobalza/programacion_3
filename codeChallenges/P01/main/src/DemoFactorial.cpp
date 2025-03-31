#include <iostream>
#include <vector>

#include <PR3PL.hpp>

int main()
{
    std::vector<std::string> program{
        // Función para calcular el factorial de un número. No funciona para n < 0.
        /*
        (fun
            (factorial)
            (n)
            (iflesser
                (var (n))
                (1)
                (1)
                (* (var (n)) (call (factorial) (+ (var (n)) (-(1)))))
            )
        )
        */
        "(fun (factorial) (n) (iflesser (var (n)) (1) (1) (* (var (n)) (call (factorial) (+ (var (n)) (-(1)))))))",
        // Prueba caso base
        "(call (factorial) (0))",
        // Prueba caso general
        "(call (factorial) (1))",
        "(call (factorial) (2))",
        "(call (factorial) (3))",
        "(call (factorial) (4))",
        "(call (factorial) (5))",
        "(call (factorial) (6))",
        "(call (factorial) (7))",
        "(call (factorial) (8))",
        "(call (factorial) (9))",
        "(call (factorial) (10))"
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