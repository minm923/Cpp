#include <iostream>
#include <algorithm>
#include <stdlib.h>

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
    void shrink();

    bool bubble(Rank lo, Rank hi);
    void bubbleSort(Rank lo, Rank hi);

    void merge(Rank lo, Rank mi, Rank hi);
    Rank mergeGetMin(Rank& Start1, Rank End1, Rank& Start2, Rank End2);
    void mergeSort(Rank lo, Rank hi);

/*
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
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

    // deconstruct
    ~Vector() { delete [] _elem; }

    T& operator[] (Rank k) const
    {
        return _elem[k];// assert: 0 <= r < _size
    }

    Rank size() const { return _size; }
    bool empty() const { return !_size; }
    void unsort(Rank lo, Rank hi);

    Rank find(const T& e) const { find(e, 0, _size); }
    Rank find(const T& e, Rank lo, Rank hi) const;
    Rank insert(const T& e) { insert(_size, e); }
    Rank insert(Rank r, const T& e);
    T remove(Rank r);
    int remove(Rank lo, Rank hi);// [lo, hi)
    int deduplicate();// 无序去重
    int uniquify();// 有序去重
    void traverse(void (*pf)(T& e));
    template<typename VST> void traverse(VST& visit);//  函数对象
    
    int disordered() const
    {
        int n = 0;

        for (int i=1; i<_size; ++i)
            if (_elem[i-1] > _elem[i]) ++n;

        return n;
    }

    Rank search(const T& e) const
    { return (0 >= _size) ? -1 : search(e, 0, _size); }

    //[lo, hi)
    Rank search(const T& e, Rank lo, Rank hi) const;

    // [lo, hi)
    void sort(Rank lo, Rank hi);
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

template<typename T>
void Vector<T>::shrink()
{
    if (_capacity < (DEFAULT_CAPACITY << 1)) return;
    if ((_size << 2) > _capacity) return;

    T* newElem = new T[_capacity >> 1];
    for (int i=0; i<_size; i++)
        newElem[i] = _elem[i];

    _capacity >>= 1;
    delete [] _elem;
    _elem = newElem;
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
    T* V = _elem + lo;

    for (Rank i=hi-lo; i>0; --i)// trick
        std::swap(V[i-1], V[rand()%i]);
}

template<typename T>
Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const
{
    while ( (lo < hi--) && (e != _elem[hi]) );// trick
    return hi;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T& e)
{
    expand();

    for (int i=_size; i>r; --i)
        _elem[i] = _elem[i-1];

    _elem[r] = e;
    ++_size;
    
    return r;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
    T e = _elem[r];
    remove(r, r+1);

    return e;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi) return 0;

    while (hi < _size)
        _elem[lo++] = _elem[hi++];

    _size = lo;
    shrink();

    return hi-lo;
}

template<typename T>
int Vector<T>::deduplicate()
{
    int oldSize = _size;
    Rank i = 1;
    while (i < _size)
    {
        (find(_elem[i], 0, i) < 0) ? ++i : remove(i);// trick
    }

    return oldSize - _size;
}

template<typename T>
void Vector<T>::traverse(void (*pf)(T& e))
{
    for (Rank i=0; i < _size; ++i)
        pf(_elem[i]);
}

template <typename T> 
template <typename VST>
void Vector<T>::traverse(VST& visit)
{
    for (Rank i=0; i < _size; ++i)
        visit(_elem[i]);
}

template <typename T>
int Vector<T>::uniquify()
{
    Rank i = 0;
    Rank j = 0;

    while (++j < _size)
    {
        if (_elem[j] != _elem[i])
        {
            _elem[++i] = _elem[j];
        }
    }

    _size = ++i;
    shrink();

    return j - i;
}

// function obj
template<typename T>
struct Increase
{
    virtual void operator()(T& e)
    {
        ++e;
    }
};

// [lo, hi)
template<typename T>
Rank Vector<T>::search(const T& e, Rank lo, Rank hi) const
{
    while (lo < hi)
    {
        int mid = (hi - lo) / 2 + lo;
        if (_elem[mid] > e)
        {
            hi = mid;
        }
        else if (_elem[mid] < e)
        {
            lo = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
    //bubbleSort(lo, hi);
    mergeSort(lo, hi);
    return ;
}


template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while(!bubble(lo, hi--));
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
    bool sorted = true;

    while (++lo < hi)
    {
        if (_elem[lo-1] > _elem[lo])
        {
            sorted = false;
            std::swap(_elem[lo-1], _elem[lo]);
        }
    }

    return sorted;
}

// [lo, hi)
template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    if (hi - lo < 2) return ;
    int mid = ((hi - lo) >> 1) + lo;
    mergeSort(lo, mid);
    mergeSort(mid, hi);
    merge(lo, mid, hi);
}

// [lo, mid), [mid, hi)
template<typename T>
void Vector<T>::merge(Rank lo, Rank mid, Rank hi)
{
    Rank Start1 = lo;
    Rank End1   = mid;
    Rank Start2 = mid;
    Rank End2   = hi;

    int iLen   = hi - lo;
    T*  arr    = new T[iLen];

    int index  = 0;
    while (index < iLen)
    {
        Rank i  = mergeGetMin(Start1, End1, Start2, End2);
        arr[index++] = _elem[i];
    }

    index =  0;
    while (index  < iLen)
    {
        _elem[lo++] = arr[index++];
    }

    delete[] arr;
}

template<typename T>
Rank Vector<T>::mergeGetMin(Rank& Start1, Rank End1, Rank& Start2, Rank End2)
{
    if (Start1 >= End1 && Start2 >= End2)
        return -1;

    if (Start1 < End1 && Start2 < End2)
    {
        return _elem[Start1] > _elem[Start2] ? Start2++ : Start1++;
    }
    else if (Start1 < End1 && Start2 >= End2)
    {
        return Start1++;
    }
    else// Start2 < End2 && Start1 >= End1
    {
        return Start2++;
    }
}


template<typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }
template<typename T> static bool lt(T& a, T& b) { return a < b; }
template<typename T> static bool eq(T* a, T* b) { return eq(*a, *b); }
template<typename T> static bool eq(T& a, T& b) { return a == b; }

void printv(int& e)
{
    std::cout << e << ' ';
}

int main(int argc, char * argv[])
{
    int arr[] = {6, 5, 4, 3, 2, 1};
    Vector<int> myv(arr, 0, 6);
    myv.traverse(printv);
    std::cout << std::endl;
    myv.sort(0, 6);
    myv.traverse(printv);
    std::cout << std::endl;

    return 0;
}

