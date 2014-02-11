#include<stdio.h>
#include<math.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <time.h>


int id[8192];

/**************************************************************************************************/
/*                                   Quick Find                                       */
/**************************************************************************************************/
void quickfind(FILE *fp)
{
	printf("Version1: Quick Find\n");

	clock_t start,end;
	start = clock();

	int l=0;
	int data[8192][2];
	int i = 0;;
	while(i<8192)
	{
		id[i]=i;
		i++;
	}
	char buffer[50];
	while(fgets(buffer,50,fp)	!=	NULL)
	{
		l++;

		buffer[strlen(buffer)-1]='\0';
		char* buf = malloc(sizeof(char)*50);
		strcpy(buf,buffer);
		//printf("%s\n",buf);

		char p1[10];
		char q1[10];
		sscanf(buf, "%[^ ]%s", p1, q1);
		//printf("p1: %s q1: %s\n",p1,q1);

		int p = atoi(p1);
		int q = atoi(q1);
		//printf("p: %d q: %d\n",p,q);

		id[p]=p;
		id[q]=q;

		data[l][0]=p;
		data[l][1]=q;

		/*
		if(id[p] != id[q])
		{

		}
		*/
	}
	int j=1;
	int pid;
	int qid;
	while(j<=l)
	{
		pid = id[data[j][0]];
		qid = id[data[j][1]];
		int k=0;
		while(k<8192)
			{
				if ( id[k] == pid)
				{
					  id[k] = qid;
					  //printf("id[%d]: %d\n",k,qid);
				}
				k++;
			}
		j++;
	}
	/**********test the clock**************/
		//long t = 10000000;
		//while( t--) ;
	/********************************************/
	end = clock();
	printf("The time for Quick Find was: %f\n", (double)(end-start)/1000);
	printf("\n");
}

int root (int i)
{
	while (id[i] != i)
		i = id[i];
	return i;
}
/**************************************************************************************************/
/*                                   Quick Union                                      */
/**************************************************************************************************/
void quickunion(FILE *fp)
{
	printf("Version2: Quick Union\n");

	clock_t start,end;
	start = clock();

	int l=0;
	int data[8192][2];
	int i = 0;;
	while(i<8192)
	{
		id[i]=i;
		i++;
	}
	char buffer[50];
	while(fgets(buffer,50,fp)	!=	NULL)
	{
		l++;

		buffer[strlen(buffer)-1]='\0';
		char* buf = malloc(sizeof(char)*50);
		strcpy(buf,buffer);
		//printf("%s\n",buf);

		char p1[10];
		char q1[10];
		sscanf(buf, "%[^ ]%s", p1, q1);
		//printf("p1: %s q1: %s\n",p1,q1);

		int p = atoi(p1);
		int q = atoi(q1);
		//printf("p: %d q: %d\n",p,q);

		id[p]=p;
		id[q]=q;

		data[l][0]=p;
		data[l][1]=q;

		/*
		if(id[p] != id[q])
		{

		}
		*/
	}

	int j=1;
	while(j<=l)
	{
		int m = root(data[j][0]);
		int n = root(data[j][1]);
		id[m] = n;
		//printf("id[%d]: %d\n",m,n);
		j++;
	}
	end = clock();
	printf("The time for Quick Union was: %f\n", (double)(end-start)/1000);
	printf("\n");
}


/**************************************************************************************************/
/*                                   WeightedQuickUnion                               */
/**************************************************************************************************/
void weightedquickunion(FILE *fp)
{
	printf("Version3: Weighted Quick Union\n");

	clock_t start,end;
	start = clock();

	int l=0;
	int data[8192][2];
	int i = 0;;
	while(i<8192)
	{
		id[i]=i;
		i++;
	}
	char buffer[50];
	while(fgets(buffer,50,fp)	!=	NULL)
	{
		l++;

		buffer[strlen(buffer)-1]='\0';
		char* buf = malloc(sizeof(char)*50);
		strcpy(buf,buffer);
		//printf("%s\n",buf);

		char p1[10];
		char q1[10];
		sscanf(buf, "%[^ ]%s", p1, q1);
		//printf("p1: %s q1: %s\n",p1,q1);

		int p = atoi(p1);
		int q = atoi(q1);
		//printf("p: %d q: %d\n",p,q);

		id[p]=p;
		id[q]=q;

		data[l][0]=p;
		data[l][1]=q;

		/*
		if(id[p] != id[q])
		{

		}
		*/
	}

	int j=1;
	int sz[8192];
	while(j<=l)
	{
		id[data[j][0]] = data[j][0];
		sz[data[j][1]] = 1;

		int m = root(data[j][0]); //p
		int n = root(data[j][1]); //q
		if (sz[m] < sz[n])
		{
			id[m] = n; sz[n] += sz[m];
			//printf("id[%d]: %d\n",m,n);
		}
		else
		{
			id[n] = m; sz[m] += sz[n];
			//printf("id[%d]: %d\n",n,m);
		}
		j++;
	}
	end = clock();
	printf("The time for Union Find was: %f\n", (double)(end-start)/1000);
	printf("\n");
}


/**************************************************************************************************/
/*                                   main	                                            */
/**************************************************************************************************/
int main(int argc, char *argv[])
{
	FILE *fp = NULL;

	//char *str="/home/revo/data/hw1data/8pair.txt";
	//	char *str="/home/revo/data/hw1data/32pair.txt";
	//	char *str="/home/revo/data/hw1data/128pair.txt";
	//	char *str="/home/revo/data/hw1data/512pair.txt";
	//	char *str="/home/revo/data/hw1data/1024pair.txt";
	//	char *str="/home/revo/data/hw1data/4096pair.txt";
		char *str="/home/revo/data/hw1data/8192pair.txt";

	int h = 0;
	while(h<3)
	{
		if(h==0)
		{
			fp = fopen(str, "r");
			quickfind(fp);
			fclose(fp);
		}
		else if(h==1)
		{
			fp = fopen(str, "r");
			quickunion(fp);
			fclose(fp);
		}
		else
		{
			fp = fopen(str, "r");
			weightedquickunion(fp);
			fclose(fp);
		}

		h++;
	}

	return 0;
}
