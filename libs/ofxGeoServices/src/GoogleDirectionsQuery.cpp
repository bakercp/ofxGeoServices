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


#include "ofx/Geo/GoogleDirectionsQuery.h"


namespace ofx {
namespace Geo {


const std::string GoogleDirectionsQuery::KEY_MODE = "mode";
const std::string GoogleDirectionsQuery::KEY_LANGUAGE = "language";
const std::string GoogleDirectionsQuery::KEY_UNITS = "units";
const std::string GoogleDirectionsQuery::KEY_REGION = "region";
const std::string GoogleDirectionsQuery::KEY_ALTERNATIVES = "alternatives";
const std::string GoogleDirectionsQuery::KEY_OPTIMIZE = "optimize";
const std::string GoogleDirectionsQuery::KEY_SENSOR = "sensor";
const std::string GoogleDirectionsQuery::KEY_CLIENT = "client";
const std::string GoogleDirectionsQuery::KEY_SIGNATURE = "signature";


const Poco::URI GoogleDirectionsQuery::GOOGLE_DIRECTIONS_BASE_URI = Poco::URI("http://maps.googleapis.com/maps/api/directions/json");


GoogleDirectionsQuery::GoogleDirectionsQuery(const std::string& origin,
                                             const std::string& destination):
    BaseDirectionsQuery(GOOGLE_DIRECTIONS_BASE_URI)
{
    setOrigin(origin);
    setDestination(destination);
    setSensor(false);
}


GoogleDirectionsQuery::GoogleDirectionsQuery(const Geo::Coordinate& origin,
                                             const Geo::Coordinate& destination):
    BaseDirectionsQuery(GOOGLE_DIRECTIONS_BASE_URI,
                        origin,
                        destination)
{
    setSensor(false);
}


GoogleDirectionsQuery::~GoogleDirectionsQuery()
{
}


void GoogleDirectionsQuery::setOrigin(const std::string& origin)
{
    Poco::Net::NameValueCollection::set(KEY_ORIGIN, origin);
}


void GoogleDirectionsQuery::setDestination(const std::string& destination)
{
    Poco::Net::NameValueCollection::set(KEY_DESTINATION, destination);
}


void GoogleDirectionsQuery::setWaypoints(const std::vector<std::string>& waypoints)
{
    std::stringstream ss;

    std::vector<std::string>::const_iterator iter = waypoints.begin();

    while (iter != waypoints.end())
    {
        if (iter != waypoints.begin())
        {
            ss << KEY_WAYPOINTS_DELIMITER; // add the delimiter
        }

        ss << (*iter); // add the coordinates

        ++iter;
    }

    Poco::Net::NameValueCollection::set(KEY_WAYPOINTS, ss.str());
}


void GoogleDirectionsQuery::setMode(const std::string& mode)
{
    Poco::Net::NameValueCollection::set(KEY_MODE, mode);
}


void GoogleDirectionsQuery::setLanguage(const std::string& language)
{
    Poco::Net::NameValueCollection::set(KEY_LANGUAGE, language);
}


void GoogleDirectionsQuery::setUnits(const std::string& units)
{
    Poco::Net::NameValueCollection::set(KEY_UNITS, units);
}


void GoogleDirectionsQuery::setRegion(const std::string& region)
{
    Poco::Net::NameValueCollection::set(KEY_REGION, region);
}


void GoogleDirectionsQuery::setAlternatives(bool alternatives)
{
    set(KEY_ALTERNATIVES, alternatives, true);
}


void GoogleDirectionsQuery::setOptimize(bool optimize)
{
    set(KEY_OPTIMIZE, optimize, true);
}


void GoogleDirectionsQuery::setSensor(bool sensor)
{
    set(KEY_SENSOR, sensor, false);
}


void GoogleDirectionsQuery::setClient(const std::string& client)
{
    Poco::Net::NameValueCollection::set(KEY_CLIENT, client);
}


void GoogleDirectionsQuery::setSignature(const std::string& signature)
{
    Poco::Net::NameValueCollection::set(KEY_SIGNATURE, signature);
}


} } // namespace ofx::Geo
