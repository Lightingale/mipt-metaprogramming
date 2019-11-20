#pragma once
#include "typelist.h"

template<class T>
class Unit {
    T value_ = T();
public:
    T GetValue(){
        return value_;
    }
};

template<>
class Unit<std::string> {
    std::string value_ = "test";
public:
    std::string GetValue(){
        return value_;
    }
};

template<class TL, template<class> class Unit>
class GenScatterHierarchy;

template<class Head, class... Tail, template<class> class Unit>
class GenScatterHierarchy<TypeList<Head, Tail...>, Unit>
        : public Unit<Head>,
          public GenScatterHierarchy<TypeList<Tail...>, Unit> {
public:
    using TList = TypeList<Head, Tail...>;
    using LeftBase = Unit<Head>;
    using RightBase = GenScatterHierarchy<TypeList<Tail...>, Unit>;
};

template<class Head, template<class> class Unit>
class GenScatterHierarchy<TypeList<Head>, Unit>
    : public Unit<Head> {
public:
    using TList = Head;
    using LeftBase = Unit<Head>;
    using RightBase = EmptyList;
};


