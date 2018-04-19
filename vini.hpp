#ifndef VINI_HPP
#define VINI_HPP

#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>

class Vini {
public:
    typedef std::map< std::string, std::string > vini_content;
    typedef std::map< std::string, vini_content > vini_file;

    //Create blank file
    Vini() : ini_file() {
        parse_text("");
    }

    //Create class from path to INI file
    Vini(std::string path) : ini_file() {
        std::ifstream file;

        file.open(path.c_str());

        std::stringstream stringbuffer;

        stringbuffer << file.rdbuf();

        file.close();
        
        parse_text(stringbuffer.str());
    }

    //Save back to file
    void save(std::string path) {
        //Not yet implimented.

        std::ofstream file;

        file.open(path.c_str());

        for (vini_file::iterator it = ini_file.begin(); it != ini_file.end(); it++) {
            file << "[" << it->first << "]" << "\n";

            for (vini_content::iterator inner_it = it->second.begin(); inner_it != it->second.end(); inner_it++)
                file << inner_it->first << "=" << inner_it->second << "\n";
        }
    }

    //Get value from file
    //section and key are self-explanatory. default_value is the value that will be returned if the key isn't in the file
    //If default_value is returned, it will also be added to the file with the same key.
    std::string get(std::string section, std::string key, std::string default_value) {
        if (ini_file[section][key] != "")
            return ini_file[section][key];
        
        //If it can't find anything, return default value.
        set(section, key, default_value);

        return default_value;
    }

    //Set value in file
    //All fields are self-explanatory
    void set(std::string section, std::string key, std::string value) {
        ini_file[section][key] = value;
    }

    vini_file ini_file;

private:
    void parse_text(std::string file_text) {
        if (file_text == "") {
            return;
        }

        std::vector<std::string> lines = split(file_text, '\n');

        std::string current_section = "global";

        for (unsigned int i = 0; i < lines.size(); i++) {
            //Line is blank
            if (lines[i] == "")
                continue;
            
            //Line is a comment
            if (lines[i][0] == ';')
                continue;
            
            //Line is the start of a section
            if (lines[i][0] == '[' && lines[i][lines[i].length() - 1] == ']') {
                std::string key = lines[i].substr(1, lines[i].size() - 2);

                current_section = key;

                //If this section already exists, the next step isn't necessary.
                if (ini_file.count(key)) {
                    continue;
                }

                ini_file[key] = vini_content();
            }

            //Finally, line is actual content
            if (std::count(lines[i].begin(), lines[i].end(), '=') == 1) {
                std::vector<std::string> keyvalpair = split(lines[i], '=');

                std::string content_string = keyvalpair[1];

                content_string.erase(std::remove(content_string.begin(), content_string.end(), '"'), content_string.end());

                ini_file[current_section][keyvalpair[0]] = content_string;
            }
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;

        std::stringstream ss(s);
        std::string item;

        while(std::getline(ss, item, delim)) {
            elems.push_back(item);
        }

        return elems;
    }

    
};

#endif //VINI_HPP