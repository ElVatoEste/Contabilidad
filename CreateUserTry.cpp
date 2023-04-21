#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <conio.h>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <windows.h>

using namespace std;

struct Node {
public:
    double value;
    string name;
    string date;
    Node* next;
};

double value;
double total_v;
double inv_i;
double mercad;
double val_temp;
int trys = 0;

char date[11];

string datos[] = {
        "Ventas",
        "Devolucion de ventas",
        "Rebaja sobre ventas",
        "Descuentos sobre ventas",
        "Inventario inicial",
        "Compras",
        "Gastos sobre compras",
        "Devolucion sobre compras",
        "Rebaja sobre compras",
        "Descuentos sobre compras",
        "Inventario final",
        "Gastos administrativos",
        "Gastos de ventas",
        "Gastos financieros",
        "Otros gastos",
        "Otros ingresos"
    	};

class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    void add(const string& name, double value) {
        Node* newNode = new Node();
        newNode->name = name;
        newNode->value = value;
        newNode->next = head;
        head = newNode;
    }

	/*
    void printList() {
        Node* currentNode = head;
        while (currentNode != nullptr) { 
            cout << currentNode->name << " = C$ " << currentNode->value << endl;
            currentNode = currentNode->next;
        }
    }
    */
    
    void printReverse(Node* currentNode) {
    if (currentNode == nullptr) {
        return;
    }
    printReverse(currentNode->next);
    Sleep(100);
    cout << "\t";
    cout << currentNode->name << " = C$ " << currentNode->value << endl;
	}
	
	void printReverseList() {
    printReverse(head);
	}

    
    void saveList(const string& fileName) {
        ofstream outFile(fileName, ios_base::app);

        Node* currentNode = head;
        while (currentNode != nullptr) {
            outFile << currentNode->name << " = C$ " << currentNode->value << endl;
            currentNode = currentNode->next;
        }

        outFile.close();
    }

private:
    Node* head;
};

struct User {
    string username; 
    string password;
};

void saveUsers(list<User*> users) {
    ofstream file("user.txt");
    for (auto user : users) {
        file << user->username << "," << user->password << endl;
    }
    file.close();
}

list<User*> loadUsers() {
    list<User*> users;
    ifstream file("user.txt");
    string line;
    while (getline(file, line)) {
        string username = line.substr(0, line.find(","));
        string password = line.substr(line.find(",") + 1);
        User* user = new User{username, password};
        users.push_back(user);
    }
    file.close();
    return users;
}

bool validateUser(list<User*> users, string username, string password) {
    for (auto user : users) {
        if (user->username == username && user->password == password) {
            return true;
        }
    }
    return false;
}

void createUser(list<User*> &users) {
    string username, password;
    cout << "\n\tIngrese el nombre de usuario: ";
    cin >> username;
    cout << "\n\tIngrese la clave: ";
    password = "";
    char c;
    while ((c = _getch()) != 13) { // 13 es el código ASCII de la tecla Enter
        if (c == '\b') { // \b es el código ASCII de la tecla Retroceso
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Borra el último caracter en la consola
            }
        } else {
            password += c;
            cout << "*";
        }
    }
    User* newUser = new User{username, password};
    users.push_back(newUser);
    saveUsers(users);
    cout << endl << "\n\tUsuario creado exitosamente" << endl;
    Sleep(1500);
}

int main() {
	
	time_t time_now = time(nullptr);
	strftime(date, 4, "%b", localtime(&time_now));
	
	string fileName = "datos_" + string(date) + ".txt";
	string fileName2 = "estadoR_" + string(date) + ".txt";
	
	inicia_Menu:
	system("cls");
	
    list<User*> users = loadUsers();
    string username, password;
    cout << "\n\tIngrese usuario: ";
    cin >> username;
    cout << "\n\tIngrese la clave: ";
    password = "";
    char c;
    while ((c = _getch()) != 13) {
        if (c == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += c;
            cout << "*";
        }
    }
    cout << endl;
    if (username == "Admin" && password == "IvanHacker00") {
        cout << "\n\tInicio de sesion exitoso como administrador!" << endl;
        Sleep(500);
        
        createUser(users);
        
        goto inicia_Menu;
        
    } else if (validateUser(users, username, password)) {
        cout << "\n\tInicio de sesion exitoso!" << endl;
        
        	Sleep(1500);
        	system("cls");
        
		    LinkedList list1;
		    LinkedList list2;
		
		    // Obtener la fecha actual y darle formato
		    
		
		    // Pedir los datos al usuario y agregarlos a la lista
		    for (int i = 0 ; i < 4; i++) {
		    	
		        cout << "\n\tIngrese el valor de " << datos[i] << " C$ ";
		        cin >> value;
		        
		        if (i == 0){
					total_v = value;
				}
				else{
					total_v = total_v - value;
				}
		        
		        list1.add(datos[i], value);
		    }
			
			list2.add("Ventas netas", total_v);
			
			cout << "\n\tIngrese el valor de " << datos[4] << " C$ ";
		    cin >> value;
		    inv_i = value;
		    list1.add(datos[4], value);
			
			for (int i = 5 ; i < 7; i++) {
		    	
		        cout << "\n\tIngrese el valor de " << datos[i] << " C$ ";
		        cin >> value;
		        
				val_temp = val_temp + value;
		        list1.add(datos[i], value);
		    }
		    
		    list2.add("Compras totales", val_temp);
		    
		    for (int i = 7 ; i < 10; i++) {
		    	
		        cout << "\n\tIngrese el valor de " << datos[i] << " C$ ";
		        cin >> value;
		        
				val_temp = val_temp - value;
		        list1.add(datos[i], value);
		    }
		    
		    mercad = inv_i + val_temp ;
		    
		    list2.add("Compras netas", val_temp);
		    
		    list1.add("Mercaderia disponible", mercad);
		    
		    cout << "\n\tIngrese el valor de " << datos[10] << " C$ ";
		    cin >> value ;
		    list1.add(datos[10], value);
		    
		    float cost_v = mercad - value;
		    float ult_brut = total_v - cost_v;
		    
		    list2.add("Costos de venta", cost_v); 
		    list2.add("Utilidad bruta", ult_brut);
		    
		    float ult_tot = ult_brut;
		    
		    for (int i = 11 ; i < 15; i++) {
		    	
		        cout << "\n\tIngrese el valor de " << datos[i] << " C$ ";
		        cin >> value;
		        
				ult_tot = ult_tot - value;
		        list1.add(datos[i], value);
		    }
		    
		    cout << "\n\tIngrese el valor de " << datos[15] << " C$ ";
		    cin >> value;
		        
			ult_tot = ult_tot + value;
		    list1.add(datos[15], value);
		    
		    double i_r = ult_tot * 0.30;
		    double total = ult_tot - i_r;
		    
		    list1.add("IR 30%", i_r);
		    list2.add("Utilidad/Perdida", total);
		    
		    
		    // Guardar la lista en un archivo y mostrarla en la consola
		    
		    list1.saveList(fileName);
		    list2.saveList(fileName2);
		    
		    cout<<"\n\n\t";
		    string frase = "Los datos han sido ingresados correctamente";
        	Sleep(1000);
    		for (int i = 0; i < frase.size(); i++) {
		        cout << frase[i];
		        Sleep(50); // Esperar 500 milisegundos
		    	}
		    
		    Sleep(1500);
		    system("cls");
		    cout <<"\n";
			list1.printReverseList();
		    cout <<"\n";
		    list2.printReverseList();

        // Aquí va el código para el menú del programa
    } else {
        cout << "\n\tUsuario o la clave son incorrectos" << endl;
        trys = trys + 1;
        
        Sleep(1500);
        
        if (trys == 3){
        	system("cls");
        	cout << "\n\tUsted a excedido el numero de intentos\n\t";
        	string frase = "Pum pa casa";
        	Sleep(1000);
    		for (int i = 0; i < frase.size(); i++) {
		        cout << frase[i];
		        Sleep(200); // Esperar 500 milisegundos
		    	}
		    exit(0);
		}
		else{
			goto inicia_Menu;
		}
        
        
    }
    return 0;
}
