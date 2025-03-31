#include <iostream>
#include <vector>

#include <PR3PL.hpp>

int main()
{

    std::vector<std::string> program{
        // Función para calcular el n-ésimo número de fibonacci con n >= 0
        /*
        (fun
            (fibonacci)
            (n)
            (iflesser
                (var (n))
                (2)
                (var (n))
                (+ (call (fibonacci) (+ (var (n))(-(1))) ) (call (fibonacci) (+ (var (n))(-(2)))))
            )
        )
        */
        "(fun (fibonacci) (n) (iflesser (var (n)) (2) (var (n)) (+ (call (fibonacci) (+ (var (n))(-(1))) ) (call (fibonacci) (+ (var (n))(-(2)))))))",
        // Prueba caso base 1
        "(call (fibonacci) (0))",
        // Prueba caso base 2
        "(call (fibonacci) (1))",
        // Prueba caso general
        "(call (fibonacci) (2))",
        "(call (fibonacci) (3))",
        "(call (fibonacci) (4))",
        "(call (fibonacci) (5))",
        "(call (fibonacci) (6))",
        "(call (fibonacci) (7))",
        "(call (fibonacci) (8))",
        "(call (fibonacci) (9))",
        "(call (fibonacci) (10))",
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