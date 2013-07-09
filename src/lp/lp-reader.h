// Copyright 2011 Ewerton Assis and Juliane Oliveira
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __lp_reader_h__
#define __lp_reader_h__

typedef struct {
  size_t number_gt_eq;
  size_t number_lt_eq;
  size_t number_var_objf;
  size_t number_subf;
  double coefficients_objf[20];
  double table[20][20];
  double basis[20];
  double column_matrix[20];
  double c_objf[20];
} lp_problem_t;

lp_problem_t *
lp_problem_from_stdin ()
{
  int i, j, g, l, row, col, sub, var;
  double cj[20], basis[20], c[20], colmat[20], tab[20][20];
  lp_problem_t *problem = (lp_problem_t *) malloc (sizeof (lp_problem_t));

  printf ("Take 'M' as a bit smaller than any smallest number in the equations\n");
  printf ("Total number of 'greater than or equal to' equalities in subjective functions: ");
  scanf ("%d", &g);
  printf ("Total number of 'less than or equal to' equalities in subjective functions: "); 
  scanf ("%d", &l);
  printf ("Total number of artificial variables is %d\n", g);
  printf ("Enter the total number of variables in objective function: ");
  scanf ("%d", &var);
  printf ("Coefficients of the objective function: \n");
  for (i = 0; i < var; i++)
    scanf ("%lf", &cj[i]);
  printf ("Total number of subjective functions: \n");
  scanf ("%d", &sub);
  
  /* Table dimension */
  col = var + 4;
  row = sub + 2;
  for (i = 1; i < row - 1; i++)
    {
      printf ("\nEnter elements in %d-th row:\n", i);
      for (j = 4; j < col; j++)
        scanf ("%lf", &tab[i][j]);
    }
  printf ("\nEnter the basis:\n");
  for (i = 0; i < sub; i++)
    scanf ("%lf", &basis[i]);
  printf ("\nEnter the values of 'C' from objective function:\n");
  for (i = 0; i < sub; i++)
    scanf ("%lf", &c[i]);
  printf ("\nEnter the column matrix:\n");
  for (i = 0; i < sub; i++)
    scanf ("%lf", &colmat[i]);
  /* Initializing the table */
  for (i = 1; i < row - 1; i++)
    tab[i][0] = i;
  for (i = 1; i < row - 1; i++)
    {
      tab[i][1] = basis[i - 1];
      tab[i][2] = c[i - 1];
      tab[i][3] = colmat[i - 1];
    }
  printf ("\nThe matrix you have inserted:\n");
  printf ("---------------------------------------\n");
  for (i = 1; i < row - 1; i++)
    {
      for (j = 0; j < col; j++)
        printf ("%.3lf\t", tab[i][j]);
      printf ("\n");
    }
  printf ("---------------------------------------\n");
  for (i = 4; i < col; i++)
    tab[row - 1][i] = 0;
  tab[row - 1][3] = 0;

  problem->number_gt_eq = g;
  problem->number_lt_eq = l;
  problem->number_var_objf = var;
  problem->number_subf = sub;
  for (i = 0; i < 20; i++)
    problem->coefficients_objf[i] = cj[i];
  for (i = 0; i < 20; i++)
    for (j = 0; j < 20; j++)
      problem->table[i][j] = tab[i][j];
  for (i = 0; i < 20; i++)
    problem->basis[i] = basis[i];
  for (i = 0; i < 20; i++)
    problem->column_matrix[i] = colmat[i];
  for (i = 0; i < 20; i++)
    problem->c_objf[i] = c[i];
  return problem;
}

void
lp_problem_destroy (lp_problem_t *problem)
{
  free (problem);
}

#endif
