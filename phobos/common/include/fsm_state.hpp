#pragma once

#include <concepts>

namespace Phobos {
    
    template<typename T, typename ...Args>
    concept FSMStateCallType = std::invocable<T, Args...> && std::movable<T>;
    
    template<typename SignalType, typename StateCallType , typename ...Args>
        requires  FSMStateCallType<StateCallType, Args...> 
    class FSMState {
        public:
        FSMState(const StateCallType &function): action{function} {}
        FSMState(const FSMState &other) = default;
        FSMState(FSMState &&other) = default;
        FSMState& operator=(const FSMState &other) = default;
        FSMState& operator=(FSMState &&other) = default;

        std::invoke_result<StateCallType, Args...>::type operator()(Args&&... args) {return action(std::forward<Args>(args)...);}
        virtual void onEntering(SignalType input) {}
        virtual void onExiting(SignalType output) {}
        StateCallType getAction() const {return action;}
        virtual ~FSMState() = default;

        private:
        StateCallType action;
    };

};