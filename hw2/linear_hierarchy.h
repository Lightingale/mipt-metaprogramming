#pragma once

#include <iostream>

#include "typelist.h"

template <class T, class Base = EmptyType>
class EventHandler : public Base
{
public:
    virtual void OnEvent(T& obj, int eventId) {
        std::cout << typeid(obj).name() << ' ' << eventId << std::endl;
    }
};

template <class TypeList, template <class AtomicType, class Base> class Unit, class Root>
class GenLinearHierarchy;

template <class Head, class... Tail, template <class, class> class Unit, class Root>
class GenLinearHierarchy<TypeList<Head, Tail...>, Unit, Root>
        : public Unit<Head, GenLinearHierarchy<TypeList<Tail...>, Unit, Root>>
{
public:
    using RootInfo = typename Root::RootInfo;
};

template <class Head, template <class AtomicType, class Base> class Unit, class Root>
class GenLinearHierarchy<TypeList<Head>, Unit, Root>
        : public Unit<Head, Root>
{
public:
    using RootInfo = typename Root::RootInfo;
};


