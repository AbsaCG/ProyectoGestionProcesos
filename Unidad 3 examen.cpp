#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ESTRUCTURA DE PROCESO 
struct Proceso {
    int id;
    string nombre;
    int prioridad;
    Proceso* siguiente;
// Constructor de la estructura
    Proceso(int i, string n, int p) {
        id = i;
        nombre = n;
        prioridad = p;
        siguiente = NULL;
    }
};

// LISTA ENLAZADA (Gestor de Procesos)  
Proceso* listaProcesos = NULL;// Apunta al primer proceso en la lista enlazada. Si es NULL, no hay procesos.
// funcion que agrega un proceso al final de la lista
void insertarProceso(int id, string nombre, int prioridad) {
    Proceso* nuevo = new Proceso(id, nombre, prioridad);// Crear un nuevo nodo proceso
    if (!listaProcesos) listaProcesos = nuevo;// Si la lista está vacía, el nuevo proceso es el primero
    else {
        Proceso* temp = listaProcesos;
        while (temp->siguiente) temp = temp->siguiente;
        temp->siguiente = nuevo;// Insertamos el nuevo proceso al final
    }
    cout << "Proceso insertado." << endl;
}
// Funcion que eimina un proceso por su ID
void eliminarProceso(int id) {
    if (!listaProcesos) return; // Si la lista esta vacia, no hay nada que eliminar
     // Caso especial: el proceso a eliminar está al inicio
    if (listaProcesos->id == id) {
        Proceso* aux = listaProcesos;// Guardamos el proceso a eliminar
        listaProcesos = listaProcesos->siguiente;// Movemos el inicio al siguiente
        delete aux;// Liberamos la memoria del proceso eliminado
        cout << "Proceso eliminado." << endl;
        return;
    }
     // Buscamos el proceso a eliminar recorriendo la lista
    Proceso* ant = listaProcesos;// Apuntamos al proceso anterior
    Proceso* act = listaProcesos->siguiente;// Apuntamos al proceso actual
    while (act && act->id != id) {
        ant = act;
        act = act->siguiente;
    }
    if (act) {
        ant->siguiente = act->siguiente;// Si encontramos el proceso, lo saltamos en la lista y liberamos memoria
        delete act;
        cout << "Proceso eliminado." << endl;
    } else cout << "Proceso no encontrado." << endl;
}
//  funcion para buscar un proceso por ID y muestra su informacion
void buscarProceso(int id) {
    Proceso* temp = listaProcesos;
    while (temp) {
        if (temp->id == id) {
            cout << "Proceso encontrado: " << temp->nombre << ", Prioridad: " << temp->prioridad << endl;
            return;
        }
        temp = temp->siguiente;// Avanzamos al siguiente proceso
    }
    cout << "Proceso no encontrado." << endl;
}
// Modifica la prioridad de un proceso 
void modificarPrioridad(int id, int nuevaPrioridad) {
    Proceso* temp = listaProcesos;
    while (temp) {
        if (temp->id == id) {
            temp->prioridad = nuevaPrioridad;// Actualizamos prioridad
            cout << "Prioridad modificada." << endl;
            return;
        }
        temp = temp->siguiente;
    }
    cout << "Proceso no encontrado." << endl;
}
// Muestra todos los procesos en la lista
void mostrarProcesos() {
    Proceso* temp = listaProcesos;
    cout << "Lista de procesos:\n";
    while (temp) {
        cout << "ID: " << temp->id << " - " << temp->nombre << " (Prioridad " << temp->prioridad << ")\n";
        temp = temp->siguiente;
    }
}
