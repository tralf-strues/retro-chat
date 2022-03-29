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

void deserializeMessage(Message* message, const char* serialized)
{
    assert(message);

    const char* separator = strchr(serialized, ',');
    message->sender.name.append(serialized, separator - serialized);

    const char* end = strchr(separator, '\n');
    message->text.append(separator + 1, end - separator - 1);
}

}