#pragma once

#include "acceptors.h"
#include <string>

class PriceCalculator : public Visitor {
public:
    void Visit(Rope* rope) override {
        price_ = 0.;
        if (rope == nullptr) {
            return;
        }
        necklacePiecePrice_ = ropePrice_;
        rope->root->Accept(this);
    }

    void Visit(GoldenChain* goldenChain) override {
        price_ = 0.;
        if (goldenChain == nullptr) {
            return;
        }
        necklacePiecePrice_ = goldenChainPrice_;
        goldenChain->root->Accept(this);
    }


    void Visit(GoldenBead* goldenBead) override {
        double weight = goldenBead->getWeight();
        double fineness = goldenBead->getFineness();
        price_ += (goldenBeadPrice_ * weight * fineness
                  + impurityPrice_ * weight * (1 - fineness)
                  + necklacePiecePrice_);
        if (goldenBead->next != nullptr) {
            goldenBead->next->Accept(this);
        }
    }

    void Visit(DiamondBead* diamondBead) override {
        double weight = diamondBead->getWeight();
        price_ += diamondBeadPrice_ * weight + necklacePiecePrice_;
        if (diamondBead->next != nullptr) {
            diamondBead->next->Accept(this);
        }
    }

    double GetPrice() {
        return price_;
    }

private:
    double price_ = 0;
    double goldenBeadPrice_ = 7.0;
    double impurityPrice_ = 1.0;
    double diamondBeadPrice_ = 5.0;
    double goldenChainPrice_ = 0.5;
    double ropePrice_ = 0.1;
    double necklacePiecePrice_ = 0.0;
};

class NecklacePrinter: public Visitor {
public:
    void Visit(Rope* rope) override {
        result_ = "";
        if (rope == nullptr) {
            result_ = "Empty necklace";
            return;
        }
        result_ += "Rope based necklace: -";
        rope->root->Accept(this);
    }

    void Visit(GoldenChain* goldenChain) override {
        result_ = "";
        if (goldenChain == nullptr) {
            result_ = "Empty necklace";
            return;
        }
        result_ += "Golden chain based necklace: -";
        goldenChain->root->Accept(this);
    }

    void Visit(GoldenBead* goldenBead) override {
        result_ += goldenBeadSymbol_;
        if (goldenBead->next != nullptr) {
            goldenBead->next->Accept(this);
        }
        else {
            result_ += '-';
        }
    }

    void Visit(DiamondBead* diamondBead) override {
        result_ += diamondBeadSymbol_;
        if (diamondBead->next != nullptr) {
            diamondBead->next->Accept(this);
        }
        else {
            result_ += '-';
        }
    }

    std::string GetResult() {
        return result_;
    }

private:
    std::string result_ = "";
    char goldenBeadSymbol_ = 'o';
    char diamondBeadSymbol_ = '*';
};

class WrongVisitor : public Visitor {
public:
    void Visit(Rope* rope) override {
        std::cerr << "Wrong visitor" << '\n';
    }

    void Visit(GoldenChain* goldenChain) override {
        std::cerr << "Wrong visitor" << '\n';
    }

    void Visit(GoldenBead* goldenBead) override {
        std::cerr << "Wrong visitor" << '\n';
    }

    void Visit(DiamondBead* diamondBead) override {
        std::cerr << "Wrong visitor" << '\n';
    }
};