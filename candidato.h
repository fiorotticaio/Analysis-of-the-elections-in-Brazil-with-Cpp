#ifndef CANDIDATO_H
#define CANDIDATO_H

#include "partido.h"
#include <string>
// #include <chrono> 

using namespace std;

class candidato {
    partido partioCandidato;
    int posRankingVotos;

    /* arquivo dos candidatos */
    int nrFederacaoPartidoCandidato = 0;    // -1: candidato em partido isolado    
    bool apenasVotosDeLegenda;           // Caso esteja "Válido (legenda)" no campo NM_TIPO_DESTINACAO_VOTOS
    int cdDetalheSituacaoCand = 0;          // processar apenas os candidatos com 2 ou 16 (candidatura deferida)
    int nrPartidoCandidato = 0;             // Número do partido
    
    string sgPartidoCandidato;              // Sigla do partido do candidato
    string nmUrnaCandidato;                 // Nome do candidato na urna
    int cdSitTotTurno = 0;                  // Situação do candidato (2 ou 3 - eleito)
    int nrCandidato = 0;                    // Número do candidato

    string dtNascimento;                    // Data de nascimento do candidato 
    // chrono::year_month_day dtNascimento;    //TODO: trocar pra um tipo de date (não sei se tem)

    int cdCargo = 0;                        // Código do cargo (7 - dep estadual, 6 - dep federal)
    int cdGenero;                           // Genero do candidato (2 - masculino, 4 - feminino)
    
    /* arquivo da votação */
    int nrVotavel = 0; 
    // o número do candidato no caso de voto nominal ou o número do partido se for voto na legenda
    // 95, 96, 97, 98 representam casos de votos em branco, nulos ou anulados, e devem ser ignorados
    int qtVotos = 0;


public:
    int getNrPartidoCandidato() const;
    bool getApenasVotosDeLegenda() const;
    void setApenasVotosDeLegenda(bool& apenasVotosDeLegenda);
    int getCdGenero() const;
    partido getPartidoCandidato() const;
    void setNrVotavel(int& nrVotavel);
    int getNrVotavel() const;
    int getNrCandidato() const;
    int getPosRankingVotos() const;
    void setPosRankingVotos(int& posRankingVotos);
    void setPartidoCandidato(partido& partioCandidato);
    int getNrFederacaoPartidoCandidato() const;
    string getDtNascimento() const; //TODO: trocar pra um tipo de date (não sei se tem)
    string getSgPartidoCandidato() const;
    int getCdSitTotTurno() const;
    int getQtVotos() const;
    void setQtVotos(int& qtVotos);
    string getNmUrnaCandidato() const;
    int getCdCargo() const;

    int calculaIdade(string& dtEleicao); //TODO: trocar pra um tipo de date (não sei se tem)
};

#endif // !CANDIDATO_H