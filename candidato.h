#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>
// #include <chrono> 

using namespace std;

class partido;

class candidato {
    partido* partioCandidato;
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

    int cdCargo = 0;                        // Código do cargo (7 - dep estadual, 6 - dep federal)
    int cdGenero;                           // Genero do candidato (2 - masculino, 4 - feminino)
    
    /* arquivo da votação */
    int nrVotavel = 0; 
    // o número do candidato no caso de voto nominal ou o número do partido se for voto na legenda
    // 95, 96, 97, 98 representam casos de votos em branco, nulos ou anulados, e devem ser ignorados
    int qtVotos = 0;

public:
    candidato(
        const int& cdCargo, 
        const int& cdDetalheSituacaoCand,
        const int& nrCandidato,
        const string& nmUrnaCandidato,
        const int& nrPartidoCandidato,
        const string& sgPartidoCandidato,
        const int& nrFederacaoPartidoCandidato,
        const string& dtNascimento,
        const int& cdSitTotTurno,
        const int& cdGenero,
        const bool& apenasVotosDeLegenda
    );
    int getNrPartidoCandidato() const;
    bool getApenasVotosDeLegenda() const;
    void setApenasVotosDeLegenda(const bool& apenasVotosDeLegenda);
    int getCdGenero() const;
    partido getPartidoCandidato() const;
    void setNrVotavel(const int& nrVotavel);
    int getNrVotavel() const;
    int getNrCandidato() const;
    int getPosRankingVotos() const;
    void setPosRankingVotos(const int& posRankingVotos);
    void setPartidoCandidato(partido* partioCandidato);
    int getNrFederacaoPartidoCandidato() const;
    string getDtNascimento() const; 
    string getSgPartidoCandidato() const;
    int getCdSitTotTurno() const;
    int getQtVotos() const;
    void setQtVotos(const int& qtVotos);
    string getNmUrnaCandidato() const;
    int getCdCargo() const;
    int calculaIdade(const string& dtEleicao); 
    void destroiCandidato();
};

#endif // !CANDIDATO_H