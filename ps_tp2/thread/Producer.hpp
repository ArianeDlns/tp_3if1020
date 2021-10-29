/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons
{
public:
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;
    using milliseconds = std::chrono::duration<int, std::milli>;

    void operator()() override
    {
        // Dépose dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages pour suivre l'avancement.

        for (int msg = 0; msg < nb_messages_; msg++)
        {
            int message = msg;
            box_.put(message);
            std::cout << "[Producer] message " << message << " vient d'être déposé par " << name_ << "\n";
            std::this_thread::sleep_for(milliseconds{random_engine_()});
        }
    }
};
