// Copyright 2011 Éwerton Assis
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

#ifndef __lp_bigm_solver_h__
#define __lp_bigm_solver_h__

#include "lp-reader.h"

void
lp_bigm_min (lp_problem_t *problem)
{
  int i, j, row, col, kc, kr, flag=-1, k;
  double sum, max, ba, kn;

  /* Starting the iteration */
  for (k = 0; k < 10; k++)
    {
      /* Initializing flag */
      flag = -1;
      /* Z0 */
      for (i = 1; i < row - 1; i++)
        problem->table[row-1][3] = problem->table[row-1][3] + problem->table[i][3] * problem->table[i][2];
      /* Zj - Cj */
      for (i = 4; i < col; i++)
        {
          sum = 0;
          for (j = 1; j < row - 1; j++)
            sum = problem->table[j][i] * problem->table[j][2] + sum;
          problem->table[row - 1][i] = sum - problem->coefficients_objf[i - 4];
        }
      /* Finding maximum in Zj - Cj */
      max = problem->table[row - 1][4];
      kc = 4;
      for (i = 4; i < col; i++)
        if (max < problem->table[row - 1][i])
          {
            max = problem->table[row - 1][i];
            kc = i;
          }
      /* Finding a b/a ratio */
      for (j = 1; j < row - 1; j++)
        if (problem->table[j][kc] > 0)
          {
            ba = (problem->column_matrix[j - 1] / problem->table[j][kc]);
            break;
          }
      kr = j;
      for (; j < row-1; j++)
        if ((problem->table[j][kc] > 0) &&
            ((problem->column_matrix[j-1] / problem->table[j][kc]) < ba))
          kr = j;
      /*Swapping key column with basis */
      problem->table[kr][1] = kc - 3;
      kn = problem->table[kr][kc];
      problem->table[kr][2] = problem->coefficients_objf[kc - 4];
      /* Dividing other rows by the formula */
      for (i = 1; i < row - 1; i++)
        if (i == kr)
          continue;
        else
          for (j = 3; j < kc; j++)
            problem->table[i][j] = problem->table[i][j] - ((problem->table[i][kc] * problem->table[kr][j]) / kn);
      for (i = 1; i < row - 1; i++)
        if (i == kr)
          continue;
        else
          for (j = kc + 1; j < col; j++)
            problem->table[i][j] = problem->table[i][j] - ((problem->table[i][kc] * problem->table[kr][j]) / kn);
      for (i = 1; i < row - 1; i++)
        if (i == kr)
          continue;
        else
          problem->table[i][kc] = problem->table[i][kc] - ((problem->table[i][kc] * problem->table[kr][kc]) / kn);
      /* Dividing key row by key number */
      for (i = 3; i < col; i++)
        problem->table[kr][i] = problem->table[kr][i] / kn;
      /* Checking if Zj - Cj are all negative */
      for (i = 4; i < col; i++)
        if (problem->table[row-1][i] > 0)
          flag = 1;
      /* Breaking the loop */
      if (flag == -1)
        break;
    }
  printf("\nThe solution found was:\n");
  for (i = 1; i < row - 1; i++)
    printf ("X%d = %lf ", (int) problem->table[i][1], problem->table[i][3]);
  printf("\n\n");
}

void
lp_bigm_max (lp_problem_t *problem)
{
  int i, j, row, col, kc, kr, flag=-1, k;
  double sum, max, ba, kn;

  /* Starting the iteration */
  for (k = 0; k < 10; k++)
    {
      /* Initializing the flag */
      flag = -1.00;
      /* Z0 */
      for (i = 1; i < row - 1;i++)
        problem->table[row - 1][3] = problem->table[row - 1][3] + problem->table[i][3] * problem->table[i][2];
      /* Zj - Cj */
      for (i = 4; i < col; i++)
        {
          sum = 0;
          for (j = 1; j < row - 1; j++)
          sum = problem->table[j][i] * problem->table[j][2] + sum;
          problem->table[row - 1][i] = sum - problem->coefficients_objf[i - 4];
        }
      /* Finding Maximum in Zj - Cj */
      max = problem->table[row - 1][4];
      kc = 4;
      for (i = 4; i < col; i++)
        if (max < problem->table[row - 1][i])
          {
            max = problem->table[row - 1][i];
            kc = i;
          }
      /* Finding a b/a ratio */
      for (j = 1; j < row - 1; j++)
        if (problem->table[j][kc] > 0)
          {
            ba = (problem->column_matrix[j - 1] / problem->table[j][kc]);
            break;
          }
      kr = j;
      for (; j < row - 1; j++)
        if ((problem->table[j][kc] > 0) && ((problem->column_matrix[j - 1] / problem->table[j][kc]) < ba))
          kr = j;
      /* Swapping key column with basis */
      problem->table[kr][1] = kc - 3;
      kn = problem->table[kr][kc];
      problem->table[kr][2] = problem->coefficients_objf[kc - 4];
      /* Dividing other rows by the formula */
      for (i = 1; i < row - 1; i++)
        if (i == kr)
          continue;
        else
          for (j = 3; j < kc; j++)
            problem->table[i][j] = problem->table[i][j] - ((problem->table[i][kc] * problem->table[kr][j]) / kn);
      for (i = 1; i < row - 1; i++)
        if (i == kr)
          continue;
        else
          for (j = kc + 1; j < col; j++)
            problem->table[i][j] = problem->table[i][j] - ((problem->table[i][kc] * problem->table[kr][j]) / kn);
      for (i = 1; i < row - 1; i++)
        if (i == kr)
          continue;
        else
          problem->table[i][kc] = problem->table[i][kc] - ((problem->table[i][kc] * problem->table[kr][kc]) / kn);
      /* Dividing key row by key number */
      for (i = 3; i < col; i++)
        problem->table[kr][i] = problem->table[kr][i] / kn;
      /* Checking if Zj - Cj are all positive */
      for (i = 4; i < col; i++)
        if (problem->table[row - 1][i] < 0)
          flag = 1;
      /* Breaking the loop */
      if (flag == -1)
        break;
    }
  printf("\nThe solution found was:\n");
  for (i = 1; i < row - 1; i++)
    printf ("X%d = %lf ", (int) problem->table[i][1], problem->table[i][3]);
  printf("\n\n");
}

#endif
