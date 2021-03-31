#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void carregarArquivo(vector<string>& lista);
bool tratarAVariavel(string& palavra);
string pegaLetras(string expressao);
string tiraEspacoEOrdena(string expressao);
vector<string> checarAnagramas(vector<string> lista,string expressao,string letras);


int main() {
	vector<string> lista;
	carregarArquivo(lista);

	cout << "Digite uma palavra ou frase de ate 16 letras: " << endl;
	string palavra;
	getline(cin, palavra);
	if (tratarAVariavel(palavra)){
		string letras=pegaLetras(palavra);
    vector<string> anagramas;
    anagramas=checarAnagramas(lista,palavra,letras);
    string tiraEspacoEOrdena(string expressao);
    cout<<palavra<<endl;
    for (int i=0;i<anagramas.size();i++){
      cout<<anagramas[i]<<endl;
    }
  }
	return 0;
}

void carregarArquivo(vector<string>& lista) {
	int count;
	ifstream inputFile;
	count = 0;
	inputFile.open("palavras.txt");
	string steam;
	if (!inputFile) {
		cout << "Arquivo nao encontrado!";
	}
	while (!inputFile.eof()) {
		inputFile >> steam;
		lista.push_back(steam);
	}
	inputFile.close();
}

bool tratarAVariavel(string& palavra) {
	for (int i = 0; i < palavra.length(); ++i) {
		if (!isalpha(palavra[i]) && palavra[i] != ' ') {
			cout << "letra nao possivel: " << palavra[i] << endl;
			return false;
		}
		palavra[i] = toupper(palavra[i]);
	}
	if (palavra.length() > 15) {
		palavra = palavra.erase(16);
	}
	return true;
}

string pegaLetras(string expressao){
  string result="";
  for (int i=0; i<expressao.length();i++){
    bool existe=false;
    for (int j=0; j< result.length();j++){
      if (expressao[i]==result[j]){
        existe=true;
      }
    }
    if (!existe){
      result+=expressao[i];
    }
  }
  return result;
}

string tiraEspacoEOrdena(string expressao){
  string result="";
  for (int i=0; i<expressao.length();i++){
    if (expressao[i]!=' '){
      result+=expressao[i];
    }
  }
  sort(result.begin(),result.end());
  return result;
}

vector<string> checarAnagramas(vector<string> lista,string expressao,string letras){
  vector<string> palavrasSelecionadas;
  for (int i=0;i<lista.size();i++){
		string checagem=lista[i];
    string ltrsAnagram = pegaLetras(lista[i]);
    int count=0;
    for (int j=0;j<checagem.length();j++){
      for (int k=0;k<letras.length();k++){
        if (letras[k]==checagem[j]){
          count++;
        }
      }
      if (count==checagem.length()){
        palavrasSelecionadas.push_back(checagem);
      }
    }
  }
  vector<string> palavrasAnagramas;
  string result="";
  string anagrama;
  for (int i=0;i<palavrasSelecionadas.size();i++){
    anagrama=palavrasSelecionadas[i];
		for (int j=i;j<palavrasSelecionadas.size();j++){
      if ((anagrama.length()+palavrasSelecionadas[j].length())==expressao.length()){
        result+=" "+palavrasSelecionadas[j];
        palavrasAnagramas.push_back(result);
        anagrama=palavrasSelecionadas[i];
        result=palavrasSelecionadas[i];
      } else if ((anagrama.length()+palavrasSelecionadas[j].length())<expressao.length()){
        result= anagrama + " " +palavrasSelecionadas[j];
        anagrama+=palavrasSelecionadas[j];
				j-=1;
      } else{
        anagrama=palavrasSelecionadas[i];
        result=palavrasSelecionadas[i];
      }
    }
  }
  palavrasSelecionadas.clear();
  string palavra1 = tiraEspacoEOrdena(expressao);
  for (int i=0;i<palavrasAnagramas.size();i++){
    string palavra2 = tiraEspacoEOrdena(palavrasAnagramas[i]);
    if (palavra1==palavra2){
      palavrasSelecionadas.push_back(palavrasAnagramas[i]);
    }
  }
  return palavrasSelecionadas;
}
