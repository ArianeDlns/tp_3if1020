/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"

/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons
{
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
    using milliseconds = std::chrono::duration<int, std::milli>;

    void operator()() override
    {
        // Déposer dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages, via un osyncstream,
        // pour suivre l'avancement.

        // Création du générateur pour des entiers entre 0 et 50
        for (int msg = 0; msg < nb_messages_; msg++)
        {
            int message = box_.get();
            osyncstream(std::cout) << "[Consumer] message " << message << " vient d'être reçu par " << name_ << "\n";
            std::this_thread::sleep_for(milliseconds{random_engine_()});
        }
    }
};
