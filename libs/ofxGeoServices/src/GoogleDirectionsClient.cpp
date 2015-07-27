// =============================================================================
//
// Copyright (c) 2014 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/Geo/GoogleDirectionsClient.h"


namespace ofx {
namespace Geo {


GoogleDirectionsClient::GoogleDirectionsClient(std::size_t maxConnections,
                                               Poco::ThreadPool& threadPool):
    BaseDirectionsClient(maxConnections, threadPool)
{
}


GoogleDirectionsClient::~GoogleDirectionsClient()
{
}


bool GoogleDirectionsClient::fromJson(const Json::Value& value,
                                      Directions& directions,
                                      std::string& status,
                                      std::string& error) const
{
    try
    {
        if (value.isMember("status"))
        {
            status = value["status"].asString();

            if (status != "OK")
            {
                if (value.isMember("error"))
                {
                    error = value["error"].asString();
                }

                return false;
            }
        }

        if (value.isMember("routes") && value["routes"].isArray())
        {
            Json::Value a = value["routes"];

            for (Json::ArrayIndex i = 0; i < a.size(); ++i)
            {
                Route route;

                if (fromJson(a[i], route))
                {
                    directions.routes.push_back(route);
                }
            }
        }

        return true;
    }
    catch (std::exception& exc)
    {
        error = "JSON Parse Error: " + std::string(exc.what() ? exc.what() : "");
        return false;
    }
}


bool GoogleDirectionsClient::fromJson(const Json::Value& value,
                                      Route& route) const
{
//    fromJson(value, route.bounds);

    if (value.isMember("overview_polyline") &&
        value["overview_polyline"].isMember("points"))
    {
        route.polyline = Geo::GeoUtils::decodeGeoPolyline(value["overview_polyline"]["points"].asString());
    }

    read(value, "copyrights", route.copyrights);
    read(value, "summary", route.summary);

    if (value.isMember("legs"))
    {
        Json::Value a = value["legs"];

        for (Json::ArrayIndex i = 0; i < a.size(); ++i)
        {
            Leg leg;

            if (fromJson(a[i], leg))
            {
                route.legs.push_back(leg);
            }
        }
    }

    // warnings
    // waypoint_order

    return true;
}


//bool GoogleDirectionsClient::fromJson(const Json::Value& json,
//                                      Bounds& bounds) const
//{
//    if (json.isMember("bounds"))
//    {
//        Json::Value _bounds = json["bounds"];
//
//        Geo::Coordinate northeast;
//        Geo::Coordinate southwest;
//
//        read(_bounds, "northeast", northeast);
//        read(_bounds, "southwest", southwest);
//
//        Geo::Coordinate northwest(northeast.getLatitude(), southwest.getLongitude());
//        Geo::Coordinate southeast(southwest.getLatitude(), northeast.getLongitude());
//
//        bounds.setNorthwest(northwest);
//        bounds.setSoutheast(southeast);
//
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}


bool GoogleDirectionsClient::fromJson(const Json::Value& value, Leg& leg) const
{
    read(value, "distance", leg.distance);
    read(value, "duration", leg.duration);
    read(value, "end_address", leg.endAddress);
    read(value, "start_address", leg.startAddress);

    read(value, "start_location", leg.start);
    read(value, "end_location", leg.end);

    if (value.isMember("steps"))
    {
        Json::Value a = value["steps"];

        for (Json::ArrayIndex i = 0; i < a.size(); ++i)
        {
            Step step;

            if (fromJson(a[i], step))
            {
                leg.steps.push_back(step);
            }
        }
    }

    return true;
}


bool GoogleDirectionsClient::fromJson(const Json::Value& value,
                                      Step& step) const
{
    read(value, "distance", step.distance);
    read(value, "duration", step.duration);

    read(value, "end_location", step.end);
    read(value, "start_location", step.start);

    read(value, "html_instructions", step.instructions);

    read(value, "html_instructions", step.instructions);
    read(value, "travel_mode", step.travelMode);

    if (value.isMember("polyline") &&
        value["polyline"].isMember("points"))
    {
        step.polyline = Geo::GeoUtils::decodeGeoPolyline(value["polyline"]["points"].asString());
    }

    return true;
}


void GoogleDirectionsClient::read(const Json::Value& json,
                                  const std::string& name,
                                  TextValue_<int>& target,
                                  const TextValue_<int>& defaultTarget)
{
    if (json.isMember(name))
    {
        const Json::Value& tv = json[name];

        if (tv.isMember("text") && tv.isMember("value"))
        {
            target = TextValue_<int>(tv["text"].asString(),
                                     tv["value"].asInt());
            return;
        }
        else
        {
            target = defaultTarget;
        }
    }
    else
    {
        target = defaultTarget;
    }
}


void GoogleDirectionsClient::read(const Json::Value& json,
                                  const std::string& name,
                                  Geo::Coordinate& target,
                                  const Geo::Coordinate& defaultTarget)
{
    if (json.isMember(name))
    {
        const Json::Value& value = json[name];

        if (value.isMember("lat") && value.isMember("lng"))
        {
            target.setLatitude(value["lat"].asDouble());
            target.setLongitude(value["lng"].asDouble());
        }
        else
        {
            target = defaultTarget;
        }
    }
    else
    {
        target = defaultTarget;
    }
}


void GoogleDirectionsClient::read(const Json::Value& json,
                                  const std::string& name,
                                  double& target,
                                  double defaultTarget)
{
    if (json.isMember(name))
    {
        Json::Value v = json[name];

        if (v.isDouble())
        {
            target = v.asDouble();
        }
        else if (v.isString())
        {
            target = ofToDouble(v.asString());
        }
        else
        {
            target = defaultTarget;
        }
    }
    else
    {
        target = defaultTarget;
    }
}

void GoogleDirectionsClient::read(const Json::Value& json,
                                  const std::string& name,
                                  std::string& target,
                                  const std::string& defaultTarget)
{
    if (json.isMember(name) && json[name].isString())
    {
        target = json[name].asString();
    }
    else
    {
        target = defaultTarget;
    }
}

void GoogleDirectionsClient::read(const Json::Value& json,
                                  const std::string& name,
                                  int& target,
                                  int defaultTarget)
{
    if (json.isMember(name))
    {
        Json::Value v = json[name];

        if (v.isInt())
        {
            target = v.asInt();
        }
        else if (v.isString())
        {
            target = ofToInt(v.asString());
        }
        else
        {
            target = defaultTarget;
        }
    }
    else
    {
        target = defaultTarget;
    }
}


} } // namespace ofx::Geo
