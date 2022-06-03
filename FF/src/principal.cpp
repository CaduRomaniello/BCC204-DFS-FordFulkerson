#include "FordFulkerson.hpp"

using namespace std;

int main(){

    // Criacao e inicializacao do grafo
    FF grafo = FF();
    grafo.inicializaGrafo();

    // Ford-Fulkerson
    vector<vector<int>> caminhos;
    vector<int> caminho;
    grafo.ff(grafo.source);

    return 0;

}