/********************************
 *     LEVENSHTEIN's Length     *
 * Studenckie Kolo Naukowe main *
 ********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 80
//find min
#define MIN2(a, b) ((a)<(b)?(a):(b))
#define MIN3(a, b, c) MIN2(MIN2(a, b), MIN2(c, b))


//def of func's
int Levenshtein (const char*, const char*, const unsigned int, const unsigned int);
int get_strings (char**, char**);

//get_strings Definition
int get_strings (char** ptr_str_1, char** ptr_str_2)
{
    char *ck1;
    //ALLOC
    *ptr_str_1 = NULL;
    *ptr_str_2 = NULL;
    *ptr_str_1 = (char* )malloc (sizeof (char) * LEN);
    *ptr_str_2 = (char* )malloc (sizeof (char) * LEN);
    if(*ptr_str_1 == NULL || *ptr_str_1 == NULL)
    {
        return -2;
    }

    //READ
    printf("Enter source string:\n   ");
    if((ck1 = fgets(*ptr_str_1, LEN, stdin)) == NULL)
    {
        //read error
        return -3;
    }
    printf("Enter target string:\n   ");
    if((ck1 = fgets(*ptr_str_2, LEN, stdin)) == NULL)
    {
        //read error
        return -3;
    }
    if(**ptr_str_1 == 10 || **ptr_str_2 == 10)
    {
        //empty string(s)
        return -1;
    }

    return 0;
}

//Levenshtein's algorithm
int Levenshtein (const char* str_1, const char* str_2, const unsigned int str_1_len, const unsigned int str_2_len)
{
    int** matrix, x, y, cost = 0;

    matrix = (int** )malloc (sizeof (int*) * (str_2_len) );
    for (y = 0; y < str_2_len; ++y)
    {
        *(matrix + y) = (int* )malloc (sizeof (int) * (str_1_len) );
    }

    //fill matrix
    for (x = 1; x <= str_1_len; ++x)
    {
        matrix[0][x-1] = x-1;
    }
    printf("\n");
    for (y = 1; y <= str_2_len; ++y)
    {
        matrix[y-1][0] = y-1;
    }

    //Levenshtein
    for (y = 1; y < str_2_len; ++y)
    {
        for (x = 1; x < str_1_len; ++x)
        {
            if ( *(str_2 + y) == *(str_1 + x))
            {
                cost = 0;
            }
            else
            {
                cost = 1;                
            }
            matrix[y][x] = MIN3(matrix[y-1][x-1] + cost, matrix[y][x-1] + 1, matrix[y-1][x] + 1);
        }
    }

    return matrix[str_2_len - 1][str_1_len - 1];
}

//main()
int main(void)
{
    int lev = 0;
    char* ptr_str_1 = NULL,
        * ptr_str_2 = NULL;

    if(get_strings(&ptr_str_1, &ptr_str_2))
    {
        printf("Problem!");
        return -10;
    }

    unsigned int str_1_len = strlen(ptr_str_1); //pattern
    unsigned int str_2_len = strlen(ptr_str_2); //data
    ptr_str_1 = realloc (ptr_str_1, str_1_len);
    ptr_str_2 = realloc (ptr_str_2, str_2_len);
    printf("%s\n%s\n", ptr_str_1, ptr_str_2);

    lev = Levenshtein(ptr_str_1, ptr_str_2, str_1_len, str_2_len);
    printf("\n\nlevenshtein's length = %d", lev);

    free(ptr_str_1);
    free(ptr_str_2);

    return 0;
}
