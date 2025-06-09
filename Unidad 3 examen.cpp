#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ===================== ESTRUCTURA DE PROCESO ===================== //
struct Proceso {
    int id;
    string nombre;
    int prioridad;
    Proceso* siguiente;

    Proceso(int i, string n, int p) {
        id = i;
        nombre = n;
        prioridad = p;
        siguiente = NULL;
    }
};
//hola
// ===================== LISTA ENLAZADA (Gestor de Procesos) ===================== //
Proceso* listaProcesos = NULL;

void insertarProceso(int id, string nombre, int prioridad) {
    Proceso* nuevo = new Proceso(id, nombre, prioridad);
    if (!listaProcesos) listaProcesos = nuevo;
    else {
        Proceso* temp = listaProcesos;
        while (temp->siguiente) temp = temp->siguiente;
        temp->siguiente = nuevo;
    }
    cout << "Proceso insertado." << endl;
}

void eliminarProceso(int id) {
    if (!listaProcesos) return;
    if (listaProcesos->id == id) {
        Proceso* aux = listaProcesos;
        listaProcesos = listaProcesos->siguiente;
        delete aux;
        cout << "Proceso eliminado." << endl;
        return;
    }
    Proceso* ant = listaProcesos;
    Proceso* act = listaProcesos->siguiente;
    while (act && act->id != id) {
        ant = act;
        act = act->siguiente;
    }
    if (act) {
        ant->siguiente = act->siguiente;
        delete act;
        cout << "Proceso eliminado." << endl;
    } else cout << "Proceso no encontrado." << endl;
}

void buscarProceso(int id) {
    Proceso* temp = listaProcesos;
    while (temp) {
        if (temp->id == id) {
            cout << "Proceso encontrado: " << temp->nombre << ", Prioridad: " << temp->prioridad << endl;
            return;
        }
        temp = temp->siguiente;
    }
    cout << "Proceso no encontrado." << endl;
}

void modificarPrioridad(int id, int nuevaPrioridad) {
    Proceso* temp = listaProcesos;
    while (temp) {
        if (temp->id == id) {
            temp->prioridad = nuevaPrioridad;
            cout << "Prioridad modificada." << endl;
            return;
        }
        temp = temp->siguiente;
    }
    cout << "Proceso no encontrado." << endl;
}

void mostrarProcesos() {
    Proceso* temp = listaProcesos;
    cout << "Lista de procesos:\n";
    while (temp) {
        cout << "ID: " << temp->id << " - " << temp->nombre << " (Prioridad " << temp->prioridad << ")\n";
        temp = temp->siguiente;
    }
}
