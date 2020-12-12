#pragma once
#include <array>
#include <string>
#include <fstream> // archivos
#include <iostream>
#include <cctype> // trabajo en caracteres
#include <unordered_map> // diccionario
using namespace std;

/*
0: no hay fichas " "
1: ficha del 1er jugador "o"
2: reina del 1er jugador "O"
-1: ficha del 2do jugador "x"
-2: reina del 2do jugador "X"
*/

class Juego {
private:
    array<array<int, 8>, 8> tablero; //int tablero[8][8]
    bool turno = true;
    string j1, j2;
    unordered_map<string, int> archivo; // diccionario = {Jose: 0}
    bool procesar_comando(string s);
    void poner_fichas();
    void reiniciar();
    bool mover_reina(int x1, int y1, int x2, int y2, bool abajo, bool der);
    bool mover_ficha(int x1, int y1, int x2, int y2, bool der);
    
public:
    Juego();
    ~Juego();
    void mostrar();
    bool fin = false;
};
