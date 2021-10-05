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

std::forward_list<int> random_list(int nb) {
    std::forward_list<int> list;
    for (int i = 0; i < nb; i++) {
        int random_number{std::rand()%100};
        list.push_front(random_number);
    }
    return list;
}

void print_list(std::forward_list<int> &list) {
    std::cout << "( ";
    for(int i : list) std::cout << i << " ";
    std::cout << ")" << std::endl;
}

void test_21() {
    std::cout << "*** test_21 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);
    std::cout << std::endl;
}

std::forward_list<int> map_iter(const std::forward_list<int> &list, std::function <int(int)> fct) {
    //the integers will appear in the reverse order
    std::forward_list<int> results;
    for(int i : list) results.push_front(fct(i));
    return results;

}

void test_22() {
    std::cout << "*** test_22 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map_iter(list,[](int a) {return a*3;});
    print_list(results);
    std::cout << std::endl;
}

std::forward_list<int> filter_iter(const std::forward_list<int> &list, std::function <bool(int)> predicat) {
    //the integers will appear in the reverse order
    std::forward_list<int> results;
    for(int i : list){
        if(predicat(i)){
            results.push_front(i);
        }
    }
    return results;
}

void test_23() {
    std::cout << "*** test_23 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map_iter(list,[](int a) {return a*3;});
    print_list(results);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> filtered = filter_iter(results,[](int a) {return (a%2 == 0);});
    print_list(filtered);

    std::cout << std::endl;
}

int main()
{
    //permet de changer l'aléatoire en dépendant de l'horloge 
    std::srand( std::time( nullptr ));

    //tests
    test_21();
    test_22();
    test_23();

    return 0;
}

