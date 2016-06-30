#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>

class Language {
    private:
        std::string language;

    public:
        Language(std::string language);
        ~Language();

        void setLanguage(std::string language);
        std::string getLanguage();
        void readXMLFile();

        std::string getText(std::string text);
        std::string getLocationImage(std::string image);
};

#endif
