#include <iostream>
#include <string>

using namespace std;

enum Color{verde, amarrillo, naranja, rojo};
enum comparacion{Menorque, Mayorque, Igualque};

struct Chiles {

    string nombre;
    int SHU;
    Color color;

};
typedef Chiles T;

struct Nodo {

    T information;
    struct Nodo *izq;
    struct Nodo *der;
};
typedef struct Nodo *Arbol;

Chiles SolicitarDatos();
void ShowData(Chiles);
bool Compare(Chiles, comparacion, Chiles);
Arbol CrearArbol(T);
void AsignarIzq(Arbol, T);
void AsignarDer(Arbol, T);
void AgregarNodo(Arbol);
void InOrder(Arbol);
void PreOrder(Arbol);
void PostOrder(Arbol);

int main(){

    cout << "\n\tInicializando Arbol..." << endl;
    Arbol arbol = CrearArbol(SolicitarDatos());

    bool status = true;
    int opcion = 0;

    while (status) {

        cout << endl;
        cout << "\tScoville Menu" << endl << endl;
        cout << "1) Agregar pimiento" << endl;
        cout << "2) Recorrer In-Order" << endl;
        cout << "3) Recorrer Pre-Order, mostrando solo los de color rojo" << endl;
        cout << "4) Recorrer Post-Order, mostrando los que tienen mas de 50,000 SHU" << endl;
        cout << "5) Salir del programa" << endl;

        cout << "\nIngrese su opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {

            case 1: AgregarNodo(arbol); break;
            case 2: 
                cout << "\nRecorriendo el arbol In-Order..." << endl;
                InOrder(arbol); 
            break;
            case 3: 
                cout << "\nRecorriendo el arbol Pre-Order y mostrando solo los pimientos de color rojo..." << endl;
                PreOrder(arbol);
            break;
            case 4: 
                cout << "\nRecorriendo el arbol Post-Order y mostrando solo los pimientos con SHU mayor a 50,000..." << endl;;
                PostOrder(arbol);
            break;
            case 5: status = false; cout << "\nFin del Programa, Adios Vaquero..." << endl << endl; break;
            default: cout << "\nEsa opcion no existe :(" << endl << endl; break; 
        }
    }
    return 0;
}

Chiles SolicitarDatos(){

    Chiles chile;

    cout << "\nIngrese el nombre del pimiento: ";
    getline(cin, chile.nombre);

    do {
        cout << "Ingrese el SHU (Scoville Heat Units) del pimiento: ";
        cin >> chile.SHU;
    }while(chile.SHU < 0);

    cout << "\nColor del pimiento: " << endl;

    int option;
    cout << "\n1) Verde" << endl;
    cout << "2) Amarrillo" << endl;
    cout << "3) Naranja" << endl;
    cout << "4) Rojo" << endl;

    cout << "\nIngrese su opcion: ";
    cin >> option;

    switch (option) {

        case 1:
            chile.color = verde;
        break;
        case 2:
            chile.color = amarrillo;
        break;
        case 3:
            chile.color = naranja;
        break;
        case 4:
            chile.color = rojo;
        break;
        default: cout << "\nEsa opcion no existe..." << endl; break;

    }
    cin.ignore();
    return chile;
}

void ShowData(Chiles chile) {

    cout << "\nNombre: " << chile.nombre << endl;
    cout << "SHU: " << chile.SHU << endl;
    cout << "Color: ";

    switch (chile.color) {
        case verde: cout << "Verde" << endl; break;
        case amarrillo: cout << "Amarillo" << endl; break;
        case naranja: cout << "Naranja" << endl; break;
        case rojo: cout << "Rojo" << endl; break; 
    }  
}

bool compare(Chiles c1, comparacion op, Chiles c2) {

    bool resultado = false;

    switch (op) {
        case Menorque: resultado = c1.SHU < c2.SHU; break;
        case Mayorque: resultado = c1.SHU > c2.SHU; break;
        case Igualque: resultado = c1.SHU == c2.SHU; break;
    }
    return resultado;
}

Arbol CrearArbol(T x) {

    Arbol hijo = new Nodo;
    hijo->information = x;
    hijo->izq = NULL;
    hijo->der = NULL;
    return hijo;
}

void AsignarIzq(Arbol a, T x) {

    if (a == NULL) {
        cout << "\nEl arbol se encuentra vacio :(" << endl;
    }
    else if (a->izq) {
        cout << "\nYa existe un subarbol izquierdo" << endl;
    }
    else {
        a->izq = CrearArbol(x);
    }
}

void AsignarDer(Arbol a, T x) {

    if (a == NULL) {
        cout << "\nEl arbol se encuentra vacio :(" << endl;
    }
    else if (a->der) {
        cout << "\nYa existe un subarbol derecho" << endl;
    }
    else {
        a->der = CrearArbol(x);
    }
}

void AgregarNodo(Arbol a) {

    cout << "\nPimiento a agregar..." << endl;

    T x = SolicitarDatos();

    Arbol temp = a;

    while (true) {
        if (compare(x, Igualque, temp->information)) {
            cout << "\nEl dato que usted desea ingresar ya existe, sry :(" << endl;
            return;
        }
        else if (compare(x, Menorque, temp->information)) {
            if (temp->izq == NULL) {
                break;
            }
            else {
                temp = temp->izq;
            }
        }
        else {
            if (temp->der == NULL) {
                break;
            }
            else {
                temp = temp->der;
            }
        }
    }
    if (compare(x, Menorque, temp->information)) {
        AsignarIzq(temp, x);
    }
    else {
        AsignarDer(temp, x);
    }
}

void InOrder(Arbol a) {

    if (a != NULL) {

        InOrder(a->izq);
        ShowData(a->information);
        InOrder(a->der);
    }
}

void PreOrder(Arbol a) {

    if (a != NULL) {
        if (a->information.color == rojo) {
            ShowData(a->information);
        }
        PreOrder(a->izq);   
        PreOrder(a->der);
    }
}

void PostOrder(Arbol a) {

    if (a != NULL) {
        PostOrder(a->izq);
        PostOrder(a->der);
        if (a->information.SHU > 50000) {
            ShowData(a->information);
        }
    }
}