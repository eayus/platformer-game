#include "Logging.hpp"

#include <iostream>

namespace Utils {

    void log(const char* message) {

        std::cout << message << std::endl;

    }

    void log(const std::string& message) {

        std::cout << message << std::endl;

    }

}
