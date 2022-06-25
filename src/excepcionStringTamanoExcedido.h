#ifndef EXCEPCIONSTRINGTAMANOEXCEDIDO_H
#define EXCEPCIONSTRING

#include<exception>
#include<string>

using namespace std;

class ExcepcionStringTamanoExcedido : public exception {
    string mensaje;

    public:
    ExcepcionStringTamanoExcedido(char* atributo, string datoErroneo) : mensaje("Error. El tamaño del dato '" + datoErroneo + "' no puede exceder los " + to_string(sizeof(atributo)) + " caracteres."){ }
    ~ExcepcionStringTamanoExcedido() = default;

    virtual const char* what() const noexcept {
        return this->mensaje.c_str();
    }



};

#endif