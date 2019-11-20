#pragma once

#include "typelist.h"

//--------- IsDerived ---------//

template<class Derived, class Base>
struct IsDerived {
    using Small = char;
    using Big = int;

    static Small Test(const Base &);

    static Big Test(...);

    static Derived makeDerived();

    static constexpr bool result = sizeof(Test(makeDerived())) == sizeof(Small);
};

//--------- Type2Type ---------//

template<typename T>
struct Type2Type {
    using type = T;
};

//--------- IsIn ---------//

template<class Tl, class Elem>
struct IsIn;

template<class Head, class... Tail, class Elem>
struct IsIn<TypeList<Head, Tail...>, Elem> {
    static constexpr bool result = IsIn<TypeList<Tail...>, Elem>::result;
};

template<class... T, class Elem>
struct IsIn<TypeList<Elem, T...>, Elem> {
    static constexpr bool result = true;
};

template<class Elem>
struct IsIn<EmptyList, Elem> {
    static constexpr bool result = false;
};

//--------- TernaryOperator ---------//

template<bool cond, class T1, class T2>
struct TernaryOperator;

template<class T1, class T2>
struct TernaryOperator<true, T1, T2> {
    using result = T1;
};

template<class T1, class T2>
struct TernaryOperator<false, T1, T2> {
    using result = T2;
};

//--------- FindTlWithElem ---------//

template<class TlOfTls, class Elem>
struct FindTlWithElem;

template<class HeadTl, class... Tail, class Elem>
struct FindTlWithElem<TypeList<HeadTl, Tail...>, Elem> {
    using result = typename TernaryOperator<
            IsIn<HeadTl, Elem>::result,
            HeadTl,
            typename FindTlWithElem<TypeList<Tail...>, Elem>::result
    >::result;
};

template<class Elem>
struct FindTlWithElem<EmptyList, Elem> {
    using result = EmptyList;
};

//--------- PushFront ---------//
// not used :(


template<class Elem, class Tl>
struct PushFront;

template<class Elem, class Head, class... T>
struct PushFront<Elem, TypeList<Head, T...>> {
    using result = TypeList<Elem, Head, T...>;
};

//--------- ReplaceFirst ---------//
// not used :(

template<class Tl, class Src, class Dst>
struct ReplaceFirst;

template<class Head, class... T, class Src, class Dst>
struct ReplaceFirst<TypeList<Head, T...>, Src, Dst> {
    using result = typename PushFront<Head, typename ReplaceFirst<TypeList<T...>, Src, Dst>::result>::result;
};

template<class... T, class Src, class Dst>
struct ReplaceFirst<TypeList<Src, T...>, Src, Dst> {
    using result = TypeList<Dst, T...>;
};

template<class Src, class Dst>
struct ReplaceFirst<EmptyList, Src, Dst> {
    using result = EmptyList;
};

//--------- MostBase ---------//

template<typename TlOfTls>
struct MostBase;

template<typename T>
struct MostBase<TypeList<T>> {
    using result = T;
};

template<typename Head, typename... Tail>
struct MostBase<TypeList<Head, Tail...>> {
private:
    using Candidate = typename MostBase<TypeList<Tail...>>::result;
public:
    using result = typename TernaryOperator<
            IsDerived<typename Candidate::Head, typename Head::Head>::result,
            Head,
            Candidate
    >::result;
};


//--------- FindElemBase ---------//
template<class Tl, class Elem>
struct FindElemBase;

template<class Head, class... Tail, class Elem>
struct FindElemBase<TypeList<Head, Tail...>, Elem> {
    using result = typename TernaryOperator<
            IsDerived<Elem, Head>::result,
            Head,
            typename FindElemBase<TypeList<Tail...>, Elem>::result
    >::result;
};

template<class Elem>
struct FindElemBase<EmptyList, Elem> {
    using result = EmptyList;
};
