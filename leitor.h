#ifndef LEITOR_H
#define LEITOR_H

#include "candidato.h"
#include "partido.h"
#include <string.h>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class leitor {

public:
    leitor(){} // Construtor
    void leArquivoCandidatos
    (
        const string& caminhoArquivo,
        map<int, candidato*>* candidatos,
        map<int, partido*>* partidos,
        const int& flag
    );
    void leArquivoVotacao
    (
        const string& caminhoArquivo,
        map<int, candidato*>* candidatos,
        map<int, partido*>* partidos,
        const int& flag
    );
    void adicionaCandidatosPartidos(map<int, candidato*>* candidatos, map<int, partido*>* partidos);
    string leitor::convert_iso88591_to_utf8(string &str);
};

#endif // !LEITOR_H