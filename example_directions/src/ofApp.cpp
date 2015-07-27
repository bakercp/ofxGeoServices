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


#include "ofApp.h"


void ofApp::setup()
{
    client.registerClientEvents(this);

    ofx::Geo::Coordinate origin(38.6276,-90.1992); // Saint Louis, Missouri, USA
    ofx::Geo::Coordinate destination(41.8819, -87.6278); // Chicago, Illinois, USA

//    std::string origin("Saint Louis, Missouri"); // Saint Louis, Missouri, USA
//    std::string destination("Chicago, Illinois"); // Chicago, Illinois, USA

    ofx::Geo::GoogleDirectionsQuery query(origin, destination);

    std::cout << query.toString() << std::endl;

    client.getDirections(query);

}


void ofApp::draw()
{
    ofBackground(0);
    
}


bool ofApp::onGeoDirectionsEvent(ofx::Geo::DirectionsEventArgs& args)
{
    const std::vector<ofx::Geo::Route>& routes = args.getDirections().routes;

    std::vector<ofx::Geo::Route>::const_iterator routeIter = routes.begin();

    while (routeIter != routes.end())
    {
        const ofx::Geo::Route& route = *routeIter;

        std::cout << "Route: " << route.summary << std::endl;

        std::vector<ofx::Geo::Leg>::const_iterator legsIter = route.legs.begin();

        while (legsIter != route.legs.end())
        {
            const ofx::Geo::Leg& leg = *legsIter;

            std::cout << "\tLeg: " << leg.startAddress << "->" << leg.endAddress << std::endl;

            std::vector<ofx::Geo::Step>::const_iterator stepsIter = leg.steps.begin();

            while (stepsIter != leg.steps.end())
            {
                const ofx::Geo::Step& step = *stepsIter;

                std::cout << "\t\tStep: " << step.start << "->" << step.end << std::endl;

                std::vector<ofx::Geo::Coordinate>::const_iterator pointIter = step.polyline.begin();

                while (pointIter != step.polyline.end())
                {
                    const ofx::Geo::Coordinate& point = *pointIter;

                    std::cout << "\t\t\t" << point << std::endl;

                    ++pointIter;
                }

                ++stepsIter;
            }

            ++legsIter;
        }

        ++routeIter;
    }

    return true;
}


bool ofApp::onGeoDirectionsErrorEvent(ofx::Geo::DirectionsErrorEventArgs& args)
{
    cout << "ERROR GOT DIRECTIONS: " << args.getException().displayText() << endl;
    return true;
}
