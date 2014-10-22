// Copyright [2014] <Emmanuelr>
#ifndef NOBINARIO_H_
#define NOBINARIO_H_
#include <stdio.h>
#include <cstdio>
#include <vector>

template<typename T>
class NoBinario {
 private:
	T* dado;
	NoBinario<T>* esquerda;
	NoBinario<T>* direita;
	virtual NoBinario<T>* balanco_insere(NoBinario<T>* arv) { return arv; }
	// Para ajudar nos herancas
	virtual NoBinario<T>* balanco_remove(NoBinario<T>* arv) { return arv; }
	// Para ajudar nos herancas
	std::vector<NoBinario<T> > elementos;
	// No lugar dos prints

 public:
	NoBinario<T>(const T& dado):
	            dado(new T(dado)), esquerda(NULL), direita(NULL) {}

	virtual ~NoBinario<T>() {
	    elementos.clear();
	}

	T* getDado() {
	    return this->dado;
	}
	NoBinario<T>* getElementos() {
	    return elementos.data();
	}
	T* busca(const T& dado, NoBinario<T>* ptr) {
	    while (ptr != NULL && *ptr->dado != dado) {
            if (*ptr->dado < dado) {
                ptr = ptr->direita;
            } else {
                ptr = ptr->esquerda;
            }
        }
        return ptr->dado;
    }
	NoBinario<T>* inserir(const T& _dado, NoBinario<T>* raiz) {
	    NoBinario<T>* novo;
	    if (_dado < *raiz->dado) {
	        if (raiz->esquerda == NULL) {
                novo = new NoBinario<T>(_dado);
                raiz->esquerda = novo;
            } else {
                inserir(_dado, raiz->esquerda);
            }
            balanco_insere(raiz);
        } else {
            if (raiz->direita == NULL) {
                novo = new NoBinario<T>(_dado);
                raiz->direita = novo;
            } else {
                inserir(_dado, raiz->direita);
            }
            balanco_insere(raiz);
        }
        return novo;
    }
    NoBinario<T>* remover(NoBinario<T>* raiz, const T& _dado) {
        NoBinario<T>* filho, temp;
        if (raiz == NULL) {
            return raiz;
        }
        if (_dado < *raiz->dado) {  // Vai para a esquerda
            raiz->esquerda = deletar(raiz->esquerda, _dado);
            return raiz;
        }
        if (_dado > *raiz->dado) {
            raiz->direita = deletar(raiz->direita, _dado);
            return raiz;
        }
        if (raiz->direita != NULL && raiz->esquerda != NULL) {
            temp = minimo(raiz->direita);  //  mínimo?
            raiz->dado = temp->dado;
            raiz->direita = deletar(raiz->direita, *raiz->dado);
            return raiz;
        }
        temp = raiz;
        if (raiz->direita != NULL) {  // filho direita
            filho = raiz->direita;
            return filho;
        }
        if (raiz->esquerda != NULL) {
            filho = raiz->esquerda;
            return filho;
        }
        delete raiz;  //  Folha.
        return NULL;
    }
	NoBinario<T>* minimo(NoBinario<T>* raiz) {
	   if (raiz != NULL) {
	        minimo(raiz->esquerda);
	   }
	   return raiz;
	}
	void preOrdem(NoBinario<T>* raiz) {
	    if (raiz != NULL) {
	 			elementos.push_back(*raiz);
	 			preOrdem(raiz->esquerda);
	 			preOrdem(raiz->direita);
	 		}
	}
	void emOrdem(NoBinario<T>* raiz) {
	    if (raiz != NULL) {
	        emOrdem(raiz->esquerda);
	        elementos.push_back(*raiz);
	        emOrdem(raiz->direita);
	   }
	}
	void posOrdem(NoBinario<T>* raiz) {
	    if (raiz != NULL) {
	        posOrdem(raiz->esquerda);
	        posOrdem(raiz->direita);
	        elementos.push_back(*raiz);
	   }
	}
};

#endif /* NOBINARIO_HPP_ */
