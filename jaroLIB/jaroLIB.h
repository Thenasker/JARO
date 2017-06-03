#ifndef JAROLIB_H_INCLUDED
#define JAROLIB_H_INCLUDED

int mostrarMenu();
void encherVetor(vector<elemento> &elementos, string nome);
void calcularMT(vector<elemento> &elementos);
void calcularJaro(vector<elemento> &elementos);
void mostrarDados(vector<elemento> &elementos, int mostra, int ordem, char zeros);
bool finalizar();
void salvarArquivo(vector<elemento> &elementos);
void ordenarElementos(vector<elemento> &elementos);


#endif // JAROLIB_H_INCLUDED
