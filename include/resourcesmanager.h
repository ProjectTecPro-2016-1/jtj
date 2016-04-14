#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include "rawimage.h"
#include <vector>

class ResourcesManager {

    // -------------------------------------------------------------
	// Function: ResourcesManager()
	// Description: ResourcesManager class builder.
	// Parameters: void
	// Attributes: nothing
	// Return: void
	// Observation: Without implementation.
	// -------------------------------------------------------------
    ResourcesManager();
    static ResourcesManager* instance = NULL;   // Pointer to instance resources.

    class ResourcesInfo { // Contain information of resources.
        Resource* resource;
        int references;
        public:
            ResourcesInfo() {
                resource = NULL;
                references = 0;
            }
    };

    vector<ResourcesInfo*> resources;   // Vector that contains information of resources.

    public:
        static ResourcesManager *getInstance();

        // -------------------------------------------------------------
    	// Function: getImage()
    	// Description:
    	// Parameters:
    	// 		const string &name;
    	// Attributes: nothing
    	// Return: RawImage *
    	// Observation: Without implementation.
    	// -------------------------------------------------------------
        RawImage* getImage(const string &name);

        // -------------------------------------------------------------
    	// Function: release()
    	// Description:
    	// Parameters:
    	// 		RawImage *image;
    	// Attributes: nothing
    	// Return: void
    	// Observation: Without implementation.
    	// -------------------------------------------------------------
        void release(RawImage* image);

        // -------------------------------------------------------------
    	// Function: load()
    	// Description:
    	// Parameters:
    	// 		const string &resourcesDescription;
    	// Attributes: nothing
    	// Return: void
    	// Observation: Without implementation.
    	// -------------------------------------------------------------
        void load(const string &resourcesDescription);
};
#endif
