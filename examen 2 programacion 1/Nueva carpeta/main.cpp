#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <windows.h> // para gotoxy y Colores
#include <conio.h> // para g

using namespace std;

// Estructuras
struct Candidato {
    string nombre;
    string partido;
    string plataforma;
    int votos;

    Candidato(string n, string p, string pl) : nombre(n), partido(p), plataforma(pl), votos(0) {}
};

struct Votante {
    string nombre;
    string cedula;
    string provincia;

    Votante(string n, string c, string p) : nombre(n), cedula(c), provincia(p) {}
};

// Variables GLOVALES
vector<Candidato> candidatos;
vector<Votante> votantes;
map<string, string> votos; //MAPEO

// Funciones y procedimientos
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void registrarCandidato() {
    string nombre, partido, plataforma;
    system("CLS");
    setColor(14); // amarillo
    gotoxy(20, 5);
    cout << "ingrese el nombre del candidato: ";
    cin.ignore();
    getline(cin, nombre);
    gotoxy(20, 6);
    cout << "ingrese el partido politico: ";
    getline(cin, partido);
    gotoxy(20, 7);
    cout << "ingrese la plataforma del candidato: ";
    getline(cin, plataforma);

    candidatos.push_back(Candidato(nombre, partido, plataforma));
    setColor(10); // Verde
    gotoxy(20, 9);
    cout << "Candidato registrado exitosamente!\n";
    getch();
}

void registrarVoto() {
    string nombreVotante, cedula, provincia, nombreCandidato;
    system("CLS");
    setColor(14); // Amarillo
    gotoxy(20, 5);
    cout << "Ingrese su cedula: ";
    cin.ignore();
    getline(cin, cedula);
    gotoxy(20, 6);
    // Verifica si el votante ya a votado
    if (votos.find(cedula) != votos.end()) {
        setColor(12); // Rojo
        gotoxy(20, 9);
        cout << "El ciudadano ya realizo su voto.\n";
        getch();
        return;
    }
    cout << "Ingrese su nombre: ";
    getline(cin, nombreVotante);
    gotoxy(20, 7);
    cout << "Ingrese su provincia: ";
    getline(cin, provincia);

  //
    gotoxy(20, 8);
    cout << "Ingrese el nombre del candidato por el que desea votar: ";
    getline(cin, nombreCandidato);

    bool candidatoEncontrado = false;
    vector<Candidato>::iterator it;
    for (it = candidatos.begin(); it != candidatos.end(); ++it) {
        if (it->nombre == nombreCandidato) {
            it->votos++;
            votantes.push_back(Votante(nombreVotante, cedula, provincia));
            votos[cedula] = nombreCandidato;
            setColor(10); // Verde
            gotoxy(20, 10);
            cout << "Voto registrado para " << nombreCandidato << "!\n";
            candidatoEncontrado = true;
            getch();
            break;
        }
    }

    if (!candidatoEncontrado) {
        setColor(12); // Rojo
        gotoxy(20, 10);
        cout << "Candidato no encontrado, seleccione un candidato ingresado.\n";
        getch();
    }
}

void mostrarResultados() {
    system("CLS");
    if (candidatos.empty()) {
        setColor(12); // Rojo
        gotoxy(20, 5);
        cout << "No hay candidatos registrados.\n";
        getch();
        return;
    }

    int totalVotos = 0;
    vector<Candidato>::const_iterator it;
    for (it = candidatos.begin(); it != candidatos.end(); ++it) {
        totalVotos += it->votos;
    }

    Candidato ganador = candidatos[0];
    for (it = candidatos.begin(); it != candidatos.end(); ++it) {
        if (it->votos > ganador.votos) {
            ganador = *it;
        }
    }

    setColor(14); // Amarillo
    gotoxy(20, 5);
    cout << "\nResultados de la votacion:\n ";
    int line = 6;
    for (it = candidatos.begin(); it != candidatos.end(); ++it) {
        double porcentaje = (totalVotos > 0) ? (it->votos * 100.0 / totalVotos) : 0;
        gotoxy(20, line++);
        cout << it->nombre << " (" << it->partido << "): " << it->votos << " votos (" << porcentaje << "%)\n";
    }

    setColor(10); // Verde
    gotoxy(20, line + 1);
    cout << "\nEl ganador es " << ganador.nombre << " del partido " << ganador.partido << " con " << ganador.votos << " votos.\n";
    getch();
}

void mostrarVotantes() {
    system("CLS");
    if (votantes.empty()) {
        setColor(12); // Rojo
        gotoxy(20, 5);
        cout << "No hay votantes registrados.\n";
        getch();
        return;
    }

    setColor(14); // Amarillo
    gotoxy(20, 5);
    cout << "\nLista de votantes:\n";
    int line = 6;
    vector<Votante>::const_iterator it;
    for (it = votantes.begin(); it != votantes.end(); ++it) {
        gotoxy(20, line++);
        cout << "Nombre: " << it->nombre << ", Cedula: " << it->cedula << ", Provincia: " << it->provincia << ", Voto por: " << votos[it->cedula] << "\n";
    }
    getch();
}

void mostrarMenu() {
    system("CLS");
    setColor(11); // Azul claro
    gotoxy(20, 5);
    cout << "\nMenu:\n";
    gotoxy(20, 6);
    cout << "1. Ingresar Candidatos\n";
    gotoxy(20, 7);
    cout << "2. Registrar Votos\n";
    gotoxy(20, 8);
    cout << "3. Mostrar Resultados\n";
    gotoxy(20, 9);
    cout << "4. Mostrar Votantes\n";
    gotoxy(20, 10);
    cout << "5. Salir\n";
    gotoxy(20, 11);
    cout << "Seleccione una opcion: ";
}

int main() {
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarCandidato();
                break;
            case 2:
                registrarVoto();
                break;
            case 3:
                mostrarResultados();
                break;
            case 4:
                mostrarVotantes();
                break;
            case 5:
                setColor(10); // Verde
                gotoxy(20, 12);
                cout << "Saliendo...\n";
                break;
            default:
                setColor(12); // Rojo
                gotoxy(20, 12);
                cout << "Opcion invalida. Intente nuevamente.\n";
                getch();
        }
    } while (opcion != 5);

    return 0;
}

