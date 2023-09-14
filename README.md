# Load-Balancer

This project will require the ability to create multiple Load Balancers, and a real-world
implementations of a queue for each. We also need a struct, a lower-level data structure that allows
data to be contained in an object (requests).
Loadbalancers are available commercially, but in this project you will build one that has:
● Requests - generates random IP addresses, both in and out, and random times for each
request to be processed. This time can be considered clock cycles, so each request will likely
take a minimum of 3 cycles. You do not have to use a system clock for this, an iterator is fine.
o IP in
o IP out
o Time (integer)
● Webserver(s)
o Receives requests from the Load Balancer
o Process the requests
o Asks for another
● Load Balancer
o Queue of requests
o Keeps track of time.
