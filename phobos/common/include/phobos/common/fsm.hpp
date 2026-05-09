#pragma once

#include <concepts>
#include <initializer_list>
#include <map>
#include <functional>

#include "phobos/common/definitions.hpp"
//#include "phobos/common/fsm_state.hpp"

namespace Phobos {
    
    template <Phobos::ValidKey KeyType, typename SignalType, typename ...Args>
    class FSM {
        public:
            using ActionType = std::function<void(FSM<KeyType, SignalType, Args...>*, Args...)>;

            struct FSMStateTuple {
                KeyType key;
                ActionType action;
            };

            struct FSMTransition {
                KeyType sourceStateKey;
                SignalType signal;
                KeyType nextStateKey;                
            };

            template <std::ranges::input_range FSMStateTupleRange, std::ranges::input_range FSMTransitionRange>
                requires std::convertible_to<std::ranges::range_value_t<FSMStateTupleRange>, FSMStateTuple> 
                            && std::convertible_to<std::ranges::range_value_t<FSMTransitionRange>, FSMTransition>
            FSM(const KeyType &initialState,
                const FSMStateTupleRange &statesList,
                const FSMTransitionRange &transitionsList)
                        : currentStateKey{initialState}
            {
                for( const auto &stateTuple: statesList) {
                    states.insert_or_assign(stateTuple.key, stateTuple.action);
                }
                for(const auto &transition: transitionsList) {
                    transitionsMap[transition.sourceStateKey][transition.signal] = transition.nextStateKey;
                }
                currentStateCall = (states[currentStateKey]);
            }

            virtual void afterStateChanged(SignalType signal, KeyType previousState) {
                std::cout<< " left " << previousState << std::endl;
            }

            virtual void beforeStateChanged(SignalType signal, KeyType newState) {
                std::cout<< " going  " << newState << std::endl;
            }


            void operator()(Args&& ...args) {currentStateCall(this, std::forward<Args>(args)...);}

            KeyType signal(const SignalType &&signal) {
                auto &transition = transitionsMap[currentStateKey];
                if (const auto stateIt =transition.find(signal); stateIt != transition.end()) {
                    auto prevKey = currentStateKey;
                    beforeStateChanged(signal, stateIt->second);
                    currentStateKey = stateIt->second;
                    currentStateCall = states[stateIt->second];
                    afterStateChanged(signal, prevKey);
                }
                return currentStateKey;
            }

            virtual ~FSM() = default;

        private:
            KeyType currentStateKey;
            ActionType currentStateCall;
            std::map<KeyType, std::map<SignalType,KeyType>> transitionsMap;
            std::map<KeyType, ActionType> states;
    }; 
};