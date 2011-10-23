
#include "common.h"
#include <fstream>

namespace App {
    bool exit = false;
    
    string interface = "";
    string pcapFilter = "";
};

void trimRight(string& str) {
    for (int i = str.size() - 1; i > 1; i--) {
        if (str[i] == '\n' || str[i] == '\r') {
            str = str.substr(0, i);
        } else {
            break;
        }
    }
}

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
        
        //cout << field.c_str() << " " << value.c_str() << " #" << endl;
        
        if (field == "interface")
            App::interface = value;
        else if (field == "filter")
            App::pcapFilter = value;
    }
    
    fs.close();
}
