/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */
class MessageBox : public BasicMessageBox {
public:
    void put( int message ) {
        // TODO : ajouter les mecanismes de synchronisation
        unique_lock lock(box_mutex_);
        send_.wait(lock, [this]() { return inbox_messages_ < box_size_; });

        basic_put( message );
        inbox_messages_++;

        box_mutex_.unlock();    
        receive_.notify_one();
    }
 
    int get() {
        // TODO : ajouter les mecanismes de synchronisation
        unique_lock lock(box_mutex_);
        receive_.wait(lock, [this]() { return  0 < inbox_messages_; });

        int message{ basic_get() };
        inbox_messages_--;

        box_mutex_.unlock();    
        send_.notify_one();
        return message;
    }
private:
    // TODO : ajouter les objets de synchronisation
    int inbox_messages_ = 0;

    std::mutex box_mutex_;
    typedef std::unique_lock<std::mutex> unique_lock;

    std::condition_variable receive_;
    std::condition_variable send_;

};
 
