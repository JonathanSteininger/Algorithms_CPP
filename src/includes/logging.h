#pragma once
#include <iostream>

static void writeSourceLocation(const char *fileName, int lineNumber) {
#ifdef ENABLE_LOGGING
    std::cout << "file: " << fileName << " @:" << std::to_string(lineNumber)
              << " | ";
#endif
}

template <typename T> inline void writeStandardLog(T text) {
#ifdef ENABLE_LOGGING
    writeSourceLocation(__FILE__, __LINE__);
    std::cout << text << "\n";
#endif
}
template <typename T>
inline void writeVariableLog(std::string text, T variable) {
#ifdef ENABLE_LOGGING
    writeSourceLocation(__FILE__, __LINE__);
    std::cout << text << std::to_string(variable) << "\n";
#endif
}
template <typename T>
inline void writeVariableLogSimple(std::string text, T variable) {
#ifdef ENABLE_LOGGING
    writeSourceLocation(__FILE__, __LINE__);
    std::cout << text << variable << "\n";
#endif
}
