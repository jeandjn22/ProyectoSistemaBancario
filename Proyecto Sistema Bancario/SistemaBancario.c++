#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

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


//Funcion para Buscar los clientes
void buscar_clientes(){
    int opcion_buscar_clientes;
    do
    {
        cout<<"--------OPCIONES PARA BUSCAR AL CLIENTE---------"<<endl;
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
    ifstream archivo("clients.csv", ios::in);

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
    ifstream archivo("clients.csv");
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
                cout<<"Numero de Identificacion: " << ci << endl;
                cout<<"Cliente: " << client << endl;
                cout<<"Numero de cuenta: " << account_number << endl;
                cout<<"Tipo de cuenta: " << account_type << endl;
                cout<<"Estado de Cuenta: " << suspend << endl;
                cout<<"Saldo Disponible: "<< balance <<endl;
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
    ifstream archivo("clients.csv", ios::in);

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
            getline(llave, balance, ',');

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
    // Se abre el archivo en modo lectura/escritura
    fstream archivo("clients.csv", ios::in | ios::out);

    if (!archivo) {
        cout << "Error al abrir el archivo" << endl;
    } else {
        string lineas;
        string ci, client, account_number, account_type, suspend, balance;
        string num_ci_a_buscar;

        cout << "Ingrese el numero de identificacion del cliente a suspender: ";
        cin >> num_ci_a_buscar;
        cout << endl;

        bool clienteEncontrado = false;

        while (getline(archivo, lineas)) {
            stringstream llave(lineas);
            getline(llave, ci, ',');
            getline(llave, client, ',');
            getline(llave, account_number, ',');
            getline(llave, account_type, ',');
            getline(llave, suspend, ',');
            getline(llave, balance, ',');

            if (num_ci_a_buscar.compare(ci) == 0) {
                clienteEncontrado = true;

                cout << "Numero de Identificacion: " << ci << endl;
                cout << "Nombre del Cliente: " << client << endl;
                cout << "Numero de Cuenta: " << account_number << endl;
                cout << "Tipo de Cuenta: " << account_type << endl;
                cout << "Estado actual: " << suspend << endl;
                cout << "Saldo Disponible: " << balance << endl;
                cout << "Desea Suspender al Cliente? s/n : ";
                char opcion;
                cin >> opcion;

                if (opcion == 's' || opcion == 'S') {
                    cout << endl;
                    cout << "Cliente Suspendido Correctamente!" << endl;

                    // Asegúrate de que "false " tiene la misma longitud que "true"
                    string nuevo_estado = "true ";
                    archivo.seekp(llave.tellg());
                    archivo.write(nuevo_estado.c_str(), nuevo_estado.size());

                    break;  // Termina el bucle ya que se encontró y suspendió al cliente
                } else {
                    cout << endl;
                    cout << "Operacion Cancelada!!" << endl;
                    return;
                }
            }
        }

        archivo.close();

        if (!clienteEncontrado) {
            cout << "El cliente no fue encontrado. Por favor, revisa el numero de identificacion." << endl;
        }
    }
}




void realizar_transferencia(){






}


void deposito(){





}



void retiro(){





}


void lista_clientes() {
    ifstream archivo("clients.csv", ios::in);

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



