
#ifndef DMEMORY_H
#define DMEMORY_H

// ����� ������, ������� ����������� �������,
// � ��� ����, ����� ��� ����������.
template< class T >
class DMemory
{
public:
	// �����������
	DMemory( int initialSize = 0 )
	{
		mData = 0;
		mSize = 0;

		if ( initialSize )
		{
			SetSize( initialSize );
		}
	}

	// ����������
	~DMemory()
	{
		if ( mData )
		{
			free( mData );
		}
	}

	// ������ � ���������
	T& operator[]( int i )
	{
		return mData[i];
	}
	const T& operator[]( int i ) const
	{
		return mData[i];
	}

	// ������� ���������
	T *Base()
	{
		return mData;
	}
	const T *Base() const
	{
		return mData;
	}

	// �������� ������� ������
	int Size() const
	{
		return mSize;
	}

	// ��������, ��� ������ ������ ��� �������� ��
	// ������� ���� ����� ����� ���������.
	void EnsureCapacity( int capacity )
	{
		if ( capacity > mSize )
		{
			int newSize = mSize;
			if ( newSize == 0 )
				newSize = 1;
			while ( newSize < capacity )
				newSize *= 2;

			SetSize( newSize );
		}
	}

	// ���������� ����� � ��� ����
	void Swell()
	{
		int newSize = mSize;
		if ( newSize == 0 )
			newSize = 1;
		newSize *= 2;

		SetSize( newSize );
	}

private:
	// ���������� ����� ������ ����� ������
	void SetSize( int newSize )
	{
		if ( mData )
			mData = (T*)realloc( mData, newSize * sizeof(T) );
		else
			mData = (T*)malloc( newSize * sizeof(T) );

		mSize = newSize;
	}

	// ���������� ������
	T *mData;

	// ������ ���������� ������
	int mSize;
};

#endif // DMEMORY_H
