//FIXME: ta dando algum probelma de dependência entre candidato e partido
#include "candidato.h"
#include "partido.h"
#include "impressora.h"
#include "leitor.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    /*======== Recebendo dados da entrada padrão =========*/
    if (argc < 4) {
        cout << "Use: ./deputados <opção_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>";
        exit(1);
    }

    


    return 0;
}