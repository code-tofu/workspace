// CS50: Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// CS50: Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();
char parent_allele(person parent);

int main(void)
{
    // CS50: Seed random number generator
    srand(time(0));

    // CS50: Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // CS50: Print family tree of blood types
    print_family(p, 0);

    // CS50: Free memory
    free_family(p);
}

// CS50: Create a new individual with `generations`
person *create_family(int generations)
{
    // CS50: Allocate memory for new person
    // creates a pointer of type person to a new person, named self
    person *self = (person *) malloc(sizeof(person)); //typedef already if not need to use struct person
    if (self == NULL) //if malloc returns NULL to person* self
    {
        return NULL;
    }
    // CS50: If there are still generations left to create
    // use the recursion return to populate the fields of struct self
    if (generations > 1)
    {
        // CS50: Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // CS50: Set parent pointers for current person
        // parent 0 and parent 1 are pointers to person struct created by createfamily function
        // person.parents[i] is a pointer to person struct
        // self is a pointer from malloc (memory). pointer is to struct self
        (*self).parents[0] = parent0; //can be coded as self->parents
        (*self).parents[1] = parent1;

        // CS50: Randomly assign current person's alleles based on the alleles of their parents
        (*self).alleles[0] = parent_allele(*parent0);
        (*self).alleles[1] = parent_allele(*parent1);
    }

    // CS50: If there are no generations left to create
    else //BASE CASE
    {
        // CS50: Set parent pointers to NULL (DONE)
        (*self).parents[0] = NULL;
        (*self).parents[1] = NULL;
        // CS50: Randomly assign alleles (DONE)
        (*self).alleles[0] = random_allele();
        (*self).alleles[1] = random_allele();
    }

    // CS50: Return newly created person (DONE)
    return self; //return a pointer of type person
    // all the elements are referred to by pointers accessed through the linked list
}

// Free `p` and all ancestors of `p`.
void free_family(person *p) //takes in pointer to person
{
    // Handle base case i.e. oldest generation (DONE)
    if ((*p).parents[0] == NULL) //assume [0]=[1]=NULL
    {
        free(p); //free pointer
        return;
    }
    // TODO: Free parents recursively
    else
    {
        free_family((*p).parents[0]);
        free_family((*p).parents[1]);
    }
    // TODO: Free child
    free(p);
    return;
}

// CS50: Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// CS50: Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

// Randomly take allele from parents, takes in 2 parent structs of type person.
char parent_allele(person parent)
{
    int r = rand() % 2; //random of 4 choices
    if (r == 0)
    {
        //printf("SELECT %c\n",parent0.alleles[0]);
        return parent.alleles[0];
    }
    else
    {
        //printf("SELECT %c\n",parent0.alleles[1]);
        return parent.alleles[1];
    }
}
