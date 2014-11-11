// Copyright [2014] <Emmanuelr>
#ifndef NOBINARIO_H_
#define NOBINARIO_H_
#include <stdio.h>
#include <cstdio>
#include <vector>

template<typename T>
class NoBinario {
 protected:
    int altura;
    T* dado;
    NoBinario<T>* esquerda;
    NoBinario<T>* direita;
    virtual NoBinario<T>* balanco_insere(NoBinario<T>* arv) { return arv; }
    // Para ajudar nos herancas
    virtual NoBinario<T>* balanco_remove(NoBinario<T>* arv) { return arv; }
    // Para ajudar nos herancas
    virtual void atualiza(NoBinario<T>* arv) {}
    std::vector<NoBinario<T> > elementos;
    // No lugar dos prints

 public:
    NoBinario<T>(const T& dado):
                dado(new T(dado)), esquerda(NULL), direita(NULL), altura(0) {}

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
            if (*(ptr->getDado()) < dado) {
                ptr = ptr->direita;
            } else {
                ptr = ptr->esquerda;
            }
        }
        if (ptr == NULL) {
            throw -1; // Throw para dizer que o dado não está presente
        }
        return ptr->getDado();
    }
    NoBinario<T>* inserir(const T& _dado, NoBinario<T>* raiz) {
        NoBinario<T>* novo;
        if (_dado < *(raiz->dado)) {
            if (raiz->esquerda == NULL) {
                novo = new NoBinario<T>(_dado);
                raiz->esquerda = novo;
            } else {
                inserir(_dado, raiz->esquerda);
            }
            balanco_insere(raiz);
        }
        if (_dado > *raiz->dado) {
            if (raiz->direita == NULL) {
                novo = new NoBinario<T>(_dado);
                raiz->direita = novo;
            } else {
                inserir(_dado, raiz->direita);
            }
            balanco_insere(raiz);

        }
        atualiza(raiz);
        return raiz;
    }
    NoBinario<T>* remover(NoBinario<T>* raiz, const T& _dado) {
        NoBinario<T>* filho = new NoBinario<T>(0);
        NoBinario<T>* temp = new NoBinario<T>(0);
        if (raiz == NULL) {
            return raiz;
        }
        if (_dado < *raiz->dado) {  // Vai para a esquerda
            raiz->esquerda = remover(raiz->esquerda, _dado);
            balanco_insere(raiz);
            atualiza(raiz);
            return raiz;
        }
        if (_dado > *raiz->dado) {
            raiz->direita = remover(raiz->direita, _dado);
            balanco_insere(raiz);
            atualiza(raiz);
            return raiz;
        }
        if (raiz->direita != NULL && raiz->esquerda != NULL) {
            temp = minimo(raiz->direita); 
            raiz->dado = temp->dado;
            raiz->direita = remover(raiz->direita, *raiz->dado);
            atualiza(raiz);
            return raiz;
        }
        temp = raiz;
        if (raiz->direita != NULL) {  // filho direita
            filho = raiz->direita;
            atualiza(raiz);
            return filho;
        }
        if (raiz->esquerda != NULL) {
            filho = raiz->esquerda;
            atualiza(raiz);
            return filho;
        }
        atualiza(raiz);
        delete raiz;  //  Folha.
        return NULL;
    }
    NoBinario<T>* minimo(NoBinario<T>* raiz) {
        NoBinario<T>* root;
        if (raiz->esquerda != NULL) {
            root = minimo(raiz->esquerda);
        } else {
            root = raiz;
        }
        return root;
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

    NoBinario<T>* getEsquerda() {
        return esquerda;
    }

    void setEsquerda(NoBinario<T>* novo) {
        this->esquerda = novo;
    }

    NoBinario<T>* getDireita() {
        return direita;
    }

    void setDireita(NoBinario<T>* novo) {
        direita = novo;
    }

    int getAltura() {
        return this->altura;       
    }

    void setAltura(int _altura) {
        this->altura = _altura;
    }
};

#endif /* NOBINARIO_HPP_ */
