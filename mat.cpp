#define DIM 2

template <typename T>
struct mat{
  T a[DIM][DIM];
  mat () {
    memset(a, 0, sizeof(T) * DIM * DIM);
  }

  void identity () {
    for (int i = 0; i < DIM; ++i)
      for (int j = 0; j < DIM; ++j) a[i][j] = i == j;
  }
  
  mat<T> operator * (const mat<T> &b) const {
    mat<T> c;
    for (int k = 0; k < DIM; k++) { 
      for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
          c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]);
        }
      }
    }
    return c;
  }
};
