#include <iostream>
#include <string>
#include <array>
#include "juego.hpp"

int main() {
    using namespace std;
    cout << "+==========+\n| Damascpp |\n+==========+\n\nTutorial:\n - Para mover una ficha, usa el comando:\n     <posicion de ficha>-><posicion a moverse>\n   Ejemplo:\n     2A->4C\n - Para rendirte, usa el comando R1\n - Para reiniciar la partida, usa el comando R2\n - Las fichas del 1er jugador son \"o\" y las reinas son \"O\"\n - Las fichas del 2do jugador son \"x\" y las reinas son \"X\"\n\n";
    Juego juego;
    while (!juego.fin)
        juego.mostrar();

    return 0;
}
