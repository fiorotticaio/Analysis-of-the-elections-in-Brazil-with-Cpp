#include "leitor.h"

void leitor::leArquivoCandidatos(
  const string &caminhoArquivo,
  map<int, candidato *>* candidatos,
  map<int, partido *>* partidos,
  const int &flag)
{
  ifstream arq(caminhoArquivo);

  if (!arq.is_open()) {
    cout << "Erro ao abrir o arquivo dos candidatos" << endl;
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

  arq.close();
}

void leitor::leArquivoVotacao
(
  const string& caminhoArquivo,
  map<int, candidato*>* candidatos,
  map<int, partido*>* partidos,
  const int &flag
) {
  ifstream arq(caminhoArquivo);

  if (!arq.is_open()) {
    cout << "Erro ao abrir o arquivo de votação" << endl;
    exit(1);
  }

  string linha;

  getline(arq, linha); // descarta a primeira linha
  while (getline(arq, linha)) { // linhas
    vector<string> infoVotacao;       
    stringstream ss(linha);
    string campo;
    while (getline(ss, campo, ';')) { // colunas
      campo = campo.substr(1, campo.length()-2); // removendo as aspas
      infoVotacao.push_back(campo);
    }

    /* checando se são votos válidos */
    if (stoi(infoVotacao[19]) == 95 ||
        stoi(infoVotacao[19]) == 96 ||
        stoi(infoVotacao[19]) == 97 ||
        stoi(infoVotacao[19]) == 98 ||
        stoi(infoVotacao[17]) != flag) continue;
    
    int existeCandidato = 0;

    /* buscando votos nominais analisando o código dos candidatos */
    if (candidatos->count(stoi(infoVotacao[19])) > 0) {
      candidato* cand = candidatos->at(stoi(infoVotacao[19]));
      if (cand != nullptr && cand->getCdCargo() == flag) {
        if (cand->getApenasVotosDeLegenda()) {
          partido* part = cand->getPartidoCandidato();
          part->setQtdVotosLegenda(part->getQtdVotosLegenda() + stoi(infoVotacao[21]));
          part->getCandidatosMap()->erase(cand->getNrCandidato()); //TODO: deletar o dandidato aqui?

        } else {
          cand->setNrVotavel(stoi(infoVotacao[19]));
          cand->setQtVotos(cand->getQtVotos() + stoi(infoVotacao[21]));
          partido* part = cand->getPartidoCandidato();
          part->setQtdVotosNominais(part->getQtdVotosNominais() + stoi(infoVotacao[21]));

          existeCandidato = 1;
        }
      }
    }

    /* buscando o código dos partidos para contabilizar os votos de legenda */
    if (existeCandidato == 0) {
      if(partidos->count(stoi(infoVotacao[19])) > 0) {
        partido* part = partidos->at(stoi(infoVotacao[19]));
        if (part != nullptr) {
          part->setQtdVotosLegenda(part->getQtdVotosLegenda() + stoi(infoVotacao[21]));
        }
      }
    }
  }
  
  // imprimindo o mapa de partidos com seus candidatos dentro (debug)
  for (const auto& [chave, part] : *partidos) {
    cout << part->getNome() << " : " << part->getQtdVotosNominais() << endl;
    map<int, candidato*>* candidatosDoPartido = part->getCandidatosMap();
    for (map<int, candidato*>::iterator it = candidatosDoPartido->begin(); it != candidatosDoPartido->end(); it++) {
      cout << "  " << it->second->getNmUrnaCandidato() << " : " << it->second->getQtVotos() << endl;
    }
  }

  arq.close();
}

void leitor::adicionaCandidatosPartidos(map<int, candidato*>* candidatos, map<int, partido*>* partidos) {
  for (const auto& [chave, cand] : *candidatos) {
    partido* part = partidos->at(cand->getNrPartidoCandidato());
    part->adicionaCandidato(cand);
    cand->setPartidoCandidato(part);
  }
}