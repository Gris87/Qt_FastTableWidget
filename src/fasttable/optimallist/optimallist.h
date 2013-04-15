#ifndef OPTIMALLIST_H
#define OPTIMALLIST_H

#include <QTypeInfo>

class OptimalListSharedData
{
public:
    OptimalListSharedData();

    void* mBuffer;
    int   mBegin;
    int   mCount;
    int   mCapacity;
    int   mReserved;
    int   mReferences;
};

template <typename T>
class OptimalList
{
public:
    OptimalList();
    OptimalList(OptimalList<T> &list);
    ~OptimalList();

    void clear();

    void reserve(int size);

    void prepend(const T &t);
    void append(const T &t);
    void append(const OptimalList<T> &t);
    void insert(int i, const T &t);

    void replace(int i, const T &t);

    void removeAt(int i);
    void removeFirst();
    void removeLast();
    int  removeAll(const T &t);
    bool removeOne(const T &t);

    T takeAt(int i);
    T takeFirst();
    T takeLast();

    const T &at(int i) const;
    const T &operator[](int i) const;
    T &operator[](int i);
    T value(int i) const;
    T value(int i, const T &defaultValue) const;
    T& first();
    const T& first() const;
    T& last();
    const T& last() const;

    int length() const;
    int size() const;
    int count() const;

    bool isEmpty() const;

    void move(int from, int to);
    void swap(int i, int j);
    void swap(OptimalList<T> &other);

    int indexOf(const T &t, int from = 0) const;
    int lastIndexOf(const T &t, int from = -1) const;
    bool contains(const T &t) const;
    bool startsWith(const T &t) const;
    bool endsWith(const T &t) const;

    int count(const T &t) const;

    OptimalList<T> mid(int pos, int length = -1) const;

    OptimalList<T> &operator=(OptimalList<T> &l);
    bool operator==(const OptimalList<T> &l) const;
    bool operator!=(const OptimalList<T> &l) const;

protected:
    enum
    {
        // Should be like this, but we use as below. Maybe it is good
//      isLarge       = QTypeInfo<T>::isLarge        || QTypeInfo<T>::isStatic,
        isLarge       = (sizeof(T)>sizeof(void *)*4),// || QTypeInfo<T>::isStatic,
        sizeOfElement = isLarge ? sizeof(void *) : sizeof(T)
    };

    void* mBuffer;
    int   mBegin;
    int   mCount;
    int   mCapacity;
    int   mReserved;

    void setOptimalCapacity();
    inline void* pointerAt(const int i);
};

template <typename T>
OptimalList<T>::OptimalList()
{
    mBuffer=0;
    mBegin=0;
    mCount=0;
    mCapacity=0;
    mReserved=0;
}

template <typename T>
OptimalList<T>::OptimalList(OptimalList<T> &list)
{
    mBuffer=0;
    mBegin=0;
    mCount=0;
    mCapacity=0;
    mReserved=0;

    *this=list;
}

template <typename T>
OptimalList<T>::~OptimalList()
{
    clear();
}

template <typename T>
void OptimalList<T>::clear()
{
    if (isLarge)
    {
        for (int i=0; i<mCount; ++i)
        {
            delete *reinterpret_cast<T**>(pointerAt(i));
        }
    }

    mBegin=0;
    mCount=0;
    mReserved=0;
    setOptimalCapacity();
}

template <typename T>
void OptimalList<T>::reserve(int size)
{
    if (mReserved!=size)
    {
        mReserved=size;
        setOptimalCapacity();
    }
}

template <typename T>
void OptimalList<T>::prepend(const T &t)
{
    ++mCount;

    if (mBegin==0)
    {
        if (mCount>=(mCapacity << 1)/3)
        {
            mBegin=mCapacity-mCount+1; // +1 - to increase capacity at the next step
            setOptimalCapacity();
        }

        mBegin=(mCapacity-mCount) >> 1;

        if (mBegin==0)
        {
            mBegin=1;
        }

        memmove(pointerAt(0), mBuffer, (mCount-1)*sizeOfElement);
    }

    --mBegin;

    if (isLarge)
    {
        *reinterpret_cast<T**>(pointerAt(0))=new T(t);
    }
    else
    if (QTypeInfo<T>::isComplex)
    {
        new (pointerAt(0)) T(t);
    }
    else
    {
        *reinterpret_cast<T*>(pointerAt(0))=t;
    }
}

template <typename T>
void OptimalList<T>::append(const T &t)
{
    ++mCount;
    setOptimalCapacity();

    if (isLarge)
    {
        *reinterpret_cast<T**>(pointerAt(mCount-1))=new T(t);
    }
    else
    if (QTypeInfo<T>::isComplex)
    {
        new (pointerAt(mCount-1)) T(t);
    }
    else
    {
        *reinterpret_cast<T*>(pointerAt(mCount-1))=t;
    }
}

template <typename T>
void OptimalList<T>::append(const OptimalList<T> &t)
{
    if (t.mCount>0)
    {
        mCount+=t.mCount;
        setOptimalCapacity();

        for (int i=0; i<t.mCount; ++i)
        {
            if (isLarge)
            {
                *reinterpret_cast<T**>(pointerAt(mCount+i-t.mCount))=new T(**reinterpret_cast<T**>(t.pointerAt(i)));
            }
            else
            if (QTypeInfo<T>::isComplex)
            {
                new (pointerAt(mCount+i-t.mCount)) T(*reinterpret_cast<T*>(t.pointerAt(i)));
            }
            else
            {
                *reinterpret_cast<T*>(pointerAt(mCount+i-t.mCount))=*reinterpret_cast<T*>(t.pointerAt(i));
            }
        }
    }
}

template <typename T>
void OptimalList<T>::insert(int i, const T &t)
{
    if (i<=0)
    {
        prepend(t);
        return;
    }

    if (i>=mCount)
    {
        append(t);
        return;
    }

    ++mCount;

    if (mBegin==0 || i>(mCount >> 1))
    {
        setOptimalCapacity();

        if (i>(mCount >> 1))
        {
            memmove(pointerAt(i+1), pointerAt(i), (mCount-i-1)*sizeOfElement);
        }
        else
        {
            // mBegin was 0
            mBegin=(mCapacity-mCount) >> 1;

            if (mBegin==0)
            {
                mBegin=1;
            }

            memmove(pointerAt(0), mBuffer, (mCount-1)*sizeOfElement);

            --mBegin;
            memmove(pointerAt(0), pointerAt(1), i*sizeOfElement);
        }
    }
    else
    {
        --mBegin;
        memmove(pointerAt(0), pointerAt(1), i*sizeOfElement);
    }

    if (isLarge)
    {
        *reinterpret_cast<T**>(pointerAt(i))=new T(t);
    }
    else
    if (QTypeInfo<T>::isComplex)
    {
        new (pointerAt(i)) T(t);
    }
    else
    {
        *reinterpret_cast<T*>(pointerAt(i))=t;
    }
}

template <typename T>
void OptimalList<T>::replace(int i, const T &t)
{
    Q_ASSERT_X(i >= 0 && i < mCount, "OptimalList<T>::replace", "index out of range");

    if (isLarge)
    {
        **reinterpret_cast<T**>(pointerAt(i))=t;
    }
    else
    {
        *reinterpret_cast<T*>(pointerAt(i))=t;
    }
}

template <typename T>
void OptimalList<T>::removeAt(int i)
{
    Q_ASSERT_X(i >= 0 && i < mCount, "OptimalList<T>::removeAt", "index out of range");

    if (isLarge)
    {
        delete *reinterpret_cast<T**>(pointerAt(i));
    }

    if (i>mCount >> 1)
    {
        memmove(pointerAt(i), pointerAt(i+1), (mCount-i-1)*sizeOfElement);
    }
    else
    {
        memmove(pointerAt(1), pointerAt(0), i*sizeOfElement);

        ++mBegin;
    }

    --mCount;
    setOptimalCapacity();
}

template <typename T>
void OptimalList<T>::removeFirst()
{
    if (mCount>0)
    {
        removeAt(0);
    }
}

template <typename T>
void OptimalList<T>::removeLast()
{
    if (mCount>0)
    {
        removeAt(mCount-1);
    }
}

template <typename T>
int OptimalList<T>::removeAll(const T &t)
{
    int removed=0;

    int i=0;

    while (i<mCount)
    {
        if (at(i)==t)
        {
            removeAt(i);
            ++removed;
        }
        else
        {
            ++i;
        }
    }

    return removed;
}

template <typename T>
bool OptimalList<T>::removeOne(const T &t)
{
    int index=indexOf(t);

    if (index>=0)
    {
        removeAt(index);
        return true;
    }

    return false;
}

template <typename T>
T OptimalList<T>::takeAt(int i)
{
    Q_ASSERT_X(i >= 0 && i < mCount, "OptimalList<T>::takeAt", "index out of range");

    T t=at(i);
    removeAt(i);
    return t;
}

template <typename T>
T OptimalList<T>::takeFirst()
{
    T t=first();
    removeFirst();
    return t;
}

template <typename T>
T OptimalList<T>::takeLast()
{
    T t=last();
    removeLast();
    return t;
}

template <typename T>
const T &OptimalList<T>::at(int i) const
{
    Q_ASSERT_X(i >= 0 && i < mCount, "OptimalList<T>::at", "index out of range");

    if (isLarge)
    {
        return **reinterpret_cast<T**>(pointerAt(i));
    }
    else
    {
        return *reinterpret_cast<T*>(pointerAt(i));
    }
}

template <typename T>
const T &OptimalList<T>::operator[](int i) const
{
    Q_ASSERT_X(i >= 0 && i < mCount, "OptimalList<T>::operator[]", "index out of range");

    if (isLarge)
    {
        return **reinterpret_cast<T**>(pointerAt(i));
    }
    else
    {
        return *reinterpret_cast<T*>(pointerAt(i));
    }
}

template <typename T>
T &OptimalList<T>::operator[](int i)
{
    Q_ASSERT_X(i >= 0 && i < mCount, "OptimalList<T>::operator[]", "index out of range");

    if (isLarge)
    {
        return **reinterpret_cast<T**>(pointerAt(i));
    }
    else
    {
        return *reinterpret_cast<T*>(pointerAt(i));
    }
}

template <typename T>
T OptimalList<T>::value(int i) const
{
    if (i>=0 && i<mCount)
    {
        return at(i);
    }
    else
    {
        return T();
    }
}

template <typename T>
T OptimalList<T>::value(int i, const T &defaultValue) const
{
    if (i>=0 && i<mCount)
    {
        return at(i);
    }
    else
    {
        return defaultValue;
    }
}

template <typename T>
T& OptimalList<T>::first()
{
    Q_ASSERT(!isEmpty());

    if (isLarge)
    {
        return **reinterpret_cast<T**>(pointerAt(0));
    }
    else
    {
        return *reinterpret_cast<T*>(pointerAt(0));
    }
}

template <typename T>
const T& OptimalList<T>::first() const
{
    Q_ASSERT(!isEmpty());

    if (isLarge)
    {
        return **reinterpret_cast<T**>(pointerAt(0));
    }
    else
    {
        return *reinterpret_cast<T*>(pointerAt(0));
    }
}

template <typename T>
T& OptimalList<T>::last()
{
    Q_ASSERT(!isEmpty());

    if (isLarge)
    {
        return **reinterpret_cast<T**>(pointerAt(mCount-1));
    }
    else
    {
        return *reinterpret_cast<T*>(pointerAt(mCount-1));
    }
}

template <typename T>
const T& OptimalList<T>::last() const
{
    if (isLarge)
    {
        return **reinterpret_cast<T**>(pointerAt(mCount-1));
    }
    else
    {
        return *reinterpret_cast<T*>(pointerAt(mCount-1));
    }
}

template <typename T>
int OptimalList<T>::length() const
{
    return mCount;
}

template <typename T>
int OptimalList<T>::size() const
{
    return mCount;
}

template <typename T>
int OptimalList<T>::count() const
{
    return mCount;
}

template <typename T>
bool OptimalList<T>::isEmpty() const
{
    return mCount==0;
}

template <typename T>
void OptimalList<T>::move(int from, int to)
{
    Q_ASSERT_X(from >= 0 && from < mCount && to >= 0 && to < mCount, "OptimalList<T>::move", "index out of range");

    if (from == to)
    {
        return;
    }


}

template <typename T>
void OptimalList<T>::swap(int i, int j)
{
    Q_ASSERT_X(i >= 0 && i < mCount && j >= 0 && j < mCount, "OptimalList<T>::swap", "index out of range");

    if (isLarge)
    {
        T *t = *reinterpret_cast<T**>(pointerAt(i));
        *reinterpret_cast<T**>(pointerAt(i)) = *reinterpret_cast<T**>(pointerAt(j));
        *reinterpret_cast<T**>(pointerAt(j)) = t;
    }
    else
    {
        T t=*reinterpret_cast<T*>(pointerAt(i));
        *reinterpret_cast<T*>(pointerAt(i)) = *reinterpret_cast<T*>(pointerAt(j));
        *reinterpret_cast<T*>(pointerAt(j)) = t;
    }
}

template <typename T>
void OptimalList<T>::swap(OptimalList<T> &other)
{
    qSwap(mBuffer,   other.mBuffer);
    qSwap(mBegin,    other.mBegin);
    qSwap(mCount,    other.mCount);
    qSwap(mCapacity, other.mCapacity);
    qSwap(mReserved, other.mReserved);
}

template <typename T>
int OptimalList<T>::indexOf(const T &t, int from) const
{
    if (from<0)
    {
        from+=mCount;

        if (from<0)
        {
            from=0;
        }
    }

    for (int i=from; i<mCount; ++i)
    {
        if (at(i)==t)
        {
            return i;
        }
    }

    return -1;
}

template <typename T>
int OptimalList<T>::lastIndexOf(const T &t, int from) const
{
    if (from<0)
    {
        from+=mCount;
    }
    else
    if (from>=mCount)
    {
        from=mCount-1;
    }

    for (int i=from; i>=0; --i)
    {
        if (at(i)==t)
        {
            return i;
        }
    }

    return -1;
}

template <typename T>
bool OptimalList<T>::contains(const T &t) const
{
    return indexOf(t)>=0;
}

template <typename T>
bool OptimalList<T>::startsWith(const T &t) const
{
    return mCount>0 && at(0)==t;
}

template <typename T>
bool OptimalList<T>::endsWith(const T &t) const
{
    return mCount>0 && at(mCount-1)==t;
}

template <typename T>
int OptimalList<T>::count(const T &t) const
{
    int res=0;

    for (int i=0; i<mCount; ++i)
    {
        if (at(i)==t)
        {
            ++res;
        }
    }

    return res;
}

template <typename T>
OptimalList<T> OptimalList<T>::mid(int pos, int length) const
{
    if (length<0 || pos+length>mCount)
    {
        length=mCount-pos;
    }

    if (pos==0 && length==mCount)
    {
        return *this;
    }

    OptimalList list;

    list.mCount=length;
    list.setOptimalCapacity();

    if (isLarge)
    {
        if (isLarge)
        {
            for (int i=0; i<length; ++i)
            {
                *reinterpret_cast<T**>(list.pointerAt(i))=new T(**reinterpret_cast<T**>(pointerAt(pos+i)));
            }
        }
        else
        {
            for (int i=0; i<length; ++i)
            {
                *reinterpret_cast<T*>(list.pointerAt(i))=*reinterpret_cast<T*>(pointerAt(pos+i));
            }
        }
    }

    return list;
}

template <typename T>
OptimalList<T> &OptimalList<T>::operator=(OptimalList<T> &l)
{
    clear();

    mCount=l.mCount;
    setOptimalCapacity();

    if (isLarge)
    {
        for (int i=0; i<mCount; ++i)
        {
            *reinterpret_cast<T**>(pointerAt(i))=new T(**reinterpret_cast<T**>(l.pointerAt(i)));
        }
    }
    else
    if (QTypeInfo<T>::isComplex)
    {
        for (int i=0; i<mCount; ++i)
        {
            new (pointerAt(i)) T(*reinterpret_cast<T*>(l.pointerAt(i)));
        }
    }
    else
    {
        for (int i=0; i<mCount; ++i)
        {
            *reinterpret_cast<T*>(pointerAt(i))=*reinterpret_cast<T*>(l.pointerAt(i));
        }
    }

    return *this;
}

template <typename T>
bool OptimalList<T>::operator==(const OptimalList<T> &l) const
{
    if (mCount != l.mCount)
    {
        return false;
    }

    if (mBuffer == l.mBuffer)
    {
        return true;
    }

    for (int i=0; i<mCount; ++i)
    {
        if (at(i)!=l.at(i))
        {
            return false;
        }
    }

    return true;
}

template <typename T>
bool OptimalList<T>::operator!=(const OptimalList<T> &l) const
{
    return !(*this == l);
}

template <typename T>
void OptimalList<T>::setOptimalCapacity()
{
    int aNewCapacity=mCapacity;
    int aSize=mCount+mBegin;

    if (aSize>aNewCapacity)
    {
        if (aNewCapacity==0)
        {
            aNewCapacity=aSize;
        }
        else
        {
            forever
            {
                aNewCapacity = aNewCapacity << 1;

                if (aSize<=aNewCapacity)
                {
                    break;
                }
            }
        }
    }
    else
    if (mCount<aNewCapacity)
    {
        forever
        {
            int aTempCapacity=aNewCapacity >> 1;

            if (mCount>aTempCapacity)
            {
                break;
            }

            aNewCapacity=aTempCapacity;

            if (aNewCapacity==0)
            {
                break;
            }
        }

        if (mCapacity!=aNewCapacity && mBegin!=0)
        {
            int aBegin=mBegin;
            mBegin=0;

            memmove(pointerAt(0), pointerAt(aBegin), mCount*sizeOfElement);
        }
    }

    if (aNewCapacity<mReserved)
    {
        aNewCapacity=mReserved;
    }

    if (mCapacity!=aNewCapacity)
    {
        mCapacity=aNewCapacity;

        if (mCapacity==0)
        {
            free(mBuffer);
            mBuffer=0;
        }
        else
        {
            mBuffer = realloc(mBuffer, mCapacity*sizeOfElement);
            Q_CHECK_PTR(mBuffer);
        }
    }
}

template <typename T>
void* OptimalList<T>::pointerAt(const int i)
{
    return (void*)((long)mBuffer+(mBegin+i)*sizeOfElement);
}

#endif // OPTIMALLIST_H
