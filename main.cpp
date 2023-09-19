#include "LoadBalancer.h"
#include <random>
#include <iostream>

using namespace std;

// Helper function to generate random ip address to populate Request ip in and ip out in main()
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

// Return the random time processing for Request
int getRandomProcessingTime(int min, int max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

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

    // Generate initial queue (number of servers * 5), a full queue
    initialQueueSize = numOfServers * 5;
    for(int i = 0; i < initialQueueSize; i++)
    {
        Request request;
        request.ip_in = genRandomIP();
        request.ip_out = genRandomIP();
        request.processingTime = getRandomProcessingTime(3, 100);
        loadBalancer.addRequest(request);
    }

    cout << "Starting queue size: " << loadBalancer.getQueueSize() << endl;

    // Set up a random number generator for adding new requests
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(50, 100);

    // Main simulation loop
    for(int currTime = 0; currTime < clockCycle; currTime++)
    {
        loadBalancer.distributeRequest();
        loadBalancer.updateServers();

        // Add new request at random times
        if(currTime == dis(gen))
        {
            Request request;
            request.ip_in = genRandomIP();
            request.ip_out = genRandomIP();
            request.processingTime = getRandomProcessingTime(3, 100);
            loadBalancer.addRequest(request);
            // cout << "add new request" << endl;
        }
    }

    cout << "Ending queue size: " << loadBalancer.getQueueSize() << endl;

    cout << "Task time range: " << loadBalancer.getMinTaskTime() << " - " << loadBalancer.getMaxTaskTime() << endl;

    return 0;
}