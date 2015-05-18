#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <map>
#include <string>

class ConfigReader
{
public:
    ConfigReader(const std::string &filename);

    // Returns true if the config reader was able to read the config file.
    bool fileRead() const;

    // Get the value at a section and a key.
    // Returns "" if the section or key can't be found.
    std::string get(const std::string &section, const std::string &key) const;

private:
    std::map<std::string, std::string> m_config;
    bool m_fileRead;
};

#endif // CONFIGREADER_H
