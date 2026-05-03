#pragma once

#include <concepts>

namespace Phobos {

    template<typename T, typename ...Args>
    requires std::invocable<T, Args...>
        && std::copy_constructible<T>
    class FSMState {
        public:
        FSMState(const T function): action{function} {}
        std::invoke_result<T, Args...>::type operator()(Args&&... args) {return action(std::forward<Args>(args)...);}
        virtual void onEntering() {}
        virtual void onExiting() {}
        virtual ~FSMState() = default;

        private:
        T action;
    };

};