#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct list
{
	int timestamp;
	double data;
	struct list *next;
	
} *List;					//* Structura pentru lista *//




	void free_list(List l)
{
	List p ,q;
	q=l;
	p=l;
	while(q->next !=NULL)
	{
		p=q;
		q=q->next;
		free(p);
	}
	free(q);
}

List init( int timestamp ,double data)
{
	List l=malloc(sizeof(struct list)); //*Initializare lista*
	l->timestamp=timestamp;
	l->data=data;
	l->next=NULL;
	return l;
}


void printlist(List l,int n)
{
	if (l != NULL)							//Functie de printare a listei
	{
	printf("%d\n",n );
	while(l != NULL)
	{
		printf("%d %0.2lf\n",l->timestamp,l->data );
		l=l->next;
	}
}
}

List add_tail(List l, int timestamp,double data)
{
	List p;
	p=l;
	List nou=malloc(sizeof(struct list));
	while(p->next != NULL)
	{	
		p=p->next;
	}
	nou->timestamp=timestamp;
	nou->data=data; 
      			//*Functia de adaugare a unui nou nod la sfarsitul listei *//
	p->next=nou;
	nou->next=NULL;


	return l;
}

int suma(List l)
{
	int summaa=0;
	while(l != NULL)
	{
		summaa=summaa+1;
		l=l->next;
	}
	return summaa;
}


double average(List p )			//*Functie care calculeaza media  aritmetica*//
{

	double a=0,d=0;
	double av=0;
	int i=0;
	for ( i = 0; i < 5; ++i)
    	{
    		a=a+p->data;
    		d=d+1;
    		p=p->next;
    	}
    	av=a/d;
	
	return av;
}


double deviation(List p)
{
	double c=0,d=0;							//Functia care afla deviatia 
	double sig=0;
	double sum3=0,med=0;
		c=average(p);
	
	int i=0;
for ( i = 0; i < 5; ++i)
{
	

		d=p->data - c;
		d=d*d;
		sum3=sum3+d;
		
		p=p->next;	

}
	med = sum3/5;

sig=sqrt(med);

	return sig;
}



											//Functie de swap
void swap(List p1, List p2)
{
	double temp = p1->data;
	p1->data = p2->data;
	p2->data = temp;

	

}
      


void SelectionSort(List head)
{
	List start = head;						//Functie de sortare a unei liste
	List traverse;
	List min;
	
	while(start->next)
	{
		min = start;
		traverse = start->next;
		
	while(traverse)
	{
		if( min->data > traverse->data )
		{
				min = traverse;
		}
			
			traverse = traverse->next;
	}				
		swap(start,min);			
		start = start->next;
	}
} 



double mediana(List p)			//Functie ce returneaza valoarea medianei
{
	int i=0;
	for ( i = 0; i < 2; i++)
	{
		p=p->next;

	}
	float kit=0;
	kit=p->data;
	return kit;
}


int mediana1(List p)			//Functie ce returneaza timestampul medianei
{
	int i=0;
	for ( i = 0; i < 2; ++i)
	{
		p=p->next;

	}
	int kit1=0;
	kit1=p->timestamp;
	return kit1;

}


double kit(List p)			//Functie ce returneaza valoarea medianei listei sortate
{
	List g=NULL;
	g=init(p->timestamp,p->data);
	p=p->next;
	int i=0;
	for ( i = 0; i < 4; i++)
	{
		g=add_tail(g,p->timestamp,p->data);
		p=p->next;
	}

	SelectionSort(g);
	double medians=0;
	medians=mediana(g);
	
return medians;
}


int kit1 (List p)		//Functie ce returneaza timestampul medianei listei sortate
{
	List g=NULL;
	g=init(p->timestamp,p->data);
	p=p->next;
	int i =0;
	for ( i = 0; i < 4; i++)
	{
		g=add_tail(g,p->timestamp,p->data);
		p=p->next;
	}

	SelectionSort(g);
	int medians=0;
	medians=mediana1(g);
	
return medians;

}

double C(int timestamp,int left,int right)
{
	double cuki1=0,cuki2=0;
double dubl=0;
cuki1=(timestamp-left);		//Calcularea C pentru taskul 1.4
cuki2=(right-left);
dubl=cuki1/cuki2;
	return dubl;
}

double w(double i,double ka)
{
	double kuka=0,kuka1=0,kuka2=0,kuka3=0,kuka4=0,kukaf=0;
	kuka=i/(ka-1);
	kuka=kuka*kuka;
	kuka=kuka*0.9;
	kuka=kuka+0.1;
											//Calcularea celor 3 w pentru taskul 1.4
	kuka1=0.1;
	
	kuka2=0.5;

	kuka2=kuka2*kuka2*0.9;

	kuka2=kuka2+0.1;

	kuka3=1;
	kuka4=kuka1+kuka2+kuka3;

	kukaf=kuka/kuka4;
	return kukaf;
}


//Task 1.1
List exceptiontask1(List l)
{
List task1,task11,qemp;
	 task1=l;
	 task11=l;
	 qemp=l;
	 int k=5;
	List task111=NULL;
	task111=init(qemp->timestamp,qemp->data);
	qemp=qemp->next;
	task111=add_tail(task111,qemp->timestamp,qemp->data);
	int z=0;
	z=k/2*2;
	int i=0;
	for ( i = 0; i < suma(l)-z; ++i)
	{
		double averag=0;
	averag = average(task1);			//Aflarea mediei aritmetice
 	
 	
 	

	double dev=0;
 	dev=deviation(task11);					//Aflarea deviatie
	
	
	double intv1=0,intv2=0;	

	intv1=averag-dev;
	intv2=averag+dev;		//Aflarea intervalului
	
	if (task1->next->next->data >= intv1 && task1->next->next->data <= intv2)	//Verificare daca mijlocul ferestrei se afla in interval
	{	
		task111=add_tail(task111,task1->next->next->timestamp,task1->next->next->data);
	}


		task1=task1->next;
		task11=task11->next;
	}
	task1=task1->next->next;
	task111=add_tail(task111,task1->timestamp,task1->data);
	task1=task1->next;
	task111=add_tail(task111,task1->timestamp,task1->data);//Adaugare ultimele doua elemente
	return task111;

}


List task3medie(List l)
{

		List task2,task21;
task2=l;
task21=NULL;
int k=5;
int z=0;
int i=0;	
	z=k/2*2;											//	Task 1.2.1	
double averag1=0;
averag1=average(task2);	//Aflarea mediei aritmetice.
task21=init(task2->next->next->timestamp,averag1); //Initializare lista cu primul element aflat
task2=task2->next;
for ( i = 0; i < suma(l)-z-1; ++i)
{
	averag1=average(task2);
	task21=add_tail(task21,task2->next->next->timestamp,averag1);//Adaugare elemente aflate in lista
	task2=task2->next;
}

	return task21;

}


List task12median(List l)
{
	List taskmed,taskmed1=NULL;   //Task 1.2
	double rezul0=0;
	int rezul01=0;
	taskmed=l;
	rezul0=kit(taskmed);
	rezul01=kit1(taskmed);
	taskmed1=init(rezul01,rezul0);
	taskmed=taskmed->next;
	int i=0;

	for (i = 0; i < suma(l)-5; i++)
	{
		
		double rezul=0;
		int rezul1=0;
		rezul=kit(taskmed);
		rezul1=kit1(taskmed);
		taskmed1=add_tail(taskmed1,rezul1,rezul);
		taskmed=taskmed->next;
	}
	return taskmed1;

}


List uniformization(List l)
{
	List un1,un2,un3;									//Task 1.3
un1=l;
un2=l;
un3=l;
int d1=0;
double d3=0;
int d4=0;	
	un1=init(un2->timestamp,un2->data);
	un2=un2->next;
	while(un2 != NULL)
	{
		d1=un2->timestamp - un3->timestamp;
		if (d1 >= 100 && d1 <= 1000)
		{
			d3=un2->data + un3->data;
			d3=d3/2;
			un2->data=d3;
			d4=un2->timestamp + un3->timestamp;
			d4=d4/2;
			un2->timestamp=d4;

			un1=add_tail(un1,d4,d3);
		}
		else
		{
			un1=add_tail(un1,un2->timestamp,un2->data);
		}
		un3=un2;
		un2=un2->next;


	}

return un1;
}



void intervaltask(int cik,List l)
{
	List kaka=NULL;
	kaka=l;
	SelectionSort(kaka);
	double kukser=cik;
	List maka=NULL;
	maka=kaka;
	int sumka=0;
	sumka=maka->data;
	int puka=0;
	int luka=0;						//Taskul Bonus

	int babah=0;
	babah=sumka % cik;

		if (babah != 0 )
		{
			sumka=sumka-1;
	
		}

		while(kaka->next != NULL)
		{		
			puka =0;
			luka=sumka;
			sumka=sumka+cik;
	
			while(kaka->data <= sumka)
			{

				if (kaka->next != NULL)
				{	
					puka=puka+1;
					maka=kaka;
					kaka=kaka->next;
				}
		
			}


		if (puka != 0)
		{
			printf("[%d, %d] %d\n",luka,sumka,puka );
		}
}

	while(kaka->data >= sumka)
	{
		luka=sumka;
		sumka=sumka+cik;
	}
	puka=1;
	printf("[%d, %d] %d\n",luka,sumka,puka );

}

List completation(List l)
{
	List mit,pit;
	mit=l;
	pit=NULL;
	double puki=0;
	double kait1=0,kait2=0,kait3=0;			//Task 1.4
	double Cij=0;
	pit=init(mit->timestamp,mit->data);
	while(mit->next->next->next != NULL)
	{
		if ((mit->next->next->next->timestamp - mit->next->next->timestamp) > 1000 )
		{
				Cij=0;
				pit=add_tail(pit,mit->next->timestamp,mit->next->data);
				pit=add_tail(pit,mit->next->next->timestamp,mit->next->next->data);
				puki=mit->next->next->timestamp;
				while(puki+200 < mit->next->next->next->timestamp )
				{
				puki=puki+200;
				Cij=0;
				Cij=C(puki,mit->next->next->timestamp,mit->next->next->next->timestamp);

				kait1=mit->data*w(0,3);
				kait1=kait1+mit->next->data*w(1,3);
				kait1=kait1+mit->next->next->data*w(2,3);

				kait2=mit->next->next->next->next->next->data*w(0,3);
				kait2=kait2+mit->next->next->next->next->data*w(1,3);
				kait2=kait2+mit->next->next->next->data*w(2,3);

				kait1=(1-Cij)*kait1;
				kait2=Cij*kait2;

				kait3=kait2+kait1;

				pit=add_tail(pit,puki,kait3);

		}
				

				mit=mit->next->next;
	}
		else
		{
			pit=add_tail(pit,mit->next->timestamp,mit->next->data);
			mit=mit->next;

		}



	}
pit=add_tail(pit,mit->next->timestamp,mit->next->data);
pit=add_tail(pit,mit->next->next->timestamp,mit->next->next->data);

return pit;
}


int main(int argc, char const *argv[])
{



	int n=0,k=5,t=0;	
	List l = NULL;
	double b=0;
	scanf("%d",&n);
	scanf("%d%lf",&t,&b);			//Adaugare elemente lista		
	l = init(t,b);
 	int i=0;
		 for ( i = 0; i < n-1; ++i)
		 {
	 		scanf("%d%lf",&t,&b);
	 		l = add_tail(l,t,b);
		 }

int elementee=0;

for ( i = 1; i <= argc-1; ++i)
{
					
	if (strcmp(argv[i],"--e1")==0)
	{
		
			l=exceptiontask1(l);
	}

	if (strcmp(argv[i],"--e2")==0)
	{
		l=task12median(l);
	}

	if (strcmp(argv[i],"--e3")==0) 	
	{
		l=task3medie(l);				 
	}

	if (strcmp(argv[i],"--u")==0 )
	{
		l=uniformization(l);
			
	}
	if (strcmp(argv[i],"--c")==0 )
	{
		l=completation(l);
			
	}
	

}

if (strcmp(argv[1],"--st2")==0 )
{
	intervaltask(atoi(argv[1]+4),l);
			
}else if (strcmp(argv[1],"--st10")==0 )

{
		intervaltask(atoi(argv[1]+4),l);

}

else
{
	elementee=suma(l);
	printlist(l,elementee);

}


return 0;
}