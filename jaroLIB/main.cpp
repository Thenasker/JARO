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
/////////////////////////////INCLUDES

/////////////////////////////DEFINES
//Definiçao do string do menu
#define menu "\n1--Mostrar distancias de pares do arquivo padrao\n\n2--Mostrar mais similares e menos similares dos pares do arquivo padrao\n\n3--Mostrar distancias de pares de um arquivo proprio\n\n4--Mostrar mais similares e menos similares dos pares de um arquivo proprio\n\n5--Consultar coindidencia de duas palavras\n\n6--Consultar coindidencia de duas frases\n\n7--Jogo lembrar palavras\n\n0--Sair\n\n"
//Definiçao do tamaño do nome dos arquivos a salver e do formato deles
#define FORMATO_NOME "jaro_%Y%m%d_%H%M%S.txt"
#define TAMANHO_NOME 25
#define CHAR_VACIO '_'
/////////////////////////////DEFINES

using namespace std;

//struct que contem todas as variaveis necessarias para calcular a distancia de Jaro e mostrar ela.
struct elemento {
    string s1;
    string s2;
    int m;
    int t;
    double jaro;
};

//Funçao que mostra o menu de opçoes inicial
int mostrarMenu(){

    int opcao=-1;

    //Enquanto o usuario nao escreva uma opçao valida o menu vai se mostrar uma e outra vez.
    while(opcao<0 || opcao>7){
        system("cls");
        //Usamos a variavel definida 'menu'
        cout << menu << endl;
        cin >> opcao;
        if(opcao<0 || opcao>7){
            cout << "Inserir uma opcao valida (0-7)" << endl;
            Sleep(2000);
        }
    }
    return opcao;
}

//Funçao que obtem os pares de palavras de um arquivo e enche o vetor de elementos com elas
void encherVetor(vector<elemento> &elementos, string nome){

    vector<string> lista;
    string aux;
    int pos=0;
    elemento elem;

    //enchemos um vetor de strings com todas as palavras do arquivo, linha a linha
    ifstream arquivo(nome.c_str());
    while (std::getline(arquivo, aux))
    {
        lista.push_back (aux);
    }

    //Usamos o metodo random_shuffle para embarajar o vetor de palavras
    random_shuffle(lista.begin(), lista.end());

    //Usamos uma variavel auxiliar 'elem' de tipo elemento para obter as palavras da lista (em pares) e adicionamos ele ao vetor de elementos.
    while (!lista.empty()){
        elem.jaro=0;
        elem.m=0;
        elem.t=0;
        //back() extrai o conteudo da ultima posiçao
        elem.s1=lista.back();
        //pop_back() elimina o objeto na ultima posiçao reduzindo o tamanho do vetor
        lista.pop_back();
        //No caso que a lista acabar sem poder ter preenchido as duas strings do elemento, prenchemos a segunda com uma linha padrao.
        if(lista.empty()){
            elem.s2="fim_da_lista";
        }else{
            elem.s2=lista.back();
            lista.pop_back();
        }
        //push_back() insereum elemento no vetor na ultima posiçao.
        elementos.push_back(elem);
    }
}

//Funçao que calcula a variavel 'm' (numeor de coincidencias) e 't' numero de transposiçoes
void calcularMT(vector<elemento> &elementos){

    string s1, s2;
    string m1, m2;
    int l1,l2;
    int m=0, t=0;
    int rango = 0;
/////////////////////////////////////////DEBUG
//          elementos.at(0).s1 = "MARTHA";
//          elementos.at(0).s2 = "MARHTA";
/////////////////////////////////////////

    for(int cont = 0 ; cont < elementos.size() ; cont ++){

        s1 = elementos.at(cont).s1;
        s2 = elementos.at(cont).s2;
        l1 = s1.length();
        l2 = s2.length();

        //obtemos o intervalo no cual dois caracteres podem ser coincidentes.
        rango = (max(s1.length(),s2.length())/2)-1;

        //por cada caracter da primeira palavra comprovamos os caracteres da segunda dentro do intervalo
        for(int i = 0 ; i < s1.length() ; i ++){
            for(int j = max(0,i-rango) ; j <= min(i+rango,l2-1) ; j ++){

                //Se obtemos uma coincidencia adicionamos esse caracter a string de coincidencias m1 e botamos null no caracter que já tem um par da segunda palavra
                //a tercera linha é para sair do loop
                if(s1.at(i) == s2.at(j)){
                    m1+= s1.at(i);
                    s2.at(j)=NULL;
                    j = min(i+rango,l2);
                }
            }
        }

        s1 = elementos.at(cont).s1;
        s2 = elementos.at(cont).s2;

        //Fazemos o mesmo mas desta vez em ordem inverso. para obter o string de coincidencias m2
        for(int i = 0 ; i < s2.length() ; i ++){
            for(int j = max(0,i-rango) ; j <= min(i+rango,l1-1) ; j ++){

                if(s2.at(i) == s1.at(j)){
                    m2+= s2.at(i);
                    s1.at(j)=NULL;
                    j = min(i+rango,l1);
                }
            }
        }

        m = m1.length();

        //Se m1 e m2 tem algum caracter transposto, adicionamos 1 a 't'
        if(m1 == m2){
            t = 0;
        }else{
            for(int i=0;i<m1.length();i++){
                if(m1.at(i) != m2.at(i)) t++;
            }
        }

        //adicionamos os valores 'm' e 't' ao elemento da lista e zeramos as variaveis usadas para voltar a começar com o seguinte par.
        elementos.at(cont).m = m;
        elementos.at(cont).t = t/2;
        m=0;
        t=0;
        m1="";
        m2="";
        rango = 0;
    }
/////////////////////////////////////////DEBUG
//    for(int k = 0; k<20 ; k++){
//        cout << elementos.at(k).s1 << " -- " << elementos.at(k).s2 << " -- " << elementos.at(k).m <<  " -- " << elementos.at(k).t << endl;
//    }
//
//    system("pause");
/////////////////////////////////////////
}

//Funçao que calcula a distancia de jaro apartir dos valores de 'm' e 't'
void calcularJaro(vector<elemento> &elementos){

    int m, s1, s2, t;

    for(int cont = 0 ; cont < elementos.size() ; cont ++){

        m = elementos.at(cont).m;
        s1 = elementos.at(cont).s1.length();
        s2 = elementos.at(cont).s2.length();
        t = elementos.at(cont).t;

        //Simplesmente aplicamos a formula para cada par de plavras.
        if(m == 0){
            elementos.at(cont).jaro = 0;
        }else{
            elementos.at(cont).jaro = ((m/(double)s1)+(m/(double)s2)+((m-t)/(double)m))/3;
        }
    }


/////////////////////////////////////////DEBUG
//    for(int k = 0; k<20 ; k++){
//        cout << elementos.at(k).s1 << " -- " << elementos.at(k).s2 << " -- " << elementos.at(k).m <<  " -- " << elementos.at(k).t <<  " -- " << elementos.at(k).jaro << endl;
//    }
//
//    system("pause");
/////////////////////////////////////////
}

//Funçao que mostra os cada par de palavras e sua distancia de jaro.
void mostrarDados(vector<elemento> &elementos, int mostra, int ordem, char zeros){

    char cont=CHAR_VACIO;

    //No caso recebamos um 0 na variavel 'mostra' isso significa que queremos mostrar todos os elementos.
    if(mostra == 0) mostra = elementos.size();

    cout <<"\t"<<left<<setw(20)<<"Palavra 1"<<setw(20)<<"Palavra 2"<<right<<setw(20)<<"Distacia de Jaro\n\n"<< endl;

    //quando ordem é 2 vao se mostrar de menor a maior
    if(ordem==2){
        for(int i = 0; i < mostra; i++){

            if((zeros=='N' || zeros=='n') && elementos.at(i).jaro == 0){
                //incrementamos a mostra em um para compensar o registro que nao vai ser mostrado
                mostra++;
            }else{
                cout <<"\t"<<left<<setw(20)<<elementos.at(i).s1<<setw(20)<<elementos.at(i).s2<<right<<setw(20)<<setprecision(3)<<elementos.at(i).jaro<< endl;

                //cada 100 elementos mostrados perguntamos ao usuario se quer continuar ou nao.
                if(i%100==0 && i!=0 && cont!='F' && cont!='f'){
                    cont=CHAR_VACIO;
                    while(cont!='S' && cont!='s' && cont!='N' && cont!='n' && cont!='F' && cont!='f'){

                        cout << "\n\nContinuar? (S/N. F para continuar ate o fim.)" << endl;

                        cin >> cont;

                        if(cont == 'N' || cont == 'n'){
                            i = mostra;
                        }else if(cont == 'S' || cont == 's' || cont == 'F' || cont == 'f'){
                            //Se o usuario decidir continuar mostramos de novo a cabezera.
                            cout <<"\n\n\t"<<left<<setw(20)<<"Palavra 1"<<setw(20)<<"Palavra 2"<<right<<setw(20)<<"Distacia de Jaro\n\n"<< endl;
                        }
                    }
                }
            }
        }
    }else{
        for(int i = mostra-1; i >=0; i--){

            cout <<"\t"<<left<<setw(20)<<elementos.at(i).s1<<setw(20)<<elementos.at(i).s2<<right<<setw(20)<<setprecision(3)<<elementos.at(i).jaro<< endl;

            if(i%100==0 && i!=0 && cont!='F' && cont!='f'){
                cont=CHAR_VACIO;
                while(cont!='S' && cont!='s' && cont!='N' && cont!='n' && cont!='F' && cont!='f'){

                    cout << "\n\nContinuar? (S/N. F para continuar ate o fim.)" << endl;

                    cin >> cont;

                    if(cont == 'N' || cont == 'n'){
                        i = mostra;
                    }else if(cont == 'S' || cont == 's' || cont == 'F' || cont == 'f'){
                        cout <<"\n\n\t"<<left<<setw(20)<<"Palavra 1"<<setw(20)<<"Palavra 2"<<right<<setw(20)<<"Distacia de Jaro\n\n"<< endl;
                    }
                }
            }
        }
    }
}

//funçao para perguntar ao usuario se ele quer finalizar o apicativo o mostrar o menu inicial outra vez
bool finalizar(){

    char fim = CHAR_VACIO;

    //Se pergunta ao usuario se que sair e devolve um valor booleano para a funçao main
    while(fim!='S' && fim!='s' && fim!='N' && fim!='n'){
        cout << "\n\n\nDeseja finalizar o programa? (S/N)" << endl;
        cin >> fim;
    }

    if(fim=='S' || fim == 's'){
        return true;
    }else{
        return false;
    }

}

//Funçao para criar e salvar um arquivo com os resultados dos pares + distancia.
void salvarArquivo(vector<elemento> &elementos){

    char salvar=CHAR_VACIO;

    //Perguntamos ao usuario se deseja salvar o vetor de elementos (com as distancias) num arquivo.
    while(salvar!='S' && salvar!='s' && salvar!='N' && salvar!='n'){
        cout << "\n\nVoce quer salvar o arquivo? (S/N)" << endl;
        cin >> salvar;
        if(salvar=='S' || salvar=='s'){

            ofstream arquivoSalvar;

            //Formatamos o nome do arquivo com a data e hora do momento da criaçao do arquivo segundo o formato definido acima.
            char nome[TAMANHO_NOME];
            time_t timestamp = time(0);
            strftime(nome, sizeof(nome), FORMATO_NOME, localtime(&timestamp));

            arquivoSalvar.open (nome);
            //Escrevemos cada linha no mesmo modo que e mostrado na tela.
            for(int i=0;i<elementos.size();i++){
                arquivoSalvar <<"\t"<<left<<setw(20)<<elementos.at(i).s1<<setw(20)<<elementos.at(i).s2<<right<<setw(20)<<setprecision(3)<<elementos.at(i).jaro<< endl;
            }
            arquivoSalvar.close();
        }
    }
}

//Vamos usar um metodo de ordenamento clasico (bubble sort)
void ordenarElementos(vector<elemento> &elementos){

    elemento aux;
    int n = elementos.size();
    int m = 0;

    cout << "Ordenando..." << endl;


    while(n>0){
        m=0;
        //Para cada elemento de 1 a m comprovamos se o anterior e maior. No caso de ser certo trocamos eles.
        for(int i = 1; i < n; i++){
            if(elementos.at(i-1).jaro > elementos.at(i).jaro){
                aux = elementos.at(i-1);
                elementos.at(i-1) = elementos.at(i);
                elementos.at(i) = aux;
                m = i;
            }
        }
        //O ultimo valor de m significa que o resto dos valores ja tao ordenados, entao reduzimos o valor de n e fazemos outra pasada.
        n = m;
    }

    //No melhor dos casos(tudo ordenado). o algoritmo so vai ter que fazer n comprobaçoes. No pior, vai ter que fazer n^2 comprobaçoes e n^2 trocas.
    //Na verdade esse tipo de algoritmo nao e muito eficiente, mas e bem simples. Para nosso volume de dados serve perfeitamente.


//    /////////////////////////////////////////DEBUG
//    for(int k = 0; k<20 ; k++){
//        cout << elementos.at(k).s1 << " -- " << elementos.at(k).s2 << " -- " << elementos.at(k).m <<  " -- " << elementos.at(k).t <<  " -- " << elementos.at(k).jaro << endl;
//    }

//    system("pause");
/////////////////////////////////////////

}
