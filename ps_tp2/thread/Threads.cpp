/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Threads.cpp
 * c++ -std=c++20 Threads.cpp -o Threads -lpthread
 */

#include <iostream>
#include <sstream>
#include <thread>

#include "../Random.hpp"
#include "../osyncstream.hpp"

#include "Producer.hpp"
#include "Consumer.hpp"
#include "MessageBox.hpp"

/*
 * Test avec 1 producteur et 1 consommateur
 */
int main()
{
    // Créer un générateur de nombres aléatoires
    Random random_engine{50};

    // Créer une boîte à lettres
    MessageBox box{};

    /*FIRST PART 
    // Créer un producteur et un consommateur
    Producer producteur{1, box, random_engine, 20};
    Consumer consomateur{2, box, random_engine, 20};

    // Créer les threads correspondants
    std::thread thread1{producteur};
    std::thread thread2{consomateur};

    thread1.join();
    thread2.join();
*/

    std::vector<std::thread> group;

    for (unsigned i = 0; i < 4; i++)
    {
        std::vector<std::thread> group;
        group.push_back(std::thread{Producer{i, box, random_engine, 10}});
    }

    for (unsigned i = 0; i < 2; i++)
    {
        group.push_back(std::thread{Consumer{i, box, random_engine, 20}});
    }

    for (auto &t : group)
        t.join();

    return 0;
}
