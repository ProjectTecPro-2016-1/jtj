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
// Description:
// Parameters:
//		string language;
// Return: void  
// -------------------------------------------------------------
Language::Language(string language) {
    setLanguagesExist();
    setLanguage(language);
    
    // readXMLFile();
}

// -------------------------------------------------------------  
// Function: ~Language()  
// Description: Destructor of class that define language of game.
// Return: void  
// -------------------------------------------------------------  
Language::~Language() {
    this->languagesExist.clear();
}

// -------------------------------------------------------------  
// Function: setLanguage()  
// Description:
// Parameters:
//      string language;
// Return: void  
// -------------------------------------------------------------
void Language::setLanguage(string informedLanguage) {

    this->language = "English";

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
// Description:
// Return: string  
// -------------------------------------------------------------
string Language::getLanguage() {
    return this->language;
}

// -------------------------------------------------------------  
// Function: getText()  
// Description:
// Parameters:
//      string text;
// Return: string  
// -------------------------------------------------------------
string Language::getText(string text) {

    string textReturn = text;

    xmlDocPtr document;
    document = openXmlDocument();

    xmlChar * textSearch = (xmlChar *) "//Text";

    xmlXPathObjectPtr resultSearchNode;
    resultSearchNode = getSearchNode(document, textSearch);

    if (resultSearchNode != NULL) {
        xmlNodeSetPtr nodeset;
        nodeset = resultSearchNode->nodesetval;
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
// Description:
// Parameters:
//      string image;
// Return: string  
// -------------------------------------------------------------
string Language::getLocationImage(string image) {

    string imageReturn = image;

    xmlDocPtr document;
    document = openXmlDocument();

    xmlChar * textSearch = (xmlChar *) "//Image";

    xmlXPathObjectPtr resultSearchNode;
    resultSearchNode = getSearchNode(document, textSearch);

    if (resultSearchNode != NULL) {
        xmlNodeSetPtr nodeset;
        nodeset = resultSearchNode->nodesetval;
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

void Language::setLanguagesExist() {

    xmlDocPtr document;
    document = openXmlDocument();

    xmlChar * textSearch = (xmlChar *) "//Languages";

    xmlXPathObjectPtr resultSearchNode;
    resultSearchNode = getSearchNode(document, textSearch);

    if (resultSearchNode != NULL) {
        xmlNodeSetPtr nodeset;
        nodeset = resultSearchNode->nodesetval;
        for (int i = 0; i < nodeset->nodeNr; i++) {
            xmlChar * descriptionLanguages;
            descriptionLanguages = xmlNodeListGetString(document, nodeset->nodeTab[i]->xmlChildrenNode, 1);
            this->languagesExist.push_back((const char *) descriptionLanguages);
            xmlFree(descriptionLanguages);
        }
        xmlXPathFreeObject(resultSearchNode);
    }

    closeXmlDocument(document);
    xmlCleanupParser();
}

vector<string> Language::getLanguagesExist() {
    return this->languagesExist;
}

xmlXPathObjectPtr Language::getSearchNode(xmlDocPtr document, xmlChar * nodeSearch) {
    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;

    context = xmlXPathNewContext(document);
    if (context == NULL) {
        printf("Error in xmlXPathNewContext\n");
        return NULL;
    }
    result = xmlXPathEvalExpression(nodeSearch, context);
    xmlXPathFreeContext(context);
    if (result == NULL) {
        printf("Error in xmlXPathEvalExpression\n");
        return NULL;
    }
    if(xmlXPathNodeSetIsEmpty(result->nodesetval)) {
        xmlXPathFreeObject(result);
        printf("No result\n");
        return NULL;
    }

    return result;
}

xmlDocPtr Language::openXmlDocument() {
    xmlDocPtr document;
    document = xmlParseFile("languages/internacionalization.xml");

    if (document == NULL) {
        assert(true && "Fail to open doc internacionalization.xml, is not possible to run the game.");
    }

    return document;
}

void Language::closeXmlDocument(xmlDocPtr document) {
    xmlFreeDoc(document);
}
