#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define BUFF_SIZE 1024
#define addr_name_length 10


typedef struct node node;

struct node {
    node ** children;
    node * parent;
    int value;
    int parent_id;
    int num_of_addresses;
    char ** addresses;
    int num_of_children;
};

node** nodes;
node* root;
int n;

void add_child(node * parent, node * child) { //Functia de adaugare a unui nod in lista de copii a altui nod

    if (parent->children == NULL) {
        parent->children = (node **)malloc(sizeof(node *));
        parent->children[0] = child;
        parent->num_of_children = 1;
    }
    else {
        int n = parent->num_of_children;
        parent->children = (node **)realloc(parent->children, (n + 1) * sizeof(node *));
        parent->children[n] = child;
        parent->num_of_children++;
    }

    child->parent = parent;
}

char ** make_address(char * array, char ** addresses, int m) { //Functia de adaugare a adreselor fiecarui nod
    addresses = (char **)malloc(m * (sizeof(char *)));
int i;
    for ( i = 0; i < m; i++) {
        addresses[i] = (char *)malloc(addr_name_length * sizeof(char));
    }

        int j=0;
        
    for (  i = 1; i < strlen(array); i++) {
        char c = array[i];
        int k = 0;

        while (c != 32 && c != '\n') {
            addresses[j][k] =c;
            k++;
            i++;
            c = array[i];
        }

        j++;
    }

    return addresses;
}

void tree_construction(FILE * fptr) {
    fptr = fopen("tree.in", "r");

    if(fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    fscanf(fptr,"%d", &n);
    int i;
    nodes = (node**)malloc(n * sizeof(node*));

    for (  i = 0; i < n; i++) {
        nodes[i] = (node*)malloc(sizeof(node));	//Initializare noduri arbore
        nodes[i]->children = NULL;
        nodes[i]->value = 0;
        nodes[i]->num_of_children = 0;
        nodes[i]->parent = NULL;
    }

    
    for (  i = 0; i < n; i++) {
        int child_id;

        fscanf(fptr, "%d", &child_id);
        node * child = nodes[child_id];//Citirea nodurilor

        int parent_id;
        int num_addr;
        char buff[1000];
        fscanf(fptr, "%d", &parent_id);//Citirea elementelor/liniilor din fisier
        fscanf(fptr, "%d", &num_addr);

        child->parent_id = parent_id;
        child->value = child_id;
        child->num_of_addresses = num_addr;

        char ** addresses;
        fgets(buff, BUFF_SIZE, fptr);
        child->addresses = make_address(buff, addresses, num_addr);//Adaugare adrese

        if (parent_id == -1) {	//Verificare daca nodul nu este parinte
            root = child;
        }
        else {
            node *parent = nodes[parent_id];
            add_child(parent, child);//Adaugare nod in lista de copii
        }


    }

    fclose(fptr);
}


void write_file_task1(FILE * fptr, FILE * in) { //Functia de scriere in fisier
    tree_construction(in); //Creare arbore

    fptr = fopen("tree.out","w"); //Deschidere fisier

    if(fptr == NULL) {
        printf("Error!");
        exit(1);
    }
    int i,w;
    fprintf(fptr, "%d ", root->value);	//Scrierea radacinii si a copiilor sai
    int e=root->num_of_children;
    for ( w = 0; w < e; w++)
    {
    	if(w == (e-1))
        {
            fprintf(fptr, "%d" , root->children[w]->value);
        }
        else
        {
            fprintf(fptr, "%d " , root->children[w]->value);
        }
    }


    fprintf(fptr,"\n");

    for ( i = 1; i < n; i++) {
         int m = nodes[i]->num_of_children;	//Scriere nodurilor 
         if (m == 0)
         {
             fprintf(fptr, "%d", nodes[i]->value);

         }
         else
        fprintf(fptr, "%d ", nodes[i]->value);
       
        int j;
        for ( j = 0; j < m; j++) {
       
       if(j == (m-1))
        {
            fprintf(fptr, "%d" , nodes[i]->children[j]->value);//Scriere copii fiecare nod
        }
        else
        {
            fprintf(fptr, "%d " , nodes[i]->children[j]->value);
        }

        
        }
        if (i < n-1)
        {
            fprintf(fptr, "\n");    
        }
        
    }
    fclose(fptr);
}


void main() {
    FILE * in;
    FILE * out;

write_file_task1(out, in); //Apelarea functiei de scriere.




}





