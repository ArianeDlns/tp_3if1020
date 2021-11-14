/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.cpp
 * c++ -std=c++20 Consumer.cpp -o Consumer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "../Random.hpp"
#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"
#include "MessageBox.hpp"

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
        // TODO : déposer dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages, via un osyncstream,
        // pour suivre l'avancement.
        for (int msg = 0; msg < nb_messages_; msg++)
        {
            int message = box_.get();
            osyncstream(std::cout) << "[Consumer] message " << message << " vient d'être reçu par " << name_ << "\n";
            std::this_thread::sleep_for(milliseconds{random_engine_()});
        }
    }
};

int main()
{
    using namespace boost::interprocess;

    // TODO : accéder à la mémoire partagée, la projeter en mémoire,
    // y accéder comme boîte à lettres, lancer le consommateur
    int box_memsize = sizeof(MessageBox);

    struct sharedbox_remove
    {
        ~sharedbox_remove() { shared_memory_object::remove("MemoryShared"); }
    } remover;

    shared_memory_object SharedBox(open_only, "MemoryShared", read_write);
    SharedBox.truncate(box_memsize);
    mapped_region map_region = mapped_region(SharedBox, read_write, 0, box_memsize);

    MessageBox *box = (MessageBox *)map_region.get_address();
    Random generator{100};
    Consumer consumer{0, *box, generator, 20};
    consumer();

    return 0;
}
