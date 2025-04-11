#include <Sampler.hpp>
#include <TestUtilities.hpp>

#include <chrono>

void test() noexcept
{
    Sampler s({19, 14, 11, 9, 7, 4, 3, 1});
    s.add_sample(20);
    Sampler s1 = std::vector<long>({20, 3, 19, 4, 9, 1, 14, 7, 11});
    Sampler s2 = std::vector<long>({1, 14, 11, 7, 9, 4, 3});
    Sampler s3 = std::vector<long>({386, 412, 352, 88, 289, 506, 194, 190, 613, 224, 896, 428, 133, 933, 258, 832, 209, 945, 687, 903, 486, 60, 598, 76, 882, 309, 269, 656, 46, 741, 242, 405, 599, 545, 750, 301, 954, 211, 21, 124, 425, 591, 554, 910, 508, 453, 625, 628, 563, 65, 245, 609, 596, 325, 616, 355, 176, 44, 668, 634, 928, 432, 290, 665, 767, 894, 737, 640, 229, 54, 906, 348, 793, 922, 520, 330, 923, 573, 932, 972, 112, 565, 915, 38, 740, 512, 673, 427, 340, 912, 624, 704, 699, 900, 802, 127, 724, 844, 262, 924, 559, 895, 289, 285, 537, 501, 987, 909, 788, 931, 180, 393, 799, 69, 584, 544, 458, 641, 939, 29, 599, 37, 527, 125, 77, 482, 626, 868, 641, 532, 854, 668, 558, 429, 379, 858, 686, 573, 739, 53, 39, 867, 695, 309, 926, 398, 388, 225, 672, 271, 608, 214, 357, 361, 171, 176, 199, 162, 603, 130, 964, 267, 386, 493, 882, 254, 404, 45, 838, 714, 485, 767, 142, 618, 985, 183, 316, 904, 891, 484, 864, 836, 387, 592, 808, 555, 379, 13, 544, 316, 295, 922, 172, 863, 354, 159, 548, 256, 882, 513, 372, 323, 214, 40, 332, 459, 666, 645, 794, 770, 287, 970, 461, 778, 150, 238, 296, 839, 687, 384, 630, 642, 778, 797, 263, 613, 479, 74, 5, 304, 680, 915, 195, 327, 252, 297, 402, 277, 720, 189, 120, 471, 744, 54, 488, 924, 246, 888, 233, 427, 856, 457, 280, 687, 85, 886, 599, 572, 84, 512, 347, 505, 471, 812, 4, 894, 938, 191, 177, 281, 575, 774, 454, 871, 3, 867, 803, 976, 333, 526, 834, 399, 669, 454, 399, 389, 470, 765, 813, 565, 301, 509, 157, 611, 486, 270, 187, 389, 77, 905, 279, 647, 185, 872, 72, 169, 898, 31, 841, 830, 721, 946, 697, 905, 237, 406, 318, 753, 345, 386, 448, 88, 687, 482, 263, 829, 435, 919, 432, 107, 247, 182, 817, 490, 252, 167, 673, 446, 741, 411, 564, 132, 874, 237, 509, 195, 541, 282, 465, 742, 539, 504, 548, 597, 526, 698, 989, 934, 316, 982, 430, 30, 900, 271, 747, 812, 459, 895, 245, 922, 872, 655, 24, 256, 774, 539, 816, 54, 800, 148, 506, 277, 504, 205, 802, 157, 263, 532, 649, 757, 444, 563, 262, 181, 310, 176, 358, 147, 3, 99, 733, 424, 179, 913, 904, 208, 5, 847, 918, 165, 188, 276, 216, 902, 642, 381, 773, 440, 750, 151, 779, 668, 691, 185, 851, 193, 356, 626, 882, 703, 398, 834, 950, 752, 3, 434, 932, 32, 819, 965, 555, 726, 604, 370, 830, 33, 748, 78, 897, 32, 391, 836, 92, 703, 845, 806, 504, 883, 409, 955, 227, 795, 607, 178, 1000, 300, 181, 808, 340, 802, 342, 427, 795, 518, 845, 71, 997, 822, 127, 898, 273, 213, 325, 517, 95, 126, 148, 400, 632, 774, 854, 914, 376, 645, 82, 189, 630, 702, 463, 317, 590, 495, 649, 420, 279, 311, 164, 97, 156, 73, 835, 274, 911, 328, 72, 668, 498, 693, 9, 842, 217, 804, 46, 210, 724, 33, 404, 974, 224, 841, 859, 66, 246, 617, 240, 478, 537, 920, 894, 321, 304, 175, 907, 264, 887, 69, 898, 109, 314, 810, 780, 419, 981, 74, 423, 216, 136, 564, 140, 900, 988, 267, 169, 952, 306, 114, 237, 419, 186, 928, 110, 907, 739, 189, 168, 504, 364, 419, 798, 364, 850, 901, 641, 848, 146, 867, 661, 415, 597, 651, 460, 662, 802, 778, 7, 971, 238, 426, 519, 95, 337, 824, 975, 881, 61, 230, 887, 991, 688, 816, 496, 435, 401, 688, 110, 998, 899, 381, 887, 31, 60, 294, 105, 719, 696, 298, 437, 313, 447, 841, 27, 810, 893, 245, 452, 915, 265, 819, 147, 23, 977, 209, 817, 550, 485, 762, 919, 592, 15, 910, 945, 531, 754, 728, 68, 405, 812, 760, 196, 803, 145, 785, 366, 389, 688, 589, 489, 732, 788, 996, 245, 475, 605, 488, 224, 949, 130, 250, 572, 600, 28, 781});

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
    // assert_equal(s3.stats(), BasicStats{2, 100, 9.777777778, 41.50617284, 4., 9., 14., 9});

    /* Prueba de obtención de las posiciones de un conjunto de claves
       Las claves 2 y 5 no están en la muestra, por esa razón, en la respuesta
       tienen posición -1.
    */
    assert_equal(s.get_by_keys({11, 2, 5, 4}),
                 {std::make_tuple(2, -1),
                  std::make_tuple(4, 2),
                  std::make_tuple(5, -1),
                  std::make_tuple(11, 5)});
    assert_equal(s3.get_by_keys({448, 904, 891, 399, 44, 730, 921, 912, 91, 394, 734, 41, 657, 469, 291, 200, 511, 713, 679, 150, 965, 88, 152, 613, 727, 711, 562, 22, 358, 933, 877, 964, 500, 302, 438, 526, 392, 840, 863, 765, 90, 63, 162, 530, 631, 55, 153, 715, 176, 508, 869, 629, 43, 975, 193, 945, 27, 362, 702, 620, 376, 714, 667, 53, 206, 57, 180, 755, 645, 101, 114, 617, 689, 915, 318, 196, 174, 194, 134, 525, 255, 579, 738, 641, 849, 931, 953, 789, 395, 268, 336, 384, 561, 299, 695, 134, 994, 40, 234, 875, 652, 20, 50, 866, 815, 971, 836, 464, 461}),
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

    auto compute_mean = [&s]()
    { return s.mean(); };
    assert_throw_exception<std::length_error>(compute_mean);

    auto compute_variance = [&s]()
    { return s.variance(); };
    assert_throw_exception<std::length_error>(compute_variance);

    auto get_sample = [&s](size_t i)
    { return s.get_sample(i); };
    assert_throw_exception<std::out_of_range>(get_sample, 10);

    auto compute_stats = [&s]()
    { return s.stats(); };
    assert_throw_exception<std::length_error>(compute_stats);

    auto get_by_position_range = [&s](size_t l, size_t r)
    { return s.get_by_position_range(l, r); };
    assert_throw_exception<std::invalid_argument>(get_by_position_range, 5, 3);
    assert_throw_exception<std::out_of_range>(get_by_position_range, 1, 3);

    auto get_by_key_range = [&s](long l, long r)
    { return s.get_by_key_range(l, r); };
    assert_throw_exception<std::invalid_argument>(get_by_key_range, 5, 3);

    auto cut_by_key_range = [&s](long l, long r)
    { return s.cut_by_key_range(l, r); };
    assert_throw_exception<std::invalid_argument>(cut_by_key_range, 5, 3);

    auto cut_by_position_range = [&s](size_t l, size_t r)
    { return s.cut_by_position_range(l, r); };
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
