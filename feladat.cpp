// g++ std=c++1y -static -O2
// g++ --debug feladat.cpp -o cucucu
#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
using namespace std;

template <class T, int N, int M, class Left, class Right>
class MatSum;

template <class T, int N, int M, class Left, class Right>
class MatSub;

template <class T, int N, int M, class Left, class Right>
class MatMulConst;

template <class T, int N, int M, class Left, class Right>
class MatMulMat;

#pragma region my_matrix

/**
 * Az osztálysablon neve my_matrix.
 * A sablon paraméterezése:
 *   - T: a mátrix alaptípusa
 *   - N: a mátrix sorainak száma
 *   - M: a mátrix oszlopainak száma
 * A sablonpéldány a matrix_base osztályból származik (amely rendelkezik
 * default konstruktorral). A beadott feladatban a matrix_base osztályt nem
 * kell (nem szabad) megvalósítani!
 */
template <class T, int N, int M>
class my_matrix /* : matrix_base */
{
private:
  T data[N][M];

public:
  /** A sablonpéldány rendelkezik default konstruktorral. */
  my_matrix() {}
  /**
   * A mátrix elemeihez való hozzáférést a kétparaméteres függvényhívás
   * operátor felüldefiniálása biztosítja.
   */
  const T &operator()(int n, int m) const;
  T &operator()(int n, int m);

  template <class Left, class Right>
  my_matrix<T, N, M> operator=(const MatSum<T, N, M, Left, Right> &v)
  {
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        data[i][j] = v(i, j);
      }
    }

    return *this;
  }

  template <class Left, class Right>
  my_matrix<T, N, M> operator=(const MatSub<T, N, M, Left, Right> &v)
  {
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        data[i][j] = v(i, j);
      }
    }

    return *this;
  }

  template <class Left, class Right>
  my_matrix<T, N, M> operator=(const MatMulConst<T, N, M, Left, Right> &v)
  {
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        data[i][j] = v(i, j);
      }
    }

    return *this;
  }

  template <class Left, class Right>
  my_matrix<T, N, M> operator=(const MatMulMat<T, N, M, Left, Right> &v)
  {
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        data[i][j] = v(i, j);
      }
    }

    return *this;
  }
};

template <class T, int N, int M>
const T &my_matrix<T, N, M>::operator()(int n, int m) const
{
  return data[n][m];
}

template <class T, int N, int M>
T &my_matrix<T, N, M>::operator()(int n, int m)
{
  return data[n][m];
}

#pragma endregion my_matrix

#pragma region Sum

template <class T, int N, int M, class Left, class Right>
class MatSum
{
  const Left &left;
  const Right &right;

public:
  MatSum(const Left &l, const Right &r) : left(l), right(r) {}

  T operator()(int n, int m) const;
};

template <class T, int N, int M, class Left, class Right>
T MatSum<T, N, M, Left, Right>::operator()(int n, int m) const
{
  return left(n, m) + right(n, m);
}

template <class T, int N, int M>
inline auto operator+(const my_matrix<T, N, M> &l, const my_matrix<T, N, M> &r)
{
  return MatSum<T, N, M, my_matrix<T, N, M>, my_matrix<T, N, M>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator+(const MatSum<T, N, M, Left, Right> &l, const my_matrix<T, N, M> &r)
{
  return MatSum<T, N, M, MatSum<T, N, M, Left, Right>, my_matrix<T, N, M>>(l, r);
}

#pragma endregion Sum

#pragma region Sub

template <class T, int N, int M, class Left, class Right>
class MatSub
{
  const Left &left;
  const Right &right;

public:
  MatSub(const Left &l, const Right &r) : left(l), right(r) {}

  T operator()(int n, int m) const;
};

template <class T, int N, int M, class Left, class Right>
T MatSub<T, N, M, Left, Right>::operator()(int n, int m) const
{
  return left(n, m) - right(n, m);
}

template <class T, int N, int M>
inline auto operator-(const my_matrix<T, N, M> &l, const my_matrix<T, N, M> &r)
{
  return MatSub<T, N, M, my_matrix<T, N, M>, my_matrix<T, N, M>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator-(const MatSub<T, N, M, Left, Right> &l, const my_matrix<T, N, M> &r)
{
  return MatSub<T, N, M, MatSub<T, N, M, Left, Right>, my_matrix<T, N, M>>(l, r);
}

#pragma endregion Sub

#pragma region MulConst

template <class T, int N, int M, class Left, class Right>
class MatMulConst
{
  const Left &left;
  const Right &right;

public:
  MatMulConst(const Left &l, const Right &r) : left(l), right(r) {}

  T operator()(int n, int m) const;
};

template <class T, int N, int M, class Left, class Right>
T MatMulConst<T, N, M, Left, Right>::operator()(int n, int m) const
{
  return left(n, m) * right;
}

template <class T, int N, int M>
inline auto operator*(const my_matrix<T, N, M> &l, const T &r)
{
  return MatMulConst<T, N, M, my_matrix<T, N, M>, T>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator*(const MatMulConst<T, N, M, Left, Right> &l, const T &r)
{
  return MatMulConst<T, N, M, MatMulConst<T, N, M, Left, Right>, T>(l, r);
}

#pragma endregion MulConst

#pragma region MulMat

template <class T, int N, int M, class Left, class Right>
class MatMulMat
{
  const Left &left;
  const Right &right;

public:
  MatMulMat(const Left &l, const Right &r) : left(l), right(r) {}

  T operator()(int n, int m) const;
};

template <class T, int N, int M, class Left, class Right>
T MatMulMat<T, N, M, Left, Right>::operator()(int n, int m) const
{
  return left(n, m) * left(n, m); // TODO
}

template <class T, int N, int M>
inline auto operator*(const my_matrix<T, N, M> &l, my_matrix<T, M, N> &r)
{
  return MatMulMat<T, N, M, my_matrix<T, N, M>, my_matrix<T, M, N>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator*(const MatMulMat<T, N, M, Left, Right> &l, my_matrix<T, M, N> &r)
{
  return MatMulMat<T, N, M, MatMulMat<T, N, M, Left, Right>, my_matrix<T, M, N>>(l, r);
}

#pragma endregion MulConst

#pragma region Debug

template <class T, int N, int M>
void printThatFuckingMatrix(string s, my_matrix<T, N, M> &maci)
{
  cout << s << endl;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      cout << setw(10) << maci(i, j);
    }
    cout << endl;
  }
  cout << endl;
}

#pragma endregion Debug

/**
 * Példa a mátrix sablon egy felhasználására. A beadott feladatban nem szabad
 * szerepelnie.
 */
int main()
{
  const int N = 3;
  const int M = 3;
  my_matrix<int, N, M> mtx1;
  my_matrix<int, N, M> mtx2;
  my_matrix<int, N, M> mtx3;
  my_matrix<int, N, M> mtx4;

  // my_matrix<double, N, M> mtx1;
  // my_matrix<double, N, M> mtx2;
  // my_matrix<double, N, M> mtx3;
  // my_matrix<double, N, M> mtx4;

  // int seed
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
    {
      mtx1(i, j) = i + j + (2 * i);
      mtx2(i, j) = i * j + (3 * i);
      mtx3(i, j) = i + j + (4 * i) + 1;
    }

  // double seed
  // for (int i = 0; i < N; i++)
  //   for (int j = 0; j < M; j++)
  //   {
  //     mtx1(i, j) = i + j + (2 * i) / 1.2;
  //     mtx2(i, j) = i * j + (3 * i) / 3.14;
  //     mtx3(i, j) = i + j + (4 * i) + 1 / 2.71;
  //   }

  printThatFuckingMatrix("mtx1 =", mtx1);
  printThatFuckingMatrix("mtx2 =", mtx2);
  printThatFuckingMatrix("mtx3 =", mtx3);

  cout << endl
       << endl;

#pragma region Add
  // mtx4 = mtx1 + mtx3;
  // printThatFuckingMatrix("mtx1 + mtx3 =", mtx4);

  mtx4 = mtx1 + mtx2 + mtx3;
  printThatFuckingMatrix("mtx1 + mtx2 + mtx3 =", mtx4);

  // mtx4 = mtx1 + mtx2 + mtx3 + mtx1;
  // printThatFuckingMatrix("mtx1 + mtx2 + mtx3 + mtx1 =", mtx4);
#pragma endregion

#pragma region Sub
  // mtx4 = mtx1 - mtx3;
  // printThatFuckingMatrix("mtx1 - mtx3 =", mtx4);

  // mtx4 = mtx1 - mtx2 - mtx3;
  // printThatFuckingMatrix("mtx1 - mtx2 - mtx3 =", mtx4);

  // mtx4 = mtx1 - mtx2 - mtx3 - mtx1;
  // printThatFuckingMatrix("mtx1 - mtx2 - mtx3 - mtx1 =", mtx4);

#pragma endregion

#pragma region Mul with Constant
  mtx4 = mtx4 * 3;
  // mtx4 = mtx4 * 3.141592;
  printThatFuckingMatrix("mtx4 * 4 =", mtx4);
#pragma endregion

  return 0;
}
