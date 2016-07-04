#include "language.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <libxml/xpath.h>
#include <libxml/parser.h>

using namespace std;

// -------------------------------------------------------------  
// Function: Language()  
// Description: Constructor of class that define language of the game and languages that exist on
//              xml file
// Parameters:
//		string language;     Language selected in run of the game
// Return: void  
// -------------------------------------------------------------
Language::Language(string language) {
    setLanguagesExist();
    setLanguage(language);
}

// -------------------------------------------------------------  
// Function: ~Language()  
// Description: Destructor of class that define language of the game.
// Return: void  
// -------------------------------------------------------------  
Language::~Language() {
    this->languagesExist.clear();
}

// -------------------------------------------------------------  
// Function: setLanguage()  
// Description: Verify and set language for the game will started
// Parameters:
//      string language;        Language that informed in run of the game - Default is English
// Return: void  
// -------------------------------------------------------------
void Language::setLanguage(string informedLanguage) {

    // Set default language
    this->language = "English";

    // Checking and changing the language if is correct
    if (informedLanguage.compare("") != 0) {
        for (unsigned int i = 0; i < getLanguagesExist().size(); i++) {
            if (getLanguagesExist().at(i).compare(informedLanguage) == 0) {
                this->language = informedLanguage;
            } else {
                // Nothing to do
            }
        }
    } else {
        // Nothing to do
    }
}

// -------------------------------------------------------------  
// Function: getLanguage()  
// Description: Return language that the game are be playing
// Return: string  
// -------------------------------------------------------------
string Language::getLanguage() {
    return this->language;
}

// -------------------------------------------------------------  
// Function: getText()  
// Description: Searching and returning text of xml with selected language
// Parameters:
//      string text;        Text of needs to be searching and changing
// Return: string  
// -------------------------------------------------------------
string Language::getText(string text) {

    // Setting the return if not finding the text in xml file
    string textReturn = text;

    xmlDocPtr document = NULL;
    document = openXmlDocument();

    // Setting master tag organization for localizate the texts
    xmlChar * textSearch = (xmlChar *) "//Text";

    // Searching the master tag
    xmlXPathObjectPtr resultSearchNode = NULL;
    resultSearchNode = getSearchNode(document, textSearch);

    if (resultSearchNode != NULL) {
        xmlNodeSetPtr nodeset = NULL;
        nodeset = resultSearchNode->nodesetval;
        
        // Searching the text value in finding nodes of text tag 
        for (int i = 0; i < nodeset->nodeNr; i++) {
            xmlChar * textAttribute;
            textAttribute = xmlNodeListGetString(document, nodeset->nodeTab[i]->properties->children, 1);
            if (textAttribute != NULL) {
                if (text.compare((char *) textAttribute) == 0) {
                    textReturn = searchTextReturn(document, nodeset->nodeTab[i]);
                } else {
                    // Nothing to do
                }
            } else {
                // Nothing to do
            }
            xmlFree(textAttribute);
        }
        xmlXPathFreeObject(resultSearchNode);
    }

    closeXmlDocument(document);
    xmlCleanupParser();

    return textReturn;
}

// -------------------------------------------------------------  
// Function: searchTextReturn()  
// Description: Searching the text finding on languages exists
// Parameters:
//      xmlDocPtr document;         Xml file that will use to search the texts
//      xmlNodePtr currentNode;     Xml tag/node that index the text find
// Return: string  
// -------------------------------------------------------------
string Language::searchTextReturn(xmlDocPtr document, xmlNodePtr currentNode) {
    string textReturn = "";
    xmlNodePtr currentSon = currentNode->xmlChildrenNode;
    while (currentSon != NULL) {
        if ((!xmlStrcmp(currentSon->name, (const xmlChar *) getLanguage().c_str()))){
            textReturn = (char *) xmlNodeListGetString(document, currentSon->xmlChildrenNode, 1);
            break;
        }
        currentSon = currentSon->next;
    }
    return textReturn;
}

// -------------------------------------------------------------  
// Function: getLocationImage()  
// Description: Searching and returning location of image in xml with selected language
// Parameters:
//      string image;       Location of iamge that needs to be changing with the select language.
// Return: string  
// -------------------------------------------------------------
string Language::getLocationImage(string image) {

    // Setting the return if not finding the image in xml file
    string imageReturn = image;

    xmlDocPtr document = NULL;
    document = openXmlDocument();

    // Setting master tag organization for localizate the images
    xmlChar * textSearch = (xmlChar *) "//Image";

    // Searching the master tag
    xmlXPathObjectPtr resultSearchNode = NULL;
    resultSearchNode = getSearchNode(document, textSearch);

    if (resultSearchNode != NULL) {
        xmlNodeSetPtr nodeset = NULL;
        nodeset = resultSearchNode->nodesetval;

        // Searching the location value in finding nodes of image tag 
        for (int i = 0; i < nodeset->nodeNr; i++) {
            xmlChar * imageAttribute;
            imageAttribute = xmlNodeListGetString(document, nodeset->nodeTab[i]->properties->children, 1);
            if (imageAttribute != NULL) {
                if (image.compare((char *) imageAttribute) == 0) {
                    imageReturn = searchTextReturn(document, nodeset->nodeTab[i]);
                } else {
                    // Nothing to do
                }
            } else {
                // Nothing to do
            }
            xmlFree(imageAttribute);
        }
        xmlXPathFreeObject(resultSearchNode);
    }

    closeXmlDocument(document);
    xmlCleanupParser();

    return imageReturn;
}

// -------------------------------------------------------------  
// Function: setLanguagesExist()  
// Description: Setting the languages exists in xml files for checking the language selected
// Return: void  
// -------------------------------------------------------------
void Language::setLanguagesExist() {

    xmlDocPtr document = NULL;
    document = openXmlDocument();

    // Setting master tag organization for localizate the languages that are disponible
    xmlChar * textSearch = (xmlChar *) "//Languages";

    // Searching the master tag
    xmlXPathObjectPtr resultSearchNode = NULL;
    resultSearchNode = getSearchNode(document, textSearch);

    if (resultSearchNode != NULL) {
        xmlNodeSetPtr nodeset = NULL;
        nodeset = resultSearchNode->nodesetval;

        // Adding the languages in vector of languages exists
        for (int i = 0; i < nodeset->nodeNr; i++) {
            xmlChar * descriptionLanguages;
            descriptionLanguages = xmlNodeListGetString(document, 
                                                        nodeset->nodeTab[i]->xmlChildrenNode, 1);
            this->languagesExist.push_back((const char *) descriptionLanguages);
            xmlFree(descriptionLanguages);
        }
        xmlXPathFreeObject(resultSearchNode);
    } else {
        // Nothing to do
    }

    closeXmlDocument(document);
    xmlCleanupParser();
}

// -------------------------------------------------------------  
// Function: getLanguagesExist()  
// Description: Getting the languages exists in xml files for checking the language selected
// Return: vector of string
// -------------------------------------------------------------
vector<string> Language::getLanguagesExist() {
    return this->languagesExist;
}

// -------------------------------------------------------------  
// Function: getSearchNode()  
// Description: Getting the languages exists in xml files for checking the language selected
// Parameters:
//      xmlDocPtr document;         Xml file that will use to search the texts
//      xmlChar * nodeSearch;       Text to need to be searched
// Return: xmlXPathObjectPtr
// -------------------------------------------------------------
xmlXPathObjectPtr Language::getSearchNode(xmlDocPtr document, xmlChar * nodeSearch) {
    xmlXPathContextPtr context = NULL;
    xmlXPathObjectPtr result = NULL;

    // Checking the context of the xml file
    context = xmlXPathNewContext(document);
    if (context != NULL) {
        // Finding and checking if it is valid
        result = xmlXPathEvalExpression(nodeSearch, context);
        xmlXPathFreeContext(context);
        if (result != NULL) {
            // Checking if the result of search is not empty - Inverted the standart flow
            if(xmlXPathNodeSetIsEmpty(result->nodesetval)) {
                xmlXPathFreeObject(result);
                printf("No result\n");
                return NULL;
            } else {
                // Nothing to do
            }
        } else {
            printf("Error in xmlXPathEvalExpression\n");
            return NULL;
        }
    } else {
        printf("Error in xmlXPathNewContext\n");
        return NULL;
    }

    return result;
}

// -------------------------------------------------------------  
// Function: openXmlDocument()  
// Description: Open the file xml of internationalization
// Return: xmlDocPtr
// -------------------------------------------------------------
xmlDocPtr Language::openXmlDocument() {
    xmlDocPtr document = NULL;
    document = xmlParseFile("languages/internacionalization.xml");

    if (document == NULL) {
        assert(true && "Fail to open doc internacionalization.xml, is not possible to run the game.");
    }

    return document;
}

// -------------------------------------------------------------  
// Function: closeXmlDocument()  
// Description: Close the xml file after are used
// Parameters:
//      xmlDocPtr document;         Xml file that will closed
// Return: void
// -------------------------------------------------------------
void Language::closeXmlDocument(xmlDocPtr document) {
    xmlFreeDoc(document);
}
