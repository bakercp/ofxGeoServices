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


#include "ofx/HTTP/DefaultClientTaskQueue.h"
#include "ofx/Geo/BaseDirectionsQuery.h"
#include "ofx/Geo/GeoUtils.h"


namespace ofx {
namespace Geo {


class BaseDirectionsEventArgs: public ofEventArgs
{
public:
    BaseDirectionsEventArgs(const Poco::UUID& requestId):
        _requestId(requestId)
    {
    }


    virtual ~BaseDirectionsEventArgs()
    {
    }

    const Poco::UUID getRequestId() const
    {
        return _requestId;
    }

private:
    const Poco::UUID& _requestId;

};


class DirectionsEventArgs: public BaseDirectionsEventArgs
{
public:
    DirectionsEventArgs(const Poco::UUID& requestId,
                        const Directions& directions):
        BaseDirectionsEventArgs(requestId),
        _directions(directions)
    {
    }


    virtual ~DirectionsEventArgs()
    {
    }


    const Directions& getDirections() const
    {
        return _directions;
    }

private:
    const Directions& _directions;

};


typedef HTTP::ClientErrorEventArgs DirectionsErrorEventArgs;


class DirectionsEvents
{
public:
    ofEvent<DirectionsEventArgs> onGeoDirectionsEvent;
    ofEvent<DirectionsErrorEventArgs> onGeoDirectionsErrorEvent;

};


class BaseDirectionsClient:
    public HTTP::DefaultClientTaskQueue,
    public AbstractDirectionsDeserializer
{
public:
    BaseDirectionsClient(std::size_t maxConnections = -1,
                         Poco::ThreadPool& threadPool = Poco::ThreadPool::defaultPool());

    virtual ~BaseDirectionsClient();

    virtual Poco::UUID getDirections(const BaseDirectionsQuery& query);

    template<class ListenerClass>
    void registerClientEvents(ListenerClass* listener);

    template<class ListenerClass>
    void unregisterClientEvents(ListenerClass* listener);


protected:
    bool onHTTPClientResponseEvent(HTTP::ClientResponseEventArgs& args);
    bool onHTTPClientErrorEvent(HTTP::ClientErrorEventArgs& args);

    DirectionsEvents events;

};


template<class ListenerClass>
void BaseDirectionsClient::registerClientEvents(ListenerClass* listener)
{
    ofAddListener(events.onGeoDirectionsEvent, listener, &ListenerClass::onGeoDirectionsEvent);
    ofAddListener(events.onGeoDirectionsErrorEvent, listener, &ListenerClass::onGeoDirectionsErrorEvent);
}


template<class ListenerClass>
void BaseDirectionsClient::unregisterClientEvents(ListenerClass* listener)
{
    ofRemoveListener(events.onGeoDirectionsEvent, listener, &ListenerClass::onGeoDirectionsEvent);
    ofRemoveListener(events.onGeoDirectionsErrorEvent, listener, &ListenerClass::onGeoDirectionsErrorEvent);
}


} } // namespace ofx::Geo
