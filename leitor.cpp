#include "leitor.h"

void leitor::leArquivoCandidatos
(
    const string& caminhoArquivo,
    const map<int, candidato*>* candidatos,
    const map<int, partido*>* partidos,
    const int& flag
) {
    ifstream arq;
    arq.open(caminhoArquivo);

    if (!arq.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    string linha; // string da linha inteiro do csv
    getline(arq, linha); // descarta a primeira linha

    while (getline(arq, linha)) {
        cout << linha[0] << endl;
    }

    arq.close();
}

void leitor::leArquivoVotacao
(
    const string& caminhoArquivo,
    const map<int, candidato*>* candidatos,
    const map<int, partido*>* partidos,
    const int &flag
) {

}

void leitor::adicionaCandidatosPartidos(const map<int, candidato*>* candidatos, const map<int, partido*>* partidos) {

}

void leitor::destroiLeitor() {
    // Libera todo o espaço reservado para o leitor
}