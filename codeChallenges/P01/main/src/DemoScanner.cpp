#include <iostream>
#include <vector>

#include <Scanner.hpp>

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
        "(fun pow2 (x) (* (var (x)) (var (x))))",
        "(call pow2 (8))"
    };

    for (const auto& expression: program)
    {
        Scanner scanner{expression};

        std::cout << "Expression: " << expression << '\n';

        while (true)
        {
            Token token = scanner.get_next_token();

            if (token.first == TokenType::EoF)
            {
                break;
            }

            std::cout << "<" << to_string(token.first) << ",\"" << token.second << "\">";
        }

        std::cout << "\n\n";
    }

    return EXIT_SUCCESS;
}