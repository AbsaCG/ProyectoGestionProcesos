#include <iostream>
#include <string>
using namespace std;

// Estructura que representa a una persona en el árbol genealógico
struct Nodo {
    int id;             // Identificador unico de la persona
    string nombre;      // Nombre de la persona
    Nodo* izq;          // Puntero al hijo izquierdo
    Nodo* der;          // Puntero al hijo derecho
    Nodo* padre;        // Puntero hacia el padre de la persona
};

// Funcion para crear un nuevo nodo con nombre y ID
Nodo* crearNodo(int id, string nombre) {
    Nodo* nuevo = new Nodo();       // Reserva espacio en memoria
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->izq = NULL;              // No tiene hijo izquierdo 
    nuevo->der = NULL;              // No tiene hijo derecho 
    nuevo->padre = NULL;            // Tampoco tiene padre asignado 
    return nuevo;
}

// Buscar una persona en el arbol por su ID
Nodo* buscarPorID(Nodo* raiz, int id) {
    if (raiz == NULL) return NULL;  // Si el arbol esta vacio, no hay nada que buscar
    if (raiz->id == id) return raiz;  // Si se encontró el ID, se devuelve el nodo

    // Buscar en el hijo izquierdo
    Nodo* encontrado = buscarPorID(raiz->izq, id);
    if (encontrado != NULL) return encontrado;

    // Si no esta en el izquierdo, buscar en el derecho
    return buscarPorID(raiz->der, id);
}

// Función para insertar un nuevo hijo a un padre ya registrado
void insertarHijo(Nodo* padre, int id, string nombre) {
    Nodo* hijo = crearNodo(id, nombre);  // Crear nuevo hijo
    hijo->padre = padre;                 // Se le asigna su padre

    // Verificamos si hay espacio para agregar como hijo izquierdo o derecho
    if (padre->izq == NULL)
        padre->izq = hijo;               // Si el izquierdo esta vacio, lo ponemos ahi
    else if (padre->der == NULL)
        padre->der = hijo;               // Si el derecho esta vacio, va ahi
    else
        cout << "Esta persona ya tiene dos descendientes.\n";
}

// Mostrar el arbol de forma visual, girado hacia la izquierda
void mostrarArbol(Nodo* raiz, int espacio = 0, int separacion = 5) {
    if (raiz == NULL) return;

    espacio += separacion;  // Aumentamos espacio para mostrar el siguiente nivel

    // Mostrar el subarbol derecho primero
    mostrarArbol(raiz->der, espacio);

    // Imprimir el nodo actual con sangria
    cout << endl;
    for (int i = separacion; i < espacio; i++) cout << " ";
    cout << "(" << raiz->id << ") " << raiz->nombre << "\n";

    // Luego mostrar el subárbol izquierdo
    mostrarArbol(raiz->izq, espacio);
}

// Mostrar relaciones familiares directas
void mostrarRelacion(Nodo* persona) {
    if (persona == NULL) return;

    // Mostrar datos de la persona
    cout << "Nombre: " << persona->nombre << " (ID: " << persona->id << ")\n";

    // Mostrar su padre
    if (persona->padre != NULL)
        cout << "Padre: " << persona->padre->nombre << " (ID: " << persona->padre->id << ")\n";
    else
        cout << "No tiene padre registrado (es raíz).\n";

    // Mostrar sus hijos si tiene
    if (persona->izq != NULL)
        cout << "Hijo izquierdo: " << persona->izq->nombre << " (ID: " << persona->izq->id << ")\n";
    if (persona->der != NULL)
        cout << "Hijo derecho: " << persona->der->nombre << " (ID: " << persona->der->id << ")\n";
    if (persona->izq == NULL && persona->der == NULL)
        cout << "No tiene hijos registrados.\n";
}

// Programa principal
int main() {
    Nodo* raiz = NULL;        // Aqui guardamos al ancestro principal (el primero)
    int opcion, id, idPadre;  // Variables para menu e ingreso de datos
    string nombre;

    do {
        // Menu de opciones
        cout << "\n--- MENU GENEALOGICO  ---\n";
        cout << "1. Ingresar ancestro principal\n";
        cout << "2. Insertar descendiente\n";
        cout << "3. Mostrar arbol\n";
        cout << "4. Mostrar ancestros por ID\n";
        cout << "5. Mostrar descendientes por ID\n";
        cout << "6. Mostrar relaciones familiares\n";
        cout << "7. Recorrido Preorden\n";
        cout << "8. Recorrido Inorden\n";
        cout << "9. Recorrido Postorden\n";
        cout << "10. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: // Opcion para crear al ancestro principal
                if (raiz != NULL) {
                    cout << "Ya hay un ancestro registrado.\n";
                    break;
                }
                cout << "ID del ancestro: ";
                cin >> id;
                cout << "Nombre del ancestro: ";
                cin.ignore();              // Limpiar buffer del Enter
                getline(cin, nombre);      // Leer nombre completo
                raiz = crearNodo(id, nombre);
                cout << "Ancestro agregado.\n";
                break;

            case 2: // Insertar un descendiente
                cout << "ID del padre existente: ";
                cin >> idPadre;
                cout << "ID del descendiente: ";
                cin >> id;
                cout << "Nombre del descendiente: ";
                cin.ignore();
                getline(cin, nombre);
                {
                    Nodo* padreNodo = buscarPorID(raiz, idPadre);
                    if (padreNodo != NULL)
                        insertarHijo(padreNodo, id, nombre);
                    else
                        cout << "No se encontro ese ID en el arbol.\n";
                }
                break;

            case 3: // Mostrar arbol completo
                cout << "\n--- Arbol genealogico ---\n";
                mostrarArbol(raiz);
                break;

            case 4: // Mostrar ancestros
                cout << "Ingrese ID de la persona: ";
                cin >> id;
                {
                    Nodo* p = buscarPorID(raiz, id);
                    if (p != NULL) {
                        cout << "Ancestros de (" << id << ") " << p->nombre << ":";
                        mostrarAncestros(p);
                    } else {
                        cout << "Persona no encontrada.\n";
                    }
                }
                break;

            case 5: // Mostrar descendientes
                cout << "Ingrese ID de la persona: ";
                cin >> id;
                {
                    Nodo* p = buscarPorID(raiz, id);
                    if (p != NULL)
                        mostrarDescendientes(p);
                    else
                        cout << "Persona no encontrada.\n";
                }
                break;

            case 6: // Mostrar relaciones familiares
                cout << "Ingrese ID de la persona: ";
                cin >> id;
                {
                    Nodo* p = buscarPorID(raiz, id);
                    if (p != NULL)
                        mostrarRelacion(p);
                    else
                        cout << "Persona no encontrada.\n";
                }
                break;

            case 7: // Preorden
                cout << "\n--- Recorrido Preorden ---\n";
                preorden(raiz);
                cout << "\n";
                break;

            case 8: // Inorden
                cout << "\n--- Recorrido Inorden ---\n";
                inorden(raiz);
                cout << "\n";
                break;

            case 9: // Postorden
                cout << "\n--- Recorrido Postorden ---\n";
                postorden(raiz);
                cout << "\n";
                break;

            case 10: // Salir del programa
                cout << "Saliendo del programa.\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 10);  // El menú se repite hasta que el usuario elija salir

    return 0;
}

