#include "language.hpp"
#include <iostream>
#include <cassert>
#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
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
    assert(language != "" && "Fail to select a language because this is blank.");

    readXMLFile();
    setLanguage(language);
}

void Language::readXMLFile() {

    // xmlDocPtr xmlDocument;
    // xmlDocument = xmlParseFile("languages/internacionalization.xml");

    // xmlNodePtr internationalizationRoot;
    // internationalizationRoot = xmlDocGetRootElement(xmlDocument);
    // clog << internationalizationRoot->type << " - " << internationalizationRoot->name << endl;

    // xmlNodePtr languagesNode;
    // languagesNode = internationalizationRoot->children;
    // languagesNode = languagesNode->next;
    // clog << languagesNode->type << " - " << languagesNode->name << endl;

    // xmlNodePtr quantityLanguagesNode;
    // quantityLanguagesNode = languagesNode->children->next;
    
    // xmlChar * quantityLanguagesContent;
    // quantityLanguagesContent = xmlNodeListGetString(xmlDocument, quantityLanguagesNode->xmlChildrenNode, 1);
    // clog << quantityLanguagesNode->type << " - " << quantityLanguagesNode->name << " - " << quantityLanguagesContent << endl;

    // xmlNodePtr listOfLanguagesNode = quantityLanguagesNode->next->next;
    // for (int i = 0; i < 3; i++) {
    //     xmlNodePtr languageNodeEspecific = listOfLanguagesNode->children->next;
    //     xmlChar * listOfLanguagesContent;
    //     listOfLanguagesContent = xmlNodeListGetString(xmlDocument, languageNodeEspecific->xmlChildrenNode, 1);
    //     clog << languageNodeEspecific->type << " - " << languageNodeEspecific->name << " - " << listOfLanguagesContent << endl;
    //     languageNodeEspecific = languageNodeEspecific->next;
    // }



    // xmlNodePtr imagesNode;
    // imagesNode = languagesNode->next->next;
    // clog << imagesNode->type << " - " << imagesNode->name << endl;

    // xmlNodePtr textsNode;
    // textsNode = imagesNode->next->next;
    // clog << textsNode->type << " - " << textsNode->name << endl;


    // while(cur != NULL) {
    //     if(cur->type == XML_ELEMENT_NODE) {                       
    //         xmlChar* content;   
        
    //         cur = cur->children;
                
    //         while(cur != NULL) {
    //             if(cur->type == XML_ELEMENT_NODE) {                       
    //                 content = xmlNodeListGetString(xmlDocument, cur->xmlChildrenNode, 1);
    //                 printf("%s : %s\n",cur->name,content);
    //                 xmlFree(content);
    //                 /*free(content);*/   /* windows */
    //                 content = NULL;
    //             }

    //             cur = cur->next;
    //         }
    //     }

    //     cur = cur->next;
    // }
        
    // xmlFreeDoc(xmlDocument); 
}

// -------------------------------------------------------------  
// Function: ~Language()  
// Description: Destructor of class that define language of game.
// Return: void  
// -------------------------------------------------------------  
Language::~Language() {

}

// -------------------------------------------------------------  
// Function: setLanguage()  
// Description:
// Parameters:
//      string language;
// Return: void  
// -------------------------------------------------------------
void Language::setLanguage(string language) {
    this->language = language;
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
    return text;
}

// -------------------------------------------------------------  
// Function: getLocationImage()  
// Description:
// Parameters:
//      string image;
// Return: string  
// -------------------------------------------------------------
string Language::getLocationImage(string image) {
    return image;
}