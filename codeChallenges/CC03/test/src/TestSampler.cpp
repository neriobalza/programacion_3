#include <Sampler.hpp>
#include <TestUtilities.hpp>

#include <chrono>

void test() noexcept
{
    Sampler s({19, 14, 11, 9, 7, 4, 3, 1});
    s.add_sample(20);
    Sampler s1 = std::vector<long>({20, 3, 19, 4, 9, 1, 14, 7, 11});
    Sampler s2 = std::vector<long>({1, 14, 11, 7, 9, 4, 3});

    // Prueba de tamaño
    assert_equal(s.size(), 9UL);

    // Prueba de obtención de lista por rango de posiciones
    assert_equal(s.get_by_position_range(2, 5), {4, 7, 9});
    assert_equal(s.get_by_position_range(3, 3), {7});

    // Prueba de obtención de lista ordenada
    assert_equal(s.list(), {1, 3, 4, 7, 9, 11, 14, 19, 20});

    /* Pruebas de media y varianza. Valores de prueba calculados con las
       funciones AVERAGE(...) y VAR.P(...) de Libre Office Calc.
    */
    assert_equal(s.mean(), 9.777777778);
    assert_equal(s.variance(), 41.50617284);

    // Prueba de obtención del i-ésimo elemento. Caso 4.
    assert_equal(s.get_sample(4), 9L);

    // Prueba de obtención de estadísticas
    assert_equal(s.stats(), BasicStats{1, 20, 9.777777778, 41.50617284, 4., 9., 14., 9});

    /* Prueba de obtención de las posiciones de un conjunto de claves
       Las claves 2 y 5 no están en la muestra, por esa razón, en la respuesta
       tienen posición -1.
    */
    assert_equal(s.get_by_keys({11, 2, 5, 4}),
                 {std::make_tuple(2, -1),
                  std::make_tuple(4, 2),
                  std::make_tuple(5, -1),
                  std::make_tuple(11, 5)});

    // Prueba de obtención de una lista ordenada por rango de claves
    assert_equal(s.get_by_key_range(3, 11), {4, 7, 9, 11});
    assert_equal(s.get_by_key_range(5, 15), {7, 9, 11, 14});

    // Prueba de dejar en sampler, las claves entre dos rangos
    assert_equal(s1.cut_by_key_range(4, 11).list(), {7, 9, 11});
    assert_equal(s1.cut_by_key_range(6, 20).list(), {7, 9, 11});

    // Prueba de dejar en sampler, las claves entre dos rangos de posiciones
    assert_equal(s2.cut_by_position_range(2, 5).list(), {4, 7, 9});
}

void test_exceptions() noexcept
{
    Sampler s{};

    auto compute_mean = [&s] () { return s.mean(); };
    assert_throw_exception<std::length_error>(compute_mean);

    auto compute_variance = [&s] () { return s.variance(); };
    assert_throw_exception<std::length_error>(compute_variance);

    auto get_sample = [&s] (size_t i) { return s.get_sample(i); };
    assert_throw_exception<std::out_of_range>(get_sample, 10);

    auto compute_stats = [&s] () { return s.stats(); };
    assert_throw_exception<std::length_error>(compute_stats);

    auto get_by_position_range = [&s] (size_t l, size_t r) { return s.get_by_position_range(l, r); };
    assert_throw_exception<std::invalid_argument>(get_by_position_range, 5, 3);
    assert_throw_exception<std::out_of_range>(get_by_position_range, 1, 3);

    auto get_by_key_range = [&s] (long l, long r) { return s.get_by_key_range(l, r); };
    assert_throw_exception<std::invalid_argument>(get_by_key_range, 5, 3);

    auto cut_by_key_range = [&s] (long l, long r) { return s.cut_by_key_range(l, r); };
    assert_throw_exception<std::invalid_argument>(cut_by_key_range, 5, 3);

    auto cut_by_position_range = [&s] (size_t l, size_t r) { return s.cut_by_position_range(l, r); };
    assert_throw_exception<std::invalid_argument>(cut_by_position_range, 5, 3);
    assert_throw_exception<std::out_of_range>(cut_by_position_range, 1, 3);
}

void measure_time() noexcept
{
    // Programa aquí tus medidas de tiempo. Te dejo un ejemplo.
    
    std::cout << "Constructor time: ";
    
    auto tp1 = std::chrono::high_resolution_clock::now();
    Sampler{std::vector<long>({20, 3, 19, 4, 9, 1, 14, 7, 11})};
    auto tp2 = std::chrono::high_resolution_clock::now();

    auto t = std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();
    
    std::cout << t << " ms\n";
}

int main()
{
    std::cout << std::setprecision(6) << std::fixed << std::boolalpha;
    test();
    test_exceptions();
    measure_time();
    std::cout << "Everything ok!\n";
    return EXIT_SUCCESS;
}
