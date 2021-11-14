/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.cpp
 * c++ -std=c++20 Producer.cpp -o Producer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "../Random.hpp"

#include "ProdOrCons.hpp"
#include "MessageBox.hpp"

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
        // TODO : déposer dans box nb_messages nombres entiers positifs avec attente
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

int main()
{
    using namespace boost::interprocess;

    // TODO : créer la mémoire partagée, la projeter en mémoire,
    // y construire la boîte à lettres, lancer le producteur

    int box_memsize = sizeof(MessageBox);

    // Remove shared memory on construction and destruction
    struct sharedbox_remove
    {
        sharedbox_remove() { shared_memory_object::remove("MemoryShared"); }
        ~sharedbox_remove() { shared_memory_object::remove("MemoryShared"); }
    } remover;

    shared_memory_object SharedBox(create_only, "MemoryShared", read_write);
    SharedBox.truncate(box_memsize);
    mapped_region map_region = mapped_region(SharedBox, read_write, 0, box_memsize);
    MessageBox *box = new (map_region.get_address()) MessageBox();
    Random generator{100};
    Producer producer = Producer(0, *box, generator, 20);
    producer();

    return 0;
}
