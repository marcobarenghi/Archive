#ifndef _buff_h_
#define _buff_h_
#include <climits>

template <typename T>
class buffer {
public:
	buffer();
	buffer(int num);
	~buffer();
	void Put(T add);
	void Print();
	T Get();
	int Capacity() const;
	int Size() const;

private:
	int m_capacity, m_currentSize, m_headPos;
	bool m_wasFull;
	T* m_array;
};

template <typename T>
buffer<T>::buffer(){
	m_capacity = 0;
	m_currentSize = 0;
	m_headPos = 0;
	m_wasFull = false;
	};

template <typename T>
buffer<T>::buffer(int num){
	m_array = new T[num];
	m_capacity = num;
	m_currentSize = 0;
	m_headPos = 0;
	m_wasFull = false;
};

template <typename T>
buffer<T>::~buffer(){ 
	delete[] m_array;
};

template <typename T>
void buffer<T>::Put(T add){	
	if (m_currentSize < m_capacity)
	{
		m_array[m_currentSize] = add;
		
		m_headPos = 0;
		m_currentSize++;
		
	}
	else if (m_currentSize == m_capacity)
	{
		m_wasFull = true;
		m_array[m_headPos] = add;
		if (m_headPos < m_capacity - 1)
			m_headPos++;
		else
			m_headPos = 0;
			
	}
}

template <typename T>
void buffer<T>::Print(){
	if (m_currentSize == 0)
		std::cout << "  Print(): empty buffer!" << std::endl;

	else
	{
		std::cout << "  ";
		for (int i = 0; i < m_currentSize; i++)
			std::cout << m_array[i] << " ";
		std::cout <<std::endl;
	}
}

template <typename T>
T buffer<T>::Get(){	
	if (m_currentSize == 0)
	{
		std::cout << "  Get(): WARNING! Buffer is empty. NULL value will be returned!" << std::endl;
		return {};
	}
		
	T tmpVal = m_array[m_headPos];
	T* tmp_array = new T[m_currentSize];
	int counttmp = 0;
    for (int i = 0; i < m_currentSize; i++)
    {
		if (i != m_headPos)
		{
			tmp_array[counttmp] = m_array[i];
			counttmp++;
		}
    }
    
    if (m_wasFull == true)
    {
		if (m_headPos == m_currentSize - 1)
			m_headPos = 0;

		m_wasFull = false;
	}
	else
		m_headPos = 0;
	
     
    delete[] m_array;
    m_array = tmp_array;   
	m_currentSize--;
	
	if (m_currentSize == 0)
		m_wasFull = false;

	return tmpVal;
}

template <typename T>
int buffer<T>::Capacity() const {return m_capacity;}

template <typename T>
int buffer<T>::Size() const {return m_currentSize;}

#endif //_buff_h_
