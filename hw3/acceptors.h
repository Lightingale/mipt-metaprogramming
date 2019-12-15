#pragma once

#include "acceptors_visitors_init.h"

class Acceptor {
public:
    virtual void Accept(Visitor* v) = 0;
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
    virtual ~Bead() = default;

protected:
    float weight_ = 1.;
};

class GoldenBead : public Bead
{
public:
    explicit GoldenBead(float weight, Bead* next_bead = nullptr)
            : Bead(weight, next_bead) {}
    GoldenBead(float weight, float fineness, Bead* next_bead = nullptr)
        : Bead(weight, next_bead), fineness_(fineness) {}

    float getFineness() {
        return fineness_;
    }

    void Accept(Visitor* v) override {
        return v->Visit(this);
    }

protected:
    float fineness_ = 0.9;
};

class DiamondBead : public Bead {
public:
    explicit DiamondBead(float weight, Bead* next_bead = nullptr) : Bead(weight, next_bead) {};

    void Accept(Visitor* v) override {
        return v->Visit(this);
    }
};

class NecklaceBase: public Acceptor {
public:
    NecklaceBase() = delete;
    explicit NecklaceBase(Bead* bead) : root(bead) {}
    Bead* root = nullptr;
    virtual ~NecklaceBase() {
        Bead* bead = root;
        while (bead != nullptr) {
            Bead* next_del = bead->next;
            delete bead;
            bead = next_del;
        }
    }
};

class GoldenChain: public NecklaceBase {
public:
    explicit GoldenChain(Bead* bead) : NecklaceBase(bead) {}
    void Accept(Visitor* v) override {
        return v->Visit(this);
    }
};

class Rope: public NecklaceBase {
public:
    explicit Rope(Bead* bead) : NecklaceBase(bead) {}

    void Accept(Visitor* v) override {
        return v->Visit(this);
    }

};

class WrongChain: public NecklaceBase
{
public:
    explicit WrongChain(Bead* bead) : NecklaceBase(bead) {}

    void Accept(Visitor* v) override {
        return v->Visit(this);
    }
};