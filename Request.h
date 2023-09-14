#include <string.h>
#include <iostream>
/*
* The request struct will contain and ip:in and ip:out and the processing time
*/
struct Request{
    std::string ip_in;
    std::string ip_out;
    int processingTime;
};