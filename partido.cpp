#include "partido.h"

partido::partido(const int &numero, const string &sigla, const string &nome) {
    this->candidatos = new map<int, candidato*>(); 
    this->numero = numero;
    this->sigla = sigla;
    this->nome = nome;
}

void partido::destroiPartido() {
    delete this->candidatos;
    delete this;
}

int partido::getMaiorQtdDeVotosDeUmCandidato() const {
    return this->maiorQtdDeVotosDeUmCandidato;
}

void partido::setMaiorQtdDeVotosDeUmCandidato(const int& maiorQtdDeVotosDeUmCandidato) {
    this->maiorQtdDeVotosDeUmCandidato = maiorQtdDeVotosDeUmCandidato;
}

void partido::setQtdVotosNominais(const int& qtdVotosNominais) {
    this->qtdVotosNominais = qtdVotosNominais;
}

// list<candidato> partido::getCandidatos() const {
//     return list<candidato>(this->candidatos->begin(), this->candidatos->end());
// }

map<int, candidato*>* partido::getCandidatosMap() const {
    return this->candidatos;
}

int partido::getQtdVotosNominais() const {
    return this->qtdVotosNominais;
}

int partido::getQtdVotosLegenda() const {
    return this->qtdVotosLegenda;
}

void partido::setQtdVotosLegenda(const int& qtdVotosLegenda) {
    this->qtdVotosLegenda = qtdVotosLegenda;
}

int partido::getQtdCandidatosEleitos() const {
    return this->qtdCandidatosEleitos;
}

int partido::getNumero() const {
    return this->numero;
}

string partido::getNome() const {
    return this->nome;
}

string partido::getSigla() const {
    return this->sigla;
}

int partido::getQtdVotosTotal() const {
    return this->qtdVotosTotal;
}

void partido::adicionaCandidato(candidato* cand) {
    pair<int, candidato*> novoElemento = make_pair(cand->getNrCandidato(), cand);
    this->candidatos->insert(novoElemento);
}

void partido::calculaQuantidadeDeVotos(const int& flag) {
    // calcula a quantidade de votos do partido
}

// candidato partido::getCandidatoMaisVotado(const list<candidato>& candidatos, const int& flag) {
//     // retorna o candidato mais votado do partido
// }

// candidato partido::getCandidatoMenosVotado(const list<candidato> &candidatos, const int &flag) {
//     // retorna o candidato menos votado do partido
// }

/* Debug */
void partido::imprimeCandidatos() const {
    // cout << "Candidatos do partido " << this->getSigla() << " (" << this->getNome() << "):" << endl;
    // for (auto& candidato : this->candidatos) {
    //     cout << "Candidato " << candidato.second.getNrVotavel() << " - " << candidato.second.getNmUrnaCandidato() << " - " << candidato.second.getQtVotos() << " votos" << endl;
    // }
}