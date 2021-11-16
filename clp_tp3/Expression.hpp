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
    Expression() { counter_++; };
    virtual ~Expression() { counter_--; };
    static int counter_;
    virtual std::ostream &print(std::ostream &out) const = 0;
    virtual Expression *derive(std::string nom) const = 0;
    virtual Expression *copy() const = 0;
    virtual std::string toString() const = 0;

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
    Nombre(int valeur)
    {
        this->valeur_ = valeur;
    };
    ~Nombre(){};
    std::ostream &print(std::ostream &out) const override;
    Expression *derive(std::string valeur) const override
    {
        return new Nombre{0};
    };
    Nombre *copy() const override { return new Nombre{valeur_}; };
    std::string toString() const override
    {
        return std::to_string(valeur_);
    };

private:
    int valeur_;
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
    };
    Variable *copy() const override { return new Variable{var_}; };
    std::string toString() const override
    {
        return var_;
    };

private:
    std::string var_;
};

inline std::ostream &Variable::print(std::ostream &out) const
{
    return out << this->var_;
}

class Operation : public Expression
{
public:
    Operation(Expression *left, Expression *right) : Expression()
    {
        op_left_ = left;
        op_right_ = right;
    }
    ~Operation()
    {
        delete op_left_;
        delete op_right_;
    }
    std::string toString() const override
    {
        return "";
    }

protected:
    Expression *op_left_;
    Expression *op_right_;

private:
};

class Addition : public Operation
{
public:
    Addition(Expression *left, Expression *right) : Operation(left, right) {}
    ~Addition() {}

    std::string toString() const override
    {
        return "(" + op_left_->toString() + " + " + op_right_->toString() + ")";
    }
    std::ostream &print(std::ostream &out) const override
    {
        return out << Addition::toString();
    }
    Addition *copy() const override { return new Addition(op_left_->copy(), op_right_->copy()); }
    Addition *derive(std::string variableName) const override
    {
        Expression *left_dev = op_left_->derive(variableName);
        Expression *right_dev = op_right_->derive(variableName);
        Addition *e = new Addition(left_dev, right_dev);
        return e;
    }

private:
};

class Multiply : public Operation
{
public:
    Multiply(Expression *left, Expression *right) : Operation(left, right) {}
    ~Multiply() {}

    std::string toString() const override
    {
        return "(" + op_left_->toString() + " * " + op_right_->toString() + ")";
    }
    std::ostream &print(std::ostream &out) const override
    {
        return out << Multiply::toString();
    }
    Multiply *copy() const override { return new Multiply(op_left_->copy(), op_right_->copy()); }

    Addition *derive(std::string variableName) const override
    {
        Expression *u = op_left_->copy();
        Expression *v = op_right_->copy();

        Expression *up = op_left_->derive(variableName);
        Expression *vp = op_right_->derive(variableName);

        Multiply *vp_u = new Multiply(vp, u);
        Multiply *up_v = new Multiply(up, v);

        Addition *e = new Addition(up_v, vp_u);
        return e;
    }

private:
};

#endif
