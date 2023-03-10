#include "candidato.h"
#include "partido.h"
#include "impressora.h"
#include "leitor.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include <locale>


using namespace std;

int main(int argc, char* argv[]) {

    /*======== Recebendo dados da entrada padrão =========*/
    
    if (argc < 4) {
        cout << "Use: ./deputados <opção_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>";
        exit(1);
    }


    int flag;
    
    if (strcmp(argv[1], "--estadual") == 0) flag = 7;
    else if (strcmp(argv[1], "--federal") == 0) flag = 6;
    else flag = 0;

    if (flag != 6 && flag != 7) {
        cout << "Código de deputado não reconhecido" << endl;
        exit(1);
    }


    bool dataEhValida = true;
    string dataDaEleicao = argv[4];
    if (dataDaEleicao.length()<10) dataEhValida=false;
    else {
        int diaEleicao = stoi(dataDaEleicao.substr(0, 1));
        int mesEleicao = stoi(dataDaEleicao.substr(3, 4));
        int anoEleicao = stoi(dataDaEleicao.substr(6, 9));
        if (diaEleicao<0 || diaEleicao>31) dataEhValida=false;
        if (mesEleicao<0 || mesEleicao>12) dataEhValida=false;
        if (anoEleicao<0) dataEhValida=false;
    }

    if (!dataEhValida) {
        cout << "Data de eleição inválida" << endl;
        exit(1);
    }



    string caminhoArquivoCandidatos = argv[2];
    string caminhoArquivoVotacao = argv[3];


    /*=========== Criando variáveis importantes (ponteiro para maps) ===========*/
    map<int, candidato*>* candidatos = new map<int, candidato*>;    // <NR_CANDIDATO, CANDIDATO>
    map<int, partido*>* partidos = new map<int, partido*>;          // <NR_PARTIDO, PARTIDO>
    
    
    /*======= Leitura dos dados ===========*/
    leitor* meuLeitor = new leitor();
    meuLeitor->leArquivoCandidatos(caminhoArquivoCandidatos, candidatos, partidos, flag);
    meuLeitor->adicionaCandidatosPartidos(candidatos, partidos);
    meuLeitor->leArquivoVotacao(caminhoArquivoVotacao, candidatos, partidos, flag);


    /*======== Processando os dados =========*/
    for (const auto& [chave, part] : *partidos) {
        part->calculaQuantidadeDeVotos(flag);
    }

    impressora* minhaImpressora = new impressora();
    list<candidato*>* candidatosOrdenados = minhaImpressora->ordenaCandidatos(candidatos, flag, dataDaEleicao);
    list<partido*>* partidosOrdenados = minhaImpressora->ordenaPartidos(partidos, flag);


    /*======== Imprimindo relatórios ========*/

    try { 
        cout.imbue(locale("pt_BR.utf8"));
    } catch (const runtime_error& e) {
        cout << "Locale pt_BR.utf8 is not available: " << e.what() << endl;
        exit(1);
    }
  

    /* Relatório 1 */
    minhaImpressora->imprimeRelatorio1(candidatosOrdenados, flag);
    cout << endl;

    /* Relatório 2 */
    minhaImpressora->imprimeRelatorio2(candidatosOrdenados, flag);
    cout << endl;

    /* Relatório 3 */
    minhaImpressora->imprimeRelatorio3(candidatosOrdenados, flag);
    cout << endl;

    /* Relatório 4 */
    minhaImpressora->imprimeRelatorio4(candidatosOrdenados, flag);
    cout << endl;

    /* Relatório 5 */
    minhaImpressora->imprimeRelatorio5(candidatosOrdenados, flag);
    cout << endl;

    /* Relatório 6 */
    minhaImpressora->imprimeRelatorio6(partidosOrdenados, flag);
    cout << endl;

    /* Relatório 8 */
    list<partido*>* partidosOrdenadosMaiorCand = minhaImpressora->ordenaPartidosPorMaiorVotoCandidato(partidosOrdenados, flag);
    minhaImpressora->imprimeRelatorio8(partidosOrdenadosMaiorCand, flag, dataDaEleicao);
    cout << endl;

    /* Relatório 9 */
    minhaImpressora->imprimeRelatorio9(candidatosOrdenados, flag, dataDaEleicao);
    cout << endl;

    /* Relatório 10 */
    minhaImpressora->imprimeRelatorio10(candidatosOrdenados, flag);
    cout << endl;

    /* Relatório 11 */
    minhaImpressora->imprimeRelatorio11(partidosOrdenados, flag);
    cout << endl;


    /*======== Liberando toda a memória alocada ========*/

    /* deletando os partidos */
    map<int, partido*>::iterator it;
    for (it = partidos->begin(); it != partidos->end(); it++) {
        partido* part = it->second;
        part->destroiPartido();
    }
    delete partidos;

    /* deletando os candidatos */
    map<int, candidato*>::iterator it2;
    for (it2 = candidatos->begin(); it2 != candidatos->end(); it2++) {
        candidato* cand = it2->second;
        delete cand;
    }
    delete candidatos;

    delete meuLeitor;
    delete minhaImpressora;
    delete candidatosOrdenados;
    delete partidosOrdenados;
    delete partidosOrdenadosMaiorCand;

    /* voltando a localidade para o normal para evitar o vazamento de memória */
    cout.imbue(locale::classic());

    return 0;
}