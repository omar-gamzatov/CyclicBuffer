#pragma once

template<typename T>
class CyclicBuffer {
	T* buffer;
	T* begin;
	T* end;
	unsigned int m_size;

public:
	CyclicBuffer(unsigned int _size)
		: m_size(_size)
	{
		buffer = new T[_size];
		begin = buffer;
		end = buffer;
	}

	void push(const T& val)
	{
		*end = val;
		if (isFull())
			begin = increment(begin);
		end = increment(end);
	}

	void push(T&& val)
	{
		*end = std::move(val);
		if (isFull())
			begin = increment(begin);
		end = increment(end);
	}

	[[nodiscard]]
	T pop()
	{
		T* tmp = begin;
		if (!isEmpty())
			begin = increment(begin);
		return *tmp;
	}

	T front() const
	{
		return *begin;
	}

	unsigned int size() const
	{
		return m_size;
	}

	bool isEmpty() const
	{
		return end == increment(begin);
	}

	bool isFull() const
	{
		return end == begin;
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