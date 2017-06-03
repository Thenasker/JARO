#ifndef JAROLIB_H_INCLUDED
#define JAROLIB_H_INCLUDED

/////////////////////////////INCLUDES
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
//Input/output manipulation. É usada para modificar a estrutura da saida de resultados.
#include <iomanip>
//Biblioteca usada para gerar os arquivos com nomes baseados na data (ao estilo dos logs)
#include <ctime>
/////////////////////////////INCLUDES
using namespace std;

struct elemento {
    string s1;
    string s2;
    int m;
    int t;
    double jaro;
};

//Cabezera das funçoes da biblioteca
int mostrarMenu();
void encherVetor(vector<elemento> &elementos, string nome);
void calcularMT(vector<elemento> &elementos);
void calcularJaro(vector<elemento> &elementos);
void mostrarDados(vector<elemento> &elementos, int mostra, int ordem, char zeros);
bool finalizar();
void salvarArquivo(vector<elemento> &elementos);
void ordenarElementos(vector<elemento> &elementos);


#endif // JAROLIB_H_INCLUDED
