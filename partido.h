#ifndef PARTIDO_H
#define PARTIDO_H

#include "candidato.h"
#include <string>
#include <map>
#include <list>

using namespace std;

class partido {
    string nome;
    string sigla;
    int numero = 0;
    
    map<int, candidato> candidatos;
    
    int qtdVotosTotal = 0;
    int qtdVotosLegenda = 0;
    int qtdVotosNominais = 0;
    int nrFederacaoPartido = 0;
    int qtdCandidatosEleitos = 0;
    int maiorQtdDeVotosDeUmCandidato = 0;

public:
    int getMaiorQtdDeVotosDeUmCandidato() const;
    void setMaiorQtdDeVotosDeUmCandidato(int& maiorQtdDeVotosDeUmCandidato);
    void setQtdVotosNominais(int& qtdVotosNominais);
    list<candidato> getCandidatos() const;
    map<int, candidato> getCandidatosMap() const;
    int getQtdVotosNominais() const;
    int getQtdVotosLegenda() const;
    void setQtdVotosLegenda(int& qtdVotosLegenda);
    int getQtdCandidatosEleitos() const;
    int getNumero() const;
    string getNome() const;
    string getSigla() const;
    int getQtdVotosTotal() const;
    void adicionaCandidato(candidato& candidato);

    void calculaQuantidadeDeVotos(int& flag);
    candidato getCandidatoMaisVotado(list<candidato>& candidatos, int& flag);
    candidato getCandidatoMenosVotado(list<candidato>& candidatos, int& flag);
    void imprimeCandidatos() const;
};

#endif // !PARTIDO_H