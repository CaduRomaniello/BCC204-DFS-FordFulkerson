#include "DFS.hpp"

using namespace std;

/*
======================================================================================================
FUNCOES
======================================================================================================
*/

// percorre o vetor da ordem de visitacao printando cada item
void printFinal(list<int> ordemVisitacao){
    // for (int i = 0; i < static_cast<int>(ordemVisitacao.size()); i++){
    //     cout << ordemVisitacao[i] << "\n";
    // }

    for (auto i : ordemVisitacao){
        cout << i << "\n";
    }
}

/*
======================================================================================================
ARESTA
======================================================================================================
*/

Aresta::Aresta(int id, int origem, int destino, double peso, bool visitado, bool direcionada){
    this->id = id;
    this->origem = origem;
    this->destino = destino;
    this->peso = peso;
    this->visitado = visitado;
    this->direcionada = direcionada;
}
Aresta::~Aresta(){}

void Aresta::printInfo(){
    cout << "--------- Aresta ---------\n";
    cout << "Id         : " << this->id << "\n" ;
    cout << "Origem     : " << this->origem << "\n" ;
    cout << "Destino    : " << this->destino << "\n" ;
    cout << "Peso       : " << this->peso << "\n" ;
    cout << "Visitado   : " << this->visitado << "\n" ;
    cout << "Direcionada     : " << this->direcionada << "\n\n" ;
}

/*
======================================================================================================
VERTICE
======================================================================================================
*/

Vertice::Vertice(int id, bool visitado){
    this->id = id;
    this->visitado = visitado;
}
Vertice::~Vertice(){}

void Vertice::printInfo(){
    cout << "--------- Vertice ---------\n";
    cout << "Id                            : " << this->id << "\n" ;
    cout << "Visitado                      : " << this->visitado << "\n" ;
    cout << "Tamanho da lista de adjacencia: " << this->adjacencia.size() << "\n\n" ;
}

/*
======================================================================================================
GRAFO
====================================================================================================== 
*/

Grafo::Grafo(){}
Grafo::Grafo(int qntd_vertices, int qntd_arestas, int vertice_inicial, bool direcionado):qntd_vertices(qntd_vertices), qntd_arestas(qntd_arestas), vertice_inicial(vertice_inicial), direcionado(direcionado){}
Grafo::~Grafo(){}

void Grafo::inicializaGrafo(){

    // Leitura dos dados iniciais
    int qntd_vertices, qntd_arestas, direcionado, vertice_inicial;

    cin >> qntd_vertices >> qntd_arestas >> direcionado >> vertice_inicial;

    this->qntd_arestas = qntd_arestas;
    this->qntd_vertices = qntd_vertices;
    this->vertice_inicial = vertice_inicial;
    this->direcionado = direcionado;

    // Lendo vertices
    for (int i = 1; i <= this->qntd_vertices; i++){
        Vertice v(i, false);
        this->vertices.push_back(v);;
    }

    // Lendo arestas e criando listas de adjacencia
    int origem, destino;
    double peso;

    for (int i = 1; i <= this->qntd_arestas; i++){
        cin >> origem >> destino >> peso;
        
        Aresta a = Aresta(i, origem, destino, peso, false, true);
        this->arestas.push_back(a);

        this->vertices[origem - 1].adjacencia.push_back(i); // popula a lista de adjacencia

        // caso o grafo nao for direcionado a aresta tambem eh adicionada na lista de adjacencia do vertice de destino
        if (!this->direcionado){
            this->vertices[destino - 1].adjacencia.push_back(i);
        }

    }

    // ordena a lista de adjacencia de todos os vertices para fazer a analise na ordem crescente de indice
    for (int i = 0; i < this->qntd_vertices; i++){
        this->vertices[i].adjacencia.sort();
    }
}

void Grafo::DFS(int idVerticeAtual, list<int>* ordem_visitacao){
    
    // marca o vertice como visitado e insere no vetor que da ordem de visitacao
    this->vertices[idVerticeAtual - 1].visitado = true;
    ordem_visitacao->push_back(idVerticeAtual);

    // as operacoes sao realizadas para todos os itens da lista de adjacencia do vertice
    for (auto i : this->vertices[idVerticeAtual - 1].adjacencia){
        int idProxVertice;

        // verificacao para saber qual o proximo vertice a ser visitado que depende se o grafo eh direcionado ou n
        if (this->direcionado){
            idProxVertice = this->arestas[i - 1].destino;
        }
        else{
            if (this->arestas[i - 1].origem == idVerticeAtual){
                idProxVertice = this->arestas[i - 1].destino;
            }
            else{
                idProxVertice = this->arestas[i - 1].origem;
            }
        }

        // operacoes identicas ao pseudocodigo
        if (this->vertices[idProxVertice - 1].visitado){
            if (!(this->arestas[i - 1].visitado)){
                this->arestas[i - 1].visitado = true;
            }
        }
        else{
            this->arestas[i - 1].visitado = true;
            this->DFS(idProxVertice, ordem_visitacao);
        }
    }
}

void Grafo::printInfo(){
    cout << "--------- Grafo ---------\n";
    cout << "Qntd vertices  : " << this->qntd_vertices << "\n" ;
    cout << "Qntd arestas   : " << this->qntd_arestas << "\n" ;
    cout << "Vertice inicial: " << this->vertice_inicial << "\n\n" ;
}