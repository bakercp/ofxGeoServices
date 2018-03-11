//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


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
