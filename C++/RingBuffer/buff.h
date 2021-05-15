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
	void Print(bool eta);
	T Get();
	int Capacity() const;
	int Size() const;

private:
	int m_capacity, m_currentSize, m_headPos;
	T* m_array;
	int *m_eta; //measures eta of all added elements -> needed to find m_headPos each time
};

template <typename T>
buffer<T>::buffer(){
	m_capacity = 0;
	m_currentSize = 0;
	m_headPos = 0;
	};

template <typename T>
buffer<T>::buffer(int num){
	m_array = new T[num];
	m_eta = new int[num];
	m_capacity = num;
	m_currentSize = 0;
	m_headPos = 0;
};

template <typename T>
buffer<T>::~buffer(){ 
	delete[] m_array;
	delete[] m_eta;
};

template <typename T>
void buffer<T>::Put(T add){	
	if (m_currentSize < m_capacity)
	{
		m_array[m_currentSize] = add;
		for (int i = 0; i < m_currentSize; i++)
		{
			m_eta[i]++;
		}
		
		int maxEta = -1;
		for (int i = 0; i < m_currentSize; i++)
		{
			if( maxEta < m_eta[i])
			{
				maxEta = m_eta[i];
				m_headPos = i;
			}
		}
		m_currentSize++;
		
	}
	else if (m_currentSize == m_capacity)
	{
		m_eta[m_headPos] = 0;
		m_array[m_headPos] = add;
		for (int i = 0; i < m_currentSize; i++)
		{
			if(i != m_headPos)
			{
			m_eta[i]++;
			}
		}
		
		int maxEta = -1;
		for (int i = 0; i < m_currentSize; i++)
		{
			if( maxEta < m_eta[i])
			{
				maxEta = m_eta[i];
				m_headPos = i;
			}
		}	
	}
}

template <typename T>
void buffer<T>::Print(bool printeta){
	if (m_currentSize == 0)
	{
		std::cout << "BUFFER IS EMPTY: CAN'T PRINT" << std::endl;
	}
	
	if (m_currentSize > 0 && printeta==false)
	{
		for (int i = 0; i < m_currentSize; i++)
		{
			std::cout << m_array[i] << " ";
		}
		std::cout << std::endl;
	}
	else if (m_currentSize > 0 && printeta==true)
	{

		for (int i = 0; i < m_currentSize; i++)
		{
			std::cout << m_array[i]  << " (" << m_eta[i] << ") ";
		}
		std::cout << std::endl;
	}
}

template <typename T>
T buffer<T>::Get(){	
	if (m_currentSize == 0)
	{
		std::cout << "Buffer is empty. Can't get value!" << std::endl;
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
    delete[] m_array;
    m_array = tmp_array;
    
    int *tmp_eta = new int();  
	int counttmpeta = 0;
    for (int i = 0; i < m_currentSize; i++)
    {
		if (i != m_headPos)
		{
			tmp_eta[counttmpeta] = m_eta[i];
			counttmpeta++;
		}
    }  
    delete[] m_eta;
    m_eta = tmp_eta;
	m_currentSize--;
	
	int maxEta = -1;
		for (int i = 0; i < m_currentSize; i++)
		{
			if( maxEta < m_eta[i])
			{
				maxEta = m_eta[i];
				m_headPos = i;
			}
		}
	
	return tmpVal;
}

template <typename T>
int buffer<T>::Capacity() const {return m_capacity;}

template <typename T>
int buffer<T>::Size() const {return m_currentSize;}

#endif //_buff_h_
