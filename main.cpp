#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    /*======== Recebendo dados da entrada padrão =========*/
    if (argc < 4) {
        printf("Use: ./deputados <opção_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>");
        exit(1);
    }

    printf("Análise\n");

    return 0;
}