#ifndef EXCEPCIONNUMERONEGATIVO_H
#define EXCEPCIONNUMERONEGATIVO_H

#include<exception>
#include<string>

using namespace std;

class ExcepcionNumeroNegativo : public exception {
    public:
    ExcepcionNumeroNegativo() noexcept = default;
    ~ExcepcionNumeroNegativo() = default;

    virtual const char* what() const noexcept {
        return "Error. No es permitido ingresar números negativos.";
    }



};

#endif