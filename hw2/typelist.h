#pragma once

#include <iostream>

struct EmptyType {
    using RootInfo = void*;
};

template<typename... T>
struct TypeList {
    using Head = EmptyType;
    using Tail = EmptyType;
};

using EmptyList = TypeList<>;

template<typename H, typename... T>
struct TypeList<H, T...> {
    using Head = H;
    using Tail = TypeList<T...>;
};

template<typename TL>
void PrintTypeList() {
    std::cout << typeid(typename TL::Head).name() << ' ';
    PrintTypeList<typename TL::Tail>();
};

template<>
void PrintTypeList<EmptyList>() {
    std::cout << "";
    std::cout << std::endl;
};

