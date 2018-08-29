//
// Created by Peter Zheng on 2018/08/29.
//

#ifndef GARBAGE_COLLECTION_CPP_IMPL_EXCEPTION_H
#define GARBAGE_COLLECTION_CPP_IMPL_EXCEPTION_H


#include <exception>
#include <string>

namespace GCImpl {
    class exception : public std::exception {
    private:
        std::string message;
        std::string type;
    public:
        exception() = default;

        exception(const std::string &datamess, const std::string &dataType) {
            message = datamess;
            type = dataType;
        }

        ~exception() {}

        const char *what() const {
            return std::string(message + " " + type).c_str();
        }
    };
}
#endif //GARBAGE_COLLECTION_CPP_IMPL_EXCEPTION_H
