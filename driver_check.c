#include <stdio.h>
#include <stdlib.h> // atoi, qsort
#include <stdint.h>

extern uint64_t rdtsc ();

// TODO: adjust for each kernel
extern void baseline (unsigned n , double a [ n ][ n ] ,const double b [ n ] ,const double c [ n ]); // dej   modifie
 
// TODO: adjust for each kernel 
// deja modifie
/*static void init_array2D (unsigned n, double a[n][n]) {
   int i, j;

   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         a[i][j] = (double) rand() / RAND_MAX;
}
*/
//jai ajoute ceci pour la declaration de b et c vu que ce sont des tableaux a une dimension
static void init_array1D (unsigned n, double b[n]) {
   int i;

   for (i=0; i<n; i++)
      b[i]= (double) rand() / RAND_MAX;
}

// TODO: adjust for each kernel
// jai modifie
static void print_array (int n, double  a[n][n], const char *output_file_name) {
   int i, j;

   FILE *fp = fopen (output_file_name, "w");
   if (fp == NULL) {
      fprintf (stderr, "Cannot write to %s\n", output_file_name);
      return;
   }

   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         fprintf (fp, "%f\n", a[i][j]);

   fclose (fp);
}
// jai ajoute celui ci
/*static void print_array1D (unsigned n, double b[n], const char *output_file_name) {
   int i;

   FILE *fp = fopen (output_file_name, "w");
   if (fp == NULL) {
      fprintf (stderr, "Cannot write to %s\n", output_file_name);
      return;
   }

   for (i=0; i<n; i++)
      fprintf (fp, "%f\n", b[i]);
   fclose (fp);
}*/

int main (int argc, char *argv[]) {
   /* check command line arguments */
   if (argc != 3) {
      fprintf (stderr, "Usage: %s <size> <output file name>\n", argv[0]);
      return 1;
   }

   /* get command line arguments */
   const unsigned size = atoi (argv[1]); /* problem size */
   const char *output_file_name = argv[2];

   /* allocate arrays. TODO: adjust for each kernel */
   double (*a)[size] = malloc (size * size * sizeof a[0][0]);
   double (*b) = malloc (size * sizeof b[0]); // jai modifie cette ligne vu que c'est 1D
   double (*c) = malloc (size * sizeof c[0]); // jai modifie cette ligne vu que c'est 1D

   /* init arrays */
   srand(0);
   init_array1D (size, c);
   init_array1D (size, b);

   /* print output */
   /* print output */
    baseline (size, a, b, c);
   print_array (size, a, output_file_name);

   /* free arrays. TODO: adjust for each kernel */ // je pense que ca va deja

   free (a);
   free (b);
   free (c);

   return EXIT_SUCCESS;
}
