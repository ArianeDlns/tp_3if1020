/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * TestExpression.cpp
 * c++ -std=c++20 -o TestExpression TestExpression.cpp Expression.cpp -lgtest -lpthread
 */


// [Question]: Ajouter les attributs et les associations. Un opérateur peut soit posséder ses opérandes (composition), soit simplement les connaître (association simple ou agrégation) : quelle est la bonne sémantique à retenir ici ?
// [Réponse]: 

// [Question]: Quel est l'intérêt d'avoir une super-classe Operation ?
// [Réponse]: 

// [Question]:  Définir la sémantique précise du comportement de dérivation d'une expression par rapport à une variable (la méthode recevra le nom de la variable en argument) : ce comportement doit-il modifier l'instance courante ou créer une nouvelle instance représentant la dérivée de l'objet courant ?
// [Réponse]: 

#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "Expression.hpp"

TEST(TestNombre, TestNumber0)
{
    Nombre n{0};
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "0");
}

TEST(TestNombre, TestNumber123)
{
    Nombre n{1.23};
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "1.23");
}

TEST(TestVariable, TestVar)
{
    Variable n{"Var"};
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "Var");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
