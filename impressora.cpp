#include "impressora.h"

void impressora::setNumeroDeVagas(const int &numeroDeVagas) {
    this->numeroDeVagas = numeroDeVagas;
}

list<candidato> impressora::ordenaPartidosPorMaiorVotoCandidato(const list<partido> &partidos, const int &flag) {
    // ordena partidos por maior votos de candidato
}

list<partido> impressora::ordenaPartidos(const map<int, partido> &partidos, const int &flag) {
    // ordena partidos por maior votos 
}

list<candidato> impressora::ordenaCandidatos(const map<int, candidato> &candidatos, const int &flag) {
    // ordena candidatos por maior votos 
}

void impressora::imprimeCandidato(const candidato &c, const int &i) {
    // O argumento "i" faz referencia a qual indice será colocado antes do nome do candidato.
    //   -> Para i=-1 será colocado a posição do candidato no ranking de votos
    //   -> Para qualquer outro valor será usado o i como indice
    string ehFederacao = "";
    if (c.getNrFederacaoPartidoCandidato() != -1) ehFederacao = "*";

    cout.imbue(locale("pt_BR.UTF-8"));

    i == -1? cout << c.getPosRankingVotos() << " - " : cout << i << " - ";

    cout << ehFederacao << c.getNmUrnaCandidato() << " (" << c.getSgPartidoCandidato() << ", "
        << c.getQtVotos() << " votos)" << endl;
}

/* Debug */
void impressora::imprimeCandidatos(const list<candidato> &candidatos) {
    int i = 1;
    for (auto cand : candidatos) {
        imprimeCandidato(cand, i);
        i++;
    }
}

/* Debug */
void impressora::imprimePartidos(const list<partido> &partidos) {
    for (auto partido : partidos) {
        cout << partido.getNumero() << " - " << partido.getSigla() << " - "
            << partido.getQtdVotosTotal() << endl;
    }
}

void impressora::imprimeRelatorio1(const list<candidato> &candidatos, const int &flag) {
    int vagas = 0;
    for (auto cand : candidatos) {
        // FIXME: -> ao invés de .?
        if ((cand.getCdSitTotTurno() == 2 || cand.getCdSitTotTurno() == 3) && cand.getCdCargo() == flag) {
            vagas++;
        }
    }
    this->setNumeroDeVagas(vagas);
    cout << "Número de vagas: " << vagas << endl;
}

void impressora::imprimeRelatorio2(const list<candidato> &candidatos, const int &flag) {
    cout << "Deputados ";
    if (flag == 7) cout << "estaduais ";
    else cout << "federais ";
    cout << "eleitos:" << endl;

    int i = 1;

    for (auto c : candidatos) {
        if (c.getCdCargo() != flag || i < this->numeroDeVagas || (c.getCdSitTotTurno() != 2 && c.getCdSitTotTurno() != 3)) {
            this->imprimeCandidato(c, i);
            i++;
        }
    }
}

void impressora::imprimeRelatorio3(const list<candidato> &candidatos, const int &flag) {
    cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):";
    
    int i = 1;

    for (auto c : candidatos) {
        if (c.getCdCargo() != flag || i > this->numeroDeVagas) continue;
        this->imprimeCandidato(c, -1);
        i++;
    }
}

void impressora::imprimeRelatorio4(const list<candidato> &candidatos, const int &flag) {
    cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:";
    cout << "\n(com sua posição no ranking de mais votados)\n";

    for (candidato c : candidatos) {
        if (c.getCdCargo() != flag || c.getCdSitTotTurno() == 2 || c.getCdSitTotTurno() == 3) continue;
        if (c.getPosRankingVotos() > this->numeroDeVagas) break;
        this->imprimeCandidato(c, -1);
    }
}

void impressora::imprimeRelatorio5(const list<candidato> &candidatos, const int &flag) {
    cout << "Eleitos, que se beneficiaram do sistema proporcional:\n";
    cout << "(com sua posição no ranking de mais votados)\n";

    for (candidato c : candidatos) {
            
        if (
            c.getCdCargo() == flag &&
            (c.getCdSitTotTurno() == 2 || c.getCdSitTotTurno() == 3) &&
            c.getPosRankingVotos() > this->numeroDeVagas
        ) this->imprimeCandidato(c, -1);
        
        else continue;
    }      
}

void impressora::imprimeRelatorio6(const list<partido> &partidos, const int &flag) {
    cout << "Votação dos partidos e número de candidatos eleitos:\n";

    int i = 1;

    cout.imbue(locale("pt_BR.UTF-8"));

    for (auto p : partidos) {
        cout << i << " - " << p.getSigla() << " - " << p.getNumero() << ", " << p.getQtdVotosTotal();
        p.getQtdVotosTotal() > 1 ? cout << " votos " : cout << " voto ";
        cout << "(" << p.getQtdVotosNominais();
        p.getQtdVotosNominais() > 1 ? cout << " nominais " : cout << " nominal ";
        cout << "e" << p.getQtdVotosLegenda() << " de legenda), " << p.getQtdCandidatosEleitos();
        p.getQtdCandidatosEleitos() > 1 ? cout << " candidatos eleitos\n" : cout << " candidato eleito\n";

        i++;
    }
}

void impressora::imprimeRelatorio8(const list<partido> &partidos, const int &flag) {
    cout << "Primeiro e último colocados de cada partido:\n";

    int i = 1;

    cout.imbue(locale("pt_BR.UTF-8"));

    for (auto p : partidos) {

        if (p.getQtdVotosNominais() == 0) continue;

        // FIXME: o tipo de alocação aqui (e em outros lugares) vai mudar
        list<candidato> candidatosOrdenados = this->ordenaCandidatos(p.getCandidatosMap(), flag);
        candidato candidatoMaisVotado = p.getCandidatoMaisVotado(candidatosOrdenados, flag);
        candidato candidatoMenosVotado = p.getCandidatoMenosVotado(candidatosOrdenados, flag);

        cout << i << " - " << p.getSigla() << " - " << p.getNumero() << ", " << candidatoMaisVotado.getNmUrnaCandidato()
            << " (" << candidatoMaisVotado.getNrCandidato() << ", " << candidatoMaisVotado.getQtVotos();
        candidatoMaisVotado.getQtVotos() > 1 ? cout << " votos)" : cout << " voto)";

        cout << " / ";

        cout << i << " - " << p.getSigla() << " - " << p.getNumero() << ", " << candidatoMenosVotado.getNmUrnaCandidato()
            << " (" << candidatoMenosVotado.getNrCandidato() << ", " << candidatoMenosVotado.getQtVotos();
        candidatoMenosVotado.getQtVotos() > 1 ? cout << " votos)\n" : cout << " voto)\n";
    }
}

void impressora::imprimeRelatorio9(const list<candidato> &candidatos, const int &flag, const string &dtEleicao) {
    cout << "Eleitos, por faixa etária (na data da eleição):\n";

    int qtdEleitosMenor30 = 0, qtdEleitosMaior30Menor40 = 0, qtdEleitosMaior40Menor50 = 0;
    int qtdEleitosMaior50Menor60 = 0, qtdEleitosMaior60 = 0, qtdEleitosTotal = 0; 

    for (candidato c : candidatos) {
        if (
            c.getCdCargo() == flag &&
            (c.getCdSitTotTurno() == 2 || c.getCdSitTotTurno() == 3)
        ) {
            if (c.calculaIdade(dtEleicao) < 30) qtdEleitosMenor30++;
            else if (c.calculaIdade(dtEleicao) < 40) qtdEleitosMaior30Menor40++;
            else if (c.calculaIdade(dtEleicao) < 50) qtdEleitosMaior40Menor50++;
            else if (c.calculaIdade(dtEleicao) < 60) qtdEleitosMaior50Menor60++;
            else qtdEleitosMaior60++;
        }
    }

    qtdEleitosTotal = qtdEleitosMenor30 + qtdEleitosMaior30Menor40 + qtdEleitosMaior40Menor50 + qtdEleitosMaior50Menor60 + qtdEleitosMaior60;

    cout << setprecision(2) << fixed;

    cout << "Idade < 30: " << qtdEleitosMenor30 << " (" << (qtdEleitosMenor30 * 100) / qtdEleitosTotal << "%)\n";
    cout << "30 <= Idade < 40: " << qtdEleitosMaior30Menor40 << " (" << (qtdEleitosMaior30Menor40 * 100) / qtdEleitosTotal << "%)\n";
    cout << "40 <= Idade < 50: " << qtdEleitosMaior40Menor50 << " (" << (qtdEleitosMaior40Menor50 * 100) / qtdEleitosTotal << "%)\n";
    cout << "50 <= Idade < 60: " << qtdEleitosMaior50Menor60 << " (" << (qtdEleitosMaior50Menor60 * 100) / qtdEleitosTotal << "%)\n";
    cout << "60 <= Idade: " << qtdEleitosMaior60 << " (" << (qtdEleitosMaior60 * 100) / qtdEleitosTotal << "%)\n";
}

void impressora::imprimeRelatorio10(const list<candidato> &candidatos, const int &flag) {
    cout << "Eleitos, por gênero:\n";

    int qtdEleitosFeminino = 0, qtdEleitosMasculino = 0, qtdEleitosTotal = 0;

    for (candidato c : candidatos) {
        if (
            c.getCdCargo() == flag &&
            (c.getCdSitTotTurno() == 2 || c.getCdSitTotTurno() == 3)
        ) {
            if (c.getCdGenero() == 4) qtdEleitosFeminino++;
            else qtdEleitosMasculino++;
        }
    }

    qtdEleitosTotal = qtdEleitosFeminino + qtdEleitosMasculino;

    cout << setprecision(2) << fixed;

    cout << "Feminino: " << qtdEleitosFeminino << " (" << (qtdEleitosFeminino * 100) / qtdEleitosTotal << "%)\n";
    cout << "Masculino: " << qtdEleitosMasculino << " (" << (qtdEleitosMasculino * 100) / qtdEleitosTotal << "%)\n";
}

void impressora::imprimeRelatorio11(const list<partido> &partidos, const int &flag) {
    
    int qtdVotosNominaisDeTodosOsPartidos = 0, qtdDeVotosDeLegendaDeTodoOsPartidos = 0;
    int qtdVotosTotaisDeTodosOsPartidos = 0;

    for (partido p : partidos) {
        qtdVotosNominaisDeTodosOsPartidos += p.getQtdVotosNominais();
        qtdDeVotosDeLegendaDeTodoOsPartidos += p.getQtdVotosLegenda();
        qtdVotosTotaisDeTodosOsPartidos += p.getQtdVotosTotal();
    }

    cout.imbue(locale("pt_BR.UTF-8"));
    cout << setprecision(2) << fixed;

    cout << "Total de votos válidos: " << qtdVotosTotaisDeTodosOsPartidos << endl;
    cout << "Total de votos nominais: " << qtdVotosNominaisDeTodosOsPartidos << "(" << (qtdVotosNominaisDeTodosOsPartidos * 100) / qtdVotosTotaisDeTodosOsPartidos << "%)\n";
    cout << "Total de votos de legenda: " << qtdDeVotosDeLegendaDeTodoOsPartidos << "(" << (qtdDeVotosDeLegendaDeTodoOsPartidos * 100) / qtdVotosTotaisDeTodosOsPartidos << "%)\n";
}

void impressora::destroiImpressora() {
    // libera todo o espaço de memóira alocado para a impressora
}