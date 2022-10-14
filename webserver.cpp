#ifndef REQUEST_CPP
#include "request.cpp"
#endif

class webserver
{
public:
    /**
     * webserver() is the default constructor for webserver class, this
     * function will create an empty webserver
     */
    webserver() {}

    /**
     * webserver(int inputServerNum) function will create a webserver with the
     * given input as the webserver number, and the time of that webserver to 0
     * @param serverNum int that is the server number assigned to a webserver
     */
    webserver(int inputServerNum)
    {
        time = 0;
        serverNum = inputServerNum;
    }

    /**
     *
     * This functions gives a request to the webserver
     * @param req request that is being given to the webserver
     * @param currTime int that is the current time
     * clock
     */
    void addRequest(request r, int currTime)
    {
        req = r;
        time = currTime;
    }

    /**
     * This getter functions returns the current request assigned to the webserver
     * @return request of the webserver
     */
    request getRequest() { return req; }

    /**
     * This getter functions returns the identifier of the webserver, which is an
     * int
     * @return server number of the webserver
     */
    int getServerNum() { return serverNum; }

    /**
     * This function indicates if a server is busy handling a request or not
     * @param currTime that is the time that being checked
     * @return request has been processed by webserver(true), webserver still
     * processing request (false)
     *
     */
    bool isRequestDone(int currTime)
    {
        return (currTime >= (time + req.reqStartTime));
    }

private:
    request req;
    int time;
    int serverNum;
};