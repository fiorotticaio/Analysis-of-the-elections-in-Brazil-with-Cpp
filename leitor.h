#ifndef LEITOR_H

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
};

#endif // !LEITOR_H