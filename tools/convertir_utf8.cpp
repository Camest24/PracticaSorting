#include <iostream>
#include <fstream> // habilitamos ifstream para leer archivos y ofstream para escribir archivos
#include <algorithm>


int main() {
    std::ifstream archivo("data/dataset.txt",std::ios::binary); //Abrimos dataset e binario,leemos los bytes tal cual como estan escriitos. Sin que el siistema traduzca otros saltos e linea y otros bytes
    //Ahora teemos q leer todos los bytes del archivo a memoria de una vez, la forma mas sencilla es basicamente esto
    std::string bytesCrudos((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>()); // esto lee,todo el archivo de un golpe,byte por byte,sin decir nada

    //Ahora, vamos a decodificar esos bytes a texto real
    // Prrimero verificiamos el BOM
    unsigned char b0 = bytesCrudos[0];
    unsigned char b1 = bytesCrudos[1];
    if (b0 !=0xFF || b1 != 0xFE) {
        std::cerr << "El archivo no tiene BOM" << std::endl;
        return 1;
    }
        //usamos el unsigned char pporq en muchos compiladores char es signedd
        std::string texto;
        for (size_t i = 2 ; i < bytesCrudos.size();i+=2) {
            char c = bytesCrudos[i];
            if (c == '\r') continue;
            texto +=c;
        }
        std::cout <<"Lineas: " << std::count(texto.begin(),texto.end(),'\n') << std::endl;

std::ofstream salida("data/dataset_utf8.txt"); //offstream es como ifstream pero pa escribir,
    salida << texto;
        return 0;
}