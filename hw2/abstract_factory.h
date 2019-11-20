#pragma once

#include "typelist_operations.h"
#include "scatter_hierarchy.h"
#include "linear_hierarchy.h"

template<class T>
struct FactoryUnit {
    virtual T* DoGet(Type2Type<T> type) = 0;

    virtual ~FactoryUnit() = default;
};

template<typename TL>
struct AbstractFactory : public GenScatterHierarchy<TL, FactoryUnit> {
    using RootInfo = TL;
    template<class T>
    typename FindElemBase<TL, T>::result* Get() {
        using BaseT = typename FindElemBase<TL, T>::result;
        FactoryUnit<BaseT>& unit = *this;
        return unit.DoGet(Type2Type<BaseT>());
    }
};

template<class ConcreteT, class Base>
class ConcreteFactoryUnit : public Base {
public:
    using BaseProductList = typename Base::RootInfo;
    using BaseT = typename FindElemBase<BaseProductList, ConcreteT>::result;
    BaseT* DoGet(Type2Type<BaseT>) override {
        return new ConcreteT;
    }
};

template<int n, int m, class... Tls>
class GetAbstractFactory {
private:
    using TlOfTls = TypeList<Tls...>;
    using BaseTl = typename MostBase<TlOfTls>::result;
public:
    using BaseFactory = AbstractFactory<BaseTl>;
    template<class T>
    struct GetConcreteFactory {
        using ConcreteTs = typename FindTlWithElem<TlOfTls, T>::result;
        using result = GenLinearHierarchy<ConcreteTs, ConcreteFactoryUnit, BaseFactory>;
    };
};
