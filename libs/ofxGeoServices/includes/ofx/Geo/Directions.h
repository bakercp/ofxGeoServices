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


#include <vector>
#include <string>
#include "ofx/Geo/Coordinate.h"
//#include "ofx/Geo/Bounds.h"


namespace ofx {
namespace Geo {


template <class ValueType>
class TextValue_
{
public:
    TextValue_(): _text(""), _value(0)
    {
    }

    TextValue_(const std::string& text, const ValueType& value):
        _text(text), _value(value)
    {
    }

    const std::string& getText() const
    {
        return _text;
    }

    void setText(const std::string& text)
    {
        _text = text;
    }

    ValueType getValue() const
    {
        return _value;
    }

    void setValue(const ValueType& value)
    {
        _value = value;
    }

protected:
    std::string _text;
    ValueType _value;

};


typedef TextValue_<int> Distance;
typedef TextValue_<int> Duration;


class Step
{
public:
    Distance distance;
    Duration duration;

    std::string instructions;
    std::string manuever;
    std::string travelMode;

    std::vector<Coordinate> polyline;

    Coordinate start;
    Coordinate end;

};


class Leg
{
public:
    Distance distance;
    Duration duration;

    Coordinate start;
    Coordinate end;

    std::string startAddress;
    std::string endAddress;

    std::vector<Step> steps;

};


class Route
{
public:
    std::string summary;
    std::string copyrights;

    std::vector<Leg> legs;

    std::vector<Coordinate> polyline;
//    Geo::Bounds bounds;

    std::vector<std::string> warnings;
    std::vector<std::size_t> waypointOrder;
};



class Directions
{
public:
    std::vector<Route> routes;
    
};


} } // namespace ofx::Geo
