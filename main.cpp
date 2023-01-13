//FIXME: ta dando algum probelma de dependência entre candidato e partido
// #include "candidato.h"
// #include "partido.h"
// #include "impressora.h"
// #include "leitor.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>

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

    /*=========== Criando variáveis importantes (maps) ===========*/
    // map<int, candidato*>* candidatos; 
    // map<int, partido*>* partidos;
    


    
    /*======= Leitura dos dados ===========*/




    /*======== Processando os dados =========*/




    /*======== Imprimindo relatórios ========*/





    return 0;
}