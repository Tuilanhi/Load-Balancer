#include "WebServer.h"
#include <iostream>

using namespace std;

/**
 * \brief construct the WebServer by calling its constructor
 */
WebServer::WebServer() : isBusy(false), processingTimeLeft(0) {}

/**
 * \brief Checks whether or not the WebServer is busy
 *
 * This function returns true if the WebServer is busy and false otherwise
 * 
 * \return The whether or not the WebServer is busy
 */
bool WebServer::getBusy() const
{
    return isBusy;
}

/**
 * \brief process the request
 *
 * This function takes in a request and process it 
 * 
 * \param request The current request
 * \return void
 */
void WebServer::processRequest(const Request& request)
{
    if(isBusy) // Error checking for when the server is overload
    {
        throw runtime_error("Server is currently busy");
    }
    isBusy = true;
    processingTimeLeft = request.processingTime;
    currRequest = request;
}

/**
 * \brief update the WebServer
 *
 * This function updates the WebServer by subtracting the request's processing time and flag isBusy is false once it is done
 * 
 * \return void
 */
void WebServer::update()
{
    // decrement the processing time left by 1, and checks if the server has finished processing the current request
    if(isBusy)
    {
        --processingTimeLeft;
        if(processingTimeLeft <= 0)
        {
            isBusy = false;
        }
    }
}