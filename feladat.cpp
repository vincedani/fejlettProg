/**
 * MatSum osztálysablon.
 * Az összeadás műveletet valósítja meg NxM mátrixok között.
 * NxM = NxM + NxM
 *
 * A sablon paraméterezése:
 * - T: a mátrix alaptípusa
 * - N: a mátrix sorainak száma
 * - M: a mátrix oszlopainak száma
 * - Left: az összeadás baloldali operandusának típusa
 * - Right: az összeadás jobboldali operandusának típusa
 */
template <class T, int N, int M, class Left, class Right>
class MatSum;

/**
 * MatSub osztálysablon.
 * Az kivonás műveletet valósítja meg NxM mátrixok között.
 * NxM = NxM - NxM
 *
 * A sablon paraméterezése:
 * - T: a mátrix alaptípusa
 * - N: a mátrix sorainak száma
 * - M: a mátrix oszlopainak száma
 * - Left: az kivonás baloldali operandusának típusa
 * - Right: az kivonás jobboldali operandusának típusa
 */
template <class T, int N, int M, class Left, class Right>
class MatSub;

/**
 * MatMulConst osztálysablon.
 * Az szorzás műveletet valósítja meg NxM mátrix és a mátrix alaptípusa (T)
 * között.
 * NxM = NxM * T
 * NxM = T * NxM
 *
 * A sablon paraméterezése:
 * - T: a mátrix alaptípusa
 * - N: a mátrix sorainak száma
 * - M: a mátrix oszlopainak száma
 * - Left: az szorzás baloldali operandusának típusa
 * - Right: az szorzás jobboldali operandusának típusa
 */
template <class T, int N, int M, class Left, class Right>
class MatMulConst;

/**
 * MatMulMat osztálysablon.
 * Az szorzás műveletet valósítja meg NxK és KxM mátrixok között. Az eredmény
 * NxM mátrix lesz.
 * NxM = NxK * KxM
 *
 * A sablon paraméterezése:
 * - T: a mátrix alaptípusa
 * - N: a baloldali mátrix sorainak száma
 * - M: a jobboldali mátrix sorainak száma
 * - K: az baloldali operandus mátrix oszlopainak száma
 * - Left: az szorzás baloldali operandusának típusa
 * - Right: az szorzás jobboldali operandusának típusa
 */
template <class T, int N, int M, int K, class Left, class Right>
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
class my_matrix : matrix_base
{
private:
  /**
   * A sablonpéldány rendelkezik egy T típusú NxM méretű tömbbel,
   * mely a mátrix értékeit tárolja.
   */
  T data[N][M];

public:
  /** A sablonpéldány rendelkezik default konstruktorral. */
  my_matrix() {}
  /**
   * A mátrix elemeihez való hozzáférést a kétparaméteres függvényhívás
   * operátor felüldefiniálása biztosítja.
   */
  const T &operator()(int n, int m) const;
  /**
   * Lásd const T &operator()(int n, int m) const; dokumentációja.
   */
  T &operator()(int n, int m);

  /**
   * Az egyenlőség operátor felüldefiniálása, mely MatSum objektumból készít
   * my_matrix típusú objektumot.
   * obj (my_matrix) = result (MatSum<...>)
   */
  template <class Left, class Right>
  my_matrix<T, N, M> &operator=(const MatSum<T, N, M, Left, Right> &v)
  {
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
        data[i][j] = v(i, j);

    return *this;
  }

  /**
   * Az egyenlőség operátor felüldefiniálása, mely MatSub objektumból készít
   * my_matrix típusú objektumot.
   * obj (my_matrix) = result (MatSub<...>)
   */
  template <class Left, class Right>
  my_matrix<T, N, M> &operator=(const MatSub<T, N, M, Left, Right> &v)
  {
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
        data[i][j] = v(i, j);

    return *this;
  }

  /**
   * Az egyenlőség operátor felüldefiniálása, mely MatMulConst objektumból készít
   * my_matrix típusú objektumot.
   * obj (my_matrix) = result (MatMulConst<...>)
   */
  template <class Left, class Right>
  my_matrix<T, N, M> &operator=(const MatMulConst<T, N, M, Left, Right> &v)
  {
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
        data[i][j] = v(i, j);

    return *this;
  }

  /**
   * Az egyenlőség operátor felüldefiniálása, mely MatMulMat objektumból készít
   * my_matrix típusú objektumot.
   * obj (my_matrix) = result (MatMulMat<...>)
   */
  template <int K, class Left, class Right>
  my_matrix<T, N, M> &operator=(const MatMulMat<T, N, M, K, Left, Right> &v)
  {
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
        data[i][j] = v(i, j);

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

/**
 * MatSum osztálysablon.
 * Az összeadás műveletet valósítja meg NxM mátrixok között.
 * NxM = NxM + NxM
 *
 * A sablon paraméterezése:
 * - T: a mátrix alaptípusa
 * - N: a mátrix sorainak száma
 * - M: a mátrix oszlopainak száma
 * - Left: az összeadás baloldali operandusának típusa
 * - Right: az összeadás jobboldali operandusának típusa
 */
template <class T, int N, int M, class Left, class Right>
class MatSum
{
  /**
   * A mátrix baloldali operandusát tárolja el, amely Left típusú.
   */
  const Left &left;
  /**
   * A mátrix jobboldali operandusát tárolja el, amely Right típusú.
   */
  const Right &right;

public:
  /**
   * Az osztály konstruktora, mely a kapott paramétereket inicializálja.
   */
  MatSum(const Left &l, const Right &r) : left(l), right(r) {}

  /**
   * A mátrix elemeihez való hozzáférést a kétparaméteres függvényhívás
   * operátor felüldefiniálása biztosítja.
   */
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

template <class T, int N, int M, class Left, class Right>
inline auto operator+(const my_matrix<T, N, M> &l, const MatSum<T, N, M, Left, Right> &r)
{
  return MatSum<T, N, M, my_matrix<T, N, M>, MatSum<T, N, M, Left, Right>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator+(const MatSub<T, N, M, Left, Right> &l, const my_matrix<T, N, M> &r)
{
  return MatSum<T, N, M, MatSub<T, N, M, Left, Right>, my_matrix<T, N, M>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator+(const my_matrix<T, N, M> &l, const MatSub<T, N, M, Left, Right> &r)
{
  return MatSum<T, N, M, my_matrix<T, N, M>, MatSub<T, N, M, Left, Right>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator+(const MatMulConst<T, N, M, Left, Right> &l, const my_matrix<T, N, M> &r)
{
  return MatSum<T, N, M, MatMulConst<T, N, M, Left, Right>, my_matrix<T, N, M>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator+(const my_matrix<T, N, M> &l, const MatMulConst<T, N, M, Left, Right> &r)
{
  return MatSum<T, N, M, my_matrix<T, N, M>, MatMulConst<T, N, M, Left, Right>>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator+(const MatMulMat<T, N, M, K, Left, Right> &l, const my_matrix<T, N, M> &r)
{
  return MatSum<T, N, M, MatMulMat<T, N, M, K, Left, Right>, my_matrix<T, N, M>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator+(const MatSum<T, N, M, L, R> &l, const MatSum<T, N, M, L1, R1> &r)
{
  return MatSum<T, N, M, MatSum<T, N, M, L, R>, MatSum<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator+(const MatSum<T, N, M, L, R> &l, const MatSub<T, N, M, L1, R1> &r)
{
  return MatSum<T, N, M, MatSum<T, N, M, L, R>, MatSub<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator+(const MatSub<T, N, M, L1, R1> &l, const MatSum<T, N, M, L, R> &r)
{
  return MatSum<T, N, M, MatSub<T, N, M, L1, R1>, MatSum<T, N, M, L, R>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator+(const MatSum<T, N, M, L, R> &l, const MatMulConst<T, N, M, L1, R1> &r)
{
  return MatSum<T, N, M, MatSum<T, N, M, L, R>, MatMulConst<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator+(const MatSum<T, N, M, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatSum<T, N, M, MatSum<T, N, M, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator+(const MatSub<T, N, M, L, R> &l, const MatSub<T, N, M, L1, R1> &r)
{
  return MatSum<T, N, M, MatSub<T, N, M, L, R>, MatSub<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator+(const MatSub<T, N, M, L, R> &l, const MatMulConst<T, N, M, L1, R1> &r)
{
  return MatSum<T, N, M, MatSub<T, N, M, L, R>, MatMulConst<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator+(const MatSub<T, N, M, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatSum<T, N, M, MatSub<T, N, M, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator+(const MatMulConst<T, N, M, L, R> &l, const MatMulConst<T, N, M, L1, R1> &r)
{
  return MatSum<T, N, M, MatMulConst<T, N, M, L, R>, MatMulConst<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator+(const MatMulConst<T, N, M, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatSum<T, N, M, MatMulConst<T, N, M, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator+(const MatMulMat<T, N, M, K, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatSum<T, N, M, MatMulMat<T, N, M, K, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

#pragma endregion Sum

#pragma region Sub

/**
 * MatSub osztálysablon.
 * Az kivonás műveletet valósítja meg NxM mátrixok között.
 * NxM = NxM - NxM
 *
 * A sablon paraméterezése:
 * - T: a mátrix alaptípusa
 * - N: a mátrix sorainak száma
 * - M: a mátrix oszlopainak száma
 * - Left: az kivonás baloldali operandusának típusa
 * - Right: az kivonás jobboldali operandusának típusa
 */
template <class T, int N, int M, class Left, class Right>
class MatSub
{
  /**
   * A mátrix baloldali operandusát tárolja el, amely Left típusú.
   */
  const Left &left;
  /**
   * A mátrix jobboldali operandusát tárolja el, amely Right típusú.
   */
  const Right &right;

public:
  /**
   * Az osztály konstruktora, mely a kapott paramétereket inicializálja.
   */
  MatSub(const Left &l, const Right &r) : left(l), right(r) {}

  /**
   * A mátrix elemeihez való hozzáférést a kétparaméteres függvényhívás
   * operátor felüldefiniálása biztosítja.
   */
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

template <class T, int N, int M, class Left, class Right>
inline auto operator-(const my_matrix<T, N, M> &l, const MatSub<T, N, M, Left, Right> &r)
{
  return MatSub<T, N, M, my_matrix<T, N, M>, MatSub<T, N, M, Left, Right>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator-(const MatSum<T, N, M, Left, Right> &l, const my_matrix<T, N, M> &r)
{
  return MatSub<T, N, M, MatSum<T, N, M, Left, Right>, my_matrix<T, N, M>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator-(const my_matrix<T, N, M> &l, const MatSum<T, N, M, Left, Right> &r)
{
  return MatSub<T, N, M, my_matrix<T, N, M>, MatSum<T, N, M, Left, Right>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator-(const MatMulConst<T, N, M, Left, Right> &l, const my_matrix<T, N, M> &r)
{
  return MatSub<T, N, M, MatMulConst<T, N, M, Left, Right>, my_matrix<T, N, M>>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator-(const MatMulMat<T, N, M, K, Left, Right> &l, const my_matrix<T, N, M> &r)
{
  return MatSub<T, N, M, MatMulMat<T, N, M, K, Left, Right>, my_matrix<T, N, M>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator-(const MatSum<T, N, M, L, R> &l, const MatSum<T, N, M, L1, R1> &r)
{
  return MatSub<T, N, M, MatSum<T, N, M, L, R>, MatSum<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator-(const MatSum<T, N, M, L, R> &l, const MatSub<T, N, M, L1, R1> &r)
{
  return MatSub<T, N, M, MatSum<T, N, M, L, R>, MatSub<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator-(const MatSub<T, N, M, L1, R1> &l, const MatSum<T, N, M, L, R> &r)
{
  return MatSub<T, N, M, MatSub<T, N, M, L1, R1>, MatSum<T, N, M, L, R>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator-(const MatSum<T, N, M, L, R> &l, const MatMulConst<T, N, M, L1, R1> &r)
{
  return MatSub<T, N, M, MatSum<T, N, M, L, R>, MatMulConst<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator-(const MatSum<T, N, M, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatSub<T, N, M, MatSum<T, N, M, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator-(const MatSub<T, N, M, L, R> &l, const MatSub<T, N, M, L1, R1> &r)
{
  return MatSub<T, N, M, MatSub<T, N, M, L, R>, MatSub<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator-(const MatSub<T, N, M, L, R> &l, const MatMulConst<T, N, M, L1, R1> &r)
{
  return MatSub<T, N, M, MatSub<T, N, M, L, R>, MatMulConst<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator-(const MatSub<T, N, M, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatSub<T, N, M, MatSub<T, N, M, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

template <class T, int N, int M, class L, class R, class L1, class R1>
inline auto operator-(const MatMulConst<T, N, M, L, R> &l, const MatMulConst<T, N, M, L1, R1> &r)
{
  return MatSub<T, N, M, MatMulConst<T, N, M, L, R>, MatMulConst<T, N, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator-(const MatMulConst<T, N, M, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatSub<T, N, M, MatMulConst<T, N, M, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator-(const MatMulMat<T, N, M, K, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatSub<T, N, M, MatMulMat<T, N, M, K, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

#pragma endregion Sub

#pragma region MulConst

/**
 * MatMulConst osztálysablon.
 * Az szorzás műveletet valósítja meg NxM mátrix és a mátrix alaptípusa (T)
 * között.
 * NxM = NxM * T
 * NxM = T * NxM
 *
 * A sablon paraméterezése:
 * - T: a mátrix alaptípusa
 * - N: a mátrix sorainak száma
 * - M: a mátrix oszlopainak száma
 * - Left: az szorzás baloldali operandusának típusa
 * - Right: az szorzás jobboldali operandusának típusa
 */
template <class T, int N, int M, class Left, class Right>
class MatMulConst
{
  /**
   * A mátrix baloldali operandusát tárolja el, amely Left típusú.
   */
  const Left &left;
  /**
   * A mátrix jobboldali operandusát tárolja el, amely Right típusú.
   */
  const Right &right;

public:
  /**
   * Az osztály konstruktora, mely a kapott paramétereket inicializálja.
   */
  MatMulConst(const Left &l, const Right &r) : left(l), right(r) {}

  /**
   * A mátrix elemeihez való hozzáférést a kétparaméteres függvényhívás
   * operátor felüldefiniálása biztosítja.
   */
  T operator()(int n, int m) const;
};

/**
 * MatMulConst osztálysablon egy specializációja,
 * NxM = NxM * T
 * T - a mátrix alaptípusa
 */
template <class T, int N, int M, class Left>
class MatMulConst<T, N, M, Left, T>
{
  /**
   * A mátrix baloldali operandusát tárolja el, amely Left típusú.
   */
  const Left &left;
  /**
   * A mátrix jobboldali operandusát tárolja el, amely T típusú.
   */
  const T &right;

public:
  /**
   * Az osztály konstruktora, mely a kapott paramétereket inicializálja.
   */
  MatMulConst(const Left &l, const T &r) : left(l), right(r) {}

  /**
   * A mátrix elemeihez való hozzáférést a kétparaméteres függvényhívás
   * operátor felüldefiniálása biztosítja.
   */
  T operator()(int n, int m) const
  {
    return left(n, m) * right;
  };
};

/**
 * MatMulConst osztálysablon egy specializációja,
 * NxM = T * NxM
 * T - a mátrix alaptípusa
 */
template <class T, int N, int M, class Right>
class MatMulConst<T, N, M, T, Right>
{
  /**
   * A mátrix baloldali operandusát tárolja el, amely T típusú.
   */
  const T &left;
  /**
   * A mátrix jobboldali operandusát tárolja el, amely Right típusú.
   */
  const Right &right;

public:
  /**
   * Az osztály konstruktora, mely a kapott paramétereket inicializálja.
   */
  MatMulConst(const T &l, const Right &r) : left(l), right(r) {}

  /**
   * A mátrix elemeihez való hozzáférést a kétparaméteres függvényhívás
   * operátor felüldefiniálása biztosítja.
   */
  T operator()(int n, int m) const
  {
    return left * right(n, m);
  };
};

template <class T, int N, int M>
inline auto operator*(const my_matrix<T, N, M> &l, const T &r)
{
  return MatMulConst<T, N, M, my_matrix<T, N, M>, T>(l, r);
}

template <class T, int N, int M>
inline auto operator*(const T &l, const my_matrix<T, N, M> &r)
{
  return MatMulConst<T, N, M, T, my_matrix<T, N, M>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator*(const MatSum<T, N, M, Left, Right> &l, const T &r)
{
  return MatMulConst<T, N, M, MatSum<T, N, M, Left, Right>, T>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator*(const T &l, const MatSum<T, N, M, Left, Right> &r)
{
  return MatMulConst<T, N, M, T, MatSum<T, N, M, Left, Right>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator*(const MatSub<T, N, M, Left, Right> &l, const T &r)
{
  return MatMulConst<T, N, M, MatSub<T, N, M, Left, Right>, T>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator*(const T &l, const MatSub<T, N, M, Left, Right> &r)
{
  return MatMulConst<T, N, M, T, MatSub<T, N, M, Left, Right>>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator*(const MatMulConst<T, N, M, Left, Right> &l, const T &r)
{
  return MatMulConst<T, N, M, MatMulConst<T, N, M, Left, Right>, T>(l, r);
}

template <class T, int N, int M, class Left, class Right>
inline auto operator*(const T &l, const MatMulConst<T, N, M, Left, Right> &r)
{
  return MatMulConst<T, N, M, T, MatMulConst<T, N, M, Left, Right>>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const MatMulMat<T, N, M, K, Left, Right> &l, const T &r)
{
  return MatMulConst<T, N, M, MatMulMat<T, N, M, K, Left, Right>, T>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const T &l, const MatMulMat<T, N, M, K, Left, Right> &r)
{
  return MatMulConst<T, N, M, T, MatMulMat<T, N, M, K, Left, Right>>(l, r);
}

#pragma endregion

#pragma region MulMat

/**
 * MatMulMat osztálysablon.
 * Az szorzás műveletet valósítja meg NxK és KxM mátrixok között. Az eredmény
 * NxM mátrix lesz.
 * NxM = NxK * KxM
 *
 * A sablon paraméterezése:
 * - T: a mátrix alaptípusa
 * - N: a baloldali mátrix sorainak száma
 * - M: a jobboldali mátrix sorainak száma
 * - K: az baloldali operandus mátrix oszlopainak száma
 * - Left: az szorzás baloldali operandusának típusa
 * - Right: az szorzás jobboldali operandusának típusa
 */
template <class T, int N, int M, int K, class Left, class Right>
class MatMulMat
{
  /**
   * A mátrix baloldali operandusát tárolja el, amely Left típusú.
   */
  const Left &left;
  /**
   * A mátrix jobboldali operandusát tárolja el, amely Right típusú.
   */
  const Right &right;

public:
  /**
   * Az osztály konstruktora, mely a kapott paramétereket inicializálja.
   */
  MatMulMat(const Left &l, const Right &r) : left(l), right(r) {}

  /**
   * A mátrix elemeihez való hozzáférést a kétparaméteres függvényhívás
   * operátor felüldefiniálása biztosítja.
   */
  T operator()(int n, int m) const;
};

template <class T, int N, int M, int K, class Left, class Right>
T MatMulMat<T, N, M, K, Left, Right>::operator()(int n, int m) const
{
  T Cnm = 0;

  for (int i = 0; i < K; i++)
    Cnm += left(n, i) * right(i, m);

  return Cnm;
}

template <class T, int N, int M, int K>
inline auto operator*(const my_matrix<T, N, K> &l, const my_matrix<T, K, M> &r)
{
  return MatMulMat<T, N, M, K, my_matrix<T, N, K>, my_matrix<T, K, M>>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const MatSum<T, N, M, Left, Right> &l, const my_matrix<T, K, M> &r)
{
  return MatMulMat<T, N, M, K, MatSum<T, N, M, Left, Right>, my_matrix<T, K, M>>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const my_matrix<T, N, K> &l, const MatSum<T, K, M, Left, Right> &r)
{
  return MatMulMat<T, N, M, K, my_matrix<T, N, K>, MatSum<T, K, M, Left, Right>>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const MatSub<T, N, M, Left, Right> &l, const my_matrix<T, K, M> &r)
{
  return MatMulMat<T, N, M, K, MatSub<T, N, M, Left, Right>, my_matrix<T, K, M>>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const MatMulConst<T, N, M, Left, Right> &l, const my_matrix<T, K, M> &r)
{
  return MatMulMat<T, N, M, K, MatMulConst<T, N, M, Left, Right>, my_matrix<T, K, M>>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const my_matrix<T, N, K> &l, const MatMulConst<T, K, M, Left, Right> &r)
{
  return MatMulMat<T, N, M, K, my_matrix<T, N, K>, MatMulConst<T, K, M, Left, Right>>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const MatMulMat<T, N, M, K, Left, Right> &l, const my_matrix<T, M, N> &r)
{
  return MatMulMat<T, N, M, K, MatMulMat<T, N, M, K, Left, Right>, my_matrix<T, M, N>>(l, r);
}

template <class T, int N, int M, int K, class Left, class Right>
inline auto operator*(const my_matrix<T, N, K> &l, const MatMulMat<T, N, M, K, Left, Right> &r)
{
  return MatMulMat<T, N, M, K, my_matrix<T, N, K>, MatMulMat<T, N, M, K, Left, Right>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator*(const MatSum<T, N, M, L, R> &l, const MatSum<T, K, M, L1, R1> &r)
{
  return MatMulMat<T, N, M, K, MatSum<T, N, M, L, R>, MatSum<T, K, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator*(const MatSum<T, N, K, L, R> &l, const MatSub<T, K, M, L1, R1> &r)
{
  return MatMulMat<T, N, M, K, MatSum<T, N, K, L, R>, MatSub<T, K, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator*(const MatSum<T, N, M, L, R> &l, const MatMulConst<T, K, M, L1, R1> &r)
{
  return MatMulMat<T, N, M, K, MatSum<T, N, M, L, R>, MatMulConst<T, K, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator*(const MatSum<T, N, M, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatMulMat<T, N, M, K, MatSum<T, N, M, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator*(const MatMulMat<T, N, M, K, L1, R1> &l, const MatSum<T, N, M, L, R> &r)
{
  return MatMulMat<T, N, M, K, MatMulMat<T, N, M, K, L1, R1>, MatSum<T, N, M, L, R>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator*(const MatSub<T, N, M, L, R> &l, const MatSub<T, K, M, L1, R1> &r)
{
  return MatMulMat<T, N, M, K, MatSub<T, N, M, L, R>, MatSub<T, K, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator*(const MatSub<T, N, M, L, R> &l, const MatMulConst<T, K, M, L1, R1> &r)
{
  return MatMulMat<T, N, M, K, MatSub<T, N, M, L, R>, MatMulConst<T, K, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator*(const MatSub<T, N, M, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatMulMat<T, N, M, K, MatSub<T, N, M, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator*(const MatMulConst<T, N, M, L, R> &l, const MatMulConst<T, K, M, L1, R1> &r)
{
  return MatMulMat<T, N, M, K, MatMulConst<T, N, M, L, R>, MatMulConst<T, K, M, L1, R1>>(l, r);
}

template <class T, int N, int M, int K, class L, class R, class L1, class R1>
inline auto operator*(const MatMulConst<T, N, M, L, R> &l, const MatMulMat<T, N, M, K, L1, R1> &r)
{
  return MatMulMat<T, N, M, K, MatMulConst<T, N, M, L, R>, MatMulMat<T, N, M, K, L1, R1>>(l, r);
}

template <class T, int N, int M, int J, int K, int K1, class L, class R, class L1, class R1>
inline auto operator*(const MatMulMat<T, N, M, K, L, R> &l, const MatMulMat<T, M, J, K1, L1, R1> &r)
{
  return MatMulMat<T, N, J, M, MatMulMat<T, N, M, K, L, R>, MatMulMat<T, M, J, K1, L1, R1>>(l, r);
}

#pragma endregion
