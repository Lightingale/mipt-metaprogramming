#pragma once

#include "typelist.h"
#include "executors.h"

template <
        class Visitor, class VisitorsTL,
        class Acceptor, class AcceptorsTL,
        class DispatcherRT,
        class... Args
        >
class StaticDispatcher
{
public:

    using VisitorsHead = typename VisitorsTL::Head;
    using AcceptorsHead = typename AcceptorsTL::Head;

    using VisitorsTail = typename VisitorsTL::Tail;
    using AcceptorsTail = typename AcceptorsTL::Tail;

    static DispatcherRT Go(Visitor* visitor, Acceptor* acceptor, Args... args) {
        auto visitor_head = dynamic_cast<VisitorsHead*>(visitor);
        if (visitor_head) {
            return StaticDispatcher<
                    Visitor, VisitorsTL, Acceptor, AcceptorsTL, DispatcherRT, Args...
                    >::DispatchAcceptor(visitor, acceptor, args...);
        }
        else {
            return StaticDispatcher<
                    Visitor, VisitorsTail, Acceptor, AcceptorsTL, DispatcherRT, Args...
                    >::Go(visitor, acceptor, args...);
        }
    }

    static DispatcherRT DispatchAcceptor(Visitor* visitor, Acceptor* acceptor, Args... args) {
        auto acceptor_head = dynamic_cast<AcceptorsHead*>(acceptor);
        if (acceptor_head) {
            acceptor_head->Accept(visitor);
            Executor<DispatcherRT, VisitorsHead, AcceptorsHead, Args...> fun;
            return fun(static_cast<VisitorsHead*>(visitor), acceptor_head, args...);
        }
        else {
            return StaticDispatcher<
                    Visitor, VisitorsTL, Acceptor, AcceptorsTail, DispatcherRT, Args...
                    >::DispatchAcceptor(visitor, acceptor, args...);
        }
    }
};

template <
        class Visitor,
        class Acceptor, class AcceptorsTL,
        class DispatcherRT,
        class... Args
>
class StaticDispatcher<Visitor, EmptyList, Acceptor, AcceptorsTL, DispatcherRT, Args...> {
public:
    static DispatcherRT Go(Visitor* visitor, Acceptor* acceptor, Args... args) {
        Executor<DispatcherRT, Visitor, Acceptor, Args...> fun;
        fun.OnError('v');
        return DispatcherRT();
    }
};

template <
        class Visitor, class VisitorsTL,
        class Acceptor,
        class DispatcherRT,
        class... Args
>
class StaticDispatcher<Visitor, VisitorsTL, Acceptor, EmptyList, DispatcherRT, Args...> {
public:
    static DispatcherRT DispatchAcceptor(Visitor* visitor, Acceptor* acceptor, Args... args) {
        Executor<DispatcherRT, Visitor, Acceptor, Args...> fun;
        fun.OnError('a');
        return DispatcherRT();
    }
};
