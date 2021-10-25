/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.hpp
 */

#ifndef NUMBER_HPP_INCLUDED
#define NUMBER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>

class Number
{
public:
    // Instantiation
    Number(unsigned long l) { first_ = new Digit(l); }
    // Affectation par copie
    Number(const Number &n) { first_ = new Digit(*(n.first_)); }
    // Affectation
    Number &operator=(const Number &n)
    {
        first_ = new Digit(*n.first_);
        return *this;
    }
    // Destructeur
    ~Number() { delete first_; }

    void print(std::ostream &out) const { first_->print(out); }

private:
    using DigitType = unsigned int;
    // Un seul chiffre décimal par maillon : l'objectif ici n'est pas la performance
    static const DigitType number_base{10u};
    struct Digit
    {
        DigitType digit_;
        Digit *next_;
        Digit(unsigned long l)
        {
            if (l < number_base)
            {
                digit_ = (DigitType)l;
                next_ = nullptr;
            }
            else
            {
                unsigned long divide{l / number_base};
                unsigned long reste{l % number_base};
                digit_ = (DigitType(reste));
                next_ = new Digit(divide);
            }
        }
        // Affectation par copie
        Digit(const Digit &d)
        {
            digit_ = d.digit_;
            if (d.next_ != nullptr)
            {
                Digit *next = new Digit(*(d.next_));
                next_ = next;
            }
        }
        // Affectation
        Digit &operator=(const Digit &d)
        {
            digit_ = d.digit_;
            if (d.next_ != nullptr)
            {
                next_ = new Digit(*(d.next_));
            }
            return *this;
        }
        // Destructeur
        ~Digit()
        {
            if (next_ != nullptr)
                delete next_;
        }
        void print(std::ostream &out) const
        {
            if (next_ != nullptr)
            {
                next_->print(out);
            }
            out << digit_;
        }
    };
    Digit *first_;
};

inline std::ostream &operator<<(std::ostream &out, const Number &n)
{
    n.print(out);
    return out;
}

#endif
