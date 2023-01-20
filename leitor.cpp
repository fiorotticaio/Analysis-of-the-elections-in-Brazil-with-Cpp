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

    /* adiciona o partido ao mapa de partidos (mesmo se o voto for invalido ou nulo) */
    if (partidos->count(stoi(infoCandidato[27])) <= 0) {
      partido* novoPartido = new partido(
        stoi(infoCandidato[27]), // stoi converte string para int
        infoCandidato[28],
        infoCandidato[29]
      );
      pair<int, partido*> novoElemento = make_pair(novoPartido->getNumero(), novoPartido);
      partidos->insert(novoElemento);
    } 

    /* checagem da candidatura definida ou se é voto de legenda direto */
    bool ehLegenda = (strcmp(infoCandidato[67].c_str(), "Válido (legenda)") == 0) ? true : false; 
    bool ehValido = (stoi(infoCandidato[68]) == 2 || stoi(infoCandidato[68]) == 16);
    bool ehDoEscopo = stoi(infoCandidato[13]) == flag;

    if ((!ehLegenda && !ehValido) || (!ehDoEscopo)) continue;

    /* removendo espaços em branco do nome do candidato e da sigla do seu partido */
    infoCandidato[18].erase(infoCandidato[18].find_last_not_of(" ") + 1);
    infoCandidato[18].erase(0, infoCandidato[18].find_first_not_of(" "));
    infoCandidato[28].erase(infoCandidato[28].find_last_not_of(" ") + 1);
    infoCandidato[28].erase(0, infoCandidato[28].find_first_not_of(" "));

    /* criando um novo candidato */
    candidato* novoCandidato = new candidato(
      stoi(infoCandidato[13]),
      stoi(infoCandidato[68]),
      stoi(infoCandidato[16]),
      infoCandidato[18],
      stoi(infoCandidato[27]),
      infoCandidato[28],
      stoi(infoCandidato[30]),
      infoCandidato[42],
      stoi(infoCandidato[56]),
      stoi(infoCandidato[45]),
      ehLegenda
    );
    /* adiciona o candidato ao mapa */
    pair<int, candidato*> novoElemento = make_pair(novoCandidato->getNrCandidato(), novoCandidato);
    candidatos->insert(novoElemento);
  }

  // // imprimindo o mapa de partidos
  // for(const auto& [chave, valor] : *partidos) {
  //   cout << chave << " : " << valor->getNome() << endl;
  // }
  // cout << "\n\n";
  // // imprimindo o mapa de candidatos
  // for(const auto& [chave, valor] : *candidatos) {
  //   cout << chave << " : " << valor->getNmUrnaCandidato() << endl;
  // }

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
  for (const auto& [chave, cand] : *candidatos) {
    partido* part = partidos->at(cand->getNrPartidoCandidato());
    part->adicionaCandidato(cand);
    cand->setPartidoCandidato(part);
  }

  // // imprimindo o mapa de partidos com seus candidatos dentro
  // for (const auto& [chave, part] : *partidos) {
  //   cout << part->getNome() << endl;
  //   map<int, candidato*>* candidatosDoPartido = part->getCandidatosMap();
  //   for (map<int, candidato*>::iterator it = candidatosDoPartido->begin(); it != candidatosDoPartido->end(); it++) {
  //     cout << "  " << it->second->getNmUrnaCandidato() << endl;
  //   }
  // }
}