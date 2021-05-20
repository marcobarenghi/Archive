#include<iostream>
#include<cstring>
#include"particle.h"
#include"astrobody.h"
using namespace std;

int main(){
	
	cout << "Creating particle and printing information" << endl;
	particle one = particle(1,2);
	one.print();
	cout << "-----------------------------------------------" << endl << endl;

	cout << "Creating first Astronomical body" << endl;
	double moonDistance = 3.84e8;
	astrobody two =astrobody("Earth",5.97e24,6.4e6,moonDistance);
	two.print();
	cout << endl;
	
	cout << "Since astrobody inherits particle, I can set its charge and print it" << endl;
	two.setcharge(0);
	cout <<  two.getname() << "'s charge = " << two.getcharge() << endl;
	
	cout << "Creating second Astronomical body" << endl;
	double earthDistance = 1.5e11;
	astrobody*three = new astrobody("Sun",1.99e30,0.69e9,earthDistance);
	three->print();
	cout << "-----------------------------------------------" << endl << endl;
	
	cout << "Quick test for get and set methods of astrobody" << endl;
	two.setmass(0.);
	cout << "Set wrong Earth mass: " << two.getmass() << endl;
	two.setmass(5.97e24);
	cout << "Back to normal" << endl;
	two.print();
	 
	return 0;
}
