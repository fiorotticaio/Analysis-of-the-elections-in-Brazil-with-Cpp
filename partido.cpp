#include "partido.h"

partido::partido(const int &numero, const string &sigla, const string &nome) {
    // this->candidatos = map<int, candidato>(); // não sei se ta certo (tem os bagui de ponteiro ainda pra ver)
    this->numero = numero;
    this->sigla = sigla;
    this->nome = nome;
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

void partido::adicionaCandidato(const candidato& candidato) {
    // this->candidatos.insert(pair<int, candidato>(candidato.getNumero(), candidato));
}

void partido::calculaQuantidadeDeVotos(const int& flag) {
    // calcula a quantidade de votos do partido
}

candidato partido::getCandidatoMaisVotado(const list<candidato>& candidatos, const int& flag) {
    // retorna o candidato mais votado do partido
}

candidato partido::getCandidatoMenosVotado(const list<candidato> &candidatos, const int &flag) {
    // retorna o candidato menos votado do partido
}

/* Debug */
void partido::imprimeCandidatos() const {
    cout << "Candidatos do partido " << this->getSigla() << " (" << this->getNome() << "):" << endl;
    for (auto& candidato : this->candidatos) {
        cout << "Candidato " << candidato.second.getNrVotavel() << " - " << candidato.second.getNmUrnaCandidato() << " - " << candidato.second.getQtVotos() << " votos" << endl;
    }
}

void partido::destroiPartido() {
    // libera todo o espaço de memória alocado para o partido
}