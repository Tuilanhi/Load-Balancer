/**
 * @{ \name Struct request
 */
/**
 * \brief create a struct request
 *
 * These member variables represent the ip in, ip out and the processing time for a request
 */
#include <string.h>
#include <iostream>

struct Request{
    std::string ip_in;
    std::string ip_out;
    int processingTime;
};