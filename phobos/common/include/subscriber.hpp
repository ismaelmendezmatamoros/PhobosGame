#pragma once

#include "definitions.hpp"
#include "publisher.hpp"

#include <concepts>
#include <queue>
#include <map>
#include <memory>
#include <list>
#include <ranges>

namespace Phobos {

    template<std::copy_constructible T>
    class Subscriber;

    template<std::copy_constructible T>
    class Publisher;

    using SubscriptionControlBlockKeyType = std::pair<intptr_t, intptr_t>;
    template<std::copy_constructible T>
    struct SubscriptionControlBlock {
        
        Subscriber<T> *subscriber;
        Publisher<T> *publisher;
        std::queue<T> data;
    };

    template<std::copy_constructible T>
    class Subscriber {
        public:
            Subscriber() = default;
            ~Subscriber() {
                for (auto &[id, controlBlock] : controlBlocks) {
                    controlBlock.get()->reset();
                }
            }
            

            Subscriber(Subscriber &&other) {
                move(std::forward(other));
            }

            Subscriber &operator=(Subscriber &&other) {
                move(std::forward(other));
            }

            Subscriber(const Subscriber &other) {
                move(std::forward(other));
            }

            Subscriber &operator=(const Subscriber &other) {
                move(std::forward(other));
            }

            void subscribe(const Publisher<T> *publisher) {
                if (!publisher)
                    return;
            }

            bool unsubscribe(const Publisher<T> *publisher) {
                if (!publisher)
                    return false;

                SubscriptionControlBlockKeyType key{publisher, this};
                auto it = controlBlocks.find(key);
                if (it == controlBlocks.end())
                    return false;
                it->second.get()->reset();
                
                return controlBlocks.erase(it->first) > 0;
            }

            int clearDeadPublishers() {
                auto eraseIfCheck = [](const auto& item) {
                    return !item || !*item;
                };
                return controlBlocks.erase_if(eraseIfCheck);
                
            }

            int numSubscriptions() const {
                clearDeadPublishers();
                return controlBlocks.size();
            }

            std::list<Publisher<T>*> getPublishers() const {
                clearDeadPublishers();
                auto getPublisherFunc = [](const auto &key) {
                    return static_cast<Publisher<T>*>(key.publisher);
                };
                return controlBlocks | std::views::keys | std::views::transform(getPublisherFunc) | std::ranges::to<std::list>;
            }

        protected:
            void move(Subscriber &&other) {
                
            }

            std::map<SubscriptionControlBlockKeyType, std::shared_ptr<std::unique_ptr<SubscriptionControlBlock<T>>>> controlBlocks;

    };
}

#include "subscriber.icc"