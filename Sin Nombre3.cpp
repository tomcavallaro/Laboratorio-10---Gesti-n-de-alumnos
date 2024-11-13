#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct estudiante{
    int id;
    string nombre;
    int nota;
};

void agregarestudiante();
void mostrarestudiantes();
void actualizarestudiante();
void elimiarestudiante();

void agregarestudiante(){
    estudiante e;
    
    srand(time(0)); 
    e.id = 1000 + rand() % 9999; 
    cout << "ID generado automáticamente: " << e.id << endl;

    cin.ignore(); 
    cout << "Ingrese el nombre completo del nuevo estudiante: ";
    getline(cin, e.nombre);
    cout << "Ingrese la nota del estudiante: ";
    cin >> e.nota;


    ofstream estudiantes("estudiantes.txt", ios::app);
    if (estudiantes.fail()) {
        cout << "Error de apertura de archivo\n" << endl;
        return;
    }


    estudiantes << e.id << endl;
    estudiantes << e.nombre << endl;
    estudiantes << e.nota << endl;
    
    estudiantes.close();

    cout << "Estudiante ingresado correctamente\n" << endl;
}

void mostrarestudiantes(){
    ifstream estudiantes("estudiantes.txt");
    if (estudiantes.fail()) {
        cout << "Error de apertura de archivo estudiantes\n" << endl;
        return;
    }

    cout << "Listado de estudiantes:\n";
    estudiante e;
    while (estudiantes >> e.id) {
        estudiantes.ignore();  // Para limpiar el buffer después de leer el ID
        getline(estudiantes, e.nombre);
        estudiantes >> e.nota;
        estudiantes.ignore();  

        // Mostrar los datos del estudiante
        cout << "ID: " << e.id << ", Nombre: " << e.nombre << ", Nota: " << e.nota << endl;
    }
    estudiantes.close();
}

void actualizarestudiante(){
    ifstream estudiantes("estudiantes.txt");
    if(estudiantes.fail()){
        cout << "Error de apertura de archivo estudiantes\n" << endl;
        return;
    }

    ofstream temp("temp.txt");
    if(temp.fail()){
        cout << "No se pudo crear el archivo temporal\n" << endl;
        estudiantes.close();
        return;
    }

    int idBuscar;
    string nuevoNombre;
    int nuevaNota;
    
    cout << "Ingrese el ID del alumno que desea actualizar: ";
    cin >> idBuscar;
    cin.ignore();
    cout << "Ingrese el nuevo nombre: ";
    getline(cin, nuevoNombre);
    cout << "Ingrese la nueva nota: ";
    cin >> nuevaNota;

    estudiante e;
    bool encontraralumno = false;

    // Leer todo el archivo original
    while (estudiantes >> e.id) {
        estudiantes.ignore();  // Limpiar el buffer
        getline(estudiantes, e.nombre);
        estudiantes >> e.nota;
        estudiantes.ignore();  // Limpiar el buffer después de leer la nota

        // Si encontramos el alumno por ID, actualizamos sus datos
        if (e.id == idBuscar) {
            e.nombre = nuevoNombre;
            e.nota = nuevaNota;
            encontraralumno = true;
        }

        // Escribir los datos (actualizados o no) al archivo temporal
        temp << e.id << endl << e.nombre << endl << e.nota << endl;
    }

    estudiantes.close();
    temp.close();

    // Si encontramos al estudiante y lo actualizamos, reemplazamos el archivo original
    if (encontraralumno) {
        remove("estudiantes.txt");
        rename("temp.txt", "estudiantes.txt");
        cout << "Estudiante actualizado correctamente\n" << endl;
    } else {
        remove("temp.txt");
        cout << "No se encontró al alumno con ID " << idBuscar << endl;
    }
}

void eliminarestudiante(){

	    ifstream estudiantes("estudiantes.txt");
    if(estudiantes.fail()){
        cout << "Error de apertura de archivo estudiantes\n" << endl;
        return;
    }

    ofstream temp("temp.txt");
    if(temp.fail()){
        cout << "No se pudo crear el archivo temporal\n" << endl;
        estudiantes.close();
        return;
    }

int idEliminar;
bool encontrado=false;    
estudiante e;

cout << "ingrese el id del alumno que quiere eliminar" << endl;
cin >> idEliminar;

while ( estudiantes >> e.id >> e.nombre >> e.nota){
	if(e.id==idEliminar){
		encontrado = true;
	}else{
		temp << e.id << " " << e.nombre << " " << e.nota << endl;
	}
}
estudiantes.close();
temp.close();
if(encontrado){
	remove("estudiantes.txt");
	rename("temp.txt", "estudiantes.txt");
	cout<<"Estudiante eliminado correctamente"<<endl;
	}
	else{
		remove("temp.txt");
			cout<<"No se encotro ningun alumno con ese ID"<<idEliminar<<endl;
		}
}


int main(){
    int opcion;
    
    do {
        cout << "     --- MENU ---" << endl;
        cout << "1 - Agregar estudiante" << endl;
        cout << "2 - Mostrar todos los estudiantes" << endl;
        cout << "3 - Actualizar estudiante" << endl;
        cout << "4 - Eliminar estudiante" << endl;
        cout << "5 - Salir" << endl;
        cout << endl;
        cout << "Ingrese la opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1:
                agregarestudiante();
                break;
            case 2:
                mostrarestudiantes();
                break;
            case 3:
                actualizarestudiante();
                break;
            case 4:
				eliminarestudiante();
                break;
            case 5:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción incorrecta. Intente de nuevo." << endl;
        }
    } while(opcion != 5);

    return 0;
}

