#pragma once

#include <concepts>

namespace Phobos {
    
    template<typename T, typename ...Args>
    concept StateCallType = std::invocable<T, Args...> && std::copy_constructible<T>;
    
    template<typename KeyType, typename StateCallType, typename ...Args>
    class FSMState {
        public:
        FSMState(const StateCallType function): action{function} {}
        std::invoke_result<StateCallType, Args...>::type operator()(Args&&... args) {return action(std::forward<Args>(args)...);}
        virtual void onEntering(KeyType input) {}
        virtual void onExiting(KeyType output) {}
        virtual ~FSMState() = default;

        private:
        StateCallType action;
    };

};