#pragma once

#include "functor.h"
#include "acceptors.h"
#include "visitors.h"

class ArgumentTypesFormatter
{
public:
    template <class FirstArgType, class... Args>
    void FormatArgs(FirstArgType firstArg, Args... args) {
        result_ += typeid(FirstArgType).name();
        result_ += ", ";
        FormatArgs<Args...>(args...);
    };

    template <class Arg>
    void FormatArgs(Arg arg) {
        result_ += typeid(Arg).name();
    }

    void FormatArgs() {
        result_ = "(empty arguments list)";
    }

    std::string GetResult() {
        return result_;
    }
private:
    std::string result_;
};

void PrintArgs() {
    std::cout << "(no arguments)";
}

template <class Arg>
void PrintArgs(Arg arg) {
    std::cout << arg;
}

template <class FirstArgType, class... Args>
void PrintArgs(FirstArgType firstArg, Args... args) {
    std::cout << firstArg << ", ";
    PrintArgs(args...);
}


template <typename ResultType, class Visitor, class Acceptor, class... Args>
class Executor : public FunctorImpl<ResultType, Visitor*, Acceptor*, Args...> {
public:
    ResultType operator()(Visitor* visitor, Acceptor* acceptor, Args... args) override  {
        ArgumentTypesFormatter af;
        af.FormatArgs(args...);
        std::cout << "No definition found for arguments with typeids: " << af.GetResult() << '\n' << "Arguments: ";
        PrintArgs(args...);
        return ResultType();
    }
    void OnError(char what) {
        if (what == 'a') {
            std::cerr << "No matching acceptors" << '\n';
        }
        else if (what == 'v') {
            std::cerr << "No matching visitors" << '\n';
        }
        else {
            std::cerr << "Unknown error" << '\n';
        }
    }
};

template<>
class Executor<std::string, PriceCalculator, GoldenChain, double>
        : public FunctorImpl<std::string, PriceCalculator*, GoldenChain*, double>
{
public:
    std::string operator()(PriceCalculator* priceCalculator, GoldenChain* goldenChain, double discount) override {
        // additional discount for gold
        return "Total price: " + std::to_string(priceCalculator->GetPrice() * (1 - discount - 0.05));
    }
};

template<>
class Executor<std::string, PriceCalculator, Rope, double>
        : public FunctorImpl<std::string, PriceCalculator*, Rope*, double>
{
public:
    std::string operator()(PriceCalculator* priceCalculator, Rope* rope, double discount) override {
        return "Total price: " + std::to_string(priceCalculator->GetPrice() * (1 - discount));
    }
};

template<>
class Executor<std::string, NecklacePrinter, GoldenChain, double>
        : public FunctorImpl<std::string, NecklacePrinter*, GoldenChain*, double>
{
public:
    std::string operator()(NecklacePrinter* necklacePrinter, GoldenChain* goldenChain, double discount) override {
        return necklacePrinter->GetResult() + " with discount " + std::to_string(discount + 0.05);
    }
};

template<>
class Executor<std::string, NecklacePrinter, Rope, double>
        : public FunctorImpl<std::string, NecklacePrinter*, Rope*, double>
{
public:
    std::string operator()(NecklacePrinter* necklacePrinter, Rope* rope, double discount) override {
        return necklacePrinter->GetResult() + " with discount " + std::to_string(discount);
    }
};

