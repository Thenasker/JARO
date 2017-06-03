/*
*   Questão 8.
*
*   A distancia de Jaro é uma medida da similaridade entre duas strings. Quanto maior
*   for a distância de Jaro para duas strings, mais semelhantes são elas. A pontuação
*   é normalizada tal que 0 equivale a sem similaridade e 1 é uma correspondencia exata;
*
*   Definição A distância de Jaro dj entre duas strings s1 e s2 é:
*
*       dj = 0                                      Se m = 0
*       dj = 1/3 ((m/|s1|)+(m/|s2|)+((m-t)/m))      Se m > 0
*
*   Onde
*       - m é o numero de caracteres iguais;
*       - t é o numero de transposições;
*
*   Duas strings s1 e s2 são consideradas correspondentes se tiverem
*       ((max(|s1|,|s2|)/2)-1)
*
*   Tarefa:
*       -Implementar o algoritmo Jaro-distância e mostrar as distâncias para cada um dos
*       seguintes pares: http://www.puzzlers.org/pub/wordlists/unixdict.txt
*
*       -Identifique as de maior similaridade e as de menor;
*
*
*   Instruçoes:
*       1º abrir o projeto da biblioteca e compilar ela.
*       2º Sttings -> Compiler -> Linker settings -> Add -> Rota da biblioteca (arquivo .a)
*       3º Compilar e executar o programa
*/

/////////////////////////////INCLUDES
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
//Input/output manipulation. É usada para modificar a estrutura da saida de resultados.
#include <iomanip>
//Biblioteca usada para gerar os arquivos com nomes baseados na data (ao estilo dos logs)
#include <ctime>
//Incluimos nossa biblioteca particular
#include "jaroLIB.h"
/////////////////////////////INCLUDES

/////////////////////////////DEFINES
//Definiçao do string do menu
#define menu "\n1--Mostrar distancias de pares do arquivo padrao\n\n2--Mostrar mais similares e menos similares dos pares do arquivo padrao\n\n3--Mostrar distancias de pares de um arquivo proprio\n\n4--Mostrar mais similares e menos similares dos pares de um arquivo proprio\n\n5--Consultar coindidencia de duas palavras\n\n6--Consultar coindidencia de duas frases\n\n7--Jogo lembrar palavras\n\n0--Sair\n\n"
//Definiçao do string do titulo do jogo.
#define jogo "          __    __ __ __ __    __ __          __ __ __ __ \n         |  |  |           |  |   __|        |           |\n         |  |  |   __ __   |  |  |           |   __ __   |\n         |  |  |  |     |  |  |  |   __ __   |  |     |  |\n __ __   |  |  |  |     |  |  |  |  |__   |  |  |     |  |\n|   __|  |  |  |  |__ __|  |  |  |     |  |  |  |__ __|  |\n|  |__ __|  |  |           |  |  |__ __|  |  |           |\n|__ __ __ __|  |__ __ __ __|  |__ __ __ __|  |__ __ __ __|\n                __ __ __       __ __ __ __                \n               |         \\    |   __ __ __|               \n               |   __ __  \\   |  |                        \n               |  |     \\  |  |  |__ __ __                \n               |  |     |  |  |   __ __ __|               \n               |  |__ __/  |  |  |                        \n               |          /   |  |__ __ __                \n               |__ __ __ /    |__ __ __ __|               \n          __    __ __ __ __    __ __ __ __    __ __ __ __ \n         |  |  |   __ __   |  |   __ __   |  |           |\n         |  |  |  |     |  |  |  |__ __|  |  |   __ __   |\n         |  |  |  |     |  |  |      __ __|  |  |     |  |\n __ __   |  |  |  |__ __|  |  |     |        |  |     |  |\n|   __|  |  |  |   __ __   |  |  |\\   \\      |  |__ __|  |\n|  |__ __|  |  |  |     |  |  |  | \\    \\    |           |\n|__ __ __ __|  |__|     |__|  |__|  \\__ __|  |__ __ __ __|\n"
//Definiçao do tamaño do nome dos arquivos a salver e do formato deles
#define FORMATO_NOME "jaro_%Y%m%d_%H%M%S.txt"
#define TAMANHO_NOME 25
//Definiçao de um caracter padrao para inicializar as variaveis tipo char
#define CHAR_VACIO '_'
/////////////////////////////DEFINES

using namespace std;

//Mostrar distancias de pares do arquivo padrao
bool opcao1(){

    system("cls");

    //Criamos nosso vetor de structs de tipo elemento
    vector<elemento> elementos;

    //Chamamos a funçao encherVetor() da biblioteca jaroLIB. Pasamos nosso vetor por referencia e o nome do arquivo padrao
    encherVetor(elementos,"jaro.txt");

    //Chamamos a funçao calcularMT() da biblioteca jaroLIB. Pasamos nosso vetor por referencia.
    calcularMT(elementos);

    //Chamamos a funçao calcularJaro() da biblioteca jaroLIB. Pasamos nosso vetor por referencia.
    calcularJaro(elementos);

    //Chamamos a funçao mostrarDados() da biblioteca jaroLIB. Pasamos nosso vetor por referencia, '0' indicando que queremos
    //mostrar todos os dados do vetor, '2' indicando que queremos que mostre os dados de menor a maior e CHAR_VACIO para que
    //mostre os pares que obtiveram dist. de jaro = 0.
    mostrarDados(elementos,0,2,CHAR_VACIO);

    //Chamamos a funçao salvarArquivo() da biblioteca jaroLIB. Pasamos nosso vetor por referencia.
    salvarArquivo(elementos);

    //devolvemos o valor que vamos obter da funçao finalizar() da biblioteca jaroLIB.
    return finalizar();
}

//Mostrar mais similares e menos similares dos pares do arquivo padrao
bool opcao2(){

    system("cls");

    vector<elemento> elementos;

    //Criamos as variaveis que vao indicar a ordem a mostrar, se o usuario quer ver os pares com
    //distancias de jaro = 0 e o numero de resultados que quer ver.
    int ordem=-1;
    char zeros=CHAR_VACIO;
    int mostra=-1;

    //Mesmo desenvolvimento que na funçao opcao1
    encherVetor(elementos,"jaro.txt");
    calcularMT(elementos);
    calcularJaro(elementos);

    //Chamamos a funçao ordenarElementos() da biblioteca jaroLIB. Pasamos nosso vetor por referencia.
    ordenarElementos(elementos);


    //Perguntamos ao usuario pela ordem
    while(ordem!=1 && ordem!=2){
        system("cls");
        cout << "Selecionar ordem:" << endl;
        cout << "\t1-Maior a menor" << endl;
        cout << "\t2-menor a Maior" << endl;
        cin >> ordem;
    }

    //Noc caso na ordem seja de menor a maior, perguntamos ao usuario se quer mostrar as d. de jaro = 0.
    if(ordem==2){

        while(zeros!='S' && zeros!='s' && zeros!='N' && zeros!='n'){
            system("cls");
            cout << "Deseja mostrar os pares com distancias de jaro igual a zero? (S/N)" << endl;
            cin >> zeros;
        }

    }

    //Perguntamos ao usuario qual quer que seja a mostra dos mais/menos semelhantes
    while(mostra < 0){
        system("cls");
        cout << "Indicar o numero de pares a mostrar (0 para mostrar todos)." << endl;
        cin >> mostra;
    }

    //Chamamos a funçao mostrarDados() da biblioteca jaroLIB. Pasamos nosso vetor por referencia, e os dados obtidos do usuario
    mostrarDados(elementos,mostra,ordem,zeros);

    //Mesmo desenvolvimento que na funçao opcao1
    salvarArquivo(elementos);
    return finalizar();
}

//As opçoes 3 e 4 sao semelhantes as 1 e 2. A unica diferencia e que antes da chamada a encherVetor() obtemos a rota do arquivo (valida) do usuario.

//Mostrar distancias de pares de um arquivo proprio
bool opcao3(){

    system("cls");

    vector<elemento> elementos;
    string nome_arquivo;
    int erro=0;

////////////////////////////////////////////DEBUG
//C:\Users\thenasker\Desktop\JARO\arquivo_proprio.txt
////////////////////////////////////////////
        while(erro==0){
            cout << "Escreva o path de seu arquivo:" << endl;
            cin >> nome_arquivo;

            ifstream ifs(nome_arquivo.c_str());

            if(!ifs.is_open()){
                erro=0;
            }
            else{
                cout << "Erro ao abrir o arquivo!" << endl;
                erro=1;
                ifs.close();
            }
        }

    encherVetor(elementos,nome_arquivo);
    calcularMT(elementos);
    calcularJaro(elementos);

    mostrarDados(elementos,0,2,CHAR_VACIO);

    salvarArquivo(elementos);

    return finalizar();
}

//Mostrar mais similares e menos similares dos pares de um arquivo proprio
bool opcao4(){

    system("cls");

    vector<elemento> elementos;
    int ordem=-1;
    char zeros=CHAR_VACIO;
    int mostra=-1;
    int erro=0;
    string nome_arquivo;


    while(erro==0){
        cout << "Escreva o path de seu arquivo:" << endl;
        cin >> nome_arquivo;

        ifstream ifs(nome_arquivo.c_str());

        if(!ifs.is_open()){
            erro=0;
        }
        else{
            cout << "Erro ao abrir o arquivo!" << endl;
            erro=1;
            ifs.close();
        }
    }

    encherVetor(elementos,nome_arquivo);
    calcularMT(elementos);
    calcularJaro(elementos);
    ordenarElementos(elementos);


    while(ordem!=1 && ordem!=2){
        system("cls");
        cout << "Selecionar ordem:" << endl;
        cout << "\t1-Maior a menor" << endl;
        cout << "\t2-menor a Maior" << endl;
        cin >> ordem;
    }

    if(ordem==2){

        while(zeros!='S' && zeros!='s' && zeros!='N' && zeros!='n'){
            system("cls");
            cout << "Deseja mostrar os pares com distancias de jaro igual a zero? (S/N)" << endl;
            cin >> zeros;
        }

    }

    while(mostra < 0){
        system("cls");
        cout << "Indicar o numero de pares a mostrar (0 para mostrar todos)." << endl;
        cin >> mostra;
    }

    mostrarDados(elementos,mostra,ordem,zeros);

    salvarArquivo(elementos);
    return finalizar();
}

//Consultar coindidencia de duas palavras
bool opcao5(){

    vector<elemento> elementos;
    elemento aux;
    char cont=CHAR_VACIO;

    while(cont!='N' && cont!='n'){
        system("cls");
        cout << "Escreva duas palavras para obter a distancia de jaro. Numeros e simbolos sao aceitados. ";
        cout << "No caso de escrever mais de uma palavra (separadas por espacos) so sera tomada em conta a primeira delas.\n" << endl;
        system("pause");

        system("cls");

        //Recebemos do usuario as duas palavras que queremos comparar e armazenamos elas num objeto elemento auxuliar
        aux.s1="";
        aux.s2="";
        cout << "Escreva a primeira palavra:" << endl;
        cin >>aux.s1;

        cout << "Escreva a segunda palavra:" << endl;
        cin >>aux.s2;

        aux.m=0;
        aux.t=0;
        aux.jaro=0;
        //Adicionamos o elemento auxiliar ao vetor que precisamos para calcular os dados com as funçoes da biblioteca.
        elementos.push_back(aux);

        calcularMT(elementos);
        calcularJaro(elementos);

        system("cls");
        //Mostramos o resultado.
        cout << "A distancia de Jaro entre \"" << elementos.at(0).s1 << "\" e \"" << elementos.at(0).s2 << "\" e igual a " << setprecision(3)<<elementos.at(0).jaro<< endl;

        cont=CHAR_VACIO;
        while(cont!='N' && cont!='n' && cont!='S' && cont!='s'){
            cout << "\n\nDeseja consultar outro par de palavras? (S/N)" << endl;
            cin >> cont;
        }
        elementos.pop_back();
    }
    return finalizar();
}

//Consultar coindidencia de duas frases. O funcionamiento é muito similar a opçao 5.
bool opcao6(){

    vector<elemento> elementos;
    elemento aux;
    char cont=CHAR_VACIO;

    while(cont!='N' && cont!='n'){
        system("cls");
        cout << "Escreva duas frases para obter a distancia de jaro. Numeros e simbolos sao aceitados."<< endl;
        system("pause");

        system("cls");

        aux.s1="";
        aux.s2="";
        cout << "Escreva a primeira frase:" << endl;
        //Precisamos desse getchar() para capturar o \r del system("pause");
        getchar();
        std::getline (std::cin,aux.s1);

        cout << "\nEscreva a segunda frase:" << endl;
        std::getline (std::cin,aux.s2);

        aux.m=0;
        aux.t=0;
        aux.jaro=0;
        elementos.push_back(aux);

        calcularMT(elementos);
        calcularJaro(elementos);

        system("cls");
        cout << "A distancia de Jaro entre as frases:" << endl;
        cout << "\n\"" << elementos.at(0).s1 << "\"" << endl;
        cout << "\ne" << endl;
        cout << "\n\"" << elementos.at(0).s2 << "\"" << endl;
        cout << "\ne igual a " << setprecision(3)<<elementos.at(0).jaro<< endl;

        cont=CHAR_VACIO;
        while(cont!='N' && cont!='n' && cont!='S' && cont!='s'){
            cout << "\n\nDeseja consultar outro par de frases? (S/N)" << endl;
            cin >> cont;
        }
        elementos.pop_back();
    }
    return finalizar();
}

//Jogo lembrar palavras
bool opcao7(){

    vector<elemento> elementos;
    string s1aux;
    elemento aux;
    double media;

    system("cls");

    cout << jogo << endl;
    cout << "\n\nInstrucoes:\n" << endl;
    cout << "\tVao aparecer uma serie de palavras (cada vez mais compridas). Voce vai ter 3 segundos para ler bem a palabra e depois vai ter que escrever ela o mais semelhante posivel. O objetivo do jogo e conseguir a maior distancia de jaro posivel em todas as palavras.\n" << endl;

    //Utilizamos um arquivo padrao para armazenar as palavras do jogo na primeira string de cada elemento do vetor.
    aux.m=0;
    aux.t=0;
    aux.jaro=0;
    aux.s2="";
    ifstream arquivo("jogo.txt");
    while (std::getline(arquivo, s1aux))
    {
        aux.s1 = s1aux;
        elementos.push_back (aux);
    }

    system("pause");

    system("cls");
    cout << "Preparado?" <<endl;
    Sleep(1000);
    cout << "3" <<endl;
    Sleep(1000);
    cout << "2" <<endl;
    Sleep(1000);
    cout << "1" <<endl;
    Sleep(1000);
    cout << "A jogar!" <<endl;
    Sleep(1000);

    //Agora armazenamos as respostas do usuario na segunda string de cada elemento.
    for(int i = 0; i < elementos.size(); i++){
        system("cls");
        cout << elementos.at(i).s1 << endl;
        Sleep(3000);
        system("cls");
        cout << "Resposta: ";
        cin >> elementos.at(i).s2;
    }
    system("cls");

    //Fazemos os calculos como sempre e mostramos os resultados e a media final.
    calcularMT(elementos);
    calcularJaro(elementos);

    cout << "Resultados:\n" << endl;
    for(int i = 0; i < elementos.size(); i++){
        cout << elementos.at(i).s1 <<endl;
        cout << elementos.at(i).s2 << "\t" << setprecision(3) <<elementos.at(i).jaro << "\n" << endl;
    }

    for(int i = 0; i < elementos.size(); i++){
        media+=elementos.at(i).jaro;
    }
    media = media/elementos.size();

    cout << "A sua pontoacao (media entre as distancias de jaro obtidas) e de: " << setprecision(3) << media << endl;


    salvarArquivo(elementos);
    return finalizar();
}

//Funçao main
int main(){

    bool finalizar = false;

    //Mostramos a introduçao
    cout << "Linguagem de programacao" << endl;
    cout << "Questao 8. Distancia de Jaro." << endl;
    cout << "Pablo Rufat Munoz" << endl;
    cout << "Marcos Marques" << endl;
    cout << "2017/1\n\n" << endl;
    system("pause");

    //Mientras a funçao finalizar() nao devolva true, vamos chamar a funçao que mostra o menu.
    while(!finalizar){
        switch(mostrarMenu()){
            case(0):
                finalizar = true;
                break;
            case(1):
                finalizar = opcao1();
                break;
            case(2):
                finalizar = opcao2();
                break;
            case(3):
                finalizar = opcao3();
                break;
            case(4):
                finalizar = opcao4();
                break;
            case(5):
                finalizar = opcao5();
                break;
            case(6):
                finalizar = opcao6();
                break;
            case(7):
                finalizar = opcao7();
                break;
            default:
                finalizar = true;
                break;
        };
    }
    return 0;
}
