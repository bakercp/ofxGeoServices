//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <vector>
#include <string>
#include "ofx/HTTP/URIBuilder.h"
#include "ofx/Geo/Coordinate.h"
#include "ofx/Geo/Directions.h"


namespace ofx {
namespace Geo {


class BaseDirectionsQuery: public HTTP::URIBuilder
{
public:
    BaseDirectionsQuery(const Poco::URI& baseURI);

    BaseDirectionsQuery(const Poco::URI& baseURI,
                        const Geo::Coordinate& origin,
                        const Geo::Coordinate& destination);

    virtual ~BaseDirectionsQuery();

    virtual void setOrigin(const Geo::Coordinate& origin);

    virtual void setDestination(const Geo::Coordinate& destination);

    virtual void setWaypoints(const std::vector<Geo::Coordinate>& waypoints);

    static const std::string KEY_ORIGIN;
    static const std::string KEY_DESTINATION;
    static const std::string KEY_WAYPOINTS;
    static const std::string KEY_WAYPOINTS_DELIMITER;

};


} } // namespace ofx::Geo
