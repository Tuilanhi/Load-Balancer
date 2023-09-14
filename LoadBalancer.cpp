#include "LoadBalancer.h"

// constructor that initializes the vector WebServers with number of servers, and set int current time to 0
LoadBalancer::LoadBalancer(int numOfServers) : webservers(numOfServers){}

// Accepts Request and add it to the request queue
void LoadBalancer::addRequest(const Request& request){
    requestQueue.push(request);
}

// distribute requests from the queue to the servers. It gives the request to the server when the server is not busy
void LoadBalancer::distributeRequest()
{
    for(auto& server: webservers) // loop through all webserver in webservers vectors
    {
        if(!server.getBusy() && !requestQueue.empty()) // Check to make sure that the server is not busy and the queue is not empty
        {
            Request request = requestQueue.front();
            server.processRequest(request); // process the first request pushed into the queue
            requestQueue.pop(); // pop the request from the queue of requests

            int taskTime = request.processingTime;

            // Update minTaskTime and maxTaskTime
            minTaskTime = std::min(minTaskTime, taskTime);
            maxTaskTime = std::max(maxTaskTime, taskTime);
        }
    }
}

// Adds a web server instance to the servers vector
void LoadBalancer::addServer()
{
    webservers.push_back(WebServer());
}

// Removes a webserver instance from the servers vector
void LoadBalancer::removeServer()
{
    if(!webservers.empty())
    {
        webservers.pop_back();
    }
}

// update each server by calling their update() and increment the current time
void LoadBalancer::updateServers()
{
    for(auto& server:webservers)
    {
        server.update();
    }

    // The size of the request queue is checked. If the queue size exceed num of Servers * 3, a new server is added.
    // If the queue size falls below number of Server * 2 and there are multiple servers, a server is removed.
    int queueSize = requestQueue.size();
    if(queueSize > webservers.size() * 5)
    {
        addServer();
    }
    else if(queueSize < webservers.size() * 5 && webservers.size() > 1)
    {
        removeServer();
    }
}

int LoadBalancer::getQueueSize() // Return the size of the current Request queue
{
    return requestQueue.size();
}

int LoadBalancer::getMinTaskTime() const // Return minimum task time
{ 
    return minTaskTime;
}

int LoadBalancer::getMaxTaskTime() const // Return the maximum task time
{
    return maxTaskTime;
}
