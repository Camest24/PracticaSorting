#include <iostream> // Para cout/cerr, mensajes por consola
#include <fstream> // habilitamos ifstream para leer archivos y ofstream para escribir archivos
#include <algorithm>// Para std::count,


int main() {
    std::ifstream archivo("data/dataset.txt",std::ios::binary); //Abrimos dataset e binario,leemos los bytes tal cual como estan escriitos. Sin que el siistema traduzca otros saltos e linea y otros bytes
    //Ahora teemos q leer todos los bytes del archivo a memoria de una vez, la forma mas sencilla es basicamente esto
    std::string bytesCrudos((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>()); // esto lee,todo el archivo de un golpe,byte por byte,sin decir nada

    //Ahora, vamos a decodificar esos bytes a texto real
    // Primero verificiamos el BOM
    unsigned char b0 = bytesCrudos[0]; // Primer byte del archivo
    unsigned char b1 = bytesCrudos[1]; // Segundo byte del archivo
    if (b0 !=0xFF || b1 != 0xFE) { // 0xFF, 0xFE es el BOm de UTF-16, si no coincide no es el archivo q esperabamos
        std::cerr << "El archivo no tiene BOM" << std::endl; // Avisa el error por consola
        return 1; // Termina el programa con código de error
    }

        std::string texto; // Aquí se va armando el texto ya decodificado
        for (size_t i = 2 ; i < bytesCrudos.size();i+=2) {// Arranca en 2 para saltar el BOM, y avanza de 2 en 2 porque en UTF-16 cada carácter ocupa 2 bytes
            char c = bytesCrudos[i]; //Toma el byte bajo , para ASCII,el byte alto siempre es 0x00,entonces el bajo basta para reconstruir el caracter
            if (c == '\r') continue; // Salta el retorno del CRFL de wiidnows dejando a \n
            texto +=c; //Agrega el caracter ya decoficiado al final
        }
        std::cout <<"Lineas: " << std::count(texto.begin(),texto.end(),'\n') << std::endl; // Cuenta saltos de línea como verificación rápida (debería dar 100,000)

std::ofstream salida("data/dataset_utf8.txt"); //offstream es como ifstream pero pa escribir,
    salida << texto; //Escribe el texto convertido en un arhivo de salida
        return 0; //Indica q termina sin errores
}