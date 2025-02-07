#ifndef PALAVRA_HPP_
#define PALAVRA_HPP_
#include <string>
#include <algorithm>
#include "../estruturas/Lista.hpp"
/** Classe Palavra.
* Essa clase servirá para armazenar as palavras que fazem a indexação por chaves secundárias 
* do problema proposto. Serão armazenadas todas as palavras-chave do conteúdo das manpages e
* também todos os comandos associados à essas palavras-chave.
*/
using namespace std;
class Palavra {
private:

	// Atributo palavra.
	std::string palavra;

	// Lista que contém todos os comandos que estão associados à essa palavra.
	Lista<string> comandosQueContem;

public:

	/** Construtor padrão da classe Palavra.
	* Recebe apenas uma palavra como argumento.
	* @param string a palavra que está sendo criada.
	*/
	Palavra(std::string _palavra) {
		palavra = _palavra;
	}

	/** Associa mais um comando a esta palavra.  
	* Este método faz sentido pois queremos armazenar todos os comandos que referenciam determinada
	* palavra. Só faz essa associação caso esse comando ainda não esteja associado com esta palavra.
	* 
	* @param string comando que vai ser associado com essa palavra.
	*/
	void adicionarComandosQueContem(std::string comando) {
		// Se comando NÃO existe na lista.
		if (!comandosQueContem.contem(comando)) {
			comandosQueContem.adiciona(comando);
		}
	}

	/** 
	* Retorna a lista duplamente encadeada de comandos que estão associados à essa palavra.
	*/
	Lista<string> retornarComandosQueContem() {
		return comandosQueContem;
	}

	/** 
	* Retorna o atributo palavra.
	*/
	std::string retornarPalavra() {
		return palavra;
	}
	
	/**
	* Sobrescrita do operador "<", que agora funciona de acordo com ordem das strings. 
	*/
	bool operator<(const Palavra& rhs) const {
		return palavra < rhs.palavra;
	}

	/**
	* Sobrescrita do operador "==", que agora funciona de acordo com a igualdade das strings.
	*/
	bool operator==(const Palavra& rhs) const {
		return palavra == rhs.palavra;
	}

};
#endif