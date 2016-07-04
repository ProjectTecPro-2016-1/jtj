#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <vector>
#include <string>
#include <libxml/xpath.h>
#include <libxml/parser.h>

class Language {
    private:
        std::string language;                       // Language selected in run of the game.
        std::vector<std::string> languagesExist;    // Languages that exist in xml file.

    public:
        Language(std::string language);
        ~Language();

        void setLanguage(std::string informedLanguage);
        std::string getLanguage();

        std::string getText(std::string text);
        std::string searchTextReturn(xmlDocPtr document, xmlNodePtr currentNode);
        std::string getLocationImage(std::string image);

        std::vector<std::string> getLanguagesExist();
        void setLanguagesExist();

        xmlDocPtr openXmlDocument();
        void closeXmlDocument(xmlDocPtr document);
        xmlXPathObjectPtr getSearchNode(xmlDocPtr document, xmlChar * nodeSearch);
};

#endif
