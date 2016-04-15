#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>

using namespace std;

class Resource {
    public:

        // -------------------------------------------------------------
    	// Function: load()
    	// Description:
    	// Parameters:
    	//		const string &name;			// Name of something that will be load.
    	// Attributes: nothing
    	// Return: void
    	// Observation: Without implementation.
    	// -------------------------------------------------------------
        virtual void load(const string& name) = 0;
};
#endif
