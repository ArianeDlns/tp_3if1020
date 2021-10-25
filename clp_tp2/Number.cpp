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
}
