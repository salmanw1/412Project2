#include <string>
using namespace std;

/**
 * request class that will hold the necesarry data for a server request such the
 * time a request starts, and the in and out IP addresses
 *
 */

class request
{
public:
    string ipIn;
    string ipOut;
    int reqStartTime;

    /**
     * Default constructor that creates an empty request, will default set
     * both ip strings to empty and reqStartTime to 0
     */
    request() {}
};