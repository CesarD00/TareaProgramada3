#ifndef EXCEPCIONSTRINGTAMANOEXCEDIDO_H
#define EXCEPCIONSTRING

#include<exception>
#include<string>

using namespace std;

class ExcepcionStringTamanoExcedido : public exception {
    public:
    ExcepcionStringTamanoExcedido() noexcept = default;
    ~ExcepcionStringTamanoExcedido() = default;

    virtual const char* what() const noexcept {
        return "Error. Ingresó un dato o más que superan el límite de tamaño permitido.";
    }



};

#endif