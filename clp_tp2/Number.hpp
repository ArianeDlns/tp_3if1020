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
#include <math.h>

class Number
{
public:
    // Instantiation
    Number(unsigned long l) { first_ = new Digit(l); }
    // Affectation par copie
    Number(const Number &n) { first_ = new Digit(*(n.first_)); }
    // Affectation
    Number &operator=(Number n)
    {
        using std::swap;
        swap(first_, n.first_);
        return *this;
    }
    // Constructeur
    Number(std::string s)
    {
        if (s == "")
        {
            throw std::invalid_argument("La chaîne de caractères vide");
        }
        std::reverse(s.begin(), s.end());
        first_ = new Digit(s);
    }
    // Destructeur
    ~Number() { delete first_; }

    // Print
    void print(std::ostream &out) const { first_->print(out); }
    // Add
    void add(unsigned int i) { first_->add(i); }
    // Multiply
    void multiply(unsigned int i) { first_->multiply(i); }

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
        /// Constructeur
        Digit(std::string s)
        {
            digit_ = 0;
            unsigned long i = 0;
            unsigned long max = log10(number_base);
            unsigned long nb = std::min(max, static_cast<unsigned long>(s.size()));
            for (i = 0; i < nb; i++)
            {
                if (!std::isdigit(s[i]))
                {
                    throw std::invalid_argument("Un caractère n'est pas un nombre");
                }
                DigitType d = static_cast<unsigned int>(s[i] - '0');
                digit_ = pow(10, i) * d;
            }
            s.erase(0, nb);
            if (s.empty())
                next_ = nullptr;
            else
                next_ = new Digit(s);
        }
        // Affectation par copie
        Digit(const Digit &d)
        {
            if (next_)
            {
                next_ = nullptr;
            }
            if (d.next_)
            {
                this->next_ = new Digit(*(d.next_));
            }
            this->digit_ = d.digit_;
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
        // Add
        void add(DigitType i)
        {
            DigitType d = static_cast<unsigned long>(digit_ + i) / number_base;
            digit_ = static_cast<unsigned long>(digit_ + i) % number_base;
            if (next_ != nullptr)
            {
                next_->add(d);
            }
            else if (d != 0)
            {
                next_ = new Digit(d);
            }
        }
        // Multiply
        void multiply(DigitType i)
        {
            unsigned long new_value = digit_ * i;
            DigitType d = new_value / number_base;
            digit_ = new_value % number_base;
            if (next_ != nullptr)
            {
                next_->multiply(i);
                next_->add(d);
            }
            else if (d != 0)
            {
                next_ = new Digit(d);
            }
        }
    };
    Digit *first_;
};

inline std::ostream &operator<<(std::ostream &out, const Number &n)
{
    n.print(out);
    return out;
}
Number factorial(unsigned int i);

#endif
