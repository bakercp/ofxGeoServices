//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


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
