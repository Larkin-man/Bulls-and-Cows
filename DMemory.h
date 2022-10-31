
#ifndef DMEMORY_H
#define DMEMORY_H

// Кусок памяти, умеющий невозбранно пухнуть,
// в два раза, когда это необходимо.
template< class T >
class DMemory
{
public:
	// Конструктор
	DMemory( int initialSize = 0 )
	{
		mData = 0;
		mSize = 0;

		if ( initialSize )
		{
			SetSize( initialSize );
		}
	}

	// Деструктор
	~DMemory()
	{
		if ( mData )
		{
			free( mData );
		}
	}

	// Доступ к элементам
	T& operator[]( int i )
	{
		return mData[i];
	}
	const T& operator[]( int i ) const
	{
		return mData[i];
	}

	// Базовый указатель
	T *Base()
	{
		return mData;
	}
	const T *Base() const
	{
		return mData;
	}

	// Получить текущий размер
	int Size() const
	{
		return mSize;
	}

	// Убедимся, что памяти хватит для хранения по
	// крайней мере этого числа элементов.
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

	// Распухнуть ровно в два раза
	void Swell()
	{
		int newSize = mSize;
		if ( newSize == 0 )
			newSize = 1;
		newSize *= 2;

		SetSize( newSize );
	}

private:
	// Установить новый размер куска памяти
	void SetSize( int newSize )
	{
		if ( mData )
			mData = (T*)realloc( mData, newSize * sizeof(T) );
		else
			mData = (T*)malloc( newSize * sizeof(T) );

		mSize = newSize;
	}

	// Собственно данные
	T *mData;

	// Размер выделенной памяти
	int mSize;
};

#endif // DMEMORY_H
