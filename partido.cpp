#include "partido.h"
#include <iostream>

int partido::getMaiorQtdDeVotosDeUmCandidato() const {
    return this->maiorQtdDeVotosDeUmCandidato;
}

void partido::setMaiorQtdDeVotosDeUmCandidato(int& maiorQtdDeVotosDeUmCandidato) {
    this->maiorQtdDeVotosDeUmCandidato = maiorQtdDeVotosDeUmCandidato;
}

void partido::setQtdVotosNominais(int& qtdVotosNominais) {
    this->qtdVotosNominais = qtdVotosNominais;
}

list<candidato> partido::getCandidatos() const {
    //FIXME: não sei se funciona
    return list<candidato>(this->candidatos.begin(), this->candidatos.end());
}

map<int, candidato> partido::getCandidatosMap() const {
    return this->candidatos;
}

int partido::getQtdVotosNominais() const {
    return this->qtdVotosNominais;
}

int partido::getQtdVotosLegenda() const {
    return this->qtdVotosLegenda;
}

void partido::setQtdVotosLegenda(int& qtdVotosLegenda) {
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

void partido::adicionaCandidato(candidato& candidato) {
    //TODO: fazer esse método direito (algo parecido com essa linha de baixo)
    // this->candidatos.insert(pair<int, candidato>(candidato.getNumero(), candidato));
}

void partido::calculaQuantidadeDeVotos(int& flag) {
    //TODO: fazer esse método
}

candidato partido::getCandidatoMaisVotado(list<candidato>& candidatos, int& flag) {
    //TODO: fazer esse método
}

candidato partido::getCandidatoMenosVotado(list<candidato> &candidatos, int &flag) {
    //TODO: fazer esse método
}

/* Debug */
void partido::imprimeCandidatos() const {
    cout << "Candidatos do partido " << this->getSigla() << " (" << this->getNome() << "):" << endl;
    for (auto& candidato : this->candidatos) {
        cout << "Candidato " << candidato.second.getNrVotavel() << " - " << candidato.second.getNmUrnaCandidato() << " - " << candidato.second.getQtVotos() << " votos" << endl;
    }
}