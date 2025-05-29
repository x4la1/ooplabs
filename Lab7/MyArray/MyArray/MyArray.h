#pragma once
#include <algorithm>
#include <iterator>
#include <new>
#include <stdexcept>

template <typename T>
class MyArray
{
public:
	class Iterator
	{
	public:
		using iterator_category = std::contiguous_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		Iterator(pointer ptr, const MyArray* arrayPtr)
			: m_ptr{ ptr }
			, m_arrayPtr{ arrayPtr }
		{
			if (!(m_arrayPtr->IsValidPointer(ptr)))
			{
				throw std::out_of_range("Invalid pointer\n");
			}

			if (!arrayPtr)
			{
				throw std::out_of_range("Invalid array\n");
			}
		}

		reference operator*() const
		{
			return *m_ptr;
		}

		pointer operator->() const
		{
			return m_ptr;
		}

		Iterator& operator++()
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr + 1)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}
			++m_ptr;
			return *this;
		}

		Iterator operator++(int)
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr + 1)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}

			Iterator temp = *this;
			++(*this);
			return temp;
		}

		Iterator& operator--()
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr - 1)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}

			--m_ptr;
			return *this;
		}

		Iterator operator--(int)
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr - 1)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}
			Iterator temp = *this;
			--m_ptr;
			return temp;
		}

		Iterator operator+(const difference_type& n)
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr + n)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}

			return Iterator(m_ptr + n, m_arrayPtr);
		}

		Iterator operator-(const difference_type& n)
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr - n)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}

			return Iterator(m_ptr - n, m_arrayPtr);
		}

		Iterator& operator+=(const difference_type& n)
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr + n)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}
			*this += n;
			return *this;
		}

		Iterator& operator-=(const difference_type& n)
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr - n)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}
			*this -= n;
			return *this;
		}

		difference_type operator-(const Iterator& other) const
		{
			return m_ptr - other.m_ptr;
		}

		bool operator==(const Iterator& other) const
		{
			return m_ptr == other.m_ptr;
		}

		bool operator!=(const Iterator& other) const
		{
			return !(*this == other);
		}

		bool operator>(const Iterator& other) const
		{
			return m_ptr > other.m_ptr;
		}

		bool operator<(const Iterator& other) const
		{
			return m_ptr < other.m_ptr;
		}

		bool operator>=(const Iterator& other) const
		{
			return m_ptr >= other.m_ptr;
		}

		bool operator<=(const Iterator& other) const
		{
			return m_ptr <= other.m_ptr;
		}

	private:
		T* m_ptr;
		const MyArray* m_arrayPtr;
	};

	class ConstIterator
	{
	public:
		using iterator_category = std::contiguous_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		ConstIterator(pointer ptr, const MyArray* arrayPtr)
			: m_ptr{ ptr }
			, m_arrayPtr{ arrayPtr }
		{
			if (!(m_arrayPtr->IsValidPointer(ptr)))
			{
				throw std::out_of_range("Invalid pointer\n");
			}

			if (!arrayPtr)
			{
				throw std::out_of_range("Invalid array\n");
			}
		}

		reference operator*() const
		{
			return *m_ptr;
		}

		pointer operator->() const
		{
			return m_ptr;
		}

		ConstIterator& operator++()
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr + 1)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}
			++m_ptr;
			return *this;
		}

		ConstIterator operator++(int)
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr + 1)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}

			Iterator temp = *this;
			++m_ptr;
			return temp;
		}

		ConstIterator& operator--()
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr - 1)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}

			--m_ptr;
			return *this;
		}

		ConstIterator operator--(int)
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr - 1)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}
			Iterator temp = *this;
			--m_ptr;
			return temp;
		}

		ConstIterator operator+(const difference_type& n)
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr + n)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}

			return ConstIterator(m_ptr + n, m_arrayPtr);
		}

		ConstIterator operator-(const difference_type& n)
		{
			if (!(m_arrayPtr->IsValidPointer(m_ptr - n)))
			{
				throw std::out_of_range("Iterator out of range\n");
			}

			return ConstIterator(m_ptr - n, m_arrayPtr);
		}

		difference_type operator-(const ConstIterator& other)
		{
			return m_ptr - other.m_ptr;
		}

		bool operator==(const ConstIterator& other) const
		{
			return m_ptr == other.m_ptr;
		}

		bool operator!=(const ConstIterator& other) const
		{
			return !(*this == other);
		}

		bool operator>(const ConstIterator& other) const
		{
			return m_ptr > other.m_ptr;
		}

		bool operator<(const ConstIterator& other) const
		{
			return m_ptr < other.m_ptr;
		}

		bool operator>=(const ConstIterator& other) const
		{
			return m_ptr >= other.m_ptr;
		}

		bool operator<=(const ConstIterator& other) const
		{
			return m_ptr <= other.m_ptr;
		}

	private:
		T* m_ptr;
		const MyArray* m_arrayPtr;
	};

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	Iterator begin() { return Iterator(m_data, this); }
	ConstIterator begin() const { return ConstIterator(m_data, this); }
	ConstIterator cbegin() const { return ConstIterator(m_data, this); }

	Iterator end() { return Iterator(m_data + m_size, this); }
	ConstIterator end() const { return ConstIterator(m_data + m_size, this); }
	ConstIterator cend() const { return ConstIterator(m_data + m_size, this); }

	ReverseIterator rbegin() { return ReverseIterator(end()); }
	ConstReverseIterator rbegin() const { return ConstReverseIterator(end()); }
	ConstReverseIterator crbegin() const { return ConstReverseIterator(end()); }

	ReverseIterator rend() { return ReverseIterator(begin()); }
	ConstReverseIterator rend() const { return ConstReverseIterator(begin()); }
	ConstReverseIterator crend() const { return ConstReverseIterator(begin()); }

	MyArray()
		: m_data{ nullptr }
		, m_size{ 0 }
		, m_capacity{ 0 }
	{
	}

	~MyArray()
	{
		Clear();
		::operator delete[](m_data);
	}

	MyArray(const MyArray& other)
		: m_data{ nullptr }
		, m_size{ 0 }
		, m_capacity{ 0 }
	{
		Reserve(other.m_capacity);
		for (size_t i = 0; i < other.m_size; ++i)
		{
			new (m_data + i) T(other.m_data[i]);
			++m_size;
		}
	}

	MyArray(MyArray&& other) noexcept
		: m_data{ other.m_data }
		, m_size{ other.m_size }
		, m_capacity{ other.m_capacity }
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	MyArray& operator=(const MyArray& other)
	{
		if (this != &other)
		{
			MyArray temp(other);
			swap(temp);
		}

		return *this;
	}

	MyArray& operator=(MyArray&& other) noexcept
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

	size_t Size() const
	{
		return m_size;
	}

	T& operator[](size_t index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range\n");
		}

		return m_data[index];
	}

	const T& operator[](size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range\n");
		}

		return m_data[index];
	}

	void PushBack(const T& element)
	{
		if (m_size == m_capacity)
		{
			Reserve(m_size + 1);
		}

		new (m_data + m_size) T{ element };
		++m_size;
	}

	void Resize(const size_t& newSize)
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
				++m_size;
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

	void Clear()
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			m_data[i].~T();
		}
		m_size = 0;
	}

	size_t GetCapacity()
	{
		return m_capacity;
	}

private:
	bool IsValidPointer(T* ptr) const
	{
		if (!ptr)
		{
			return false;
		}

		if (ptr < m_data || ptr > m_data + m_size)
		{
			return false;
		}

		return true;
	}

	void swap(MyArray& other)
	{
		std::swap(m_data, other.m_data);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_size, other.m_size);
	}

	void Reserve(const size_t& capacity)
	{
		if (m_capacity >= capacity)
			return;

		size_t newCapacity = std::max(capacity, m_capacity * 2);
		T* newData = nullptr;

		try
		{
			newData = static_cast<T*>(::operator new[](sizeof(T) * (newCapacity + 1)));
		}
		catch (...)
		{
			::operator delete[](newData);
			throw;
		}

		for (size_t i = 0; i < m_size; ++i) //check
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

	T* m_data;
	size_t m_size;
	size_t m_capacity;
};