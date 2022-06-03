#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

class Aresta{
    public:

        //Atributos
        int id;           // id da aresta
        int origem;       // origem da aresta
        int destino;      // destino da aresta
        double limiteSup; // limite superior de fluxo da aresta
        double limiteInf; // limite inferior de fluxo da aresta
        double fluxo;     // fluxo atual da aresta
        bool visitado;    // flag para saber se a aresta foi visitada
        bool inversa;     // flag para saber se a aresta eh inversa
        bool usavel;      /* flag para saber se a aresta pode ser utilizada (caso nao seja possivel aumentar ou diminuir seu fluxo,
                             dependendo se ela eh inversa ou nao, aresta.usavel = false)*/
        int idOposta;     // flag para saber a aresta oposta correspondente

        //Metodos
        Aresta(int id = -1, int origem = -1, int destino = -1, double limiteSup = -1.0, double limiteInf = -1.0, double fluxo = -1.0, bool visitado = false, bool inversa = false, bool usavel = false, int idOposta = -1); // construtor
        ~Aresta(); // destrutor

        void printInfo(); // print de debug
};

class Rotulo{

    public:
        bool resetado;  // flag que indica se o rotulo eh valido ou nao (true se o vertice possuir o rotulo e false caso contrario)
        int rot;        // vertice anterior
        char op;        // '+' para arco direto, '-' para arco inverso, '0' para o vertice inicial
        double aumento; // a folga adicionada ao vertice

        Rotulo(); // contrutor
        Rotulo(bool resetado, int rot = -1, char op = '0', double aumento = 1000000); // contrutor com parametros
        ~Rotulo(); // destrutor
};

class Vertice{
    public:

        //Atributos
        int id;                          // id do vertice
        bool visitado;                   // flag usada no DFS para saber se o vertice foi visitado
        list<pair<int, int>> adjacencia; /* lista de adjacencia do vertice onde cada no possui um par 
                                            <indice do vertice alcancado, indice da aresta utilizada> */
        Rotulo rotulo;                   // rotulo do vertice utilizado no algoritmo Ford-Fulkerson

        //Metodos
        Vertice(int id, bool visitado = false); // construtor
        ~Vertice(); // destrutor

        void printInfo(); // print de debug
};

class FF{
    public:

        //Atributos
        int qntd_vertices;        // qntd de vertices no grafo
        int qntd_arestas;         // qntd de arestas no grafo
        int source;               // vertice inicial que por default eh o vertice de id 1
        int target;               // vertice final que por default eh o ultimo vertice
        vector<Vertice> vertices; // vetor que contem todos os vertices do grafo
        vector<Aresta> arestas;   // vetor que contem todas as arestas do grafo

        //Metodos
        FF(); // construtor
        FF(int qntd_vertices, int qntd_arestas, int source, int target); // construtor com parametros
        ~FF(); // destrutor

        void inicializaGrafo();                                           // funcao que realiza a leitura do grafo
        void dfs(int vertice_inicial, vector<int>* caminho, bool* achou); // algoritmo DFS baseado no trabalho anterior
        void ff(int vertice_atual);                                       // ford-fulkerson
        void construirCaminho(Rotulo r);                                  /* funcao que constroi o caminho percorrido pelo algoritmo e
                                                                             printa o output*/
        void aumentaFluxo(double aumento, vector<int> arestasUsadas);     // funcao que ajusta o fluxo das arestas a cada iteracao do FF
        void cancelaRotulos();                                            // cancela o rotulo dos vertices a cada iteracao do FF

        void printInfo(); // print de debug
};

#endif