#include "leitor.h"

void leitor::leArquivoCandidatos(
  const string &caminhoArquivo,
  map<int, candidato *>* candidatos,
  map<int, partido *>* partidos,
  const int &flag)
{
  ifstream arq(caminhoArquivo);

  if (!arq.is_open()) {
    cout << "Erro ao abrir o arquivo" << endl;
    exit(1);
  }

  string linha;

  getline(arq, linha); // descarta a primeira linha
  while (getline(arq, linha)) { // linhas
    vector<string> infoCandidato;       
    stringstream ss(linha);
    string campo;
    while (getline(ss, campo, ';')) { // colunas
      campo = campo.substr(1, campo.length()-2); // removendo as aspas
      infoCandidato.push_back(campo);
    }

    /* adiciona o partido à lista de partidos (mesmo se o voto for invalido ou nulo) */
    if (partidos->count(stoi(infoCandidato[27])) <= 0) {
      partido* novoPartido = new partido(
        stoi(infoCandidato[27]), // stoi converte string para int
        infoCandidato[28],
        infoCandidato[29]
      );
      pair<int, partido*> novoElemento = make_pair(novoPartido->getNumero(), novoPartido);
      partidos->insert(novoElemento);
    } 
  }

  // imprimindo o mapa de partidos
  for(const auto& [chave, valor] : *partidos) {
    cout << chave << " : " << valor->getNome() << endl;
  }

  arq.close();
}

void leitor::leArquivoVotacao
(
  const string& caminhoArquivo,
  map<int, candidato*>* candidatos,
  map<int, partido*>* partidos,
  const int &flag
) {

}

void leitor::adicionaCandidatosPartidos(map<int, candidato*>* candidatos, map<int, partido*>* partidos) {

}

void leitor::destroiLeitor() {
  // Libera todo o espaço reservado para o leitor
}