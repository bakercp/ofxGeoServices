//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include <vector>
#include <string>
#include "ofxHTTP.h"
#include "ofx/Geo/Coordinate.h"
#include "ofx/Geo/AbstractServiceTypes.h"
#include "ofx/Geo/Directions.h"
#include "ofx/Geo/BaseDirectionsQuery.h"


namespace ofx {
namespace Geo {


class GoogleDirectionsQuery: public BaseDirectionsQuery
{
public:
    GoogleDirectionsQuery(const std::string& origin,
                          const std::string& destination);

    GoogleDirectionsQuery(const Geo::Coordinate& origin,
                          const Geo::Coordinate& destination);

    virtual ~GoogleDirectionsQuery();

    void setOrigin(const std::string& origin);
    void setDestination(const std::string& destination);
    void setWaypoints(const std::vector<std::string>& waypoints);

    void setMode(const std::string& mode);
    void setLanguage(const std::string& language);
    void setUnits(const std::string& units);
    void setRegion(const std::string& region);
    void setAlternatives(bool alternatives);
    void setOptimize(bool optimize);
    void setSensor(bool sensor);
    void setClient(const std::string& client);
    void setSignature(const std::string& signature);

    static const std::string KEY_MODE;
    static const std::string KEY_LANGUAGE;
    static const std::string KEY_UNITS;
    static const std::string KEY_REGION;
    static const std::string KEY_ALTERNATIVES;
    static const std::string KEY_OPTIMIZE;
    static const std::string KEY_SENSOR;
    static const std::string KEY_CLIENT;
    static const std::string KEY_SIGNATURE;

    static const Poco::URI GOOGLE_DIRECTIONS_BASE_URI;

};


} } // namespace ofx::Geo
