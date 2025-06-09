#include <iostream>
#include <stdlib.h>
#include "Server.h"
using namespace std;

int main() {
//	cout << "Hello World!!!" << endl; // prints Hello World!!!
//	return 0;
	char reciever = 'r';
	system("gns -s");
	//SC::Server server = SC::Server();
	Server server = Server();
	return server.qnet_init(2, reciever);
}
