#include "CStringList.h"
#include <utility>
#include <stdexcept>

CStringList::CStringList()
{
	m_end = new Node(""); 
	m_rend = new Node("");//утечка памяти
}

CStringList::CStringList(const std::initializer_list<std::string>& initializerList)
{
	m_end = new Node("");
	m_rend = new Node("");
	for (const auto& str: initializerList)
	{
		PushBack(str);
	}
}

CStringList::CStringList(const CStringList& other)
{
	m_end = new Node("");
	m_rend = new Node("");
	for (const auto& str : other)
	{
		PushBack(str);
	}
}

CStringList::CStringList(CStringList&& other) noexcept : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size), m_end(other.m_end), m_rend(other.m_rend) //swap
{
	other.m_head = other.m_tail = other.m_end = other.m_rend = nullptr;
	other.m_size = 0;
}

CStringList& CStringList::operator=(const CStringList& other)
{
	CStringList temp(other);
	swap(temp);
	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
	Clear();
	swap(other);
	return *this;
}

CStringList::~CStringList() { Clear(); }

void CStringList::PushFront(const std::string& str)
{
	Node* node = new Node(str);
	if (!m_head)
	{
		m_head = m_tail = node;
		node->next = m_end;
		node->prev = m_rend;
		m_rend->next = node;
		m_end->prev = node;
	}
	else
	{
		node->next = m_head;
		m_head->prev = node;
		m_head = node;
		node->prev = m_rend;
		m_rend->next = node;
	}
	m_size++;
}

void CStringList::PushBack(const std::string& str)
{
	Node* node = new Node(str); //утечка
	if (!m_tail)
	{
		m_head = m_tail = node;
		node->next = m_end;
		node->prev = m_rend;
		m_rend->next = node;
		m_end->prev = node;
	}
	else
	{
		m_tail->next = node;
		node->prev = m_tail;
		m_tail = node;
		node->next = m_end;
		m_end->prev = node;
	}
	m_size++;
}

void CStringList::Insert(Iterator it, const std::string& str) //check const iterator
{
	if (it == end())
	{
		PushBack(str);
		return;
	}
	if (it == begin())
	{
		PushFront(str);
		return;
	}
	Node* node = new Node(str);
	node->next = it.ptr;
	node->prev = it.ptr->prev;
	it.ptr->prev->next = node;
	m_size++;
}

void CStringList::Erase(Iterator it)
{
	if (it.ptr == m_end)
	{
		throw std::invalid_argument("Can not delete this element\n");
	}

	if (m_size == 1)
	{
		delete it.ptr;
		m_size--;
		return;
	}

	if (it.ptr == m_head)
	{
		it.ptr->next->prev = m_rend;
		m_head = it.ptr->next;
		m_rend->next = m_head;
		delete it.ptr;
		m_size--;
		return;
	}

	if (it.ptr == m_tail)
	{
		it.ptr->prev->next = m_end;
		m_tail = it.ptr->prev;
		m_end->prev = m_tail;
		delete it.ptr;
		m_size--;
		return;
	}

	it.ptr->next->prev = it.ptr->prev;
	it.ptr->prev->next = it.ptr->next;
	delete it.ptr;
}

void CStringList::Clear()
{
	Node* temp;
	while (m_rend)
	{
		temp = m_rend;
		m_rend = m_rend->next;
		delete temp;
	}
	m_tail = nullptr;
	m_size = 0;
}

size_t CStringList::Size() const
{
	return m_size;
}
bool CStringList::Empty() const
{
	return m_size == 0;
}

void CStringList::swap(CStringList& other)
{
	std::swap(m_head, other.m_head);
	std::swap(m_tail, other.m_tail);
	std::swap(m_size, other.m_size);
	std::swap(m_rend, other.m_rend);
	std::swap(m_end, other.m_end);
}


CStringList::Iterator::Iterator(Node* p) : ptr{ p } {}

CStringList::Iterator::reference CStringList::Iterator::operator*() const { return ptr->data; }

CStringList::Iterator::pointer CStringList::Iterator::operator->() const { return &(ptr->data); }

CStringList::Iterator& CStringList::Iterator::operator++()
{
	if (ptr->next == nullptr)
	{
		throw std::invalid_argument("Cannot inrement past end\n");
	}
	ptr = ptr->next;
	return *this;
}

CStringList::Iterator CStringList::Iterator::operator++(int)
{
	Iterator temp = *this;
	++(*this);
	return temp;
}

CStringList::Iterator& CStringList::Iterator::operator--()
{
	if (ptr->prev == nullptr)
	{
		throw std::invalid_argument("Cannot inrement pre begin\n");
	}
	ptr = ptr->prev;
	return *this;
}

CStringList::Iterator CStringList::Iterator::operator--(int)
{
	Iterator temp = *this;
	--(*this);
	return temp;
}

bool CStringList::Iterator::operator==(const Iterator& other) const
{
	return ptr == other.ptr;
}

bool CStringList::Iterator::operator!=(const Iterator& other) const
{
	return ptr != other.ptr;
}

CStringList::ConstIterator::ConstIterator(const Node* p) : ptr{ p } {}

CStringList::ConstIterator::reference CStringList::ConstIterator::operator*() const { return ptr->data; }

CStringList::ConstIterator::pointer CStringList::ConstIterator::operator->() const { return &(ptr->data); }

CStringList::ConstIterator& CStringList::ConstIterator::operator++()
{
	if (ptr->next == nullptr)
	{
		throw std::invalid_argument("Cannot inrement past end\n");
	}
	ptr = ptr->next;
	return *this;
}

CStringList::ConstIterator CStringList::ConstIterator::operator++(int)
{
	ConstIterator temp = *this;
	++(*this);
	return temp;
}

CStringList::ConstIterator& CStringList::ConstIterator::operator--()
{
	if (ptr->prev == nullptr)
	{
		throw std::invalid_argument("Cannot inrement pre begin\n");
	}
	ptr = ptr->prev;
	return *this;
}

CStringList::ConstIterator CStringList::ConstIterator::operator--(int)
{
	ConstIterator temp = *this;
	--(*this);
	return temp;
}

bool CStringList::ConstIterator::operator==(const ConstIterator& other) const
{
	return ptr == other.ptr;
}
bool CStringList::ConstIterator::operator!=(const ConstIterator& other) const
{
	return ptr != other.ptr;
}