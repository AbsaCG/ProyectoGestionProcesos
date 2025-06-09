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
// COLA DE PRIORIDAD (Planificador de CPU) 
Proceso* colaCPU = NULL;
// Encola un proceso en la cola de CPU segun su prioridad
void encolarProceso(Proceso* proc) {
    if (!colaCPU || proc->prioridad > colaCPU->prioridad) {
        proc->siguiente = colaCPU;// El nuevo proceso apunta al inicio actual
        colaCPU = proc;// Y ahora es el inicio de la cola
    } else {
    	 // Recorremos para encontrar la posición correcta (orden descendente)
        Proceso* temp = colaCPU;
        while (temp->siguiente && temp->siguiente->prioridad >= proc->prioridad)
            temp = temp->siguiente;
        proc->siguiente = temp->siguiente;
        temp->siguiente = proc;
    }
    cout << "Proceso encolado para ejecucion." << endl;
}
// Ejecuta (elimina) el primer proceso en la cola de CPU
void ejecutarProceso() {
    if (!colaCPU) {
        cout << "No hay procesos en cola." << endl;
        return;
    }
    Proceso* proc = colaCPU;// Tomamos el primer proceso
    colaCPU = colaCPU->siguiente;// La cola avanza al siguiente proceso
    cout << "Ejecutando: " << proc->nombre << " (Prioridad " << proc->prioridad << ")\n";
    delete proc;// Liberamos memoria del proceso ejecutado
}
// Muestra los procesos en la cola de CPU
void mostrarCola() {
    Proceso* temp = colaCPU;
    int contador = 0;

    cout << "\n--- Cola de CPU ---\n";

    if (!temp) {
        cout << "La cola esta vacia.\n";
        return;
    }

    while (temp) {
        cout << "- " << temp->nombre << " (Prioridad " << temp->prioridad << ")\n";
        temp = temp->siguiente;
        contador++;
    }

    cout << "Total de procesos en cola: " << contador << endl;
}
//  PILA (Gestor de Memoria)  
struct NodoMemoria {
    int bloque;
    NodoMemoria* sig;// Puntero al siguiente nodo (bloque) en la pila
    NodoMemoria(int b) { bloque = b; sig = NULL; }
};

NodoMemoria* memoria = NULL;// Apunta al ultimo bloque de memoria asignado (pila). Si es NULL, no hay bloques.
// Asigna un bloque de memoria 
void asignarMemoria(int bloque) {
    NodoMemoria* nuevo = new NodoMemoria(bloque);// Crear nuevo nodo
    nuevo->sig = memoria;// Nuevo nodo apunta al tope actual
    memoria = nuevo; // El tope ahora es el nuevo nodo
    cout << "Memoria asignada: bloque " << bloque << endl;
}
// Libera el ultimo bloque asignado 
void liberarMemoria() {
    if (!memoria) {
        cout << "No hay memoria asignada.\n";
        return;
    }
    NodoMemoria* temp = memoria;// Guardamos el tope actual
    memoria = memoria->sig;// El tope pasa al siguiente nodo
    cout << "Memoria liberada: bloque " << temp->bloque << endl;
    delete temp;// Liberamos memoria del nodo eliminado
}
// Muestra todos los bloques de memoria 
void verMemoria() {
    NodoMemoria* temp = memoria;
    cout << "Bloques de memoria asignados:\n";
    while (temp) {
        cout << "Bloque " << temp->bloque << endl;
        temp = temp->sig;
    }
}
