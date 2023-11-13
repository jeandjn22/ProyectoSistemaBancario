#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

void login();
void menu_cliente();
void menu();
void lista_clientes();
void buscar_clientes();
void buscar_cliente_num_cuenta();
void buscar_cliente_nombre();
void buscar_cliente_ci();
void suspender_cuenta();
void realizar_transferencia();
void deposito();
void retiro();

struct cuenta {
  string client;
  string ci;
  int account_number;
  string account_type;
  double balance;
};

//Funcion para Buscar los clientes
void buscar_clientes(){
    int opcion_buscar_clientes;
    do
    {
        cout<<"--------OPCIONES PARA BSUCAR AL CLIENTE---------"<<endl;
        cout<<"1. Buscar cliente por Numero de Cuenta: "<<endl;
        cout<<"2. Buscar cliente por Nombre: "<<endl;
        cout<<"3. Buscar cliente por Numero de Identificacion: "<<endl;
        cout<<"0. Regresar "<<endl;
        cout<<"Selecciona una opcion: "<<endl;
        cin>>opcion_buscar_clientes;

        switch(opcion_buscar_clientes){
            case 1: buscar_cliente_num_cuenta(); break;
            case 2: buscar_cliente_nombre(); break;
            case 3: buscar_cliente_ci(); break;
            case 0: cout<<" "<<endl; break;
            default: cout<<"Opcion incorrecta"<<endl;
        }
    }while(opcion_buscar_clientes!=0);
}

//Funcion para Buscar el Cliente por su Numero de Cuenta
void buscar_cliente_num_cuenta() {
    ifstream archivo("numeros.txt", ios::in);

    if (!archivo) {
        cout << "No se puede abrir el archivo" << endl;
    } else {
        string linea;
        string ci, client, account_number, account_type, suspend, balance;
        string numero_cuenta_buscar;

        cout << "Ingresa el numero de cuenta del cliente que desea buscar: ";
        cin >> numero_cuenta_buscar;

        bool numero_cuenta_existe = false;

        // Lee la primera línea (cabecera) y la descarta
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, ci, ',');
            getline(llave, client, ',');
            getline(llave, account_number, ',');
            getline(llave, account_type, ',');
            getline(llave, suspend, ',');
            getline(llave, balance, ',');

            if (numero_cuenta_buscar.compare(account_number) == 0) {
                numero_cuenta_existe = true;
                cout << "----------------------------------------------------" << endl;
                cout << "Id: " << ci << endl;
                cout << "Cliente: " << client << endl;
                cout << "Numero de cuenta: " << account_number << endl;
                cout << "Tipo de cuenta: " << account_type << endl;
                cout << "Suspender: " << suspend << endl;
                cout<<"Saldo Disponible: "<<balance<<endl;
                cout << "----------------------------------------------------" << endl;
            }
        }

        archivo.close();

        if (!numero_cuenta_existe) {
            cout << "El cliente con numero de cuenta: " << numero_cuenta_buscar << " no existe" << endl << endl;
        }
    }
}


//Funcion para buscar al cliente por su nombre
void buscar_cliente_nombre() {
    ifstream archivo("numeros.txt");
    if (!archivo) {
        cout << "No se puede abrir el archivo" << endl;
    } else {
        string linea;
        string ci, client, account_number, account_type, suspend, balance;
        string nombre_cliente_buscar;

        cout << "Ingrese el nombre completo del cliente a buscar: ";
        cin.ignore(); // Ignorar el salto de línea anterior
        getline(cin, nombre_cliente_buscar);

        bool nombre_encontrado = false;

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, ci, ',');
            getline(llave, client, ',');
            getline(llave, account_number, ',');
            getline(llave, account_type, ',');
            getline(llave, suspend, ',');
            getline(llave, balance, ',');
            

            if (nombre_cliente_buscar.compare(client)==0) { // Se compara el nombre ingresado con el nombre del cliente registrado para ver si existe
                nombre_encontrado = true;

                cout<<"----------------------------------------------------" << endl;
                cout<<"Id: " << ci << endl;
                cout<<"Cliente: " << client << endl;
                cout<<"Numero de cuenta: " << account_number << endl;
                cout<<"Tipo de cuenta: " << account_type << endl;
                cout<<"Estado de Cuenta: " << suspend << endl;
                cout<<"Saldo Disponible: "<<balance<<endl;
                cout << "----------------------------------------------------" << endl;
            }
        }
        archivo.close();
        if (!nombre_encontrado) { // Verificar si el nombre no se encontró
            cout << "El cliente con el nombre: " << nombre_cliente_buscar << " no existe" << endl << endl;
        }
    }
}

//Funcion para buscar al cliente por su numero de identificacion 
void buscar_cliente_ci() {
    ifstream archivo("numeros.txt", ios::in);

    if (!archivo) {
        cout<<"No se puede abrir el archivo"<<endl;
    } else {
        string linea;
        string ci, client, account_number, account_type, suspend, balance;
        string numero_cedula_buscar;

        cout<<"Ingresa el numero de identificacion del cliente que desea buscar: ";
        cin>>numero_cedula_buscar;

        bool numero_cedula_existe = false;

        // Lee la primera línea (cabecera) y la descarta
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, ci, ',');
            getline(llave, client, ',');
            getline(llave, account_number, ',');
            getline(llave, account_type, ',');
            getline(llave, suspend, ',');
            getline(llave, suspend, ',');

            if (numero_cedula_buscar.compare(ci) == 0) { //Compara el numero de identificacion ingresado, con el numero de indetificacion registrado
                numero_cedula_existe = true;
                cout<<"----------------------------------------------------" << endl;
                cout<<"Id: " << ci << endl;
                cout<<"Cliente: " << client << endl;
                cout<<"Numero de cuenta: " << account_number << endl;
                cout<<"Tipo de cuenta: " << account_type << endl;
                cout<<"Estado de Cuenta: " << suspend << endl;
                cout<<"Saldo Disponible: "<<balance<<endl;
                cout << "----------------------------------------------------" << endl;
            }
        }

        archivo.close();

        if (!numero_cedula_existe) { //En caso de que el numero de identificacion no exista
            cout << "El cliente con numero de identificacion: " << numero_cedula_buscar << " no existe" << endl << endl;
        }
    }
}


//Funcion para suspender cuenta a cliente
void suspender_cuenta() {
    //Se abre el archivo en modo lectura/escritura
    fstream archivo("numeros.txt", ios::in | ios::out);

    if (!archivo) {
        cout<< "Error al abrir el archivo" << endl;
    } else {
        string lineas;
        int contador = 0;
        string id, client, account_number, account_type, suspend, balance;
        string num_id_a_buscar;

        cout << "Ingrese el numero de identificacion del cliente a suspender: ";
        cin>>num_id_a_buscar;
        cout<<endl;

        // Crea un archivo temporal para almacenar las líneas modificadas
        ofstream archivo_temp("temp.txt");

        while (getline(archivo, lineas)) {
            stringstream llave(lineas);
            getline(llave, id, ',');
            getline(llave, client, ',');
            getline(llave, account_number, ',');
            getline(llave, account_type, ',');
            getline(llave, suspend, ',');
            getline(llave, balance, ',');

            if (num_id_a_buscar.compare(id) == 0) { //Comparamos el id ingresado con el id registrado para comprobar que exista
                cout<< contador << ". ID: " << id << endl;
                cout<<"Nombre del Cliente: " << client << endl;
                cout<<"Numero de Cuenta: " << account_number << endl;
                cout<<"Tipo de Cuenta: " << account_type << endl;
                cout<<"Estado actual: " << suspend << endl;
                cout<<"Saldo Disponible: "<<balance<<endl;
                cout << "Desea Suspender al Cliente? s/n : ";
                char opcion;
                cin >> opcion;

                if (opcion == 's') {
                    // Cambia el estado de la cuenta
                    if (suspend == "true") {
                        suspend = "false";
                    } else if (suspend == "false") {
                        suspend = "true";
                    }
                }
            }else{
                cout<<"Por favor corrija el numero de identificiacion ingresado ya que no pertenece a ningun cliente"<<endl;
            }

            // Escribe la línea en el archivo temporal
            archivo_temp << id << ',' << client << ',' << account_number << ',' << account_type << ',' << suspend << endl;
            contador++;
        }

        // Cierra los archivos
        archivo.close();
        archivo_temp.close();

        // Elimina el archivo original y renombra el archivo temporal
        remove("numeros.txt");
        rename("temp.txt", "numeros.txt");

        cout << "Operacion completada." << endl;
    }
}



void realizar_transferencia(){






}


void deposito(){





}



void retiro(){





}


void lista_clientes() {
    ifstream archivo("numeros.txt", ios::in);

    if (!archivo) {
        cout<<"No se puede abrir el archivo"<<endl;
    } else {
        string linea;
        string ci, client, account_number, account_type, suspend, balance;

        // Lee la primera línea (cabecera) y la descarta
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, ci, ',');
            getline(llave, client, ',');
            getline(llave, account_number, ',');
            getline(llave, account_type, ',');
            getline(llave, suspend, ',');
            getline(llave, balance, ',');


            cout << "----------------------------------------------------" << endl;
            cout << "Id: " << ci << endl;
            cout << "Cliente: " << client << endl;
            cout << "Numero de cuenta: " << account_number << endl;
            cout << "Tipo de cuenta: " << account_type << endl;
            cout << "Estado de Cuenta: " << suspend << endl;
            cout<<"Saldo Disponible: "<<balance<<endl;
            cout << "----------------------------------------------------" << endl;
        }

        archivo.close();
    }
}



void menu(){
    int opcion;
    do
    {
        cout<<"--------MENU---------"<<endl;
        cout<<"1. Visualizar Lista De Clientes "<<endl;
        cout<<"2. Buscar Clientes "<<endl;
        cout<<"3. Suspender cuenta a cliente "<<endl;
        cout<<"4. Realizar Transferencia a Cliente "<<endl;
        cout<<"5. Deposito o Retiro" <<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Selecciona una opcion: "<<endl;
        cin>>opcion;

        switch(opcion){
            case 1: lista_clientes(); break;
            case 2: buscar_clientes(); break;
            case 3: suspender_cuenta(); break;
            case 4: break;
            case 5: break;
            case 0: cout<<"GRACIAS POR USAR EL PROGRAMA!"<<endl; break;
            default: cout<<"Opcion incorrecta"<<endl;
        }
    }while(opcion!=0);
    
}

int main() {
    
    menu();
    return 0;
}






