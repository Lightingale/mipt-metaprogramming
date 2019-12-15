#pragma once

class NecklaceBase;
class Rope;
class GoldenChain;
class WrongChain;

class Bead;
class GoldenBead;
class DiamondBead;

class Visitor {
public:
    virtual void Visit(GoldenChain*) = 0;
    virtual void Visit(Rope*) = 0;

    virtual void Visit(GoldenBead*) = 0;
    virtual void Visit(DiamondBead*) = 0;

    // for test
    virtual void Visit(WrongChain*) {
        std::cerr << "Wrong visit";
    }
};

