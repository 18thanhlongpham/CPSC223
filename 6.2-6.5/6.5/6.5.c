#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE]; /

unsigned hash(char *s)
{
    unsigned hashval;
    
    for(hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;     
}

struct nlist *lookup(char *);

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL)  { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));

        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else  
        free((void *) np->defn);   

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}

struct nlist *undef(char *name) {
    struct nlist *found;

    found = lookup(name);

    if (found == NULL) 
        return NULL;
    else {
        if (found->next != NULL) {
            found->next = found->next->next;
            found = found->next;
        } else {
            hashtab[hash(name)] = NULL;
            free((void *) found);
        }
    }
    return found;
}

int main(int argc, char *argv[])
{
    struct nlist *table[3] = {
            (install("name1", "definition1")),
            (install("name2", "definition2")),
            (install("name3", "definition3"))
    };

    int i;

    for (i=0; i < 3; i++) {
        printf("%s->%s\n", table[i]->name, table[i]->defn);
    }

    undef("name1");
    undef("name3");

    struct nlist *result;

    char *names[3] = {
            "name1",
            "name2",
            "name3"
    };

    for (i = 0; i < 4; i++) {
        if ((result = lookup(names[i])) == NULL) {
            printf("name not found\n");
        } else {
            printf("%s->%s\n", result->name, result->defn);
        }
    }

    return 0;
}
