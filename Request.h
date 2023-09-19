/*
* The request struct will contain and ip:in and ip:out and the processing time
*/
#include <string.h>
#include <iostream>

struct Request{
    std::string ip_in;
    std::string ip_out;
    int processingTime;
};