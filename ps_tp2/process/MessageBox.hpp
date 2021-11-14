/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre processus
 */
class MessageBox : public BasicMessageBox
{
public:
    void put(int message)
    {
        // TODO : ajouter les mecanismes de synchronisation
        basic_put(message);
        unique_lock lock(box_access_);
        write_.wait(lock, [this]()
                    { return messages_waiting_ < box_size_; });

        basic_put(message);
        messages_waiting_++;

        box_access_.unlock();
        read_.notify_one();
    }

    int get()
    {
        // TODO : ajouter les mecanismes de synchronisation
        unique_lock lock(box_access_);
        read_.wait(lock, [this]()
                   { return messages_waiting_ > 0; });

        int message{basic_get()};
        messages_waiting_--;

        box_access_.unlock();

        write_.notify_one();

        return message;
    }

private:
    // TODO : ajouter les objets de synchronisation
    int messages_waiting_ = 0;

    typedef boost::interprocess::scoped_lock<
        boost::interprocess::interprocess_mutex>
        unique_lock;

    boost::interprocess::interprocess_mutex box_access_;
    boost::interprocess::interprocess_condition read_;
    boost::interprocess::interprocess_condition write_;
};
