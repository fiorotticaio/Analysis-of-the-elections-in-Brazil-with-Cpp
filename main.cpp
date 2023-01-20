#include "candidato.h"
#include "partido.h"
#include "impressora.h"
#include "leitor.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>


using namespace std;

int main(int argc, char* argv[]) {

    /*======== Recebendo dados da entrada padrão =========*/
    if (argc < 4) {
        cout << "Use: ./deputados <opção_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>";
        exit(1);
    }

    int flag;
    
    if (strcmp(argv[1], "--estadual") == 0) flag = 7;
    else if (strcmp(argv[1], "--federal") == 0) flag = 6;
    else flag = 0;

    string caminhoArquivoCandidatos = argv[2];
    string caminhoArquivoVotacao = argv[3];
    string dataDaEleicao = argv[4];

    if (flag != 6 && flag != 7) {
        cout << "Código de deputado não reconhecido" << endl;
        exit(1);
    }

    /*=========== Criando variáveis importantes (ponteiro para maps) ===========*/
    map<int, candidato*>* candidatos = new map<int, candidato*>; // <NR_CANDIDATO, CANDIDATO>
    map<int, partido*>* partidos = new map<int, partido*>; // <NR_PARTIDO, PARTIDO>
    
    
    /*======= Leitura dos dados ===========*/
    leitor* meuLeitor = new leitor();
    meuLeitor->leArquivoCandidatos(caminhoArquivoCandidatos, candidatos, partidos, flag);
    meuLeitor->adicionaCandidatosPartidos(candidatos, partidos);




    /*======== Processando os dados =========*/
    // for ()

    impressora* minhaImpressora = new impressora();




    /*======== Imprimindo relatórios ========*/





    /*======== Liberando toda a memória alocada ========*/
    // tudo que criou com o "new" precisa ser deletado

    /* deletando os partidos */
    map<int, partido*>::iterator it;
    for (it = partidos->begin(); it != partidos->end(); it++) {
        partido* part = it->second;
        part->destroiPartido();
    }
    delete partidos;

    /* deletando os candidatos */
    map<int, candidato*>::iterator it2;
    for (it2 = candidatos->begin(); it2 != candidatos->end(); it2++) {
        candidato* cand = it2->second;
        delete cand;
    }
    delete candidatos;

    delete meuLeitor;
    delete minhaImpressora;

    return 0;
}