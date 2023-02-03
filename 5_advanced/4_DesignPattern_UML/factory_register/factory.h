#ifndef FACTORY_H
#define FACTORY_H

#include<map>
#include<iostream>
#include<functional>
#include <memory>

class Message;

typedef std::shared_ptr<Message> MessagePtr;
typedef std::shared_ptr<Message> funcMessage();

class Message
{
public:
    virtual ~Message() {}

    virtual void foo()
    {

    }
};

struct factory {
    template<typename T>
    struct register_t
    {
        register_t(const std::string& key)
        {
            factory::get().map_.emplace(key, [] { return std::make_shared<T>(); });
        }
    };

    MessagePtr produce(const std::string& key)
    {
        if (map_.find(key) == map_.end())
            throw std::invalid_argument("the message key is not exist!");

        return map_[key]();
    }

    static factory& get()
    {
        static factory instance;
        return instance;
    }

private:
    factory() {}
    factory(const factory&) = delete;
    factory(factory&&) = delete;

    std::map<std::string, std::function<funcMessage>> map_;
};


#define REGISTER_MESSAGE_VNAME(T) reg_msg_##T##_
#define REGISTER_MESSAGE(T, key, ...) static factory::register_t<T> REGISTER_MESSAGE_VNAME(T)(key, ##__VA_ARGS__);



#endif // FACTORY_H
