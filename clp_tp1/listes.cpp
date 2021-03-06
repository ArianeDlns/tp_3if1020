/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * listes.cpp
 */

#include <iostream>
#include <forward_list>
#include <functional>
#include <limits>

#include <cstdlib>
#include <ctime>

std::forward_list<int> random_list(int nb)
{
    std::forward_list<int> list;
    for (int i = 0; i < nb; i++)
    {
        int random_number{std::rand() % 100};
        list.push_front(random_number);
    }
    return list;
}

void print_list(std::forward_list<int> &list)
{
    std::cout << "( ";
    for (int i : list)
        std::cout << i << " ";
    std::cout << ")" << std::endl;
}

void test_21()
{
    std::cout << "*** test_21 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);
    std::cout << std::endl;
}

std::forward_list<int> map_iter(const std::forward_list<int> &list, std::function<int(int)> fct)
{
    //the integers will appear in the reverse order
    std::forward_list<int> results;
    for (int i : list)
        results.push_front(fct(i));
    return results;
}

void test_22()
{
    std::cout << "*** test_22 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map_iter(list, [](int a)
                                              { return a * 3; });
    print_list(results);
    std::cout << std::endl;
}

std::forward_list<int> filter_iter(const std::forward_list<int> &list, std::function<bool(int)> predicat)
{
    //the integers will appear in the reverse order
    std::forward_list<int> results;
    for (int i : list)
    {
        if (predicat(i))
        {
            results.push_front(i);
        }
    }
    return results;
}

void test_23()
{
    std::cout << "*** test_23 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map_iter(list, [](int a)
                                              { return a * 3; });
    print_list(results);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> filtered = filter_iter(results, [](int a)
                                                  { return (a % 2 == 0); });
    print_list(filtered);

    std::cout << std::endl;
}

void test_24()
{
    std::cout << "*** test_24 ***" << std::endl;
    int coef{std::rand() % 5 + 1};
    auto list = random_list(10);
    print_list(list);

    std::cout << "-----------Using: " << coef << "-----------" << std::endl;
    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map_iter(list, [coef](int a)
                                              { return a * coef; });
    print_list(results);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> filtered = filter_iter(results, [](int a)
                                                  { return (a % 2 == 0); });
    print_list(filtered);
    std::cout << std::endl;
}

int reduce(const std::forward_list<int> &list, int n, std::function<int(int, int)> fct)
{
    //the integers will appear in the reverse order
    int result{n};
    for (int i : list)
    {
        result = fct(result, i);
    }
    return result;
}

void test_25()
{
    std::cout << "*** test_25 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();

    int min_value{reduce(list, max_int, [](int a, int b)
                         {
                             if (a <= b)
                                 return a;
                             return b;
                         })};
    std::cout << "Minimum: " << min_value << std::endl;

    int max_value{reduce(list, min_int, [](int a, int b)
                         {
                             if (a >= b)
                                 return a;
                             return b;
                         })};
    std::cout << "Maximum: " << max_value << std::endl;
    std::cout << std::endl;
}

/*
 * STARTING BONUS
 */

int fold_left_aux(std::forward_list<int>::const_iterator it,
                  std::forward_list<int>::const_iterator end, int n,
                  std::function<int(int, int)> fct)
{
    if (it == end)
        return n;
    else
    {
        int result{fct(*it, n)};
        return fold_left_aux(++it, end, result, fct);
    }
}

int fold_left(const std::forward_list<int> &list, int n, std::function<int(int, int)> fct)
{
    return fold_left_aux(list.cbegin(), list.cend(), n, fct);
}

void test_31()
{
    std::cout << "*** test_31 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();

    int min_value{fold_left(list, max_int,
                            [](int a, int b)
                            {
                                if (a <= b)
                                    return a;
                                return b;
                            })};
    std::cout << "Minimum: " << min_value << std::endl;

    int max_value{fold_left(list, min_int, [](int a, int b)
                            {
                                if (a >= b)
                                    return a;
                                return b;
                            })};
    std::cout << "Maximum: " << max_value << std::endl;
    std::cout << std::endl;
}

std::forward_list<int> map_aux(std::forward_list<int>::const_iterator it,
                               std::forward_list<int>::const_iterator end,
                               std::function<int(int)> fct,
                               std::forward_list<int> results)
{
    if (it == end)
        return results;
    else
    {
        int result = fct(*it);
        results = map_aux(++it, end, fct, results);
        results.push_front(result);
        return results;
    }
}

std::forward_list<int> map(const std::forward_list<int> &list,
                           std::function<int(int)> fct)
{
    std::forward_list<int> results;
    return map_aux(list.cbegin(), list.cend(), fct, results);
}

std::forward_list<int> filter_aux(std::forward_list<int>::const_iterator it,
                                  std::forward_list<int>::const_iterator end,
                                  std::function<bool(int)> fct,
                                  std::forward_list<int> results)
{
    if (it == end)
        return results;
    else
    {
        if (fct(*it))
        {
            int result = *it;
            results = filter_aux(++it, end, fct, results);
            results.push_front(result);
        }
        else
            return filter_aux(++it, end, fct, results);
        return results;
    }
}

std::forward_list<int> filter(const std::forward_list<int> &list,
                              std::function<bool(int)> fct)
{
    std::forward_list<int> results;
    return filter_aux(list.cbegin(), list.cend(), fct, results);
}

void test_32()
{
    std::cout << "*** test_32 ***" << std::endl;
    int coef{std::rand() % 5 + 1};
    auto list = random_list(10);
    print_list(list);

    std::cout << "-----------Using: " << coef << "-----------" << std::endl;
    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map(list, [coef](int a)
                                         { return a * coef; });
    print_list(results);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> filtered = filter(results, [](int a)
                                             { return (a % 2 == 0); });
    print_list(filtered);

    std::cout << std::endl;
}

void test_33()
{
    std::cout << "*** test_33 ***" << std::endl;
    int coef{std::rand() % 5 + 1};
    auto list = random_list(10);
    print_list(list);

    std::multiplies<int> mul_int;

    std::cout << "-----------Using: " << coef << "-----------" << std::endl;
    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map(list, [coef, mul_int](int a)
                                         { return mul_int(a, coef); });
    print_list(results);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> filtered = filter(results, [](int a)
                                             { return (a % 2 == 0); });
    print_list(filtered);

    std::cout << std::endl;
}

int main()
{
    //permet de changer l'aléatoire en dépendant de l'horloge
    std::srand(std::time(nullptr));

    //tests
    test_21();
    test_22();
    test_23();
    test_24();
    test_25();
    test_31();
    test_32();
    test_33();

    return 0;
}
