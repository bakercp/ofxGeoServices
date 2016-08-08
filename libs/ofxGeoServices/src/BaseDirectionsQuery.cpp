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


#include "ofx/Geo/BaseDirectionsQuery.h"


namespace ofx {
namespace Geo {


const std::string BaseDirectionsQuery::KEY_ORIGIN = "origin";
const std::string BaseDirectionsQuery::KEY_DESTINATION = "destination";
const std::string BaseDirectionsQuery::KEY_WAYPOINTS = "waypoints";
const std::string BaseDirectionsQuery::KEY_WAYPOINTS_DELIMITER = "|";


BaseDirectionsQuery::BaseDirectionsQuery(const Poco::URI& baseURI):
    HTTP::URIBuilder(baseURI)
{
}


BaseDirectionsQuery::BaseDirectionsQuery(const Poco::URI& baseURI,
                                         const Geo::Coordinate& origin,
                                         const Geo::Coordinate& destination):
    HTTP::URIBuilder(baseURI)
{
    setOrigin(origin);
    setDestination(destination);
}


BaseDirectionsQuery::~BaseDirectionsQuery()
{
}


void BaseDirectionsQuery::setOrigin(const Geo::Coordinate& origin)
{
    Poco::Net::NameValueCollection::set(KEY_ORIGIN, origin.toString());
}


void BaseDirectionsQuery::setDestination(const Geo::Coordinate& destination)
{
    Poco::Net::NameValueCollection::set(KEY_DESTINATION, destination.toString());
}


void BaseDirectionsQuery::setWaypoints(const std::vector<Geo::Coordinate>& waypoints)
{
    std::stringstream ss;

    std::vector<Geo::Coordinate>::const_iterator iter = waypoints.begin();

    while (iter != waypoints.end())
    {
        if (iter != waypoints.begin())
        {
            ss << KEY_WAYPOINTS_DELIMITER; // add the delimiter
        }

        ss << (*iter).toString(); // add the coordinates

        ++iter;
    }

    Poco::Net::NameValueCollection::set(KEY_WAYPOINTS, ss.str());
}


} } // namespace ofx::Geo
