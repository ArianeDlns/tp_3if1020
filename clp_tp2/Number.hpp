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
    Number(unsigned long l) { first_ = new Digit(l); }
    ~Number() { delete first_; }

    void print(std::ostream &out) const { first_ -> print(out); }

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
