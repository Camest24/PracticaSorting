#pragma once // header guard,evita q el archivo se incluya 2 veces por accidente y rompa la compilación.
#include <vector> //incluye el header que define std::vector,define la plantilla std:vector
#include <string> //incluye el header que define std::string,osea el tipo de dato que guarda cada palabra dentro del vector

void quickSort(std::vector<std::string>& v); // recibe el vector por referencia & para modificarlo sin copiar los 100k strings