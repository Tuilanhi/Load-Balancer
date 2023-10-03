#include "LoadBalancer.h"
#include <random>
#include <iostream>

using namespace std;

/**
 * \brief generate random ip values
 *
 * This function returns a string of random values for ip_in and ip_out
 * 
 * \return The a string representing ip values
 */
string genRandomIP()
{
    random_device rd; // produces random number 
    mt19937 gen(rd()); // Seeding with the output of the random device rd to ensure different random numbers each run
    uniform_int_distribution<> dis(0, 255); // produce integer values that are evenly distributed across the range that matches the range values that each part of an ip address have

    std::string ip = std::to_string(dis(gen)) + "." +
                     std::to_string(dis(gen)) + "." +
                     std::to_string(dis(gen)) + "." +
                     std::to_string(dis(gen));

    return ip; // returns the random generated ip address
}

/**
 * \brief Get a random processing time between minimum and maximum values
 *
 * This function returns a random processing time for each request
 * 
 * \return The random time generated
 */
int getRandomProcessingTime(int min, int max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

/**
 * \brief The main function which creates the request queue and calls the loadbalancer to process the request
 * 
 * \return 0
 */
int main()
{
    int numOfServers, clockCycle, initialQueueSize;

    // Obtain user inputs
    cout << "Enter number of servers: ";
    cin >> numOfServers;
    cout << "Enter simulation time: ";
    cin >> clockCycle;

    // initialize the LoadBalancer and WebServer
    LoadBalancer loadBalancer(numOfServers);
    vector<WebServer> webservers(numOfServers);

    ofstream myfile;

    // Generate initial queue (number of servers * 5), a full queue
    initialQueueSize = numOfServers * 5;
    for(int i = 0; i < initialQueueSize; i++)
    {
        Request request;
        request.ip_in = genRandomIP();
        request.ip_out = genRandomIP();
        request.processingTime = getRandomProcessingTime(3, 200);
        loadBalancer.addRequest(request);
    }

    myfile.open("result_log.txt", std::ofstream::trunc);
    myfile << "Starting queue size: " << loadBalancer.getQueueSize() << endl;
    myfile.close();

    // Main simulation loop
    // Loop through the simulation time and exit when time is over
    for(int currTime = 0; currTime < clockCycle; currTime++)
    {
        loadBalancer.distributeRequest();
        loadBalancer.updateServers();

        int ran = getRandomProcessingTime(1, 50);
        
        // Add new request at random times
        if(currTime % ran == 0)
        {
            Request request;
            request.ip_in = genRandomIP();
            request.ip_out = genRandomIP();
            request.processingTime = getRandomProcessingTime(3, 200);
            loadBalancer.addRequest(request);
            // cout << "add new request" << endl;
            // cout << "queue size: " << loadBalancer.getQueueSize() << endl;
        }
    }

    myfile.open("result_log.txt", std::ofstream::app);

    myfile << "WebServer size: " << loadBalancer.getServerSize() << endl;
    myfile << "Ending queue size: " << loadBalancer.getQueueSize() << endl;

    myfile << "Total processed requests: " << loadBalancer.getTotalProcessedRequests() << endl;
    myfile << "Total discarded requests: " << loadBalancer.getTotalDiscardedRequests() << endl;

    myfile << "Task time range: " << loadBalancer.getMinTaskTime() << " - " << loadBalancer.getMaxTaskTime() << endl;

    myfile.close();

    return 0;
}