#ifndef _vect_h_
#define _vect_h_
class vect{
public:
	vect();
	vect(int, int);
	~vect();
	unsigned int getN() const;
	void mergeSorting();
	int linearSearch(int pos);
	int binarySearch(int pos);

private:
	unsigned int m_N;
	double*m_v;
};
#endif
