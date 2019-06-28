#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <time.h>

#define MNN 70
#define MNN2 5010

using namespace std;

map<string, int> mp1, mp2;
double mat[MNN][MNN], matf[MNN2][MNN2];
int n;

void add(int sz, int fl)
{
  int i;
  char lin[10];
  string a("");
  FILE * pf;
  pf = fopen("results.txt","r");
  while(fscanf(pf, " %s", lin) != EOF)
    {
      a = "";
      string b(lin);
      a = a+b;
      for(i = 0; i < sz-1; i++)
	{
	  fscanf(pf, " %s", lin);
	  string b(lin);
	  a = a+"\n"+b;
	}
      int ct;
      fscanf(pf, "%d", &ct);
      if(fl)
	{
	  if(mp1.find(a) == mp1.end())
	    mp1[a] = 0;
	  mp1[a] += ct;
	}
      else
	{
	  if(mp2.find(a) == mp2.end())
	    mp2[a] = 0;
	  mp2[a] += ct;
	}
    }
  fclose(pf);
}

int main()
{
  //freopen();
  srand(time(NULL));
  int i, j;
  scanf("%d", &n);
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      scanf("%lf", &mat[i][j]);
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      {
	int ii, jj;
	for(ii = 0; ii < n; ii++)
	  for(jj = 0; jj < n; jj++)
	    matf[i*n+ii][j*n+jj] = mat[ii][jj]*mat[i][j];
      }
  int N = n*n;
  int q;
  scanf("%d", &q);
  for(int t1 = 0; t1 < q; t1++)
    {
      FILE * pf;
      pf = fopen ("gtrie/gr.txt","w");
      for(i = 0; i < N; i++)
	for(j = i+1; j < N; j++)
	  {
	    double pp = matf[i][j];
	    int mx = RAND_MAX*pp;
	    if(rand() <= mx)
	      fprintf(pf, "%d %d 1\n", i+1, j+1);
	  }
      fclose (pf);
      system("./gtrie/gtrieScanner -s 3 -m esu -g gtrie/gr.txt > tr.txt");
      add(3, 0);
      system("./gtrie/gtrieScanner -s 4 -m esu -g gtrie/gr.txt > tr.txt");
      add(4, 0);

      pf = fopen ("gtrie/gr.txt","w");
      for(i = 0; i < n; i++)
	for(j = i+1; j < n; j++)
	  {
	    double pp = mat[i][j];
	    int mx = RAND_MAX*pp;
	    if(rand() <= mx)
	      fprintf(pf, "%d %d 1\n", i+1, j+1);
	  }
      fclose (pf);
      system("./gtrie/gtrieScanner -s 3 -m esu -g gtrie/gr.txt > tr.txt");
      add(3, 1);
      system("./gtrie/gtrieScanner -s 4 -m esu -g gtrie/gr.txt > tr.txt");
      add(4, 1);
    }
  map<string, int >::iterator it;
  for(it = mp1.begin(); it != mp1.end(); it++)
    printf("%s       %d/%d = %lf\n\n", it->first.c_str(), it->second, q,
	   (double)it->second/(double)q);

  printf("-------\n\n Grafo com produto:\n");
  for(it = mp2.begin(); it != mp2.end(); it++)
    printf("%s       %d/%d = %lf\n\n", it->first.c_str(), it->second, q,
	   (double)it->second/(double)q);
  return 0;
}
