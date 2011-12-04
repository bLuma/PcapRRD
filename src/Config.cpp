
#include "common.h"
#include <fstream>

namespace App {
    bool exit = false;
    
    string interface = "";
    string pcapFilter = "";
};

/**
 * Orizne retezec zprava.
 * 
 * @param str retezec
 */
void trimRight(string& str) {
    for (int i = str.size() - 1; i > 1; i--) {
        if (str[i] == '\n' || str[i] == '\r') {
            str = str.substr(0, i);
        } else {
            break;
        }
    }
}

/**
 * Nacte konfiguraci ze souboru.
 */
void loadConfig() {
    ifstream fs(CONFIG_PATH "pcaprrd.cfg");
    
    if (!fs.is_open())
        return;
    
    while (!fs.eof() && fs.good()) {
        string line;
        getline(fs, line);
        
        if (fs.eof())
            break;
        
        if (line[0] == '#')
            continue;
        
        int delimiter = line.find('=');
        
        string field = line.substr(0, delimiter);
        string value = line.substr(delimiter + 1);
        
        trimRight(value);
        
        DEBUG_OUTPUT("loadConfig: " << field.c_str() << " = " << value.c_str());
        
        if (field == "interface")
            App::interface = value;
        else if (field == "filter")
            App::pcapFilter = value;
    }
    
    fs.close();
}

#ifdef WIN
#include <windows.h>

/**
 * Zjistuje existuje-li soubor na disku
 * 
 * @param name jmeno souboru
 * @return true, pokud existuje
 */
bool fileExists(string name) {
    string copy = name; // + RRD_FILE_EXT;
    return GetFileAttributesA(copy.c_str()) != 0xFFFFFFFF;
}

void makeDir(string name) {
    CreateDirectoryA(name.c_str(), NULL);
}
#else
#include <sys/stat.h>
/**
 * Zjistuje existuje-li soubor na disku
 * 
 * @param name jmeno souboru
 * @return true, pokud existuje
 */
bool fileExists(string name) {
    struct stat stats;
    
    string copy = name; // + RRD_FILE_EXT;
    return stat(copy.c_str(), &stats) == 0;
}

void makeDir(string name) {
    mkdir(name.c_str(), 0775);
}
#endif
