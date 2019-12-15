#include <iostream>

#include "functor.h"
#include "visitors.h"
#include "executors.h"
#include "dispatcher.h"

struct TestFunctor {
    int operator()(const std::string& s, bool b) {
        if (b) {
            std::cout << s << '\n';
            return 64;
        }
        else {
            std::cout << "false" << '\n';
            return 83;
        }
    }
};

int test_func(const std::string& s, bool b) {
    if (b) {
        std::cout << s << '\n';
        return 64;
    }
    else {
        std::cout << "false" << '\n';
        return 83;
    }
}

template <class... Args>
void f(Args... args) {
    ArgumentTypesFormatter af;
    af.FormatArgs(args...);
    std::cout << af.GetResult() << '\n';
}

int main() {
    std::cout << "Functor test: \n";
    TestFunctor tf;
    Functor<int, const std::string&, bool> fun(test_func);
    Functor<int, const std::string&, bool> fun1(tf);

    int res_true = fun("test1", true);
    int res_false = fun1("test2", false);
    std::cout << res_true << ' ' <<  res_false << '\n';

    std::cout << "ArgumentTypesFormatter test: \n";
    f(5, tf);

    std::cout << "Dispatcher test: \n";
    StaticDispatcher<
            Visitor, TypeList<PriceCalculator, NecklacePrinter>,
            Acceptor, TypeList<GoldenChain, Rope>,
            std::string, double
            > staticDispatcher;

    PriceCalculator priceCalculator;
    NecklacePrinter necklacePrinter;

    GoldenChain goldenChain(
            new GoldenBead(5.0, 0.8,
                    new GoldenBead(1.0,
                            new DiamondBead(1.0,
                                    new GoldenBead(2.0, 1.0)))));
    Rope rope(
            new DiamondBead(4.0,
                    new GoldenBead(4.0,
                            new DiamondBead(4.0))));

    std::string result1 = staticDispatcher.Go(&priceCalculator, &rope, 0.0);
    std::cout << result1 << '\n';
    std::string result2 = staticDispatcher.Go(&priceCalculator, &goldenChain, 0.5);
    std::cout << result2 << '\n';
    std::string result3 = staticDispatcher.Go(&necklacePrinter, &rope, 0.0);
    std::cout << result3 << '\n';
    std::string result4 = staticDispatcher.Go(&necklacePrinter, &goldenChain, 0.5);
    std::cout << result4 << '\n';


    WrongChain wrongChain(new DiamondBead(5.));
    std::string result5 = staticDispatcher.Go(&necklacePrinter, &wrongChain, 0.5);
    std::cout << result5 << '\n';

    WrongVisitor wrongVisitor;
    std::string result6 = staticDispatcher.Go(&wrongVisitor, &goldenChain, 0.5);
    std::cout << result6 << '\n';

    StaticDispatcher<
            Visitor, TypeList<PriceCalculator, NecklacePrinter>,
            Acceptor, TypeList<GoldenChain, Rope>,
            std::string, double, std::string
            > wrongStaticDispatcher;
    std::string result7 = wrongStaticDispatcher.Go(&necklacePrinter, &goldenChain, 0.5, "wrong param");
    std::cout << result7 << '\n';

    StaticDispatcher<
            Visitor, TypeList<PriceCalculator, NecklacePrinter>,
            Acceptor, TypeList<GoldenChain, Rope>,
            std::string
            > wrongStaticDispatcher2;
    std::string result8 = wrongStaticDispatcher2.Go(&necklacePrinter, &goldenChain);
    std::cout << result8 << '\n';

    return 0;
}