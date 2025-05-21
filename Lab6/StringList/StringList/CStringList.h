#pragma once
#include <string>
#include <iterator>
#include <initializer_list>

struct Node
{
	std::string data;
	Node* next;
	Node* prev;
	Node(const std::string& str) : data{ str }, next{ nullptr }, prev{ nullptr }{}
};

class CStringList
{
public:

	class Iterator
	{
	public:
		friend class CStringList;

		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::string;
		using difference_type = std::ptrdiff_t;
		using pointer = std::string*;
		using reference = std::string&;

		Iterator(Node* p);

		reference operator*() const;
		pointer operator->() const;

		Iterator& operator++();
		Iterator operator++(int);

		Iterator& operator--();
		Iterator operator--(int);

		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;

	private:
		Node* ptr;
	};

	class ConstIterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::string;
		using difference_type = std::ptrdiff_t;
		using pointer = const std::string*;
		using reference = const std::string&;

		ConstIterator(const Node* p);

		reference operator*() const;
		pointer operator->() const;

		ConstIterator& operator++();
		ConstIterator operator++(int);

		ConstIterator& operator--();
		ConstIterator operator--(int);

		bool operator==(const ConstIterator& other) const;
		bool operator!=(const ConstIterator& other) const;

	private:
		const Node* ptr;
	};

	CStringList();
	CStringList(const std::initializer_list<std::string>& initializerList);

	CStringList(const CStringList& other);
	CStringList(CStringList&& other) noexcept;

	CStringList& operator=(const CStringList& other);
	CStringList& operator=(CStringList&& other) noexcept;

	~CStringList();

	void PushFront(const std::string& str);
	void PushBack(const std::string& str);
	void Insert(Iterator it, const std::string& str);
	void Erase(Iterator it);

	void Clear();

	size_t Size() const;
	bool Empty() const;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	Iterator begin() { return Iterator(m_head); }
	ConstIterator begin() const { return ConstIterator(m_head); }
	ConstIterator cbegin() const { return ConstIterator(m_head); }

	Iterator end() { return Iterator(m_end); }
	ConstIterator end() const { return ConstIterator(m_end); }
	ConstIterator cend() const { return ConstIterator(m_end); }

	ReverseIterator rbegin() { return ReverseIterator(end()); }
	ConstReverseIterator rbegin() const { return ConstReverseIterator(end()); }
	ConstReverseIterator crbegin() const { return ConstReverseIterator(cend()); }

	ReverseIterator rend() { return ReverseIterator(begin()); }
	ConstReverseIterator rend() const { return ConstReverseIterator(begin()); }
	ConstReverseIterator crend() const { return ConstReverseIterator(cbegin()); }

private:
	Node* m_head = nullptr;
	Node* m_tail = nullptr;
	Node* m_rend = nullptr;
	Node* m_end = nullptr;
	size_t m_size = 0;
	void swap(CStringList& other);
};



