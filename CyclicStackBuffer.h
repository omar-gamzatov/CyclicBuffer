#pragma once

template<typename T>
class CyclicBuffer {
	T* buffer;
	T* begin;
	T* end;
	unsigned int cnt = 0;
	unsigned int m_size;

public:
	CyclicBuffer(unsigned int _size)
		: m_size(_size)
	{
		buffer = new T[_size];
		begin = buffer;
		end = buffer;
	}

	bool push(const T& val)
	{
		if (isFull())
			return false;
		++cnt;
		*end = val;
		end = increment(end);
		return true;
	}

	bool push(T&& val)
	{
		if (isFull())
			return false;
		++cnt;
		*end = std::move(val);
		end = increment(end);
		return true;
	}

	[[nodiscard]]
	T pop()
	{
		if (isEmpty())
			return *begin;
		--cnt;
		T* tmp = begin;
		if (!isEmpty()) begin = increment(begin);
		return *tmp;
	}

	T front() const
	{
		if (isEmpty())
			throw;
		return *begin;
	}

	unsigned int size() const
	{
		return m_size;
	}

	bool isEmpty() const
	{
		return (cnt == 0);
	}

	bool isFull() const
	{
		return (cnt == m_size);
	}

	~CyclicBuffer()
	{
		delete[] buffer;
	}

private:
	T* increment(T* p) const
	{
		if (p < buffer + m_size - 1)
			return p + 1;
		else
			return buffer;
	}
};
