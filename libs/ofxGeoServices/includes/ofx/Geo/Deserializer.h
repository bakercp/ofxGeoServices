//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofx/Geo/Directions.h"
#include "ofxGeo.h"
#include "ofxJson.h"


namespace ofx {
namespace Geo {


class Deserializer
{
public:
    static bool fromJson(const Json::Value& value,
                         Directions& directions,
                         std::string& status,
                         std::string& error);

    static bool fromJson(const Json::Value& value, Route& route) ;

//    bool fromJson(const Json::Value& value, Bounds& bounds) const;

    static bool fromJson(const Json::Value& value, Leg& leg) ;

    static bool fromJson(const Json::Value& value, Step& step) ;

    /// \brief A safe json reader.
    /// \param json The JSON element to be searched.
    /// \param name The name of member element.
    /// \param target The target value to save.
    /// \param defaultTarget The default value assigned to target upon failure.
    static void read(const Json::Value& json,
                     const std::string& name,
                     TextValue_<int>& target,
                     const TextValue_<int>& defaultTarget = TextValue_<int>());

    /// \brief A safe json reader.
    /// \param json The JSON element to be searched.
    /// \param name The name of member element.
    /// \param target The target value to save.
    /// \param defaultTarget The default value assigned to target upon failure.
    /// \returns true if successful.
    static void read(const Json::Value& json,
                     const std::string& name,
                     Geo::Coordinate& target,
                     const Geo::Coordinate& defaultTarget = Geo::Coordinate());

    /// \brief A safe json reader.
    /// \param json The JSON element to be searched.
    /// \param name The name of member element.
    /// \param target The target value to save.
    /// \param defaultTarget The default value assigned to target upon failure.
    /// \returns true if successful.
    static void read(const Json::Value& json,
                     const std::string& name,
                     double& target,
                     double defaultTarget = 0.0);


    /// \brief A safe json reader.
    /// \param json The JSON element to be searched.
    /// \param name The name of member element.
    /// \param target The target value to save.
    /// \param defaultTarget The default value assigned to target upon failure.
    /// \returns true if successful.
    static void read(const Json::Value& json,
                     const std::string& name,
                     std::string& target,
                     const std::string& defaultTarget = "");

    /// \brief A safe json reader.
    /// \param json The JSON element to be searched.
    /// \param name The name of member element.
    /// \param target The target value to save.
    /// \param defaultTarget The default value assigned to target upon failure.
    /// \returns true if successful.
    static void read(const Json::Value& json,
                     const std::string& name,
                     int& target,
                     int defaultTarget = 0);

};


} } // namespace ofx::Geo
