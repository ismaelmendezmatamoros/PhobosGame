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
    class Publisher;

    template<std::copy_constructible T>
    class Subscriber : public SubscriberInterface<T> {
        public:
            friend class Publisher<T>;

            Subscriber() = default;
            ~Subscriber() {
                clearSubscriptions();
            }            

            Subscriber(Subscriber &&other) {
                move(std::forward<Subscriber&&>(other));
            }

            Subscriber &operator=(Subscriber &&other) {
                move(std::forward<Subscriber&&>(other));
            }

            Subscriber(const Subscriber &other) {
                copy(other);
            }

            Subscriber &operator=(const Subscriber &other) {
                copy(other);
            }

            void subscribe(PublisherInterface<T> *publisher) override {
                if (!publisher)
                    return;
                rawSubscribe(publisher);
                this->addSubscriberToPublisher(publisher);
            }

            bool unsubscribe(PublisherInterface<T> *publisher) override {
                if (!publisher)
                    return false;
                rawUnsubscribe(publisher);
                this->deleteSubscriberInPublisher(publisher);
                return true;
            }

            int getNumSubscriptions() const {
                std::shared_lock<std::shared_mutex>sl{subscriberMutex};
                return publications.size();
            }

            std::list<PublisherInterface<T>*> getPublishers() const {
                std::shared_lock<std::shared_mutex> sl{subscriberMutex};
                return publications | std::ranges::to<std::list>;
            }

            virtual void onDataReceived(PublisherInterface<T> *publisher, T &data) = 0;

            void processPublications() {
                std::unique_lock<std::shared_mutex>sl{subscriberMutex};
                for (auto &[publisher, data] : publications) {
                    while (!data.empty()) {
                        onDataReceived(publisher, data.front());
                        data.pop();
                    }
                }
                publications.clear();
            }

            void clearSubscriptions() {
                while (!publishers.empty()) {
                    unsubscribe(*publishers.begin());
                }
            }

        protected:
            void move(Subscriber &&other) {
                publishers.clear();
                publications.clear();
                while(!other.publishers.empty()) {
                    auto pub = *other.publishers.begin();
                    subscribe(pub);
                    other.unsubscribe(pub);
                }
                publications.merge(other.publications);
                other.publications.clear();
                other.publishers.clear();
            }

            void copy(const Subscriber &other) {
                publishers.clear();
                publications.clear();
                for (auto pub: other.publishers) {
                    subscribe(pub);
                }
            }

            void addData(PublisherInterface<T> *publisher, T data) override {
                std::unique_lock<std::shared_mutex> sl{subscriberMutex};
                publications[publisher].emplace(data);
            }

            void deletePublisher(PublisherInterface<T> *publisher) override {
                rawUnsubscribe(publisher);
            }

            void rawSubscribe(PublisherInterface<T> *publisher) {
                std::unique_lock<std::shared_mutex> sl{subscriberMutex};
                if (!publisher || publishers.contains(publisher))
                    return;
                publishers.insert(publisher);
            }

            void rawUnsubscribe(PublisherInterface<T> *publisher) {
                std::unique_lock<std::shared_mutex> sl{subscriberMutex};
                publishers.erase(publisher);
            }

            mutable std::shared_mutex subscriberMutex;
            std::map<PublisherInterface<T>*, std::queue<T>> publications;
            std::set<PublisherInterface<T>*> publishers;
    };
}

#include "subscriber.icc"