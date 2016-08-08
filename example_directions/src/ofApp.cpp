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


#include "ofApp.h"


void ofApp::setup()
{
//    client.registerClientEvents(this);

    ofxGeo::Coordinate origin(38.6276, -90.1992); // Saint Louis, Missouri, USA
    ofxGeo::Coordinate destination(41.8819, -87.6278); // Chicago, Illinois, USA

//    std::string origin("Saint Louis, Missouri"); // Saint Louis, Missouri, USA
//    std::string destination("Chicago, Illinois"); // Chicago, Illinois, USA

    ofxGeo::GoogleDirectionsQuery query(origin, destination);

    std::cout << query.toString() << std::endl;


    ofBuffer buffer = ofBufferFromFile("directions.json");

    Json::Reader reader;
    Json::Value value;

    if (reader.parse(buffer, value))
    {
        ofxGeo::Directions directions;

        std::string status;
        std::string error;

        if (ofxGeo::Deserializer::fromJson(value, directions, status, error))
        {
            for (const auto& route: directions.routes)
            {
                std::cout << "Route: " << route.summary << std::endl;

                for (const auto& leg: route.legs)
                {
                    std::cout << "\tLeg: " << leg.startAddress << "->" << leg.endAddress << std::endl;
        
                    for (const auto& step: leg.steps)
                    {
                        std::cout << "\t\tStep: " << step.start << "->" << step.end << std::endl;

                        for (const auto& point: step.polyline)
                        {
                            std::cout << "\t\t\t" << point << std::endl;
                        }
                    }
                }
            }
        }
        else {
            std::cout << "1. fail." << std::endl;
        }
    }
    else {
        std::cout << "2. fail." << std::endl;
    }


//    client.getDirections(query);

}


void ofApp::draw()
{
    ofBackground(0);
    
}
