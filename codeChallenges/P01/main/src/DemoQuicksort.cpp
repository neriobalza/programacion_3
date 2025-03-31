#include <iostream>
#include <vector>

#include <PR3PL.hpp>
/*

(fun
    (partition)
    (pivottail) // Par (pivote, resto_de_la_lista_sin_pivote)
    (iflesser
        // Si la lista está vacía
        (0)
        (isunit
            (snd
                (var
                    (pivottail)
                )
            )
        )
        (pair()()) // Caso vacía, retorno dos listas vacías
        (let
            // Calculo partición con el tail de la lista recibida usando el primer elemento como pivote
            (smallbigs)
            (call
                (partition)
                (pair
                    (fst
                        (var
                            (pivottail)
                        )
                    )
                    (snd
                        (snd
                            (var
                                (pivottail)
                            )
                        )
                    )
                )
            )
            // El primero de la lista recibida es menor que el pivote?
            (iflesser
                (fst
                    (snd
                        (var
                            (pivottail)
                        )
                    )
                )
                (fst
                    (var
                        (pivottail)
                    )
                )
                // Retorno nuevo par (smalls, bigs) con el primero de la lista recibida en smalls
                (pair
                    (pair
                        (fst
                            (snd
                                (var
                                    (pivottail)
                                )
                            )
                        )
                        (fst
                            (var
                                (smallbigs)
                            )
                        )
                    )
                    (snd
                        (var
                            (smallbigs)
                        )
                    )
                )
                // Retorno nuevo par (smalls, bigs) con el primero de la lista recibida en bigs
                (pair
                    (fst
                        (var
                            (smallbigs)
                        )
                    )
                    (pair
                        (fst
                            (snd
                                (var
                                    (pivottail)
                                )
                            )
                        )
                        (snd
                            (var
                                (smallbigs)
                            )
                        )
                    )
                )
            )
        )
    )
)

// Append a list to another list
(fun
    (append)
    (p) // Par (lista_a_agregar, lista_destino)
    // Si lista_destino está vacía
    (iflesser
        (0)
        (isunit
            (snd
                (var
                    (p)
                )
            )
        )
        // Caso vacía, retorno lista_a_agregar
        (fst
            (var
                (p)
            )
        )
        // Retorno una nueva lista consistente en lista_destino agregando como segundo
        // elemento el resultado del llamado recursivo de la función append
        (pair
            (fst
                (snd
                    (var
                        (p)
                    )
                )
            )
            (call
                (append)
                (pair
                    (fst
                        (var
                            (p)
                        )
                    )
                    (snd
                        (snd
                            (var
                                (p)
                            )
                        )
                    )
                )
            )
        )
    )
)


(fun
    (quicksort)
    (xs)
    // Si la lista está vacía
    (iflesser
        (0)
        (isunit
            (var
                (xs)
            )
        )
        // Caso vacía, retorno la lista
        (var 
            (xs)
        )
        // Si la lista tiene un solo elemento
        (iflesser
            (0)
            (isunit
                (snd
                    (var
                        (xs)
                    )
                )
            )
            // Caso lista con un solo elemento, retorno la lista
            (var
                (xs)
            )
            // Caso general, el primer elemento de la lista es el pivote
            (let
                // Calculo la partición de la lista recibida
                (smallbigs)
                (call
                    (partition)
                    (pair
                        (fst
                            (var
                                (xs)
                            )
                        )
                        (snd
                            (var
                                (xs)
                            )
                        )
                    )
                )
                // Creo la lista del lado derecho poniendo el pivote como primer elemento
                // y el resultado de llamar recursivamente a quicksort con la lista de bigs
                (let
                    (rightlist)
                    (pair
                        (fst
                            (var
                                (xs)
                            )
                        )
                        (call
                            (quicksort)
                            (snd
                                (var
                                    (smallbigs)
                                )
                            )
                        )
                        
                    )
                    // Retorno la lista resultante de concatenar la lista del lado derecho a la lista de smalls
                    (call
                        (append)
                        (pair
                            (var
                                (rightlist)
                            )
                            (call
                                (quicksort)
                                (fst
                                    (var
                                        (smallbigs)
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    )
)
*/

int main()
{
    std::vector<std::string> program{
        // Función que particiona una lista en dos listas, una con los elementos menores o iguales al pivote y otra con los elementos mayores al pivote
        "(fun(partition)(pivottail)(iflesser(0)(isunit(snd(var(pivottail))))(pair()())(let(smallbigs)(call(partition)(pair(fst(var(pivottail)))(snd(snd(var(pivottail))))))(iflesser(fst(snd(var(pivottail))))(fst(var(pivottail)))(pair(pair(fst(snd(var(pivottail))))(fst(var(smallbigs))))(snd(var(smallbigs))))(pair(fst(var(smallbigs)))(pair(fst(snd(var(pivottail))))(snd(var(smallbigs)))))))))",
        // Función que concatena dos listas
        "(fun(append)(p)(iflesser(0)(isunit(snd(var(p))))(fst(var(p)))(pair(fst(snd(var(p))))(call(append)(pair(fst(var(p)))(snd(snd(var(p)))))))))",
        // Función que ordena una lista usando el algoritmo quicksort
        "(fun(quicksort)(xs)(iflesser(0)(isunit(var(xs)))(var(xs))(iflesser(0)(isunit(snd(var(xs))))(var(xs))(let(smallbigs)(call(partition)(pair(fst(var(xs)))(snd(var(xs)))))(let(rightlist)(pair(fst(var(xs)))(call(quicksort)(snd(var(smallbigs)))))(call(append)(pair(var(rightlist))(call(quicksort)(fst(var(smallbigs)))))))))))",
        "(val (lst) (pair (5) (pair (2) (pair (8) (pair (4) (pair (7) (pair (6) (pair (1) (pair (3) (pair (10) (pair (9) ())))))))))))",
        // Prueba caso de lista vacía
        "(call (quicksort) ())",
        // Prueba caso de lista con un solo elemento
        "(call (quicksort) (pair(1)()))",
        // Prueba caso general
        "(call (quicksort) (var (lst)))"
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