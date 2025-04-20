#include <math.h>

double exp_base2(double x) {
   const double LOG2E = 1.44269504089; // log2(e)
   return pow(2.0, x * LOG2E);
}

double exp_taylor9(double x) {
   // Coefficients précalculés pour les termes jusqu'à x^8
   const double c3 = 0.166667;   // 1/6
   const double c4 = 0.041667;   // 1/24
   const double c5 = 0.008333;   // 1/120
   const double c6 = 1.0/720.0;
   const double c7 = 1.0/5040.0;
   const double c8 = 1.0/40320.0;

   double res = 1.0 + x;
   double X = x * x;

   res += 0.5 * X;         // x^2 / 2
   X *= x;                 // x^3
   res += c3 * X;          // x^3 / 6
   X *= x;                 // x^4
   res += c4 * X;          // x^4 / 24
   X *= x;                 // x^5
   res += c5 * X;          // x^5 / 120
   X *= x;                 // x^6
   res += c6 * X;          // x^6 / 720
   X *= x;                 // x^7
   res += c7 * X;          // x^7 / 5040
   X *= x;                 // x^8
   res += c8 * X;          // x^8 / 40320

   return res;
}




#ifdef OPT1

#include <math.h>
void baseline(unsigned n, double a[n][n], const double b[n], const double c[n])

{

   unsigned i, j;
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
         a[i][j] = exp(b[i] + c[j]);
   }
}
#elif defined OPT1_2
#include <math.h>
#include <math.h>
void baseline(unsigned n, double a[n][n], const double b[n], const double c[n])

{

   unsigned i, j;
   for (i = 0; i < n; i++)
   {
      double bi = b[i];
      for (j = 0; j < n; j++)
         a[i][j] = exp(bi + c[j]);
   }
}


#elif defined OPT2
#include <math.h>

void baseline(unsigned n, double a[n][n], const double b[n], const double c[n]) {
   unsigned tile_size = 32; // Taille du bloc (modifiable selon l'architecture)
   unsigned i, j, ii, jj;

   for (ii = 0; ii < n; ii += tile_size) {
       for (jj = 0; jj < n; jj += tile_size) {
           for (i = ii; i < ii + tile_size && i < n; i++) {
               double bi = b[i];
               for (j = jj; j < jj + tile_size && j < n; j++) {
                   a[i][j] = exp(bi + c[j]);
               }
           }
       }
   }
}




#elif defined OPT3
#include <math.h>

void baseline(unsigned n, double a[n][n], const double b[n], const double c[n]) {
   unsigned tile_size = 32; // Taille du bloc (modifiable selon l'architecture)
   unsigned i, j, ii, jj;

   for (ii = 0; ii < n; ii += tile_size) {
       for (jj = 0; jj < n; jj += tile_size) {
           for (i = ii; i < ii + tile_size && i < n; i++) {
               double bi = b[i];
               for (j = jj; j < jj + tile_size && j < n; j++) {
                   a[i][j] = expf(bi + c[j]);
               }
           }
       }
   }
}

#elif defined OPT4
#include <math.h>

void baseline(unsigned n, double a[n][n], const double b[n], const double c[n]) {
   unsigned tile_size = 32; // Taille du bloc (modifiable selon l'architecture)
   unsigned i, j, ii, jj;

   for (ii = 0; ii < n; ii += tile_size) {
       for (jj = 0; jj < n; jj += tile_size) {
           for (i = ii; i < ii + tile_size && i < n; i++) {
               double bi = b[i];
               for (j = jj; j < jj + tile_size && j < n; j++) {
                   a[i][j] = exp_base2(bi + c[j]);
               }
           }
       }
   }
}
#elif defined OPT5
#include <math.h>

void baseline(unsigned n, double a[n][n], const double b[n], const double c[n]) {
   unsigned tile_size = 32; // Taille du bloc (modifiable selon l'architecture)
   unsigned i, j, ii, jj;

   for (ii = 0; ii < n; ii += tile_size) {
       for (jj = 0; jj < n; jj += tile_size) {
           for (i = ii; i < ii + tile_size && i < n; i++) {
               double bi = b[i];
               for (j = jj; j < jj + tile_size && j < n; j++) {
                   a[i][j] = exp_taylor9(bi + c[j]);
               }
           }
       }
   }
}


#elif defined OPT7

#include <math.h>
#include <omp.h>



void baseline(unsigned n, double a[n][n], const double b[n], const double c[n])
{
#pragma omp parallel for
   for (unsigned i = 0; i < n; i++)
   {
      double bi = b[i];
#pragma omp simd
      for (unsigned j = 0; j < n; j++)
      {
         a[i][j] = exp(bi + c[j]);
      }
   }
}
#elif defined OPT6
#include <math.h>
void baseline(unsigned n, double a[n][n], const double b[n], const double c[n])
{
   for (unsigned i = 0; i < n; i++)
   {
      double bi = b[i];
#pragma omp simd
      for (unsigned j = 0; j < n; j++)
      {
         a[i][j] = exp(bi + c[j]);
      }
   }
}
#elif defined OPT8

#include <math.h>
void baseline(unsigned n, double a[n][n], const double b[n], const double c[n]) {
   double temp[n];
   double temp1[n];
   for (unsigned j = 0; j < n; j++)
      temp[j] = exp(c[j]);
   for (unsigned i = 0; i < n; i++)
      temp1[i] = exp(b[i]);
   for (unsigned i = 0; i < n; i++) {
      for (unsigned j = 0; j < n; j++)
         a[i][j] = temp1[i]*temp[j];
   }
}

#elif defined OPT9
#include <math.h>
void baseline(unsigned n, double a[n][n], const double b[n], const double c[n])

{

   unsigned i, j;
   for (i = 0; i < n; i++)
   {
      double bi = b[i];
      for (j = 0; j < n; j++)
         a[i][j] = exp_taylor9(bi + c[j]);
   }
}


#else
#include <math.h>
void baseline(unsigned n, double a[n][n], const double b[n], const double c[n])

{

   unsigned i, j;
   for (j = 0; j < n; j++)
   {
      for (i = 0; i < n; i++)
         a[i][j] = exp(b[i] + c[j]);
   }
}

#endif
