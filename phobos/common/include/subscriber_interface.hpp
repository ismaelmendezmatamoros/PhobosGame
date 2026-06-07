#pragma once

#include <concepts>

namespace Phobos {
    template<std::copy_constructible T>
    class PublisherInterface;

    template<std::copy_constructible T>
    class SubscriberInterface {
        template<std::copy_constructible U>
        friend class PublisherInterface;

        public:
        virtual void subscribe(PublisherInterface<T> *publisher) = 0;
        virtual bool unsubscribe(PublisherInterface<T> *publisher) = 0;

        protected:
        virtual void deletePublisher(PublisherInterface<T> *publisher) = 0;
        virtual void addData(PublisherInterface<T> *publisher, T data) = 0;

        void addSubscriberToPublisher(PublisherInterface<T> *publisher) {
            if (!publisher)
                return;
            publisher->addSubscriber(this);
        }

        void deleteSubscriberInPublisher(PublisherInterface<T> *publisher) {
            if (!publisher)
                return;
            publisher->deleteSubscriber(this);
        }
    };
}