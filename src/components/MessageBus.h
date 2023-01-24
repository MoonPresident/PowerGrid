/**
 * @file displayObject.h
 * @author MoonPresident
 * @date December 21st 2022
 * 
 * Messaging system for intersystem communications
 */

#include <vector>
#include <unordered_map>
#include <functional>

typedef int MessageType;
typedef int MessageId;


class Message {
private:

public:
    Message() = default;

    MessageType messageType;
    MessageId messageId;
};

typedef std::function<void(MessageType)> Subscriber; 

class MessageBus {
    std::vector<Message> messageQueue;
    std::unordered_map<MessageType, std::vector<Subscriber>> subscriberMapping;

    void subscribe(MessageType messageType, Subscriber subscriber) {
        auto it = subscriberMapping.find(messageType);
        if (it == subscriberMapping.end()) {
            std::vector<Subscriber> newSubscriptionService();
            subscriberMapping.insert({messageType, newSubscriptionService});
        }
    }

    void unsubscribe(MessageType messageType, Subscriber subscriber) {

    }
};