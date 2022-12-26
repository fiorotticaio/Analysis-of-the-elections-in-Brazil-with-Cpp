#include "candidato.h"

int candidato::getNrPartidoCandidato() const {
    return this->nrPartidoCandidato;
}

bool candidato::getApenasVotosDeLegenda() const {
    return this->apenasVotosDeLegenda;
}

void candidato::setApenasVotosDeLegenda(bool& apenasVotosDeLegenda) {
    this->apenasVotosDeLegenda = apenasVotosDeLegenda;
}

int candidato::getCdGenero() const {
    return this->cdGenero;
}

partido candidato::getPartidoCandidato() const {
    return this->partioCandidato;
}

void candidato::setNrVotavel(int& nrVotavel) {
    this->nrVotavel = nrVotavel;
}

int candidato::getNrVotavel() const {
    return this->nrVotavel;
}

int candidato::getNrCandidato() const {
    return this->nrCandidato;
}

int candidato::getPosRankingVotos() const {
    return this->posRankingVotos;
}

void candidato::setPosRankingVotos(int& posRankingVotos) {
    this->posRankingVotos = posRankingVotos;
}

void candidato::setPartidoCandidato(partido& partioCandidato) {
    this->partioCandidato = partioCandidato;
}

int candidato::getNrFederacaoPartidoCandidato() const {
    return this->nrFederacaoPartidoCandidato;
}

string candidato::getDtNascimento() const {
    return this->dtNascimento;
}

string candidato::getSgPartidoCandidato() const {
    return this->sgPartidoCandidato;
}

int candidato::getCdSitTotTurno() const {
    return this->cdSitTotTurno;
}

int candidato::getQtVotos() const {
    return this->qtVotos;
}

void candidato::setQtVotos(int& qtVotos) {
    this->qtVotos = qtVotos;
}

string candidato::getNmUrnaCandidato() const {
    return this->nmUrnaCandidato;
}

int candidato::getCdCargo() const {
    return this->cdCargo;
}

int candidato::calculaIdade(string& dtEleicao) {

    // dd/mm/aaaa

    int diaEleicao = stoi(dtEleicao.substr(0, 1));
    int mesEleicao = stoi(dtEleicao.substr(3, 4));
    int anoEleicao = stoi(dtEleicao.substr(6, 9));

    //FIXME: verificar se a os intervalos estão corretos
    int diaNascimento = stoi(this->dtNascimento.substr(0, 1));
    int mesNascimento = stoi(this->dtNascimento.substr(3, 4));
    int anoNascimento = stoi(this->dtNascimento.substr(6, 9));

    int idade = anoEleicao - anoNascimento;

    if (mesEleicao < mesNascimento) {
        idade--;
    } else if (mesEleicao == mesNascimento) {
        if (diaEleicao < diaNascimento) {
            idade--;
        }
    }

    return idade;
}