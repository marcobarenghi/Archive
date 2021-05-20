#ifndef _particle_h_
#define _particle_h_
class particle {
public:
	particle(double massa,double carica);
	~particle();
	double getmass() const;
	double getcharge() const;
	void setcharge (double);
	virtual void print () const;
protected:
	double m_mass;
	double m_charge;
};
#endif
