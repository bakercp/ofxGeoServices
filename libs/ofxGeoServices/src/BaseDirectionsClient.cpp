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


#include "ofx/Geo/BaseDirectionsClient.h"


namespace ofx {
namespace Geo {


BaseDirectionsClient::BaseDirectionsClient(std::size_t maxConnections,
                                           Poco::ThreadPool& threadPool):
    HTTP::DefaultClientTaskQueue(maxConnections, threadPool)
{
}


BaseDirectionsClient::~BaseDirectionsClient()
{
}


Poco::UUID BaseDirectionsClient::getDirections(const BaseDirectionsQuery& query)
{
    return get(query.toString());
}


bool BaseDirectionsClient::onHTTPClientResponseEvent(HTTP::ClientResponseEventArgs& args)
{

    Json::Reader reader;
    Json::Value value;

    if (reader.parse(args.getResponseStream(), value))
    {
        Directions directions;

        std::string status;
        std::string error;

        if (fromJson(value, directions, status, error))
        {
            DirectionsEventArgs successArgs(args.getRequestId(), directions);
            ofNotifyEvent(events.onGeoDirectionsEvent, successArgs, this);
        }
        else
        {
            Poco::Exception exc(status, error);

            HTTP::ClientErrorEventArgs errorArgs(args.getRequest(),
                                                 args.getResponse(),
                                                 args.getContextRef(),
                                                 exc);

            ofNotifyEvent(events.onGeoDirectionsErrorEvent, errorArgs, this);
        }
    }
    else
    {
        Poco::Exception exc("Error Parsing JSON", reader.getFormatedErrorMessages());

        HTTP::ClientErrorEventArgs errorArgs(args.getRequest(),
                                             args.getResponse(),
                                             args.getContextRef(),
                                             exc);

        ofNotifyEvent(events.onGeoDirectionsErrorEvent, errorArgs, this);
    }

    return true;
}


bool BaseDirectionsClient::onHTTPClientErrorEvent(HTTP::ClientErrorEventArgs& args)
{
    ofNotifyEvent(events.onGeoDirectionsErrorEvent, args, this);
    return true;
}


} } // namespace ofx::Geo