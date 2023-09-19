/*
* Create a WebServer class that will
* 1. receive requests from the Load Balancer
* 2. Process the requests
* 3. Ask for another request
*/
#include "WebServer.h"
#include <iostream>

using namespace std;

// Constructor to initialize all private members
WebServer::WebServer() : isBusy(false), processingTimeLeft(0) {}

// Returns whether or not the server is busy
bool WebServer::getBusy() const
{
    return isBusy;
}

void WebServer::processRequest(const Request& request) // Process the new request
{
    if(isBusy) // Error checking for when the server is overload
    {
        throw runtime_error("Server is currently busy");
    }
    isBusy = true;
    processingTimeLeft = request.processingTime;
    currRequest = request;
}

void WebServer::update() // decrement the processing time left by 1, and checks if the server has finished processing the current request
{
    if(isBusy)
    {
        --processingTimeLeft;
        if(processingTimeLeft <= 0)
        {
            isBusy = false;
        }
    }
}