#ifndef QOPTIMALLIST_H
#define QOPTIMALLIST_H

#include <QDebug>
#include <QList>

template <typename T>
class QOptimalList
{
public:
    QOptimalList();
    ~QOptimalList();

    void clear();

    void append(const T &t);
    void insert(int i, const T &t);
    void removeAt(int i);
    void removeLast();

    const T &at(int i) const;
    const T &operator[](int i) const;
    T &operator[](int i);

    int length() const;
    int size() const;
    int count() const;

protected:
    T** mBuffer;
    int mCount;
    int mCapacity;

    void setOptimalCapacity();
};

template <typename T>
QOptimalList<T>::QOptimalList()
{
    mBuffer=0;
    mCount=0;
    mCapacity=0;
}

template <typename T>
QOptimalList<T>::~QOptimalList()
{
    clear();
}

template <typename T>
void QOptimalList<T>::clear()
{
    mCount=0;
    setOptimalCapacity();
}

template <typename T>
void QOptimalList<T>::append(const T &t)
{
    ++mCount;
    setOptimalCapacity();

    mBuffer[mCount-1]=new T();
    *mBuffer[mCount-1]=t;
}

template <typename T>
void QOptimalList<T>::insert(int i, const T &t)
{
    Q_ASSERT_X(i >= 0 && i <= mCount, "QOptimalList<T>::insert", "index out of range");

    ++mCount;
    setOptimalCapacity();

    for (int j=mCount-1; j>i; --j)
    {
        mBuffer[j]=mBuffer[j-1];
    }

    mBuffer[i]=new T();
    *mBuffer[i]=t;
}

template <typename T>
void QOptimalList<T>::removeAt(int i)
{
    Q_ASSERT_X(i >= 0 && i < mCount, "QOptimalList<T>::removeAt", "index out of range");

    for (int j=i+1; j<mCount; ++j)
    {
        mBuffer[j-1]=mBuffer[j];
    }

    --mCount;
    setOptimalCapacity();
}

template <typename T>
void QOptimalList<T>::removeLast()
{
    if (mCount>0)
    {
        removeAt(mCount-1);
    }
}

template <typename T>
const T &QOptimalList<T>::at(int i) const
{
    Q_ASSERT_X(i >= 0 && i < mCount, "QOptimalList<T>::at", "index out of range");

    return *mBuffer[i];
}

template <typename T>
const T &QOptimalList<T>::operator[](int i) const
{
    Q_ASSERT_X(i >= 0 && i < mCount, "QOptimalList<T>::operator[]", "index out of range");

    return *mBuffer[i];
}

template <typename T>
T &QOptimalList<T>::operator[](int i)
{
    Q_ASSERT_X(i >= 0 && i < mCount, "QOptimalList<T>::operator[]", "index out of range");

    return *mBuffer[i];
}

template <typename T>
int QOptimalList<T>::length() const
{
    return mCount;
}

template <typename T>
int QOptimalList<T>::size() const
{
    return mCount;
}

template <typename T>
int QOptimalList<T>::count() const
{
    return mCount;
}

template <typename T>
void QOptimalList<T>::setOptimalCapacity()
{
    int aNewCapacity=mCapacity;

    if (mCount<aNewCapacity)
    {
        do
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
        } while (true);
    }
    else
    if (mCount>=aNewCapacity)
    {
        if (aNewCapacity==0)
        {
            aNewCapacity=mCount;
        }
        else
        {
            do
            {
                int aTempCapacity=aNewCapacity << 1;

                if (mCount<aTempCapacity)
                {
                    break;
                }

                aNewCapacity=aTempCapacity;
            } while (true);
        }
    }

    if (mCapacity!=aNewCapacity)
    {
        if (aNewCapacity==0)
        {
            delete[] mBuffer;
            mBuffer=0;
        }
        else
        {
            T** aNewBuffer=new T*[aNewCapacity];
            Q_CHECK_PTR(aNewBuffer);

            if (mBuffer)
            {
                for (int i=0; i<aNewCapacity && i<mCapacity; ++i)
                {
                    aNewBuffer[i]=mBuffer[i];
                }

                qDebug()<<mBuffer;

                delete[] mBuffer;
            }

            mBuffer=aNewBuffer;
        }

        mCapacity=aNewCapacity;
    }
}

#endif // QOPTIMALLIST_H
