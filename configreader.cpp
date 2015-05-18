#include "configreader.h"

#include <fstream>

// Removes spaces from the beginning and end of a string
static std::string trimString(const std::string &s)
{
    size_t left = s.find_first_not_of(' ');
    size_t right = s.find_last_not_of(' ');

    if (left == std::string::npos || right == std::string::npos)
        return "";

    return s.substr(left, right + 1);
}

// Converts a section/key pair into a single string used as a search key in the config map
static std::string toSearchKey(const std::string &section, const std::string &key) {
    return trimString(section) + "." + trimString(key);
}

ConfigReader::ConfigReader(const std::string &filename) :
    m_fileRead(true)
{
    std::ifstream in(filename.c_str());
    if (!in) {
        m_fileRead = false;
        return;
    }

    std::string line;
    std::string curSection;
    while (std::getline(in, line)) {
        line = trimString(line);

        if (line.size() > 2 && line[0] == '[') {
            if (line[line.length() - 1] == ']') {
                // Start of a new section
                curSection = line.substr(1, line.size() - 2);
            }
        } else {
            // Split new key/value pair and add it to our map.
            size_t delimiterPos = line.find('=');
            if (delimiterPos == std::string::npos)
                continue; // Invalid key value pair

            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            if (key.length() == 0 || value.length() == 0)
                continue; // Invalid key value pair

            m_config[toSearchKey(curSection, key)] = value;
        }
    }
}

bool ConfigReader::fileRead() const
{
    return m_fileRead;
}

std::string ConfigReader::get(const std::string &section, const std::string &key) const
{
    std::map<std::string, std::string>::const_iterator it = m_config.find(toSearchKey(section, key));
    if (it != m_config.end())
        return it->second;
    return "";
}
