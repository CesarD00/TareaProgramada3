# TareaProgramada2 - Cesar Díaz Mora. C12552

### Información de la tienda       
       
| Campo | Tamaño en bytes | Offset |
| :---: | :-------------: | :----: |
| Nombre | 15 | 0 |
| Dirección de Internet | 24 | 15 |
| Dirección Física | 24 | 39 |
| Teléfono | 8 | 63 |

Bytes necesarios para la información de la tienda = 71

### Estructura de un producto

| Campo | Tamaño en bytes | Offset |
| :---: | :-------------: | :----: |
| Id | 4 | 71 |
| Nombre | 20 | 75 | 
| Existencias | 4 | 95 |

Bytes necesarios para un producto = 28

Offset Producto "n" =  71 + (n * 28)
