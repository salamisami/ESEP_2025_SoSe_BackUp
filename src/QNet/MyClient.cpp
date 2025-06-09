#include <iostream>
#include <stdlib.h>
#include "Client.h"
using namespace std;

int main() {
	char sender = 's';
	system("gns -c");
	//SC::Client client = SC::Client();
	//return CN::Client::qnet_init(2, sender);
	Client client = Client();
	return client.qnet_init(2, sender);
}
