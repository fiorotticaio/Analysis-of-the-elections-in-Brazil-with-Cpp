#ifndef IMPRESSORA_H
#define IMPRESSORA_H

#include "candidato.h"
#include "partido.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
#include <iomanip>

using namespace std;

class impressora {
    int numeroDeVagas = 0;

public:
    impressora(){} // Construtor
    void setNumeroDeVagas(const int& numeroDeVagas);
    list<candidato> ordenaPartidosPorMaiorVotoCandidato(const list<partido>& partidos, const int& flag);
    list<partido> ordenaPartidos(const map<int, partido>& partidos, const int& flag);
    // list<candidato> ordenaCandidatos(const map<int, candidato>& candidatos, const int& flag);
    void imprimeCandidato(const candidato& c, const int& i);
    void imprimeCandidatos(const list<candidato>& candidatos);
    void imprimePartidos(const list<partido>& partidos);
    void imprimeRelatorio1(const list<candidato>& candidatos, const int& flag);
    void imprimeRelatorio2(const list<candidato>& candidatos, const int& flag);
    void imprimeRelatorio3(const list<candidato>& candidatos, const int& flag);
    void imprimeRelatorio4(const list<candidato>& candidatos, const int& flag);
    void imprimeRelatorio5(const list<candidato>& candidatos, const int& flag);
    void imprimeRelatorio6(const list<partido>& partidos, const int& flag);
    // void imprimeRelatorio8(const list<partido>& partidos, const int& flag);
    void imprimeRelatorio9(const list<candidato>& candidatos, const int& flag, const string& dtEleicao);
    void imprimeRelatorio10(const list<candidato>& candidatos, const int& flag);
    void imprimeRelatorio11(const list<partido>& partidos, const int& flag);
    void destroiImpressora();
};

#endif // !IMPRESSORA_H