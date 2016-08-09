// =============================================================================
//
// Copyright (c) 2014-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include "ofx/Geo/Directions.h"
#include "ofxJson.h"
#include "ofxGeo.h"


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
