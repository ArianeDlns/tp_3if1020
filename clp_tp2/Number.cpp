/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.cpp
 */

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "Number.hpp"

Number factorial(unsigned int i)
{
    Number n{1};
    while (i > 0) {
        n.multiply(i);
        i -= 1;
    }
    return n;
};

std::istream &operator>>(std::istream &in, Number &n)
{
    // in est le flux d'entrée
    std::string str{""};
    // ignore les blancs au début
    in >> std::ws;
    while (in.good())
    {
        int c{in.get()};
        if (std::isdigit(c))
        {
            unsigned int d{static_cast<unsigned int>(c - '0')};
            str = str + std::to_string(d);
        }
        else
        {
            in.putback(c);
            break;
        }
    }
    n = Number{str};
    return in;
}
