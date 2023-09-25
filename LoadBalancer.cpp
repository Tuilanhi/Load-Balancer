#include "LoadBalancer.h"

/**
 * \brief Construct the LoadBalancer by calling its constructor
 */
LoadBalancer::LoadBalancer(int numOfServers) : webservers(numOfServers){}

/**
 * \brief add request onto the queue of requests
 *
 * This function takes in the current request and push it into a queue of requests
 * 
 * \param request the current request
 * \return void
 */
void LoadBalancer::addRequest(const Request& request){
    requestQueue.push(request);
}

/**
 * \brief distribute request to a none busy WebServer
 *
 * This function checks if a WebServer is empty or not and start distributing request to a server
 * and update the min and max time takes to process the request
 * 
 * \return void
 */
void LoadBalancer::distributeRequest()
{
    int i = 1;
    for(auto& server: webservers) // loop through all webserver in webservers vectors
    {
        if(!server.getBusy() && !requestQueue.empty()) // Check to make sure that the server is not busy and the queue is not empty
        {
            Request request = requestQueue.front();
            std::cout << "Request ip_in: " << request.ip_in << " & Request ip_out: " << request.ip_out << 
            " with processing time: " << request.processingTime << " is being processed by server " << i << std::endl;
            server.processRequest(request); // process the first request pushed into the queue
            requestQueue.pop(); // pop the request from the queue of requests

            int taskTime = request.processingTime;

            // Update minTaskTime and maxTaskTime
            minTaskTime = std::min(minTaskTime, taskTime);
            maxTaskTime = std::max(maxTaskTime, taskTime);
        }
        i++;
    }
}

/**
 * \brief Add a WebServer onto a vector of WebServers
 *
 * This function push back a new WebServer onto a vector of WebServers
 * 
 * \return void
 */
void LoadBalancer::addServer()
{
    webservers.push_back(WebServer());
}

/**
 * \brief Remove a WebServer from a vector of WebServers
 *
 * This function removes a WebServer from a vector of WebServers when called
 * 
 * \return void
 */
void LoadBalancer::removeServer()
{
    if(!webservers.empty())
    {
        webservers.pop_back();
    }
}

/**
 * \brief Update the WebServer by processing the request
 *
 * This function calls the update() in the WebServer class to process and update the busy status of the current server for the next request
 * It also adds or remove a WebServer depending on the busy the queue is.
 * 
 * \return void
 */
void LoadBalancer::updateServers()
{
    for(auto& server:webservers)
    {
        server.update();
    }

    // The size of the request queue is checked. If the queue size exceed num of Servers * 4, a new server is added.
    // If the queue size falls below number of Server * 3 and there are multiple servers, a server is removed.
    int queueSize = requestQueue.size();
    if(queueSize > webservers.size() * 4)
    {
        addServer();
    }
    else if(queueSize < webservers.size() * 3 && webservers.size() > 1)
    {
        removeServer();
    }
}

/**
 * \brief Get the current queue size
 *
 * This function returns the current queue size 
 * 
 * \return The request queue size
 */
int LoadBalancer::getQueueSize() // Return the size of the current Request queue
{
    return requestQueue.size();
}

/**
 * \brief Get the minimum processing time for all requests
 *
 * This function returns the minimum amount of time take to process a request
 * 
 * \return The minimum processing time
 */
int LoadBalancer::getMinTaskTime() const // Return minimum task time
{ 
    return minTaskTime;
}

/**
 * \brief Get the maximum processing time for all requests
 *
 * This function returns the maximum amount of time take to process a request
 * 
 * \return The maximum processing time
 */
int LoadBalancer::getMaxTaskTime() const // Return the maximum task time
{
    return maxTaskTime;
}
