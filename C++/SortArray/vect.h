#ifndef _vect_h_
#define _vect_h_
class vect{
public:
	vect();
	vect(unsigned int, int seed);
	~vect();
	unsigned int getN() const;
	void print();
	void stdSorting();
	void mergeSorting();
private:
	unsigned int m_N;
	double*m_v;
};
#endif
