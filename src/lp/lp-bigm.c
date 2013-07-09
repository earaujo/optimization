// Copyright 2013 Ewerton Assis and Juliane Oliveira
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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "bigm-solver.h"

#define USAGE "Usage: lpbigm <option> [entry]\n\
Options:\n\
-h\t\tPrint this help message and exit\n\
-i\t\tTreat entry problem as a minimization problem\n\
-a\t\tTreat entry problem as a maximization problem\n\n"

int
main (int argc, char **argv)
{
  int c, iflag = 0, aflag = 0;
  lp_problem_t *problem;

  if (argc < 2)
    {
      fprintf (stderr, USAGE);
      return 0;
    }
    while ((c = getopt (argc, argv, "hia")) != -1)
    {
      switch (c)
        {
          case 'h':
            fprintf (stdout, USAGE);
            return 0;
          case 'i':
            iflag = 1;
            break;
          case 'a':
            aflag = 1;
            break;
          case '?':
            if (isprint (optopt))
              fprintf (stderr, "Unknown option '-%c'.\n", optopt);
            else
              fprintf (stderr, "Unknown option character '\\x%x'.\n", optopt);
            fprintf (stderr, USAGE);
            return 1;
          default:
            abort ();
        }
    }
  if (iflag + aflag > 1)
    {
      fprintf (stderr, "It's not allowed to use more than one objective (max or min) at a time.\n");
      fprintf (stderr, USAGE);
      return 1;
    }
  problem = lp_problem_from_stdin ();
  if (iflag)
    lp_bigm_min (problem);
  if (aflag)
    lp_bigm_max (problem);
  lp_problem_destroy (problem);
  return 0;
}
