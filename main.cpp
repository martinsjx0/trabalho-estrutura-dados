#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Definição do tipo abstrato de dados para representar uma carta do baralho
struct Carta {
    int numero;
    string naipe;
};

// Definição do tipo abstrato de dados para representar uma pilha de cartas
class Pilha {
private:
    vector<Carta> cartas;

public:
    void clean() {
        cartas.clear();
    }

    bool empty() const {
        return cartas.empty();
    }

    void push(Carta carta) {
        cartas.push_back(carta);
    }

    void pop() {
        if (!cartas.empty()) {
            cartas.pop_back();
        }
    }

    Carta top() const {
        if (!cartas.empty()) {
            return cartas.back();
        } else {
            Carta carta;
            carta.numero = -1;  // Representa uma carta inválida
            return carta;
        }
    }
};

// Função para gerar as 52 cartas no monte
void gerarCartas(vector<Carta>& monte) {
    string naipes[] = {"Paus", "Ouros", "Copas", "Espadas"};
    for (int naipe = 0; naipe < 4; ++naipe) {
        for (int numero = 1; numero <= 13; ++numero) {
            Carta carta;
            carta.numero = numero;
            carta.naipe = naipes[naipe];
            monte.push_back(carta);
        }
    }
}

// Função para embaralhar as cartas no monte
void embaralharCartas(vector<Carta>& monte) {
    srand(time(0));
    for (int i = monte.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(monte[i], monte[j]);
    }
}

// Função para simular o jogo
void simularJogo(vector<Carta>& monte, Pilha& morto, Pilha& jogador1, Pilha& jogador2) {
    int escolhasJogador1[] = {2, 4, 6, 8, 10};  // Escolhas do jogador 1
    int escolhasJogador2[] = {1, 3, 5, 7, 9};  // Escolhas do jogador 2

    for (int i = 0; i < 5; ++i) {
        Carta cartaJogador1 = monte.back();
        monte.pop_back();
        Carta cartaJogador2 = monte.back();
        monte.pop_back();

        // Verifica se o jogador 1 ganha a carta
        if (cartaJogador1.numero == escolhasJogador1[i]) {
            jogador1.push(cartaJogador1);
        } else {
            morto.push(cartaJogador1);
        }

        // Verifica se o jogador 2 ganha a carta
        if (cartaJogador2.numero == escolhasJogador2[i]) {
            jogador2.push(cartaJogador2);
        } else {
            morto.push(cartaJogador2);
        }
    }
}

int main() {
    vector<Carta> monte;
    Pilha morto, jogador1, jogador2;

    // (D) Gerar as 52 cartas no monte
    gerarCartas(monte);

    // (E) Embaralhar as cartas no monte
    embaralharCartas(monte);

    // (F) Simular o jogo
    simularJogo(monte, morto, jogador1, jogador2);

    // (G) Anunciar o vencedor
    cout << "Jogador 1: " << jogador1.top().numero << " cartas\n";
    cout << "Jogador 2: " << jogador2.top().numero << " cartas\n";

    if (jogador1.top().numero > jogador2.top().numero) {
        cout << "Jogador 1 venceu!\n";
    } else if (jogador1.top().numero < jogador2.top().numero) {
        cout << "Jogador 2 venceu!\n";
    } else {
        cout << "Empate!\n";
    }

    return 0;
}