#pragma once

#include <concepts>

namespace Phobos {
    template<std::copy_constructible T>
    class SubscriberInterface;

    template<std::copy_constructible T>
    class PublisherInterface {
        template<std::copy_constructible U>
        friend class SubscriberInterface;

        protected:
        virtual void deleteSubscriber(SubscriberInterface<T> *subscriber) = 0;
        virtual void addSubscriber(SubscriberInterface<T> *subscriber) = 0;

        void deletePublisherInSubscriber(SubscriberInterface<T> *subscriber) {
            if (!subscriber)
                return;
            subscriber->deletePublisher(this);
        }

        void addDataToSubscriber(SubscriberInterface<T> *subscriber, T &data) {
            if (!subscriber)
                return;
            subscriber->addData(this, data);
        }
    };
}