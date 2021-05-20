#include"particle.h"
#include<iostream>

particle::particle(double mass, double charge){
	m_mass=mass;
	m_charge=charge;
}
particle::~particle() { }
double particle::getmass() const {
	return m_mass;
}
double particle::getcharge() const {
	return m_charge;
}

void particle::setcharge(double charge) {
	m_charge = charge;
}

void particle::print () const {
	std::cout<<"particle: m="<<m_mass<<", q="<<m_charge<<std::endl;
	return;
}
