#include <iostream>
#include <string>
#include <iterator>

using namespace std;

#pragma region Elso feladat

class double_space
{
  string str;

public:
  double_space(string szoveg) : str(szoveg) {}

  friend ostream &operator<<(ostream &os, const double_space &ds)
  {
    for (int i = 0; i < ds.str.length(); i++)
    {
      if (ds.str[i] == ' ')
      {
        os << "  ";
      }
      else
      {
        os << ds.str[i];
      }
    }
    return os;
  }
};

#pragma endregion

#pragma region Masodik feladat

// TODO

#pragma endregion

#pragma region Harmadik feladat

class Fibonacci
{
  int count;
  int current;

  int getFiboNumber(int n)
  {
    if (n == 1 || n == 2)
      return 1;

    return getFiboNumber(n - 1) + getFiboNumber(n - 2);
  }

public:
  Fibonacci(int n = 1) : count(n), current(0) {}
  int operator()(int k = 0)
  {
    if (k == 0)
      return getFiboNumber(++count);

    count = k;
    return getFiboNumber(k);
  }
};

#pragma endregion

#pragma region Negyedik feladat

template <class T>
class DinamikusTomb
{
  int max_elem;
  int current_size;
  T *tomb;

public:
  DinamikusTomb(int elem = 10) : tomb(new T[elem]), max_elem(elem), current_size(0) {}
  ~DinamikusTomb() { delete[] tomb; }

  int getSize() const { return current_size; }
  int getMax() const { return max_elem; }

  T &operator[](int i)
  {
    if (i < 0 || i > getSize())
      throw TombTulindexelesKivetel("tulindexelve");

    return tomb[i];
  }

  const T &operator[](int i) const
  {
    if (i < 0 || i > getSize())
      throw TombTulindexelesKivetel("tulindexelve");

    return tomb[i];
  }

  DinamikusTomb &operator+=(const T &elem)
  {
    for (int i = 0; i < current_size; i++)
    {
      if (tomb[i] == elem)
        return *this;
    }

    if (current_size == max_elem)
      throw TombTulindexelesKivetel("nem lehet beszurni");

    tomb[current_size++] = elem;
    return *this;
  }

  DinamikusTomb &operator-=(const T &elem)
  {
    int i = 0;
    while (i < current_size)
    {
      if (tomb[i] == elem)
      {
        for (int j = i; j < current_size; j++)
        {
          tomb[j] = tomb[j + 1];
        }
        --current_size;
      }
      else
      {
        i++;
      }
    }
  }

  class TombTulindexelesKivetel
  {
    const string msg;

  public:
    TombTulindexelesKivetel(const char *msg) : msg(msg) {}
    string getMsg() const { return msg; }
  };

  class iterator
  {
    T *_p;

  public:
    iterator() : _p(nullptr) {}
    iterator(T *p) : _p(p) {}
    iterator(const iterator &it) : _p(it._p) {}

    T &operator*() { return *_p; }
    T *operator->() { return _p; }

    iterator &operator++()
    {
      ++_p;
      return *this;
    }

    iterator operator++(int)
    {
      iterator temp(*this);
      ++_p;
      return temp;
    }

    bool operator==(const iterator &it) { return _p == it._p; }
    bool operator!=(const iterator &it) { return _p != it._p; }
  };

  iterator begin() { return iterator(tomb); }
  iterator end() { return iterator(tomb + getSize()); }

  friend ostream &operator<<(ostream &os, const DinamikusTomb &b)
  {
    int i = 0;
    int size = b.getSize();

    while (i < size - 1)
    {
      os << b[i] << ",";
      i++;
    }

    os << b[i];
    return os;
  }
};

#pragma endregion

int main()
{
  cout << "egy space,  ketto  space" << endl;

  Fibonacci fib;
  cout << "fibo (1):  " << fib() << endl
       << "fibo (20): " << fib(20) << endl
       << "fibo (21): " << fib() << endl
       << "fibo (5):  " << fib(5) << endl
       << endl;

  DinamikusTomb<int> dinamicArray(15);
  cout << "Init, size: " << dinamicArray.getSize() << ", values: " << dinamicArray << endl;

  for (int i = 0; i < 15; i++)
  {
    dinamicArray += i;
  }

  cout << "Filled, size: " << dinamicArray.getSize() << ", values: " << dinamicArray << endl;

  dinamicArray[4] = 99;
  dinamicArray[7] = 99;
  dinamicArray[10] = 99;
  dinamicArray[13] = 99;

  cout << "Added 99, size: " << dinamicArray.getSize() << ", values: " << dinamicArray << endl;

  dinamicArray -= 99;
  cout << "Removed 99, size: " << dinamicArray.getSize() << ", values: " << dinamicArray << endl;

  try
  {
    int i = dinamicArray[20];
  }
  catch (DinamikusTomb<int>::TombTulindexelesKivetel &e)
  {
    cout << "dinamicArray[20] " << e.getMsg() << endl;
  }
}
