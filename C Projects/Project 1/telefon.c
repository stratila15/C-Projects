#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAX_MES 100
#define MAX_COD 300

// structura pentru dictionar de la taskul 3
typedef struct {
    char *gresit;
    char *corect;
} dictionar;


/*
    str -> sirul de caractere ce trebuie codificat
    ignore -> folosit pentru taskurile 1, 3 si 4, pentru a vedea daca adaugam #
    dupa caractere de pe acelasi buton (de exemplu a, apoi C)
*/
char* codificare (char *str, int ignore) {
    char *result = (char *) malloc (MAX_COD * sizeof(char));
    strcpy(result, "");
    int j,i;
    for (i = 0; i < strlen(str); i++) {
        char character = str[i];
        if (str[i] == ' ') {
            strcat(result, "0");
        }
        // daca dam de un litera majuscula
        if (isupper(str[i])) {
            strcat(result, "1");
            character = tolower(str[i]);
        }
        // daca avem intre a si c (butonul 2)
        if (character >= 'a' && character <= 'c') {
            // folosim modulo a lua numarul de apasari pentru buton
            // o data -> a, de doua ori -> b, ca sa vedem de cate ori
            // concatenam la sirul codificat
            for ( j = 0; j < (character) % ('a' - 1); j++)
                strcat(result, "2");
            // daca urmatorul caracter e de pe acelasi buton (doar taskul 1), adaugam #
            if (i != (strlen(str) - 1) && str[i + 1] >= 'a' && str[i + 1] <= 'c' && ignore == 0) {
                strcat(result, "#");
            }    
        }

        // aplicam logica de mai sus - butonul 3
        if (character >= 'd' && character <= 'f') {
            for ( j = 0; j < (character) % ('d' - 1); j++)
                strcat(result, "3");
            if (i != (strlen(str) - 1) && str[i + 1] >= 'd' && str[i + 1] <= 'f' && ignore == 0)
                strcat(result, "#");
        }
        // butonul 4
        if (character >= 'g' && character <= 'i') {
            for ( j = 0; j < (character) % ('g' - 1); j++)
                strcat(result, "4");
            if (i != (strlen(str) - 1) && str[i + 1] >= 'g' && str[i + 1] <= 'i' && ignore == 0)
                strcat(result, "#");
        }
        // butonul 5
        if (character >= 'j' && character <= 'l') {
            for ( j = 0; j < (character) % ('j' - 1); j++)
                strcat(result, "5");
            if (i != (strlen(str) - 1) && str[i + 1] >= 'j' && str[i + 1] <= 'l' && ignore == 0)
                strcat(result, "#");
        }
        // butonul 6
        if (character >= 'm' && character <= 'o') {
            for ( j = 0; j < (character) % ('m' - 1); j++)
                strcat(result, "6");
            if (i != (strlen(str) - 1) && str[i + 1] >= 'm' && str[i + 1] <= 'o' && ignore == 0)
                strcat(result, "#");
        }
        // butonul 7
        if (character >= 'p' && character <= 's') {
            for ( j = 0; j < (character) % ('p' - 1); j++)
                strcat(result, "7");
            if (i != (strlen(str) - 1) && str[i + 1] >= 'p' && str[i + 1] <= 's' && ignore == 0)
                strcat(result, "#");
        }
        // butonul 8
        if (character >= 't' && character <= 'v') {
            for ( j = 0; j < (character) % ('t' - 1); ++j)
                strcat(result, "8");
            if (i != (strlen(str) - 1) && str[i + 1] >= 't' && str[i + 1] <= 'v' && ignore == 0)
                strcat(result, "#");
        }
        // butonul 9
        if (character >= 'w' && character <= 'z') {
            for ( j = 0; j < (character) % ('w' - 1); j++)
                strcat(result, "9");
            if (i != (strlen(str) - 1) && str[i + 1] >= 'w' && str[i + 1] <= 'z' && ignore == 0)
                strcat(result, "#");
        }
    }
    return result;
}

void decodificare (char *str) {
    int i;
    int sameNextChar = 0; // daca urmatorul caracter e la fel
    int sameChars = 1; // contor, de cate ori s-a apasat un buton
    int modulo = 3; // modulo folosit daca un buton e apasat de mai multe ori
    // ca sa stiu cum decodific: 22222 -> b (22)
    int upper = 0; // daca dau de o majuscula
    char c;
    for ( i = 0; i < strlen(str); i++) {
        // daca am 0 -> spatiu, trec la urmatorul caracter
        if (str[i] == '0') {
            printf(" ");
            continue;
            
        }
        // daca am 1, inseamna ca am o majuscula
        if (str[i] == '1') {
            upper = 1;
            continue;
        }
        // vad daca urmatorul caracter e de pe acelasi buton
        if ((i != strlen(str) - 1 && str[i] == str[i + 1]) || (i == strlen(str) - 1 && str[i] == str[i - 1])) {
            sameChars++; // cresc numarul de apasari pe buton
            sameNextChar = 1; // caracterul este acelasi...
        } else {
            sameNextChar = 0; // ...altfel nu
        }
        // daca urmatorul caracter e diferit de cel actual
        if (!sameNextChar) {
            // pe 7 si 9 am cate 4 litere
            if (str[i] == '7' || str[i] == '9') {
                modulo = 4;
            }
            // vad numarul de apasari de buton
            int digits = sameChars % modulo;
            // daca am de exemplu 6 apasari de butom, numarul de apasari va fi 3
            if (digits == 0)
                digits = modulo;
            switch (str[i]) {
                case '2':
                    // ma folosesc de ASCII aici
                    // exemplu: numarul de apasari e 1 => caracterul este 'a' - 1 + 1 = 'a'
                    // daca este 2 => 'a' - 1 + 2 = 'b'
                    c = 'a' - 1 + digits;
                    if (upper)
                        c = toupper(c);
                    printf("%c", c);
                    break;
                case '3':
                    c = 'd' - 1 + digits;
                    if (upper)
                        c = toupper(c);
                    printf("%c", c);
                    break;
                case '4':
                    c = 'g' - 1 + digits;
                    if (upper)
                        c = toupper(c);
                    printf("%c", c);
                    break;
                case '5':
                    c = 'j' - 1 + digits;
                    if (upper)
                        c = toupper(c);
                    printf("%c", c);
                    break;
                case '6':
                    c = 'm' - 1 + digits;
                    if (upper)
                        c = toupper(c);
                    printf("%c", c);
                    break;
                case '7':
                    c = 'p' - 1 + digits;
                    if (upper)
                        c = toupper(c);
                    printf("%c", c);
                    break;
                case '8':
                    c = 't' - 1 + digits;
                    if (upper)
                        c = toupper(c);
                    printf("%c", c);
                    break;
                case '9':
                    c = 'w' - 1 + digits;
                    if (upper)
                        c = toupper(c);
                    printf("%c", c);
                    break;
                default:
                    break;
            }
            // resetez
            sameChars = 1;
            upper = 0;
        }
    }
    printf("\n");
}

// taskul 3
void task3(char* phrase, dictionar *dict, int nr) {
	int i;
    phrase[strlen(phrase) - 1] = '\0';
    // spargem in cuvinte
    char *word = strtok (phrase, " ");
    // "autocorectat"
    char *result = (char *) malloc (MAX_COD * sizeof(char));
    strcpy(result, "");
    int foundWrong = 0; // daca am gasit cuvant gresit (fals default)
    while (word != NULL) {
        // cautare in dictionar
        for ( i = 0; i < nr; ++i) {
            if (strcmp(dict[i].gresit, word) == 0) {
                // corectam cuvantul
                strcat(result, dict[i].corect);
                foundWrong = 1;
                break;
            }
        }
        // daca cuvantul a fost corect deja, il inseram
        if (!foundWrong) {
            strcat(result, word);
        }
        foundWrong = 0;
        strcat(result, " ");
        // continuam sa spargem fraza
        word = strtok(NULL, " ");
    }
    // eliminam ultimul spatiu
    result[strlen(result) - 1] = '\0';
    // codificam, cu tot cu #
    char *coded = codificare(result, 0);
    printf("%s\n", coded);
    free(result);
    free(word);
    free(coded);
}

// cel mai mare divizor comun
unsigned long long cmd (unsigned long long a, unsigned long long b) {  
    unsigned long long t;
    if (b <= a) {  
        while (b != 0) {  
            t = b;  
            b = a % b;  
            a = t;  
        }  
        return a;
    } else {
        while (a != 0) {  
            t = a;  
            a = b % a;  
            b = t;  
        }
        return b;  
    }
}  

// criteriul de comparare pentru sortarea componentelor in ordine descrescatoare
int comparator (const void * a, const void * b)
{
    if(*(long long*)a - *(long long*)b < 0)
        return 1;
    if(*(long long*)a - *(long long*)b > 0)
        return -1;
    return 0;
}

// task 4
void task4(char *str) {
    int i,j;
    int count = 0;
    long long *componente = (long long*) malloc (MAX_COD * sizeof(long long)); 
    char *word = strtok(str, " ");
    // spargem mesajul si il codificam, fara #
    while (word != NULL) {
        char *convert = codificare(word, 1);
        sscanf(convert, "%lld", &componente[count]);
        count++;
        free(convert);
        word = strtok(NULL, " ");
    }
    printf("%d\n", count);
    
    for (i = 0; i < count; i++)
        printf("%lld ", componente[i]);
    printf("\n");

    // componenta maxima
    long long max = componente[0];
    int index_max = 0;
    for ( i = 0; i < count; i++) {
        if (max <= componente[i]) {
            index_max = i;
            max = componente[i];
        }
    }
    index_max++;
    printf("%lld %d\n", max, index_max);

    // daca toate componentele sunt prime intre ele
    int prime = 1;
    for ( i = 0; i < count - 1; i++) {
        for ( j = i + 1; j < count; j++) {
            if (cmd(componente[i], componente[j]) != 1) {
                prime = 0;
                break;
            }
        }
    }
    printf("%d\n", prime);
    

    int digitsSum = 0 ;
    char* mesaj_necodificat = (char *) malloc (MAX_MES * sizeof(char));
    strcpy(mesaj_necodificat, "");
    // lipim compontentele
    for ( i = 0; i < count; i++) {
        unsigned long long to_paste = componente[i];
        if (i != count - 1)
            to_paste *= 10; // adaugam 0 la fiecare componenta (fara ultima)
            // ca sa avem separator
        char *append = (char *) malloc (MAX_MES * sizeof(char));
        sprintf(append, "%llu", to_paste);
        strcat(mesaj_necodificat, append);
        free(append);
    }
    free(componente);
    // facem suma
    for ( i = 0; i < strlen(mesaj_necodificat); ++i) {
        // convertesc un caracter la int
        digitsSum += (mesaj_necodificat[i] - '0');
    }
    digitsSum = digitsSum % 9;
    // vedem daca il putem partitiona sau nu
    if (strlen(mesaj_necodificat) % digitsSum != 0) {
        printf("0\n");
        free(mesaj_necodificat);
        return;    
    }
    // partitia mesajului
    int partition = strlen(mesaj_necodificat) / digitsSum;
    long long *perfect_components = 
                (long long*) malloc ((partition + 1) * sizeof(long long));
    int k = 0; 
    // il partitionam
    for ( i = 0; i < strlen(mesaj_necodificat); i = i + digitsSum) {
        char *part = (char *) malloc ((partition + 1) * sizeof(char));
        snprintf(part, digitsSum + 1, "%s", mesaj_necodificat + i);
        perfect_components[k++] = atoll(part);
        free(part);
    }

    qsort (perfect_components, k, sizeof(long long), comparator);
    for ( i = 0; i < k; i++) {
        printf("%lld ", perfect_components[i]);
    }
    free(perfect_components);
    free(mesaj_necodificat);
    printf("\n");
}

int main (int argc, char **args) {
    int i;
    // taskul 1
    char *codify = (char *) malloc (MAX_MES * sizeof(char));
    fgets(codify, MAX_MES, stdin);
    char *coded = codificare(codify, 0);
    printf("%s\n", coded);

    // taskul 2
    char* decodify = (char *) malloc (MAX_COD * sizeof(char));
    fgets(decodify, MAX_MES, stdin);
    decodificare(decodify);

    // taskul 3
    char *autocorrect = (char *) malloc (MAX_MES * sizeof(char));
    fgets(autocorrect, MAX_COD, stdin);
    int nr;
    scanf("%d", &nr);
    dictionar *dict = (dictionar *) malloc ((nr + 1) * sizeof(dictionar));
    for ( i = 0; i < nr; i++) {
        dict[i].gresit = (char *) malloc (MAX_MES * sizeof(char));
        dict[i].corect = (char *) malloc (MAX_MES * sizeof(char));
    }
    for ( i = 0; i < nr; i++) {
        char first[MAX_MES], second[MAX_MES];
        scanf("%s %s", first, second);
        strcpy(dict[i].gresit, first);
        strcpy(dict[i].corect, second);
    }
    task3(autocorrect, dict, nr);

    // ca avem fgets dupa scanf
    int c;
    do {
        c = getchar();
    } while(c != EOF && c != '\n');

    // taskul 4
    char* last = (char *) malloc (MAX_MES * sizeof(char));
    fgets(last, MAX_MES, stdin);
    task4(last);

    free(codify);
    free(decodify);
    free(last);
    for ( i = 0; i < nr; ++i) {
        free(dict[i].gresit);
        free(dict[i].corect);
    }
    free(autocorrect);
    free(dict);
    free(coded);

    return 0;
}
