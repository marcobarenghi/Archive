#include<iostream>
#include"particle.h"
#include"astrobody.h"

astrobody::astrobody(std::string name,double massa,double radius,double distance):particle(massa,0){
	m_name=name;
	m_radius=radius;
	m_distance=distance;
}
astrobody::~astrobody() { }

void astrobody::setname (std::string name){
	m_name=name;
	return;
}
void astrobody::setmass (double mass){
	m_mass=mass;
	return;
}
void astrobody::setradius (double radius){
	m_radius=radius;
	return;
}
void astrobody::setdistance (double distance){
	m_distance=distance;
	return;
}
std::string astrobody::getname() const {
	return m_name;
}
double astrobody::getradius() const {
	return m_radius;
}
double astrobody::getdistance() const {
	return m_distance;
}
double astrobody::potential(double mass,double distance) const{
	return -6.67e-11*mass/distance;
}
void astrobody::print() const {
	std::cout<<"Astronomical body: name="<<m_name<<", m="<<m_mass<<", R="<<m_radius<<std::endl;
	std::cout<<"dist="<<m_distance<<", potential="<<potential(m_mass,m_distance)<<std::endl;
	return;
}
