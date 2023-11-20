#pragma once
#include <iostream>

static void writeSourceLocation(const char *fileName, int lineNumber, std::string *_location){
#ifdef ENABLE_LOGGING
    static std::vector<std::string> LogList = std::vector<std::string>();
    static bool loggingEnabled = true;
    if(LogList.empty()){
        LogList.push_back("main");
    }
    if(_location != nullptr){
        if(*_location == "___Toggle___"){
            loggingEnabled = !loggingEnabled;
        }
        if(*_location == "___Remove___"){
            LogList.pop_back();
            return;
        }
        LogList.push_back(*_location);
        return;
    }
    if(!loggingEnabled){
        return;
    }
    int desiredStart = 50;
    int totalTraveled = 0;
    for(std::string section : LogList){
        totalTraveled += section.length() + 1;
        std::cout << section << ">";
    }
    while(totalTraveled < desiredStart){
        std::cout << " ";
        totalTraveled++;
    }
    //std::cout << " | file: " << fileName << " @:" << std::to_string(lineNumber) << " | ";
#endif
}
inline void LOG_TOGGLE(){
#ifdef ENABLE_LOGGING
    std::string toggleString = "___Toggle___";
    writeSourceLocation("", 0, &toggleString);
#endif
}
inline void LOG_EXIT_SECTION(){
#ifdef ENABLE_LOGGING
    std::string removeString = "___Remove___";
    writeSourceLocation("", 0, &removeString);
#endif
}

inline void LOG_ADD_SECTION(std::string location){
#ifdef ENABLE_LOGGING
    writeSourceLocation("", 0, &location);
#endif
}
template <typename T>
inline void LOG(T text){
#ifdef ENABLE_LOGGING
    writeSourceLocation(__FILE__, __LINE__, nullptr);
    std::cout << text << "\n";
#endif
}
template <typename T> 
inline void LOG_VARS(std::string text, T variable){
#ifdef ENABLE_LOGGING
    writeSourceLocation(__FILE__, __LINE__, nullptr);
    std::cout << text << std::to_string(variable) << "\n";
#endif
}
template <typename T> 
inline void LOG_VARS_SIMPLE(std::string text, T variable){
#ifdef ENABLE_LOGGING
    writeSourceLocation(__FILE__, __LINE__, nullptr);
    std::cout << text << variable << "\n";
#endif
}

