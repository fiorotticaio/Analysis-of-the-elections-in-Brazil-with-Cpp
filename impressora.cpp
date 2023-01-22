#include "impressora.h"

void impressora::setNumeroDeVagas(const int &numeroDeVagas) {
    this->numeroDeVagas = numeroDeVagas;
}

list<partido*>* impressora::ordenaPartidosPorMaiorVotoCandidato(list<partido*>* partidos, const int &flag) {
    /* criando uma lista de partidos com base em outra */
    list<partido*>* partidosOrdenadosMaiorCand = new list<partido*>();
    for (auto part : *partidos) {
        partidosOrdenadosMaiorCand->push_back(part);
    }

    partidosOrdenadosMaiorCand->sort([](partido* a, partido* b) {
        return a->getMaiorQtdDeVotosDeUmCandidato() > b->getMaiorQtdDeVotosDeUmCandidato();
    });

    return partidosOrdenadosMaiorCand;
}

list<partido*>* impressora::ordenaPartidos(map<int, partido*>* partidos, const int &flag) {
    /* criando uma lista de partidos com base no mapa */
    list<partido*>* partidosOrdenados = new list<partido*>;
    for (const auto& [chave, cand] : *partidos) {
        partidosOrdenados->push_back(cand);
    }

    partidosOrdenados->sort([](partido* a, partido* b) {
        if (a->getQtdVotosTotal() == b->getQtdVotosTotal()) {
            /* caso tenham o mesmo numero de votos, o com menor número partidário ganha */
            return a->getNumero() < b->getNumero();
        } else {
            return a->getQtdVotosTotal() > b->getQtdVotosTotal();
        }
    });

    return partidosOrdenados;
}

list<candidato*>* impressora::ordenaCandidatos
(
    map<int, candidato*>* candidatos,
    const int &flag,
    const string &dtEleicao
) {    
    /* criando uma lista de candidatos com base no mapa */
    list<candidato*>* candidatosOrdenados = new list<candidato*>;
    for (const auto& [chave, cand] : *candidatos) {
        candidatosOrdenados->push_back(cand);
    }

    candidatosOrdenados->sort([dtEleicao](candidato* a, candidato* b) {
        if (a->getQtVotos() == b->getQtVotos()) {
            /* caso tenham o mesmo numero de votos, o mais velho ganha */
            int idadeA = a->calculaIdade(dtEleicao);
            int idadeB = b->calculaIdade(dtEleicao);
            return idadeA > idadeB;
        } else {
            return a->getQtVotos() > b->getQtVotos();
        }
    });

    /* Inserindo rankings na lista de candidatos */
    int i = 1;
    for (auto cand : *candidatosOrdenados) {
        if (cand->getCdCargo() != flag) continue;
        cand->setPosRankingVotos(i);
        i++;
    }

    return candidatosOrdenados;
}

void impressora::imprimeCandidato(candidato* c, const int &i) {
    // O argumento "i" faz referencia a qual indice será colocado antes do nome do candidato.
    //   -> Para i=-1 será colocado a posição do candidato no ranking de votos
    //   -> Para qualquer outro valor será usado o i como indice
    string ehFederacao = "";
    if (c->getNrFederacaoPartidoCandidato() != -1) ehFederacao = "*";

    i == -1? cout << c->getPosRankingVotos() << " - " : cout << i << " - ";

    cout << ehFederacao << c->getNmUrnaCandidato() << " (" << c->getSgPartidoCandidato() << ", "
        << c->getQtVotos() << " votos)" << endl;
}

/* Debug */
void impressora::imprimeCandidatos(list<candidato*>* candidatos) {
    int i = 1;
    for (auto cand : *candidatos) {
        this->imprimeCandidato(cand, i);
        i++;
    }
}

/* Debug */
void impressora::imprimePartidos(list<partido*>* partidos) {
    for (auto partido : *partidos) {
        cout << partido->getNumero() << " - " << partido->getSigla() << " - "
            << partido->getQtdVotosTotal() << endl;
    }
}

void impressora::imprimeRelatorio1(list<candidato*>* candidatos, const int &flag) {
    int vagas = 0;
    for (auto cand : *candidatos) {
        if ((cand->getCdSitTotTurno() == 2 || cand->getCdSitTotTurno() == 3) && cand->getCdCargo() == flag) {
            vagas++;
        }
    }
    this->setNumeroDeVagas(vagas);
    cout << "Número de vagas: " << vagas << endl;
}

void impressora::imprimeRelatorio2(list<candidato*>* candidatos, const int &flag) {
    cout << "Deputados ";
    if (flag == 7) cout << "estaduais ";
    else cout << "federais ";
    cout << "eleitos:" << endl;

    int i = 1;

    for (auto c : *candidatos) {
        if (
            c->getCdCargo() != flag || i > this->numeroDeVagas ||
            (c->getCdSitTotTurno() != 2 && c->getCdSitTotTurno() != 3)
        ) continue;
        this->imprimeCandidato(c, i);
        i++;
    }
}

void impressora::imprimeRelatorio3(list<candidato*>* candidatos, const int &flag) {
    cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
    
    int i = 1;

    for (auto c : *candidatos) {
        if (c->getCdCargo() != flag || i > this->numeroDeVagas) continue;
        this->imprimeCandidato(c, -1);
        i++;
    }
}

void impressora::imprimeRelatorio4(list<candidato*>* candidatos, const int &flag) {
    cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:";
    cout << "\n(com sua posição no ranking de mais votados)\n";

    for (auto c : *candidatos) {
        if (c->getCdCargo() != flag || c->getCdSitTotTurno() == 2 || c->getCdSitTotTurno() == 3) continue;
        if (c->getPosRankingVotos() > this->numeroDeVagas) break;
        this->imprimeCandidato(c, -1);
    }
}

void impressora::imprimeRelatorio5(list<candidato*>* candidatos, const int &flag) {
    cout << "Eleitos, que se beneficiaram do sistema proporcional:\n";
    cout << "(com sua posição no ranking de mais votados)\n";

    for (auto c : *candidatos) {
        if (
            c->getCdCargo() == flag &&
            (c->getCdSitTotTurno() == 2 || c->getCdSitTotTurno() == 3) &&
            c->getPosRankingVotos() > this->numeroDeVagas
        ) {
            this->imprimeCandidato(c, -1);
        } else continue;        
    }      
}

void impressora::imprimeRelatorio6(list<partido*>* partidos, const int &flag) {
    cout << "Votação dos partidos e número de candidatos eleitos:\n";

    int i = 1;

    for (auto p : *partidos) {
        cout << i << " - " << p->getSigla() << " - " << p->getNumero() << ", " << p->getQtdVotosTotal();
        p->getQtdVotosTotal() > 1 ? cout << " votos " : cout << " voto ";
        cout << "(" << p->getQtdVotosNominais();
        p->getQtdVotosNominais() > 1 ? cout << " nominais " : cout << " nominal ";
        cout << "e " << p->getQtdVotosLegenda() << " de legenda), " << p->getQtdCandidatosEleitos();
        p->getQtdCandidatosEleitos() > 1 ? cout << " candidatos eleitos\n" : cout << " candidato eleito\n";

        i++;
    }
}

void impressora::imprimeRelatorio8(list<partido*>* partidos, const int &flag, const string& dtEleicao) {
    cout << "Primeiro e último colocados de cada partido:\n";

    int i = 1;

    for (auto p : *partidos) {

        /* Partidos que não possuírem candidatos com um número positivo de votos válidos devem ser ignorados */
        if (p->getQtdVotosNominais() == 0) continue;

        list<candidato*>* candidatosOrdenados = this->ordenaCandidatos(p->getCandidatosMap(), flag, dtEleicao);
        candidato* candidatoMaisVotado = p->getCandidatoMaisVotado(candidatosOrdenados, flag);
        candidato* candidatoMenosVotado = p->getCandidatoMenosVotado(candidatosOrdenados, flag);

        cout << i << " - " << p->getSigla() << " - " << p->getNumero() << ", " << candidatoMaisVotado->getNmUrnaCandidato()
            << " (" << candidatoMaisVotado->getNrCandidato() << ", " << candidatoMaisVotado->getQtVotos();
        candidatoMaisVotado->getQtVotos() > 1 ? cout << " votos)" : cout << " voto)";

        cout << " / ";

        cout << i << " - " << p->getSigla() << " - " << p->getNumero() << ", " << candidatoMenosVotado->getNmUrnaCandidato()
            << " (" << candidatoMenosVotado->getNrCandidato() << ", " << candidatoMenosVotado->getQtVotos();
        candidatoMenosVotado->getQtVotos() > 1 ? cout << " votos)\n" : cout << " voto)\n";
        
        i++;
        delete candidatosOrdenados;
    }

}

void impressora::imprimeRelatorio9(list<candidato*>* candidatos, const int &flag, const string &dtEleicao) {
    cout << "Eleitos, por faixa etária (na data da eleição):\n";

    int qtdEleitosMenor30 = 0, qtdEleitosMaior30Menor40 = 0, qtdEleitosMaior40Menor50 = 0;
    int qtdEleitosMaior50Menor60 = 0, qtdEleitosMaior60 = 0, qtdEleitosTotal = 0; 

    for (auto c : *candidatos) {
        if (
            c->getCdCargo() == flag &&
            (c->getCdSitTotTurno() == 2 || c->getCdSitTotTurno() == 3)
        ) {
            if (c->calculaIdade(dtEleicao) < 30) qtdEleitosMenor30++;
            else if (c->calculaIdade(dtEleicao) < 40) qtdEleitosMaior30Menor40++;
            else if (c->calculaIdade(dtEleicao) < 50) qtdEleitosMaior40Menor50++;
            else if (c->calculaIdade(dtEleicao) < 60) qtdEleitosMaior50Menor60++;
            else qtdEleitosMaior60++;
        }
    }

    qtdEleitosTotal = qtdEleitosMenor30 + qtdEleitosMaior30Menor40 + qtdEleitosMaior40Menor50 + qtdEleitosMaior50Menor60 + qtdEleitosMaior60;

    double percentMenor30 = (qtdEleitosMenor30 * 100) / (double) qtdEleitosTotal;
    double percentMenor40 = (qtdEleitosMaior30Menor40 * 100) / (double) qtdEleitosTotal;
    double percentMenor50 = (qtdEleitosMaior40Menor50 * 100) / (double) qtdEleitosTotal;
    double percentMenor60 = (qtdEleitosMaior50Menor60 * 100) / (double) qtdEleitosTotal;
    double percentMaior60 = (qtdEleitosMaior60 * 100) / (double) qtdEleitosTotal;

    cout << "      Idade < 30: " << qtdEleitosMenor30 << " (" << fixed << setprecision(2) << percentMenor30 << "%)\n";
    cout << "30 <= Idade < 40: " << qtdEleitosMaior30Menor40 << " (" << fixed << setprecision(2) << percentMenor40 << "%)\n";
    cout << "40 <= Idade < 50: " << qtdEleitosMaior40Menor50 << " (" << fixed << setprecision(2) << percentMenor50 << "%)\n";
    cout << "50 <= Idade < 60: " << qtdEleitosMaior50Menor60 << " (" << fixed << setprecision(2) << percentMenor60 << "%)\n";
    cout << "60 <= Idade     : " << qtdEleitosMaior60 << " (" << fixed << setprecision(2) << percentMaior60 << "%)\n";
}

void impressora::imprimeRelatorio10(list<candidato*>* candidatos, const int &flag) {
    cout << "Eleitos, por gênero:\n";

    int qtdEleitosFeminino = 0, qtdEleitosMasculino = 0, qtdEleitosTotal = 0;

    for (auto c : *candidatos) {
        if (
            c->getCdCargo() == flag &&
            (c->getCdSitTotTurno() == 2 || c->getCdSitTotTurno() == 3)
        ) {
            if (c->getCdGenero() == 4) qtdEleitosFeminino++;
            else qtdEleitosMasculino++;
        }
    }

    qtdEleitosTotal = qtdEleitosFeminino + qtdEleitosMasculino;

    double percentFeminino = (qtdEleitosFeminino * 100) / (double) qtdEleitosTotal;
    double percentMasculino = (qtdEleitosMasculino * 100) / (double) qtdEleitosTotal;

    cout << "Feminino:  " << qtdEleitosFeminino << " (" << fixed << setprecision(2) << percentFeminino << "%)\n";
    cout << "Masculino: " << qtdEleitosMasculino << " (" << fixed << setprecision(2) << percentMasculino << "%)\n";
}

void impressora::imprimeRelatorio11(list<partido*>* partidos, const int &flag) {
    
    int qtdVotosNominaisDeTodosOsPartidos = 0, qtdDeVotosDeLegendaDeTodoOsPartidos = 0;
    int qtdVotosTotaisDeTodosOsPartidos = 0;

    for (auto p : *partidos) {
        qtdVotosNominaisDeTodosOsPartidos += p->getQtdVotosNominais();
        qtdDeVotosDeLegendaDeTodoOsPartidos += p->getQtdVotosLegenda();
        qtdVotosTotaisDeTodosOsPartidos += p->getQtdVotosTotal();
    }

    double percentVotosNominais = (qtdVotosNominaisDeTodosOsPartidos * 100) / (double) qtdVotosTotaisDeTodosOsPartidos;
    double percentVotosLegenda = (qtdDeVotosDeLegendaDeTodoOsPartidos * 100) / (double) qtdVotosTotaisDeTodosOsPartidos;

    cout << "Total de votos válidos:    " << qtdVotosTotaisDeTodosOsPartidos << endl;
    cout << "Total de votos nominais:   " << qtdVotosNominaisDeTodosOsPartidos << " (" 
        << fixed << setprecision(2) << percentVotosNominais << "%)\n";
    cout << "Total de votos de legenda: " << qtdDeVotosDeLegendaDeTodoOsPartidos << " (" 
         << fixed << setprecision(2) << percentVotosLegenda << "%)\n";
}