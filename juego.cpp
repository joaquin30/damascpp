#include "juego.hpp"
using namespace std;

bool Juego::mover_ficha(int x1, int y1, int x2, int y2, bool der) {
    if (!turno) {
        if (tablero[x1 + 1][y1 + (der ? 1 : -1)] < 0) {
            tablero[x1][y1] = 0;
            tablero[x1 + 1][y1 + (der ? 1 : -1)] = 0;
            tablero[x2][y2] = 1;
            return true;
        } else {
            cout << "Comando invalido\n";
            return false;
        }
    } else {
        if (tablero[x1 - 1][y1 + (der ? 1 : -1)] > 0) {
            tablero[x1][y1] = 0;
            tablero[x1 - 1][y1 + (der ? 1 : -1)] = 0;
            tablero[x2][y2] = -1;
            return true;
        } else {
            cout << "Comando invalido\n";
            return false;
        }
    }
}

bool Juego::mover_reina(int x1, int y1, int x2, int y2, bool abajo, bool der) {
    int n_mov = abs(x1-x2);
    if (!turno) {
        for (int i = 1; i < n_mov; ++i) {
            if (tablero[x1 + (abajo ? i : -i)][y1 + (der ? i : -i)] > 0) {
              cout << "Comando invalido\n";
              return false;
            }
        }

        for (int i = 1; i < n_mov; ++i)
            tablero[x1 + (abajo ? i : -i)][y1 + (der ? i : -i)] = 0;
    } else {
        for (int i = 1; i < n_mov; ++i) {
            if (tablero[x1 + (abajo ? i : -i)][y1 + (der ? i : -i)] < 0) {
                cout << "Comando invalido\n";
                return false;
            }
        }

        for (int i = 1; i < n_mov; ++i)
            tablero[x1 + (abajo ? i : -i)][y1 + (der ? i : -i)] = 0;
    }

    tablero[x1][y1] = 0;
    tablero[x2][y2] = (!turno ? 2 : -2);
    return true;
}

void Juego::poner_fichas() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i < 3 and i % 2 != j % 2)
                tablero[i][j] = 1;
            else if (i > 4 and i % 2 != j % 2)
                tablero[i][j] = -1;
            else
                tablero[i][j] = 0;
        }
    }
}

void Juego::reiniciar() {
    cout << "Quieres iniciar nueva partida? [S/N]: ";
    string tmp;
    cin >> tmp;
    if (tmp == "S") {
        poner_fichas();
        turno = true;
    } else {
        fin = true;
    }
}

Juego::Juego() {
    poner_fichas();
    ifstream entrada("jugadores.txt", ifstream::app); //append
    while (!entrada.eof()) { //end of file
        string nombre;
        int nivel;
        entrada >> nombre >> nivel;
        archivo[nombre] = nivel;
    }

    cout << "Escribe el nombre del 1er jugador: ";
    cin >> j1;
    cout << j1 << " " << archivo[j1] << endl;
    cout << "Escribe el nombre del 2do jugador: ";
    cin >> j2;
    cout << j2 << " "<< archivo[j2] << endl;  
}

Juego::~Juego() {
    ofstream salida("jugadores.txt");
    for (auto [i, j] : archivo) {
        if (!i.empty())
        salida << i << " " << j << endl;
    }
}

void Juego::mostrar() {
    // comprobar si alguien perdio
    int jg1 = 0, jg2 = 0; // lista = (1, 154, 2)   for x in lista:
    for (auto i : tablero) {
        for (auto j : i) {
            if (j > 0)
                jg1++;
            else if (j < 0)
                jg2++;
        }
    }

    if (jg1 == 0) {
        cout << "Ganador: " << j2 << endl;
        archivo[j2]++;
        reiniciar();
        return;    
    } else if (jg2 == 0) {
        cout << "Ganador: " << j1 << endl;
        archivo[j1]++;
        reiniciar();
        return;
    }
    
    // comprobamos las nuevas reinas
    for (auto& i : tablero[0]) {
        if (i == -1)
            i = -2;
    }

    for (auto& i : tablero[7]) {
        if (i == 1)
            i = 2;
    }

    // Mostramos el tablero
    cout << "  +---+---+---+---+---+---+---+---+\n";
    for (int i = 0; i < 8; ++i) {
        cout << i + 1 << " |";
        for (int j = 0; j < 8; ++j) {
            switch (tablero[i][j]) {
            case 0:
                cout << "   |";
                break;
            case 1:
                cout << " o |";
                break;
            case 2:
                cout << " O |";
                break;
            case -1:
                cout << " x |";
                break;
            case -2:
                cout << " X |";
                break;
            default:
                break;
            }
        }
        cout << "\n  +---+---+---+---+---+---+---+---+\n";
    }
    cout << "    A   B   C   D   E   F   G   H\n\n";

    // procesar el comando
    string tmp;
    turno = !turno;
    do {
        cout << "Turno de " << (!turno ? j1 : j2) << ": ";
        cin >> tmp;
    } while (!procesar_comando(tmp));

    cout << endl;
}

bool Juego::procesar_comando(string s) {
    if (s == "R1") {
        cout << "Ganador: " << (turno ? j1 : j2) << endl;
        archivo[(turno ? j1 : j2)]++;
        reiniciar();
        return true;
    } else if (s == "R2") {
        cout << "Partida reiniciada" << endl;
        turno = true;
        poner_fichas();
        return true;
    } else {
        //comprobamos si existe ->
        if (s.find("->") == string::npos) {
            cout << "Comando invalido\n";
            return false;
        }

        //comprobamos q la 1ra letra sea un num y la 2da mayuscula
        string p1, p2;
        if (isdigit(s[0]) && isupper(s[1])) {
            p1 += s[0];
            p1 += s[1];
        } else {
            cout << "Comando invalido\n";
            return false;
        }
        
        if (isdigit(s[s.size() - 2]) && isupper(s[s.size() - 1])) {
            p2 += s[s.size() - 2];
            p2 += s[s.size() - 1];
        } else {
            cout << "Comando invalido\n";
            return false;
        }
        
        // usando codigos ascii 
        int x1 = p1[0] - 49;
        int y1 = p1[1] - 65;
        int x2 = p2[0] - 49;
        int y2 = p2[1] - 65;
        // si todos los num estan en [1, 7]
        if (x1 < 0 or x1 > 7 or y1 < 0 or y1 > 7 or x2 < 0 or x2 > 7 or y2 < 0 or y2 > 7 or p1 == p2) {
            cout << "Comando invalido\n";
            return false;
        }
        
        // si la posicion de la ficha esta vacia
        // o la posicion a moverse esta ocupada
        if (tablero[x1][y1] == 0 or tablero[x2][y2] != 0) {
            cout << "Comando invalido\n";
            return false;
        }
        
        // movemos las piezas
        if (abs(tablero[x1][y1]) == 1) {
            if (abs(x2 - x1) == 1 && abs(y2 - y1) == 1) {
                tablero[x1][y1] = 0;
                tablero[x2][y2] = (!turno ? 1 : -1);
                return true;
            } else if (abs(x2 - x1) == 2 && abs(y2 - y1) == 2) { 
                if (y2 > y1)
                    return mover_ficha(x1, y1, x2, y2, true);
                else 
                    return mover_ficha(x1, y1, x2, y2, false);
            } else {
                cout << "Comando invalido\n";
                return false;
            }
        } else if (abs(tablero[x1][y1]) == 2) {
            if (abs(x2 - x1) == abs(y2 - y1)) {
                if (x2 < x1) {
                    if (y2 < y1)
                        return mover_reina(x1, y1, x2, y2, false, false);
                    else
                        return mover_reina(x1, y1, x2, y2, false, true);
                } else {
                    if (y2 < y1)
                        return mover_reina(x1, y1, x2, y2, true, false);
                    else
                        return mover_reina(x1, y1, x2, y2, true, true);
                }
            } else {
                cout << "Comando invalido\n";
                return false;
            }
        } else {
            cout << "Comando invalido\n";
            return false;
        }
    }
}