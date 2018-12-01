#include "ConfigReader.h"



void ConfigReader::readConfig() {

    // Ini file to override some path when /system/sdcard won't exit

    char dirNameBuffer[PATH_MAX + 1] = {0};
    // Read the symbolic link '/proc/self/exe'.
    const char *linkName = "/proc/self/exe";
    readlink(linkName, dirNameBuffer, sizeof(dirNameBuffer) - 1);

    // Read the same exe file + ini
    strncat(dirNameBuffer, ".ini", sizeof(dirNameBuffer) - 1);
    LOG_S(INFO) <<  "Reading Config...." << dirNameBuffer;
    reader = new INIReader(dirNameBuffer);
    if (reader->ParseError() < 0) {
        LOG_S(ERROR) << "Cant read Config";
        exit(-1);
    }
}

char* ConfigReader::getSensorName() {
    return strdup(reader->Get("Hardware", "SensorAddr", "").c_str());
}
int ConfigReader::getSensorAddr(){
    return reader->GetInteger("Hardware", "SensorAddr", 0);
}