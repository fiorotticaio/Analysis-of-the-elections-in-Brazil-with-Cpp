#ifndef LEITOR_H

#include "candidato.h"
#include "partido.h"
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <iostream>
#include <iomanip>

using namespace std;

class leitor {


public:
    // Construtor implícito
    void leArquivoCandidatos
    (
        const string& caminhoArquivo,
        const map<int, candidato>& candidatos,
        const map<int, partido>& partidos,
        const int& flag
    );
    void leArquivoVotacao
    (
        const string& caminhoArquivo,
        const map<int, candidato>& candidatos,
        const map<int, partido>& partidos,
        const int& flag
    );
    void adicionaCandidatosPartidos(const map<int, candidato>& candidatos, const map<int, partido>& partidos);  
};

#endif // !LEITOR_H