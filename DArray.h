
#ifndef DARRAY_H
#define DARRAY_H

// ������������ ������
template< class T >
class DArray
{
	enum
	{
		DEFAULT_RESERVE = 64
	};

public:
	// �����������
	DArray( int reserveMemory = DEFAULT_RESERVE )
		: mMemory( reserveMemory )
	{
		mCount = 0;
	}
	// ����������
	~DArray()
	{
		Erase();
	}

	// ������ � ���������
	T& operator[]( int i ) { return mMemory[i]; }
	const T& operator[]( int i ) const { return mMemory[i]; }
	T& Element( int i ) { return mMemory[i]; }
	const T& Element( int i ) const { return mMemory[i]; }

	// ������� ���������
	T *Base() { return mMemory.Base(); }
	const T *Base() const { return mMemory.Base(); }

	// ������ � ��������� ��������
	T& First() { return mMemory[0]; }
	T& Last() { return mMemory[mCount-1]; }
	const T& First() const { return mMemory[0]; }
	const T& Last() const { return mMemory[mCount-1]; }

	// ����� ��������� � �������
	int Count() const { return mCount; }

	// ������?
	bool IsEmpty() const { return Count() == 0; }

	// �������� ������� � ����� �������
	void PushBack( const T& c )
	{
		mMemory.EnsureCapacity( mCount+1 );
		ConstructCopy( mCount, c );
		mCount++;
	}

	// ������� ��������� �������
	void PopBack()
	{
		Destruct( mCount-1 );
		mCount--;
	}

	// �������� ������� � ������������ �����
	void Insert( int idx, const T& c )
	{
		mMemory.EnsureCapacity( mCount+1 );
		MoveElementsRight( idx, 1 );
		ConstructCopy( idx, c );
		mCount++;
	}

	// ������� ������������ �������
	void Remove( int idx )
	{
		Destruct( idx );
		MoveElementsLeft( idx+1, 1 );
		mCount--;
	}

	// ��������!
	void Erase()
	{
		while ( mCount > 0 )
			PopBack();
	}

	// ������ ���������� ������
	int MemSize() const
	{
		return mMemory.Size();
	}

	// ����������� ��������� ������ ��� ����������
	// ����� ���������.
	void EnsureCapacity( int capacity )
	{
		mMemory.EnsureCapacity( capacity );
	}

	// ����������� ������ ���������� ������ � ��� ����
	void Swell()
	{
		mMemory.Swell();
	}

	// �����
	int Find( const T& c, int startIndex = 0 )
	{
		for ( int i = startIndex; i < mCount; i++ )
		{
			if ( mMemory[i] == c )
				return i;
		}
		return -1;
	}

	// ����� � ����������! >)
	void RemoveElement( const T& c )
	{
		int i = Find( c );
		if ( i >= 0 )
			Remove( i );
	}

private:
	// ��� ����� ����������� ������ �������,
	// ������� ������� � ��������� ��������
	// ������.
	void ConstructCopy( int i, const T& c )
	{
		new ( &mMemory[i] ) T( c );
	}
	void Destruct( int i )
	{
		mMemory[i].~T();
	}

	// ��������� ����� �������
	void MoveElementsRight( int idx, int num )
	{
		int numBytesToCopy = (mCount-idx) * sizeof(T);
		if ( numBytesToCopy > 0 )
		{
			memmove( &mMemory[idx+num], &mMemory[idx], numBytesToCopy );
		}
	}

	// ��������� ����� ������
	void MoveElementsLeft( int idx, int num )
	{
		int numBytesToCopy = (mCount-idx) * sizeof(T);
		if ( numBytesToCopy > 0 )
		{
			memmove( &mMemory[idx-num], &mMemory[idx], numBytesToCopy );
		}
	}

	// ������, ��� �� ������ ������
	DMemory<T> mMemory;

	// ����� ��������� � ������� (����� ���� ������ ������� ���������� ������!)
	int mCount;
};

#endif // DARRAY_H
