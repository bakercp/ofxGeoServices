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


#pragma once


#include <vector>
#include <string>
#include <json/json.h>
#include "ofx/HTTP/URIBuilder.h"
#include "ofx/Geo/Coordinate.h"
#include "ofx/Geo/AbstractServiceTypes.h"
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
