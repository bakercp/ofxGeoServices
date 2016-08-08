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
