#pragma once

#include <memory>

#include "typelist.h"


template <typename ResultType, typename... Args>
class FunctorImpl
{
public:
    virtual ResultType operator()(Args...) = 0;
    virtual ~FunctorImpl() = default;
};

template <typename Fun, typename RT, typename... Args>
class FunctorHandler:
        public FunctorImpl<RT, Args...>
{
public:
    using ResultType = RT;

    explicit FunctorHandler(Fun& fun) : fun_(&fun) {};

    ResultType operator()(Args... args) override {
        return (*fun_)(args...);
    }

private:
    Fun* fun_;
};

template <typename RT, typename... Args>
class Functor
{
private:
    using Impl = FunctorImpl<RT, Args...>;
public:
    using ResultType = RT;

    Functor() = delete;
    Functor& operator=(const Functor& other) = default;

    explicit Functor(std::shared_ptr<Impl> spImpl) : spImpl_(spImpl) {}

    template <class Fun>
    explicit Functor(Fun& fun) :
        spImpl_(std::make_shared<FunctorHandler<Fun, RT, Args...>>(fun))
    {}

    RT operator()(Args... args) {
        return spImpl_->operator()(args...);
    }
private:
    std::shared_ptr<Impl> spImpl_;
};
