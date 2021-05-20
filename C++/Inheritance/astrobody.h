#ifndef _astrobody_h_
#define _astrobody_h_
#include"particle.h"
class astrobody:public particle{
public:
	astrobody (std::string name, double mass, double radius,double distance);
	~astrobody();
	void setname(std::string);
	void setmass (double);
	void setradius (double);
	void setdistance (double);
	std::string getname() const;
	double getradius () const;
	double getdistance() const;
	double potential(double,double) const;
	virtual void print () const;
protected:
	std::string m_name;
	double m_radius;
	double m_distance;
};
#endif
