#include <iostream>
#include <string>

extern bool tracingErrors;

void ErrorMessage(const std::string& message, int error = 0, std::ostream& output = std::cerr) {
    std::string error_mess = message + (error ? ", error:" + std::to_string(error) : "");
    if(tracingErrors)
        output << error_mess << std::endl;
    //throw exception(ErrorMessage.c_str());
}