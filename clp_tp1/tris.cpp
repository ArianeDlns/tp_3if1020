/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * tris.cpp
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <functional>

#include <cstdlib>
#include <ctime>

//using namespace std;

void print_tab(const std::vector<int> &tab){
    std::cout << "[ ";
    for (int i(0); i < tab.size(); i++){
        std::cout << tab[i] << " ";
    }
    std::cout << "]";
}

void test_11(){
    const std::vector< int > tab{ 1, -2, 3, -4, 5, -6 };
    std::cout << "*** test_11 *** " << std::endl;
    print_tab(tab);
    std::cout << std::endl;
}

void random_tab(std::vector<int> &tab){
    for (int i{0}; i < tab.size(); i++) {
        tab[i] = (rand()%21)-10;
    }
}

void test_12() {
    std::cout << "*** test_12 ***" << std::endl;
    std::vector<int>tab(10);
    random_tab(tab);
    print_tab(tab);
    std::cout << std::endl;
}

void sort_tab_1(std::vector<int> &tab){
    for (int i{0}; i < tab.size() - 1; i++) {
        int min_index{i};
        int min_value{tab[i]};
        for (int j{i+1}; j < tab.size(); j++) {
            if (tab[j] < min_value) {
                min_value = tab[j];
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(tab[i], tab[min_index]);
            }
    }
}

void test_13(){
    std::cout << "*** test_13 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    print_tab(tab);
    std::cout << " >> SORTED LIST >> ";
    sort_tab_1(tab);
    print_tab(tab);
    std::cout << std::endl;
}

bool less(int a, int b){
    return (a <= b);
}

bool greater(int a, int b){
    return (a >= b);
}

void sort_tab_2(std::vector<int> &tab, bool(*comp)(int,int)){
   std::sort(tab.begin(),tab.end(), comp);
}

void test_14(){
    std::cout << "*** test_14 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    print_tab(tab);
    std::cout << " >> SORTED LIST with -- >> ";
    sort_tab_2(tab, less);
    print_tab(tab);
    std::cout << std::endl;

    random_tab(tab);
    print_tab(tab);
    std::cout << " >> SORTED LIST with ++ >> ";
    sort_tab_2(tab, greater);
    print_tab(tab);
    std::cout << std::endl;
}


void sort_tab_3(std::vector<int> &tab, std::function <bool(int, int)> comp){
   std::sort(tab.begin(),tab.end(), comp);
}

void test_15(){
    std::cout << "*** test_15 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    print_tab(tab);
    std::cout << " >> SORTED LIST with -- >> ";
    sort_tab_3(tab, [](int a, int b) {return abs(a) <= abs(b);});
    print_tab(tab);
    std::cout << std::endl;

    random_tab(tab);
    print_tab(tab);
    std::cout << " >> SORTED LIST with ++ >> ";
    sort_tab_3(tab, [](int a, int b) {return abs(a) >= abs(b);});
    print_tab(tab);
    std::cout << std::endl;
}


int main(){
    //permet de changer l'aléatoire en dépendant de l'horloge 
    std::srand( std::time( nullptr ));

    //test
    test_11();
    test_12();
    test_13();
    test_14();
    test_15();

    return 0;
}

