//Mohamed Samatar	4/21/16
//Uses templates to perform matrix operations
#include "defs.h"

int main(){
	matrix<double> a(0), b(0);
	string s, s2;
	do{
		cout << "Choose operation:\n1 = +, 2 = -, 3 = *, 4 = transpose, ENTER to quit: ";
		getline(cin, s);
		cout << endl;
		if(s == "1")
			cout << a + b;
		if(s == "2")
			cout << a - b;
		if(s == "3")
			cout << a * b;
		if(s == "4"){
			cout << "Transpose a or b? ";
			getline(cin, s2);
			if(s2 == "a") a.transpose();
			if(s2 == "b") b.transpose();
		}
	}while(s != "");
}