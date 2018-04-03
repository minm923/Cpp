#include <iostream>
#include <algorithm>

typedef int Rank;

const int DEFAULT_CAPACITY = 3;

template <typename T>
class Vector
{
private:
    Rank _size;
    int _capacity;
    T*  _elem;
    
    // core function
    void copyFrom(T const* A, Rank lo, Rank hi);

    void expand();
/*
    void shrink();
    bool bubble(Rank lo, Rank hi);
    void bubbleSort(Rank lo, Rank hi);
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mi, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    Rank partition(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);
*/

public:
    // construct
    Vector (int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
        : _capacity(c),
          _size(0),
          _elem(NULL)
    {
        _elem = new T[_capacity];
        for ( ; _size < s; _elem[_size++] = v);// trick
    }

    Vector (T const* A, Rank lo, Rank hi)
    { copyFrom(A, lo, hi); }

    Vector (T const* A, Rank n)
    { copyFrom(A, 0, n); }

    Vector(const Vector<T>& that, Rank lo, Rank hi)
    { copyFrom(that._elem, lo, hi); }

    // copy construct
    Vector(const Vector<T>& that)
    { copyFrom(that._elem, 0, that._size); }

    // exception safe
    Vector<T>& operator=(const Vector<T>& that)
    {
        Vector<T> t(that);
        std::swap(_size, t._size);
        std::swap(_capacity, t._capacity);
        std::swap(_elem, t._elem);

        return *this;
    }

    ~Vector() { delete [] _elem; }
};

// [lo,hi)
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
    _capacity = (hi - lo) << 1;
    _elem     = new T[_capacity];
    _size     = 0;

    while (lo < hi)
    {
        _elem[_size++] = A[lo++];
    }
}

template <typename T>
void Vector<T>::expand()
{
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;

    T* newElem = new T[_capacity << 1];

    for (int i=0; i<_size; ++i)
        newElem[i] = _elem[i];
    
    _capacity <<= 1;
    delete [] _elem;
    _elem = newElem;
}

int main(int argc, char * argv[])
{
    Vector<int> myv;
    return 0;
}

