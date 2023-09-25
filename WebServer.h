#include "Request.h"

/**
 * @{ \name class WebServer
 */
/**
 * \brief create a WebServer class that hold its private member variables and functions
 *
 * Construct the WebServer object
 */
class WebServer{
private:
    bool isBusy;
    int processingTimeLeft;
    Request currRequest;
    
public:
    WebServer();
    bool getBusy() const;
    void processRequest(const Request& request);
    void update();
};