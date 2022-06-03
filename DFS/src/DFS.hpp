#ifndef DFS_H
#define DFS_H

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
        double peso;      // peso da aresta
        bool visitado;    // flag para indicar se a aresta foi visitada ou nao
        bool direcionada; // flag apra indicar se a aresta eh direcionada ou nao

        //Metodos
        Aresta(int id = -1, int origem = -1, int destino = -1, double peso = -1.0, bool visitado = false, bool direcionada = false); // construtor
        ~Aresta(); // destrutor

        void printInfo(); // print de debug
};

class Vertice{
    public:

        //Atributos
        int id;               // id do vertice
        bool visitado;        // flag para indicar se o vertice foi visitado
        list<int> adjacencia; // lista de adjacencia que contem inteiros representando o id da aresta utilizada

        //Metodos
        Vertice(int id, bool visitado = false); // construtor
        ~Vertice(); // destrutor

        void printInfo(); // print de debug
};

class Grafo{
    public:

        //Atributos
        int qntd_vertices;        // qntd de vertices do grafo
        int qntd_arestas;         // qntd de arestas do grafo
        int vertice_inicial;      // id do vertice inicial
        bool direcionado;         // indica se o grafo eh direcionado
        vector<Vertice> vertices; // vetor que armazena todos os vertices do grafo
        vector<Aresta> arestas;   // vetor que armazena todas as arestas do grafo

        //Metodos
        Grafo(); //construtor
        Grafo(int qntd_vertices, int qntd_arestas, int vertice_inicial, bool direcionado); // construtor com parametros
        ~Grafo(); // destrutor

        void inicializaGrafo(); // realiza a leitura do grafo
        void DFS(int idVerticeAtual, list<int>* ordem_visitacao); // algoritmo DFS

        void printInfo(); // print de debug
};

void printFinal(list<int> ordemVisitacao); // funcao para realizar o output

#endif