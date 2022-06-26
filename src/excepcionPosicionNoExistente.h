#ifndef EXCEPCIONPOSICIONNOEXISTENTE_H
#define EXCEPCIONPOSICIONNOEXISTENTE_H

#include<exception>
#include<string>

using namespace std;

class ExcepcionPosicionNoExistente : public exception {
    public:
    ExcepcionPosicionNoExistente() noexcept = default;
    ~ExcepcionPosicionNoExistente() = default;

    virtual const char* what() const noexcept {
        return "Error. La posición solicitada no existe.";
    }



};

#endif