/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.hpp
 */

#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>
#include <memory>

class Expression
{
public:
    Expression(){};
    virtual ~Expression(){};
    virtual std::ostream &print(std::ostream &out) const = 0;

    virtual Expression *derive(std::string nom) const = 0;
    /* Expression::derive
     Derives an expression by the variable "nom"
     Input:
        - string : the name of the variable
     Output:
        - A newly allocated Expression* element
     */

private:
};

inline std::ostream &operator<<(std::ostream &out, const Expression &exp)
{
    exp.print(out);
    return out;
}

class Nombre : public Expression
{
public:
    Nombre(float valeur)
    {
        this->valeur_ = valeur;
    };
    ~Nombre(){};
    std::ostream &print(std::ostream &out) const override;
    Expression *derive(std::string valeur) const override
    {
        return new Nombre{0};
    }

private:
    float valeur_;
};

inline std::ostream &Nombre::print(std::ostream &out) const
{
    return out << this->valeur_;
}

class Variable : public Expression
{
public:
    Variable(std::string var)
    {
        this->var_ = var;
    };
    ~Variable(){};
    std::ostream &print(std::ostream &out) const override;
    Expression *derive(std::string var) const override
    {
        if (var_ == var)
        {
            return new Nombre{1};
        }
        return new Nombre{0};
    }

private:
    std::string var_;
};

inline std::ostream &Variable::print(std::ostream &out) const
{
    return out << this->var_;
}

#endif
