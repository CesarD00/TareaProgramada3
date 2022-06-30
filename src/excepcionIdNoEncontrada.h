#ifndef EXCEPCIONIDNOENCONTRADA_H
#define EXCEPCIONIDNOENCONTRADA_H

#include<exception>
#include<string>

using namespace std;

class ExcepcionIdNoEncontrada : public exception {
    public:
    ExcepcionIdNoEncontrada() noexcept = default;
    ~ExcepcionIdNoEncontrada() = default;

    virtual const char* what() const noexcept {
        return "Error. La id del producto solicitado no existe.";
    }



};

#endif