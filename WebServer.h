#include "Request.h"

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