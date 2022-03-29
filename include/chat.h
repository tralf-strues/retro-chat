/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file chat.h
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 */

#pragma once

#include "user.h"
#include <fmt/core.h>
#include <sstream>

namespace rchat {

struct Message
{
    User        sender;
    std::string text;

    Message() = default;
    Message(const User& sender, const std::string& text) : sender(sender), text(text) {}
};

std::string serializeMessage(const Message& message)
{
    return fmt::format("{},{}", message.sender.name, message.text);
}

void deserializeMessage(Message* message, const std::string& serialized)
{
    assert(message);

    size_t i = 0;
    while (serialized[i] != ',')
    {
        message->sender.name.push_back(serialized[i++]);
    }

    ++i;

    message->text = serialized.substr(i);
}

}