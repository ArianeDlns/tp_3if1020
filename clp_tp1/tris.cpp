/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * tris.cpp
 */

#include <iostream>
#include <vector>
#include <utility>
#include <functional>

#include <cstdlib>
#include <ctime>

using namespace std;

void print_tab(std::vector<int> tab){
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


int main(){
    std::srand( std::time( nullptr ));
    test_11();
    return 0;
}

