#ifndef IMPRESSORA_H
#define IMPRESSORA_H

#include "candidato.h"
#include "partido.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
#include <iomanip>
#include <locale>

using namespace std;

class impressora {
    int numeroDeVagas = 0;

public:
    impressora(){} // Construtor
    void setNumeroDeVagas(const int& numeroDeVagas);
    list<candidato> ordenaPartidosPorMaiorVotoCandidato(const list<partido>& partidos, const int& flag);
    list<partido*>* ordenaPartidos(map<int, partido*>* partidos, const int& flag);
    list<candidato*>* ordenaCandidatos(map<int, candidato*>* candidatos, const int& flag, const string& dtEleicao);
    void imprimeCandidato(candidato* c, const int& i);
    void imprimeCandidatos(list<candidato*>* candidatos);
    void imprimePartidos(list<partido*>* partidos);
    void imprimeRelatorio1(list<candidato*>* candidatos, const int& flag);
    void imprimeRelatorio2(list<candidato*>* candidatos, const int& flag);
    void imprimeRelatorio3(list<candidato*>* candidatos, const int& flag);
    void imprimeRelatorio4(list<candidato*>* candidatos, const int& flag);
    void imprimeRelatorio5(list<candidato*>* candidatos, const int& flag);
    void imprimeRelatorio6(list<partido*>* partidos, const int& flag);
    void imprimeRelatorio8(list<partido*>* partidos, const int& flag);
    void imprimeRelatorio9(list<candidato*>* candidatos, const int& flag, const string& dtEleicao);
    void imprimeRelatorio10(list<candidato*>* candidatos, const int& flag);
    void imprimeRelatorio11(list<partido*>* partidos, const int& flag);
};

#endif // !IMPRESSORA_H