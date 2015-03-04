#include "tinyxml/tinyxml.h"
#include <iostream>
#include "tinyxml/tinystr.h"
#include <string>
#include "board.cpp"

int main(){

	Board bordje("Speelveld1.0.xml");

	cout << bordje.Name << endl;
	
	cout << bordje << endl;
}
