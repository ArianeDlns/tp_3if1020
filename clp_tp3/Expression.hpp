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

private:
    std::string var_;
};

inline std::ostream &Variable::print(std::ostream &out) const
{
    return out << this->var_;
}

#endif
