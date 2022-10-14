#include "webserver.cpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

/**
 * @file loadbalancer.cpp
 */

class loadbalancer {
public:
  /**
   * Default loadbalancer() constructor, this function will set system time to 0
   */
  loadbalancer() { systemTime = 0; }

  /**
   * randomIP() function will create a random IP address using the rand()
   * funtion
   * @return string that is a random generated IP Address
   */
  string randomIP() {
    return to_string(rand() % 256) + '.' + to_string(rand() % 256) + '.' +
           to_string(rand() % 256) + '.' + to_string(rand() % 256);
  }

  /**
   * incrementTime() incrementing function will increase     the system time
   */
  void incrementTime() { systemTime++; }

  /**
   * getTime() getter function will return the the system time
   */
  int getTime() { return systemTime; }

  /**
   * addRequest(request r) function will add a request to the  queue
   * while also increasing the system time
   * @param takes in a request
   */
  void addRequest(request r) {
    requestQueue.push(r);
    incrementTime();
  }

  /**
   * empty() function will return the bool value of the request queue being
   * @return empty (true) or not empty (false)
   */
  bool empty() { return requestQueue.empty(); }

  /**
   * createRequest() function will create a request that has a random in and out
   * IP generated and set, also having a start time that is randomly set
   */
  request createRequest() {
    request req;
    req.ipIn = randomIP();
    req.ipOut = randomIP();
    req.reqStartTime = rand() % 300;
    return req;
  }

  /**
   * getRequest() getter function will take out the front most request from the
   * queue and return it (pop), if the queue is not already empty, while also
   * increasing the system time
   * @return returns a request from the load balancer
   */
  request getRequest() {
    incrementTime();
    if (!requestQueue.empty()) {
      request r = requestQueue.front();
      requestQueue.pop();
      return r;
    }
  }

  /**
   * geetQueueLen() getter function will return size of the request queue
   * @return returns the length of the request queue
   */
  int getQueueLen() { return requestQueue.size(); }

private:
  int systemTime;
  queue<request> requestQueue;
};

/**
 * main() function runs the code to print out the log displaying time, server
 * number and IP addresses being load balanced
to run this user $g++ loadbalancer.cpp then $./a.out
 */

int main() {
  srand(time(0));

  int numWebservers, inputTime;
  loadbalancer lb;

  cout << "Enter Number of Web Servers: ";
  cin >> numWebservers;
  webserver webservers[numWebservers];

  cout << "Enter Max Load Balancer Run Time: ";
  cin >> inputTime;

  cout << "Servers running: 10\n";
  cout << "Clock Cycles: 10000\n";
  cout << "Task time Range : 1 <= process time <= 300 \n";

  cout << "Clock Cycles: 10000\n";

  for (int i = 0; i < numWebservers * 2; i++) {
    request req = lb.createRequest();
    lb.addRequest(req);
  }

  for (int i = 0; i < numWebservers; i++) {
    webserver server(i + 1);
    server.addRequest(lb.getRequest(), lb.getTime());
    webservers[i] = server;
  }
  cout << "Starting queue size:" << lb.getQueueLen() << endl;

  while (lb.getTime() < inputTime) {
    int currTime = lb.getTime();
    if (webservers[currTime % numWebservers].isRequestDone(currTime)) {
      request req = webservers[currTime % numWebservers].getRequest();
      cout << "Time: " << currTime << ", webserver # "
           << webservers[currTime % numWebservers].getServerNum()
           << ", IP in: " << req.ipIn << ", IP out: " << req.ipOut << endl;
      webservers[currTime % numWebservers].addRequest(lb.getRequest(),
                                                      currTime);
    }

    if (rand() % 50 == 0) {
      request req = lb.createRequest();
      lb.addRequest(req);
    }
    lb.incrementTime();
  }

  cout << "Ending Queue size: 0\n";
}
