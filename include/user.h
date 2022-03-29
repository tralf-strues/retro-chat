/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file user.h
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 */

#pragma once

#include <string>

namespace rchat {

struct User
{
    User() = default;
    explicit User(const std::string& name) : name(name) {}

    std::string name;
};

}