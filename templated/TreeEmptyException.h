#ifndef MY_DATA_STRUCTURES_TREEEMPTYEXCEPTION_H
#define MY_DATA_STRUCTURES_TREEEMPTYEXCEPTION_H

#include <string>
#include <exception>
#include <iomanip>

namespace myds {

    class TreeEmptyException : public std::exception {
        private:
        std::string _message;

        public:
        TreeEmptyException(const std::string& functionName) {
            std::string msg;
            std::stringstream ss_msg{msg};
            ss_msg << "Attempted to  us \"" << functionName << "\" on empty Tree";
            _message = ss_msg.str();
        }
        const char *what() const noexcept override {
            return _message.c_str();
        }
    };

} // myds

#endif //MY_DATA_STRUCTURES_TREEEMPTYEXCEPTION_H
