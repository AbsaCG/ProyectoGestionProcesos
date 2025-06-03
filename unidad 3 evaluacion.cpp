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

// ===================== COLA DE PRIORIDAD (Planificador de CPU) ===================== //
Proceso* colaCPU = NULL;

void encolarProceso(Proceso* proc) {
    if (!colaCPU || proc->prioridad > colaCPU->prioridad) {
        proc->siguiente = colaCPU;
        colaCPU = proc;
    } else {
        Proceso* temp = colaCPU;
        while (temp->siguiente && temp->siguiente->prioridad >= proc->prioridad)
            temp = temp->siguiente;
        proc->siguiente = temp->siguiente;
        temp->siguiente = proc;
    }
    cout << "Proceso encolado para ejecución." << endl;
}

void ejecutarProceso() {
    if (!colaCPU) {
        cout << "No hay procesos en cola." << endl;
        return;
    }
    Proceso* proc = colaCPU;
    colaCPU = colaCPU->siguiente;
    cout << "Ejecutando: " << proc->nombre << " (Prioridad " << proc->prioridad << ")\n";
    delete proc;
}

void mostrarCola() {
    Proceso* temp = colaCPU;
    cout << "Cola de CPU:\n";
    while (temp) {
        cout << temp->nombre << " (Prioridad " << temp->prioridad << ")\n";
        temp = temp->siguiente;
    }
}

// ===================== PILA (Gestor de Memoria) ===================== //
struct NodoMemoria {
    int bloque;
    NodoMemoria* sig;
    NodoMemoria(int b) { bloque = b; sig = NULL; }
};

NodoMemoria* memoria = NULL;

void asignarMemoria(int bloque) {
    NodoMemoria* nuevo = new NodoMemoria(bloque);
    nuevo->sig = memoria;
    memoria = nuevo;
    cout << "Memoria asignada: bloque " << bloque << endl;
}

void liberarMemoria() {
    if (!memoria) {
        cout << "No hay memoria asignada.\n";
        return;
    }
    NodoMemoria* temp = memoria;
    memoria = memoria->sig;
    cout << "Memoria liberada: bloque " << temp->bloque << endl;
    delete temp;
}

void verMemoria() {
    NodoMemoria* temp = memoria;
    cout << "Bloques de memoria asignados:\n";
    while (temp) {
        cout << "Bloque " << temp->bloque << endl;
        temp = temp->sig;
    }
}

// ===================== MENÚ PRINCIPAL ===================== //
int main() {
    int opcion;
    do {
        cout << "\n--- Menú Sistema de Gestión de Procesos ---\n";
        cout << "1. Insertar Proceso\n2. Eliminar Proceso\n3. Buscar Proceso\n4. Modificar Prioridad\n5. Mostrar Procesos\n";
        cout << "6. Encolar Proceso CPU\n7. Ejecutar Proceso CPU\n8. Mostrar Cola CPU\n";
        cout << "9. Asignar Memoria\n10. Liberar Memoria\n11. Ver Memoria\n0. Salir\nOpción: ";
        cin >> opcion;

        int id, prio, bloque;
        string nombre;

        switch (opcion) {
            case 1:
                cout << "ID: "; cin >> id;
                cout << "Nombre: "; cin >> nombre;
                cout << "Prioridad: "; cin >> prio;
                insertarProceso(id, nombre, prio);
                break;
            case 2:
                cout << "ID a eliminar: "; cin >> id;
                eliminarProceso(id);
                break;
            case 3:
                cout << "ID a buscar: "; cin >> id;
                buscarProceso(id);
                break;
            case 4:
                cout << "ID a modificar: "; cin >> id;
                cout << "Nueva prioridad: "; cin >> prio;
                modificarPrioridad(id, prio);
                break;
            case 5:
                mostrarProcesos(); break;
            case 6:
                cout << "ID del proceso a encolar: "; cin >> id;
                // Copia temporal para encolar
                {
                    Proceso* temp = listaProcesos;
                    while (temp && temp->id != id) temp = temp->siguiente;
                    if (temp) encolarProceso(new Proceso(temp->id, temp->nombre, temp->prioridad));
                    else cout << "Proceso no encontrado en lista." << endl;
                }
                break;
            case 7:
                ejecutarProceso(); break;
            case 8:
                mostrarCola(); break;
            case 9:
                cout << "Bloque a asignar: "; cin >> bloque;
                asignarMemoria(bloque); break;
            case 10:
                liberarMemoria(); break;
            case 11:
                verMemoria(); break;
            case 0:
                cout << "Fin del programa.\n"; break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);

    return 0;
}

