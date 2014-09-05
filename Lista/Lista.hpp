/**
* File: Lista.hpp
* @author: Emmanuel Podestá, Fernando Paladini.
* @since: Created on 25 de Agosto de 2014, 20:52.
* Copyright 2014 Emmanuel Podestá, Fernando Paladini.
* < Na verdade é Copyleft, MIT License \o/ >
*/
/** Classe Lista.
* A classe Lista implementa uma lista de vetores simples, não-encadeada, que tem métodos
* como fornecer posição do ponteiro, adicionar elemento no início, adicionar elemento na posição,
* remover item da posição, remover do início, existe, entre outros.
*/
#ifndef LISTA_HPP_
#define LISTA_HPP_
#define MAXLISTA 100
#define ERROLISTACHEIA -1
#define ERROLISTAVAZIA -2
#define ERROPOSICAO -3
template <typename T>
class Lista {
 private:
    T *dados;
	int ultimo, tamanho;

 public:
	/** Construtor padrão da Lista.
	* O construtor padrão da Lista constroi uma lista de tamanho "MAXLISTA", uma constante definida no escopo da classe.
	* O "tamanho" da lista será também definido com o valor de "MAXLISTA".
	* @see limpar()
	*/
	Lista() {
	    dados = new T[MAXLISTA];
		ultimo = -1;
		tamanho = MAXLISTA;
	}
	/** Construtor da Lista recebendo como argumento o tamanho da lista a ser criada.
	* O construtor da Lista constrói uma lista de tamanho "tam". Além disso, o "tamanho" da lista será também definido co mo valor de "tam".
	* @param tam Argumento que informa qual é o tamanho da lista que será criada.
	* @see limpar()
	*/
	explicit Lista(int tam) {
	    dados = new T[tam];
		ultimo = -1;
		tamanho = tam;
	}

	/** Destrutor padrão da Lista.
	* O destrutor padrão da lista desaloca a memória dinâmica alocada para este objeto. Antes disso, zera o tamanho da lista.
	* @see limpar()
	*/
	~Lista(){
		ultimo = -1;
		delete[] dados;
	}
	/** Adiciona um novo elemento no final da Lista.
	* Este método recebe um dado do tipo T e adiciona este elemento no final da lista, ou seja, adiciona esse dado na última posição da lista.
	* @param dado O dado que será inserido dentro da lista. Precisa ser do mesmo tipo de dados que a lista armazena.
	* @see listaCheia()
	* @exception ERROLISTACHEIA Exceção que indica que um novo dado não pode ser adicionado, pois a lista já está cheia.
	* @return um inteiro que indica a posição do último elemento a ser adicionado na lista (no caso, o último).
	*/
	void adiciona(T dado) {
	    if (!listaCheia()) {
			dados[++ultimo] = dado;
		} else {
			throw ERROLISTACHEIA;
		}
	}
	/** Adiciona um novo elemento no início da Lista.
	* Este método recebe um dado do tipo T e adiciona este elemento no início da lista, ou seja, adiciona esse dado na posição zero.
	* @param dado O dado que será inserido dentro da lista. Precisa ser do mesmo tipo de dados que a lista armazena.
	* @see listaCheia()
	* @exception ERROLISTACHEIA Exceção que indica que um novo addo não pode ser adicionado, pois a lista já está cheia.
	* @return um inteiro que indica a posição do último elemento a ser adicionado na lista (no caso, zero).
	*/
	void adicionaNoInicio(T dado) {
	    int posicao;
		if (!listaCheia()) {
			ultimo = ultimo + 1;
			for(posicao = ultimo; posicao > 0; posicao--) {
				dados[posicao] = dados[posicao -1];
			}
			dados[0] = dado;
		} else {
			throw ERROLISTACHEIA;
		}
	}
	/** Adiciona um novo elemento em uma posição específica da Lista.
	* Este método recebe um dado do tipo T e adiciona este elemento em determinada posição.
	* @param posicao A posição na lista em que o dado será adicionado.
	* @param dado O dado a ser inserido na Lista.
	* @see listaCheia()
	* @exception ERROLISTACHEIA Exceção que indica que um novo dado não pode ser adicionado, pois a lista já está cheia.
	* @return um inteiro que indica a posição do último elemento a ser adicionado na lista (no caso, o "destino").
	*/
	void adicionaNaPosicao(T dado, int destino) {
	    int posicao;
		if (listaCheia()) {
			throw ERROLISTACHEIA;
		} else {
			if(destino < 0 || destino > ultimo + 1)
				throw ERROPOSICAO;
			ultimo = ultimo + 1;
			for(posicao = ultimo; posicao > destino; posicao--) {
				dados[posicao] = dados[posicao - 1];
			}
			dados[destino] = dado;
		}
	}

	/** Adiciona um novo elemento seguindo a ordem da Lista.
	* Este método recebe um dado do tipo T e adiciona este elemento em determinada posição.
	* @param dado O dado a ser inserido na Lista.
	* @see listaCheia()
	* @exception ERROLISTACHEIA Exceção que indica que um novo dado não pode ser adicionado, pois a lista já está cheia.
	* @return um inteiro que indica a posição do último elemento a ser adicionado na lista (no caso, a posição encontrada que está de acordo com a ordenação da Lista).
	*/
	void adicionaEmOrdem(T dado) {
	    int posicao = 0;
		if (listaCheia()) {
			throw ERROLISTACHEIA;
		} else {
			for(int i = 0; i <= ultimo; i++) {
				if (maior(dado, dados[posicao])) {
					posicao++;
				} else {
					break;
				}
			}
			adicionaNaPosicao(dado, posicao);
		}
	}
	/** Retira o último elemento da Lista.
	* Este método retira o último elemento da Lista e decrementa o ponteiro da Lista.
	* @see listaVazia()
	* @exception ERROLISTAVAIZA Exceção que indica que um dado não pode ser retirado, pois a lista já está vazia.
	* @return o dado do tipo T que foi retirado do final da Lista.
	*/
	T retira() {
	    if (!listaVazia()) {
			ultimo = ultimo - 1;
			return dados[ultimo + 1];
		} else {
			throw ERROLISTAVAZIA;
		}
	}
	/** Retira o primeiro elemento da Lista.
	* Este método retira o primeiro elemento da Lista e traz todos os dados uma posição para frente.
	* @see listaVazia()
	* @exception ERROLISTAVAZIA Exceção que indica que um dado não pode ser retirado, pois a lsita já está vazia.
	* @return o dado do tipo T que foi retirado do início da Lista.
	*/
	T retiraDoInicio() {
	    int posicao;
		if (!listaVazia()) {
			ultimo = ultimo - 1;
			int valor = dados[0];
			for(posicao = 0; posicao <= ultimo; posicao++) {
				dados[posicao] = dados[posicao + 1];
			}
			return valor;
		} else {
			throw ERROLISTAVAZIA;
		}
	}

	/** Retira um elemento em uma posição específica da Lista.
	* @see listaVazia()
	* @param fonte A posição do dado a ser retirado.
	* @exception ERROLISTAVAZIA Exceção que indica que um dado não pode ser retirado, pois a lsita já está vazia.
	* @return o dado do tipo T que foi retirado da posição específica da Lista.
	*/
	T retiraDaPosicao(int posicao) {
	    int fonte, valor;
		if (!listaVazia()) {
		    if (!(posicao > ultimo || posicao <= -1)) {
		        valor = dados[posicao];
			    ultimo = ultimo - 1;
			    for (fonte = posicao; fonte <= ultimo; fonte++) {
			    	dados[fonte] = dados[fonte + 1];
			    }
			    return valor;
			 } else {
			    throw ERROPOSICAO;
			 }
		} else {
			throw ERROLISTAVAZIA;
		}
	}

	/** Retira um elemento da Lista, se este objeto existir dentro da Lista.
	* @see listaVazia()
	* @param dado A posição do dado a ser retirado.
	* @exception ERROPOSICAO Exceção que indica que o dado enviado via argumento não existe dentro dessa Lista, logo não pode ser removido.
	* @exception ERROLISTAVAZIA Exceção que indica que um dado não pode ser retirado, pois a lsita já está vazia.
	* @return o dado do tipo T que foi retirado.
	*/
	T retiraEspecifico(T dado) {
	    int posicao;
		if (!listaVazia()) {
			posicao = this->posicao(dado);
			if (posicao < 0) {
				throw ERROPOSICAO;
			} else {
				return retiraDaPosicao(posicao);
			}
		} else {
			throw ERROLISTAVAZIA;
		}
	}
	/** Verifica se um determinado elemento existe na Lista. Se sim, retorna a sua posição.
	* @param dado O dado que será verificado a existência dentro da Lista.
	* @exception ERROPOSICAO Exceção que indica que o elemento enviado via argumento não existe dentro dessa Lista.
	* @return a posição do elemento que foi encontrado na Lista.
	*/
	int posicao(T dado) {
	    int posicao = 0;
		for(int i = 0; i <= ultimo; i++) {
			if (igual(dados[posicao], dado)) {
				break;
			} else {
				posicao++;
			}
		}
		if (posicao > ultimo) {
			throw ERROPOSICAO;
		} else {
			return posicao;
		}
	}

	/** Verifica se a Lista contêm o elemento especificado.
	* @param dado O dado que será verificado a existência dentro da Lista.
	* @return um boolean que indica se a Lista contêm ou não o elemento especificado.
	*/
	bool contem(T dado) {
	    int igl = 0;
		for(int i = 0; i < tamanho; i++) {
			if (igual(dados[i], dado)) {
				igl = 1;
				break;
			}
		}
		return igl == 1;
	}
	/**Verifica se um dado do Tipo T é igual a um dado do mesmo tipo.
	 * @param dado1 e dado2 Estes parâmetros indicam quais dados serão comparados.
	 * @return um boolean que indica se os dados são iguais ou não.
	 */
	bool igual(T dado1, T dado2) {
	    return dado1 == dado2;
	}
	/**Verifica se um de dois dados é maior que o outro.
	 * @param dado1 e dado2 São parâmetros que serão comparados.
	 * @return É retornado um boolean que mostra se um dado é maior que outro.
	 */
	bool maior(T dado1, T dado2) {
	    return dado1 > dado2;
	}
	/**Verifica se um dos dados é menor que o outro.
	 * @param dado1 e dado 2 são parâmetros que serão verificados no método.
	 * @return Retorna um boolean verificando se um dado é menor que o outro.
	 */
	bool menor(T dado1, T dado2) {
	    return dado1 < dado2;
	}
	/**Verifica se a Lista está cheia.
	 * O método tem a função de utilizar o valor da posição da variável ultimo e comparar com o tamanho da lista.
	 * Se a lista estiver cheia a posição do ultimo será igual ao tamanho da lista - 1(este "-1" é por causa que o indiceda
	 * lista começa em 0);
	 * @return É retornado um boolean mostrando se a lista está cheia ou não.
	 */
	bool listaCheia() {
		return ultimo == tamanho -1;
	}
	/**Método verifica se a Lista está vazia.
	 *Por meio de uma comparação entre a variável ultimo e o valor -1(que indica uma fila sem nenhum elemento)
	 *podemos verificar se a lista está vazia ou não.
	 *@return Retorna um boolean que mostra se a pilha está vazia ou não.
	 */
	bool listaVazia() {
	    return ultimo == -1;
	}
	/**Método responsável por destruir uma lista
	 * Este método coloca a posição do ultimo em -1, pois está posição indica que nenhum elemento está na lista.
	 * Além disso, este método deleta o ponteiro dados.
	 */
    void destroiLista() {
        ultimo = -1;
		delete[] dados;

    }
};
#endif /* LISTA_HPP_ */
