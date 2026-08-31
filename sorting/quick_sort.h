#pragma once // header guard,evita q el archivo se incluya 2 veces por accidente y rompa la compilación, recibe el vector por referencia & para modificarlo sin copiar 100.000 strings
#include <vector>
#include <string>

void quickSort(std::vector<std::string>& v);