#pragma once

#include "visitors_init.h"
#include "visitors.h"

class Acceptor {
public:
    virtual float Accept(Visitor* v) = 0;
};

class Bead : public Acceptor
{
public:
    explicit Bead(float weight, Bead* next_bead = nullptr)
        : weight_(weight), next(next_bead) {}
    float getWeight() {
        return weight_;
    }

    Bead* next;

protected:
    float weight_ = 1;
};

class GoldenBead : public Bead
{
public:
    GoldenBead(float weight, float fineness, Bead* next_bead = nullptr)
        : Bead(weight, next_bead), fineness_(fineness) {}
    float getFineness() {
        return fineness_;
    }
protected:
    float fineness_ = 0.9;
};

class DiamondBead : public Bead {};

class NecklaceBase: public Acceptor {
public:
    NecklaceBase() = delete;
    explicit NecklaceBase(Bead* bead) : root(bead) {}
    Bead* root = nullptr;
};

class GoldenChain: public NecklaceBase {};
class Rope: public NecklaceBase {};