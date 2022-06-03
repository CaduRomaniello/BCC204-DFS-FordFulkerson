#include "FordFulkerson.hpp"

using namespace std;

/*
======================================================================================================
ARESTA
======================================================================================================
*/

Aresta::Aresta(int id, int origem, int destino, double limiteSup, double limiteInf, double fluxo, bool visitado, bool inversa, bool usavel, int idOposta){
    this->id = id;
    this->origem = origem;
    this->destino = destino;
    this->limiteSup = limiteSup;
    this->limiteInf = limiteInf;
    this->fluxo = fluxo;
    this->visitado = visitado;
    this->inversa = inversa;
    this->usavel = usavel;
    this->idOposta = idOposta;
}
Aresta::~Aresta(){}

void Aresta::printInfo(){
    cout << "--------- Aresta ---------\n";
    cout << "Id         : " << this->id << "\n" ;
    cout << "Origem     : " << this->origem << "\n" ;
    cout << "Destino    : " << this->destino << "\n" ;
    cout << "limiteSup  : " << this->limiteSup << "\n" ;
    cout << "limiteInf  : " << this->limiteInf << "\n" ;
    cout << "fluxo      : " << this->fluxo << "\n" ;
    cout << "Visitado   : " << this->visitado << "\n" ;
    cout << "Inversa    : " << this->inversa << "\n" ;
    cout << "Usavel     : " << this->usavel << "\n" ;
    cout << "IdOposta   : " << this->idOposta << "\n\n" ;
}

/*
======================================================================================================
ROTULO
======================================================================================================
*/

Rotulo::Rotulo(){}
Rotulo::Rotulo(bool resetado, int rot, char op, double aumento):resetado(resetado), rot(rot), op(op), aumento(aumento){}
Rotulo::~Rotulo(){}

/*
======================================================================================================
VERTICE
======================================================================================================
*/

Vertice::Vertice(int id, bool visitado){
    this->id = id;
    this->visitado = visitado;
    this->rotulo = Rotulo();
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

FF::FF(){}
FF::FF(int qntd_vertices, int qntd_arestas, int source, int target):qntd_vertices(qntd_vertices), qntd_arestas(qntd_arestas), source(source), target(target){}
FF::~FF(){}

void FF::inicializaGrafo(){

    // Leitura dos dados iniciais
    int qntd_vertices, qntd_arestas;

    cin >> qntd_vertices >> qntd_arestas;

    this->qntd_arestas = qntd_arestas;
    this->qntd_vertices = qntd_vertices;
    this->source = 1;
    this->target = qntd_vertices;

    // Lendo vertices
    // Para o primeiro vertice o rotulo ja eh atualizado com os valores default como no pseudocodigo
    for (int i = 1; i <= this->qntd_vertices; i++){
        Vertice v(i, false);
        if (i == 1){
            v.rotulo.rot = -1;
            v.rotulo.op = '0';
            v.rotulo.aumento = 1000000;
            v.rotulo.resetado = false;
        }
        else{
            v.rotulo.resetado = true;
        }
        this->vertices.push_back(v);;
    }

    // Lendo arestas e criando listas de adjacencia
    int count = 1;
    int origem, destino;
    double limite;

    for (int i = 1; i <= this->qntd_arestas; i++){
        cin >> origem >> destino >> limite;
        
        Aresta a = Aresta(count, origem, destino, limite, 0, 0, false, false, true, count + 1);
        this->arestas.push_back(a);
        this->vertices[origem - 1].adjacencia.push_back(pair<int, int>(destino, count)); // popula a lista de adjacencia do vertice
        count++;

        Aresta inversa = Aresta(count, destino, origem, 0, 0, 0, false, true, false, count - 1);
        this->arestas.push_back(inversa);
        this->vertices[destino - 1].adjacencia.push_back(pair<int, int>(origem, count)); // popula a lista de adjacencia do vertice
        count++;
    }

    // ordena a lista de adjacencia dos vertices para fazer a analise em ordem crescente de indice
    for (int i = 0; i < this->qntd_vertices; i++){
        this->vertices[i].adjacencia.sort();
    }

}

// Essa funcao se baseia na funcao do trabalho anterior com algumas modificacoes para se adequar ao trabalho 2
void FF::dfs(int vertice_inicial, vector<int>* caminho, bool* achou){
    
    // a primeira diferenca eh esse if no inicio da funcao que para a recursao na primeira vez q ela alcancar o vertice final
    if (vertice_inicial == this->target){
        caminho->push_back(vertice_inicial); // insere o vertice final no vetor de caminho
        *achou = true; // seta a flag para true para inidicar que a recursao pode parar

        // reseta a flag visitado de todos os vertices para poder executar o DFS novamente sem problemas
        for (int i = 0; i < (int)this->vertices.size(); i++){
            this->vertices[i].visitado = false;
        }
        return;
    }

    this->vertices[vertice_inicial - 1].visitado = true;
    caminho->push_back(vertice_inicial);

    for (auto i : this->vertices[vertice_inicial - 1].adjacencia){
        // como o grafo esta em constante mudanca durante a execucao, caso a aresta nao possa ser utilziada olhamos a proxima
        if (!this->arestas[i.second - 1].usavel){
            continue;
        }

        // como todos os grafos utilziados nas instancias sao direcionados a verificao se o grafo eh direcionado ou nao nao eh mais necessaria
        int vertice_atual = this->arestas[i.second - 1].destino;

        if (this->vertices[vertice_atual - 1].visitado){
            if (!(this->arestas[i.second - 1].visitado)){
                this->arestas[i.second - 1].visitado = true;
            }
        }
        else{
            this->arestas[i.second - 1].visitado = true;
            this->dfs(vertice_atual, caminho, achou);

            // caso o DFS tenha alcancado o ultimo vertice a recursao eh aprada
            if (*achou){
                return;
            }
        }
    }
    
    // outra diferenca do algoritmo do trabalho 1 eh que aqui eh preciso saber o caminho encontrado ate o vertice final, apra isso liberamos o vertice para ser visitado novamente e tiramos ele do vetor de caminho
    this->vertices[vertice_inicial - 1].visitado = false;
    caminho->pop_back();
}

void FF::ff(int vertice_atual){
    bool achouCaminho = false; // variavel que indicara caso o DFS tenha achado um caminho ate o vertice final
    vector<int> caminho;       // vetor que indica o caminho percorrido pelo DFS
    vector<int> arestasUsadas; // vetor que indica as aretas utilziadas para chegar no vetor final
    int idProxVertice;         // variavel que sera usada para indcar o proximo vertice que sera utilizado na proxima iteracao

    do
    {
        achouCaminho = false; // resetando a flag
        this->dfs(vertice_atual, &caminho, &achouCaminho);

        // o ford-fulkerson sera executado caso tenha caminho ate o vertice final
        if (achouCaminho){
            // todas as operacoes do ford-fulkerson serao realizadas em todos os vertices do caminho
            for (int i = 0; i < (int)caminho.size() - 1; i++){
                Vertice* v = &this->vertices[caminho[i] - 1]; // pegando o vertice para facilitar a leitura do codigo psoteriormente
                idProxVertice = caminho[i + 1]; // o id do vertice que sera alcancado a partir do Vertice v

                int idAresta;
                // procurando na lista de adjacencia qual a aresta utilizada para se chegar em idProxVertice
                for (auto j : v->adjacencia){
                    if (j.first == idProxVertice && this->arestas[j.second - 1].usavel){
                        idAresta = j.second;
                        break;
                    }
                }
                arestasUsadas.push_back(idAresta);
                Aresta* a = &this->arestas[idAresta - 1]; // pegando a aresta utilizada nessa iteracao para facilitar a leitura

                // esse if realiza as operacoes descritas no pseudocodigo
                if (a->inversa){
                    this->vertices[idProxVertice - 1].rotulo.rot = v->id;
                    this->vertices[idProxVertice - 1].rotulo.op = '-';
                    this->vertices[idProxVertice - 1].rotulo.aumento = min(v->rotulo.aumento, (a->fluxo - a->limiteInf));
                    this->vertices[idProxVertice - 1].rotulo.resetado = false; // indica que o vertice foi rotulado
                }
                else{
                    this->vertices[idProxVertice - 1].rotulo.rot = v->id;
                    this->vertices[idProxVertice - 1].rotulo.op = '+';
                    this->vertices[idProxVertice - 1].rotulo.aumento = min(v->rotulo.aumento, (a->limiteSup - a->fluxo));
                    this->vertices[idProxVertice - 1].rotulo.resetado = false; // indica que o vertice foi rotulado
                }

                // caso o vertice final tenha sido alcancado
                if (this->vertices[this->target - 1].rotulo.resetado == false){
                    // construir o caminho
                    this->construirCaminho(this->vertices[this->target - 1].rotulo);
                    cout << endl;
                    // aumentar o fluxo nos arcos
                    // atualizar grafo
                    aumentaFluxo(this->vertices[this->target - 1].rotulo.aumento, arestasUsadas);
                    // cancelar rotulos
                    cancelaRotulos();
                    break;
                }
            }

            // resetando os vetores para a proxima iteracao
            caminho.clear();
            arestasUsadas.clear();
        }
    } while (achouCaminho);

}

void FF::construirCaminho(Rotulo r){
    // percorre o caminho realizado pelo DFS de maneira recursiva ate encontrar o primeiro vertice e printa o output
    if (r.rot != 1){
        construirCaminho(this->vertices[r.rot - 1].rotulo);
    }
    cout << "[" << r.rot << ", " << r.op << ", " << r.aumento << "] ";
}

void FF::aumentaFluxo(double aumento, vector<int> arestasUsadas){
    // a atualziacao precisa ser feita em todas as arestas utilziadas nessa iteracao do Ford-Fulkerson
    for (int i = 0; i < (int)arestasUsadas.size(); i++){
        Aresta* a = &this->arestas[arestasUsadas[i] - 1]; // pegando a aresta ara facilitar a leitura

        // as operacos da atualizacao dependem se a aresta eh inversa ou nao
        if (a->inversa){
            // verificando a integridade da solucao (debug)
            if (a->fluxo - aumento < a->limiteInf){
                cout << "ERRO 1!" << endl;
                exit(0);
            }

            // atualzando o fluxo da aresta
            a->fluxo -= aumento;

            // bloqueando a aresta caso ela alcance seu limite
            if (a->fluxo == a->limiteInf){
                a->usavel = false;
            }

            // idOposta representa a aresta que faz o caminho inverso da aresta em questao, 
            // para arestas inversas ela representa a sua respectiva aresta nao inversa
            // para arestas nao inversas ela representa a sua respectiva aresta inversa
            int idOposta = a->idOposta;

            // atualizando a aresta oposta
            this->arestas[idOposta - 1].fluxo -= aumento;
            this->arestas[idOposta - 1].usavel = true;
        }
        else{
            // verificando a integridade da solucao (debug)
            if (aumento + a->fluxo > a->limiteSup){
                cout << "ERRO 2!" << endl;
                exit(0);
            }

            // atualzando o fluxo da aresta
            a->fluxo += aumento;

            // bloqueando a aresta caso ela alcance seu limite
            if (a->fluxo == a->limiteSup){
                a->usavel = false;
            }

            // idOposta representa a aresta que faz o caminho inverso da aresta em questao, 
            // para arestas inversas ela representa a sua respectiva aresta nao inversa
            // para arestas nao inversas ela representa a sua respectiva aresta inversa
            int idOposta = a->idOposta;

            // atualizando a aresta oposta
            this->arestas[idOposta - 1].fluxo += aumento;
            this->arestas[idOposta - 1].usavel = true;
        }
    }
}

void FF::cancelaRotulos(){
    Vertice* v = &this->vertices[this->target - 1];

    // cancela todos os rotulos dos vertices do caminho encontrado pelo DFS nessa iteracao
    while(v->rotulo.rot != -1){
        v->rotulo.resetado = true;
        v = &this->vertices[v->rotulo.rot - 1];
    }
}