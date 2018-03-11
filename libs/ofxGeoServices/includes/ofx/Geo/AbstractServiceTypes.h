//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <string>
#include <vector>
#include <json/json.h>


namespace ofx {
namespace Geo {


class Directions;


class AbstractDirectionsDeserializer
{
public:
    virtual ~AbstractDirectionsDeserializer()
    {
    }

    virtual bool fromJson(const Json::Value& value,
                          Directions& directions,
                          std::string& status,
                          std::string& error) const = 0;

};


} } // namespace ofx::Geo
