# Analysis-of-the-elections-in-Brazil-with-Cpp

## BUGS

Um dos problemas encontrados durante a elaboração do código, foi a referência a outras classes dentro de uma classe, o que implicava que era necessário fazer uma série de inclusões em cadeia (possivelmente infinitas), para resolver os erros de sintaxe. Contudo, para contornar o problema, foi utilizada uma “referência provisória”, apenas para remediar a falta de referência à classe em questão, porém esta não tinha nenhum atributo ou implementação. Esse detalhe pode ser visto no cabeçalho da classe candidato, que precisa mencionar a classe partido em várias de suas funções, portanto criou-se uma referência provisória chamada partido, como mostra o código abaixo.

```cpp
// candidato.h

#ifndef CANDIDATO_H
#define CANDIDATO_H

using namespace std;

class partido; //referência provisória

class candidato {
    /* ...atributos... */

public:
    /* ...construtor e outros métodos... */
};

#endif // !CANDIDATO_H
```

Outro detalhe a se comentar, foi a metodologia de desempate adotada, que, como enunciado nas especificações do projeto, baseou-se na idade do candidato. Assim, elaborou-se uma função que calcula a idade por meio de uma string correspondente à data da eleição, ou seja, irá se calcular a idade do candidato até o momento da eleição. Tal função pode ser observada na Figura 8 abaixo.

```cpp
int candidato::calculaIdade(const string& dtEleicao) {

    int diaEleicao = stoi(dtEleicao.substr(0, 1));
    int mesEleicao = stoi(dtEleicao.substr(3, 4));
    int anoEleicao = stoi(dtEleicao.substr(6, 9));

    int diaNascimento = stoi(this->dtNascimento.substr(0, 1));
    int mesNascimento = stoi(this->dtNascimento.substr(3, 4));
    int anoNascimento = stoi(this->dtNascimento.substr(6, 9));

    int idade = anoEleicao - anoNascimento;

    if (mesEleicao < mesNascimento) {
        idade--;
    } else if (mesEleicao == mesNascimento) {
        if (diaEleicao <= diaNascimento) {
            idade--;
        }
    }

    return idade;
}
```

Dessa forma, utilizou-se a função de cálculo de idade dentro da função de ordenação por meio da ferramenta sort do mapa de candidatos, ilustrada na Figura 9 a seguir.

```cpp
candidatosOrdenados->sort([dtEleicao](candidato* a, candidato* b) {
  if (a->getQtVotos() == b->getQtVotos()) {
    /* caso tenham o mesmo numero de votos, o mais velho ganha */
    int idadeA = a->calculaIdade(dtEleicao);
    int idadeB = b->calculaIdade(dtEleicao);
    return idadeA < idadeB;
  } else {
    return a->getQtVotos() > b->getQtVotos();
  }
});
```

Tal implementação trouxe os resultados desejados, porém, anteriormente a essa lógica ilustrada, utilizou-se um sinal de “>” para o critério de desempate na idade, o que gerava o efeito contrário do desejado. Ainda, foi feito o cálculo da idade parcialmente correto inicialmente, já que na condicional aninhada referente ao caso em que o mês de nascimento fosse igual ao mês das eleições, não havia um sinal de ”<=” e apenas ”<”, o que gerava inconsistências em alguns pouquíssimos casos ao longo dos testes.

Outro detalhe a se ressaltar é a formatação dos números na saída que, segundo a especificação do projeto, deveria ter como separador de milhar o ponto “.” em alguns casos, com exceção dos números dos partidos e candidatos (códigos de urna), que deviam ser apresentados com formatação padrão.

Para obter esse resultado, foi usada a manipulação da saída do programa produzida pelo comando cout, por meio da definição do modo de codificação UTF-8 em português brasileiro, ou seja, pt_BR.utf8. Para isso, usou-se do comando  cout.imbue(locale("pt_BR.utf8")); o qual aplica o estilo de separação de milhar com o ponto final “.” e decimais com vírgula “,”. Para se obter a formatação padrão no número do candidato/partido, fez-se um reajuste para a codificação "clássica" do C que, após impresso o número em questão, voltava para a codificação UTF-8, como mostra o código na Figura 10 abaixo.

```cpp
 /* 
    impressão das seguintes informações do candidato (mais votado):
      - posição no ranking
      - sigla do partido
      - número do partido
      - nome do candidato
  */
      
  cout << i << " - " << p->getSigla() << " - " << p->getNumero() << ", "
      << candidatoMaisVotado->getNmUrnaCandidato() << " (";


  /* 
    impressão das seguintes informações do candidato (mais votado):
      - código do candidato
  */
  cout.imbue(locale::classic());
  cout << candidatoMaisVotado->getNrCandidato();
  cout.imbue(locale("pt_BR.utf8"));

  /* 
    impressão das seguintes informações do candidato (mais votado):
      - número de votos
  */
  cout << ", " << candidatoMaisVotado->getQtVotos();
  candidatoMaisVotado->getQtVotos() > 1 ? cout << " votos)" : cout << " voto)";
  cout << " / ";

  /* 
    impressão das seguintes informações do candidato (menos votado):
      - nome do candidato
  */
  cout << candidatoMenosVotado->getNmUrnaCandidato() << " (";


  /* 
    impressão das seguintes informações do candidato (menos votado):
      - número do candidato
  */
  cout.imbue(locale::classic());
  cout << candidatoMenosVotado->getNrCandidato();
  cout.imbue(locale("pt_BR.utf8"));

  /* 
    impressão das seguintes informações do candidato (menos votado):
      - número de votos
  */
  cout << ", " << candidatoMenosVotado->getQtVotos();
  candidatoMenosVotado->getQtVotos() > 1 ? cout << " votos)\n" : cout << " voto)\n";
```