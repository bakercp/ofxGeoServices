//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


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
        else
        {
            std::cout << "1. fail." << std::endl;
        }
    }
    else
    {
        std::cout << "2. fail." << std::endl;
    }


//    client.getDirections(query);

}


void ofApp::draw()
{
    ofBackground(0);

}
