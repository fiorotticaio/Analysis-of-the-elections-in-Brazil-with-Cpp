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
    int maiorQtdDeVotosDeUmCandidato = -1;

    for (map<int, candidato*>::iterator it = this->candidatos->begin(); it != this->candidatos->end(); it++) {
        candidato* cand = it->second;
        if ((cand->getCdSitTotTurno() == 2 ||
            cand->getCdSitTotTurno() == 3) &&
            cand->getCdCargo() == flag)
        {
            this->qtdCandidatosEleitos++;
        }

        /* já preparando pra ordenar pro relatório 8 */
        if (cand->getCdCargo() == flag) {
            if (cand->getQtVotos() > maiorQtdDeVotosDeUmCandidato) {
                maiorQtdDeVotosDeUmCandidato = cand->getQtVotos();
            }
        }
    }

    this->setMaiorQtdDeVotosDeUmCandidato(maiorQtdDeVotosDeUmCandidato);
    this->qtdVotosTotal = this->qtdVotosLegenda + this->qtdVotosNominais;
}

candidato* partido::getCandidatoMaisVotado(list<candidato*>* candidatos, const int& flag) {
    candidato* maisVotado = NULL;
    for (auto cand : *candidatos) {
        if (cand->getCdCargo() != flag) continue;

        if (maisVotado == NULL) {
            maisVotado = cand;
        } else if (cand->getQtVotos() > maisVotado->getQtVotos()) {
            maisVotado = cand;
        }
    }
    return maisVotado;
}

candidato* partido::getCandidatoMenosVotado(list<candidato*>* candidatos, const int &flag) {
    candidato* menosVotado = NULL;
    for (auto cand : *candidatos) {
        if (cand->getCdCargo() != flag) continue;

        if (menosVotado == NULL) {
            menosVotado = cand;
        } else if (cand->getQtVotos() < menosVotado->getQtVotos()) {
            menosVotado = cand;
        }
    }
    return menosVotado;
}

/* Debug */
void partido::imprimeCandidatos() const {
    // cout << "Candidatos do partido " << this->getSigla() << " (" << this->getNome() << "):" << endl;
    // for (auto& candidato : this->candidatos) {
    //     cout << "Candidato " << candidato.second.getNrVotavel() << " - " << candidato.second.getNmUrnaCandidato() << " - " << candidato.second.getQtVotos() << " votos" << endl;
    // }
}