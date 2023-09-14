#include "WebServer.h"
#include <vector>
#include <queue>
#include <iostream>


class LoadBalancer{
private:
    std::queue<Request> requestQueue;
    std::vector<WebServer> webservers;
    int currTime;
    int minTaskTime = std::numeric_limits<int>::max();
    int maxTaskTime = std::numeric_limits<int>::min();
public:
    LoadBalancer(int numServers);
    void addRequest(const Request& request);
    void distributeRequest();
    void addServer();
    void removeServer();
    void updateServers();
    int getQueueSize();
    int getMinTaskTime() const;
    int getMaxTaskTime() const;
};