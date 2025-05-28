/*

template <typename T>
MyArray<T>::MyArray()
	: m_data{ nullptr }
	, m_size{ 0 }
	, m_capacity{ 0 }
{
}

template <typename T>
MyArray<T>::~MyArray()
{
	Clear();
	::operator delete[](m_data);
}

template <typename T>
MyArray<T>::MyArray(const MyArray& other)
	: m_data{ nullptr }
	, m_size{ 0 }
	, m_capacity{ 0 }
{
	Reserve(other.m_capacity);
	for (size_t i = 0; i < other.m_size; ++i)
	{
		new (m_data + i) T(other.m_data[i]); //uninitialized copy[n]
		++m_size;
	}
}

template <typename T>
MyArray<T>::MyArray(MyArray&& other)
	: m_data{ other.m_data }
	, m_size{ other.m_size }
	, m_capacity{ other.m_capacity }
{
	other.m_data = nullptr;
	other.m_size = 0;
	other.m_capacity = 0;
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(const MyArray& other)
{
	if (this != &other)
	{
		MyArray temp(other);
		swap(temp);
	}

	return *this;
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(MyArray&& other)
{
	if (this != &other)
	{
		Clear();
		m_capacity = 0;
		::operator delete[](m_data);
		swap(other);
	}
	return *this;
}

template <typename T>
void MyArray<T>::Reserve(const size_t& capacity)
{
	if (m_capacity <= capacity)
		return;

	size_t newCapacity = std::max(capacity, m_capacity * 2);
	T* newData = nullptr;

	try
	{
		newData = static_cast<T*>(::operator new[](sizeof(T) * (newCapacity + 1))); //reinterpret_cast
	}
	catch (...)
	{
		::operator delete[](newData);
		throw;
	}

	for (size_t i = 0; i < m_size; ++i)
	{
		new (newData + i) T(std::move(m_data[i])); 
	}
	for (size_t i = 0; i < m_size; ++i)
	{
		m_data[i].~T();
	}
	::operator delete[](m_data);
	m_data = newData;
	m_capacity = newCapacity;
}

template <typename T>
void MyArray<T>::PushBack(const T& element) //rvalue refference
{
	if (m_size == m_capacity)
	{
		Reserve(m_size + 1);
	}
	new (m_data + m_size) T(element);
	++m_size;
}

template <typename T>
void MyArray<T>::Resize(size_t newSize)
{
	if (newSize > m_capacity)
	{
		Reserve(newSize);
	}
	if (newSize > m_size)
	{
		for (size_t i = m_size; i < newSize; ++i)  
		{
			new (m_data + i) T();
		}
	}
	else if (newSize < m_size)
	{
		while (m_size > newSize)
		{
			--m_size;
			m_data[m_size].~T();
		}
	}
}

template <typename T>
void MyArray<T>::Clear()
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_data[i].~T();
	}
	m_size = 0;
}

template <typename T>
T& MyArray<T>::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range\n");
	}

	return m_data[index];
}

template <typename T>
const T& MyArray<T>::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range\n");
	}

	return m_data[index];
}

template <typename T>
void MyArray<T>::swap(MyArray& other)
{
	std::swap(m_data, other.m_data);
	std::swap(m_capacity, other.m_capacity);
	std::swap(m_size, other.m_size);
}

template <typename T>
bool MyArray<T>::IsValidPointer(T* ptr) const
{
	return !(ptr == nullptr || ptr < m_data || ptr > m_data + m_size);
}

template <typename T>
size_t MyArray<T>::Size() const
{
	return m_size;
}

template <typename T>
MyArray<T>::Iterator::Iterator(pointer ptr, const MyArray* arrayPtr)


template <typename T>
MyArray<T>::Iterator::reference MyArray<T>::Iterator::operator*() const

template <typename T>
MyArray<T>::Iterator::pointer MyArray<T>::Iterator::operator->() const


template <typename T>
MyArray<T>::Iterator& MyArray<T>::Iterator::operator++()


template <typename T>
MyArray<T>::Iterator MyArray<T>::Iterator::operator++(int) //use prefix


template <typename T>
MyArray<T>::Iterator& MyArray<T>::Iterator::operator--()


template <typename T>
MyArray<T>::Iterator MyArray<T>::Iterator::operator--(int)


template <typename T>
MyArray<T>::Iterator MyArray<T>::Iterator::operator+(const difference_type& n)


template <typename T>
MyArray<T>::Iterator MyArray<T>::Iterator::operator-(const difference_type& n)


template <typename T>
MyArray<T>::Iterator::difference_type MyArray<T>::Iterator::operator-(const Iterator& other) const



template <typename T>


template <typename T>
MyArray<T>::Iterator MyArray<T>::begin() 

template <typename T>
MyArray<T>::ConstIterator MyArray<T>::begin() 

template <typename T>
MyArray<T>::ConstIterator MyArray<T>::cbegin() const 

template <typename T>
MyArray<T>::Iterator MyArray<T>::end() 

template <typename T>
MyArray<T>::ConstIterator MyArray<T>::end() const 

template <typename T>
MyArray<T>::ConstIterator MyArray<T>::cend() const 

template <typename T>
MyArray<T>::ReverseIterator MyArray<T>::rbegin() 

template <typename T>
MyArray<T>::ConstReverseIterator MyArray<T>::rbegin() const 

template <typename T>
MyArray<T>::ConstReverseIterator MyArray<T>::crbegin() const 

template <typename T>
MyArray<T>::ReverseIterator MyArray<T>::rend() 

template <typename T>
MyArray<T>::ConstReverseIterator MyArray<T>::rend() const 

template <typename T>
MyArray<T>::ConstReverseIterator MyArray<T>::crend() const
*/