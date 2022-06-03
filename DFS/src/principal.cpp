#include "DFS.hpp"

using namespace std;

int main(){

    // Criacao e inicializacao do grafo
    Grafo grafo = Grafo();
    grafo.inicializaGrafo();

    // DFS
    list<int> caminho;
    grafo.DFS(grafo.vertice_inicial, &caminho);

    // Print
    printFinal(caminho);

    return 0;

}