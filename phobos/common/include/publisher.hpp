#pragma once

#include "definitions.hpp"
#include "publisher_interface.hpp"
#include "subscriber_interface.hpp"

#include <concepts>
#include <queue>
#include <map>
#include <memory>
#include <list>
#include <ranges>
#include <mutex>
#include <optional>
#include <set>
#include <shared_mutex>

namespace Phobos {
    
    template<std::copy_constructible T>
    class Subscriber;

    template<std::copy_constructible T>
    class Publisher : public PublisherInterface<T> {
        public:
            friend class Subscriber<T>;
            
            Publisher() = default;
            ~Publisher() {
                clearSubscriptors();
            }            

            Publisher(Publisher &&other) {
                move(std::forward(other));
            }

            Publisher &operator=(Publisher &&other) {
                move(std::forward(other));
            }

            Publisher(const Publisher &other) {
                copy(other);
            }

            Publisher &operator=(const Publisher &other) {
                copy(other);
            }

            bool removeSubscriber(SubscriberInterface<T> *subscriber) {
                if (!subscriber)
                    return false;
                deleteSubscriber(subscriber);
                this->deletePublisherInSubscriber(subscriber);
                return true;
            }

            void publishData(T data) {
                std::shared_lock<std::shared_mutex> sl{PublisherMutex};
                for (auto sub: subscribers) {
                    this->addDataToSubscriber(sub, data);
                }
            }

            int getNumSubscriptors() const {
                std::shared_lock<std::shared_mutex> sl{PublisherMutex};
                return subscribers.size();
            }

            std::list<SubscriberInterface<T>*> getSubscribers() const {
                std::shared_lock<std::shared_mutex> sl{PublisherMutex};
                return subscribers | std::ranges::to<std::list>;
            }

            void clearSubscriptors() {
                while(!subscribers.empty()) {
                    removeSubscriber(*subscribers.begin());
                }
            }

        protected:
            void addSubscriber(SubscriberInterface<T> *subscriber) override {
                if (!subscriber)
                    return;
                std::unique_lock<std::shared_mutex> sl{PublisherMutex};
                if (!subscriber || subscribers.contains(subscriber))
                    return;
                subscribers.insert(subscriber);
                
            }

            void move(Publisher &&other) {
                subscribers.clear();
                for (auto sub: subscribers) {
                    sub->unsubscribe(other);
                    sub->subscribe(this);
                }
                other.subscribers.clear();
            }

            void copy(const Publisher &other) {
                
            }

            void deleteSubscriber(SubscriberInterface<T> *subscriber) override {
                if (!subscriber)
                    return;
                std::unique_lock<std::shared_mutex> sl{PublisherMutex};
                subscribers.erase(subscriber);
            }

            mutable std::shared_mutex PublisherMutex;
            std::set<SubscriberInterface<T>*> subscribers;
    };
}

#include "publisher.icc"