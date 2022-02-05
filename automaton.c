#include "automaton.h"
#include "chararray.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define UNABLE_OPEN_FILE 4
#define NON_VALID_FILE 10

automaton *createAutomaton(char const *filename)
{
    automaton *tmp = malloc(sizeof(automaton));
    if (tmp==NULL)
    {
        fprintf(stderr,"Unable to allocate memory for automaton. Aborting task and exiting program.\n");
        exit(EXIT_FAILURE);
    }
    tmp->states = newStack();
    FILE * automatonFile = fopen(filename,"rb");
    if (automatonFile==NULL)
    {
        fprintf(stderr,"File \"%s\" cannot be opened. Aborting task.\n",filename);
        fprintf(stderr,"Opening file returned code %i.\n",errno);
        deleteStack(tmp->states);
        free(tmp);
        exit(UNABLE_OPEN_FILE);
    }
    if (readFile(automatonFile,tmp))//readFile va lire le fichier d'automate et compléter les champs manquants
    {
        fclose(automatonFile);
        printf("File \"%s\" successfully read. Please enter your words.\n",filename);
        return tmp;
    }
    else
    {
        fclose(automatonFile);
        fprintf(stderr,"File \"%s\" is not a valid automaton file. Aborting task.\n",filename);
        clearAutomaton(tmp);
        exit(NON_VALID_FILE);
    }
}

void clearAutomaton(automaton *aut)//Sert à libérer la mémoire lorsque le programme se finit.
{
    deleteStack(aut->states);
    if (aut->actions != NULL)
    {
        for (int i = 0; i < aut->nbStates; i++)
        {
            free(aut->actions[i]);
        }
    }
    if (aut->branchement != NULL)
    {
        for (int i = 0; i < aut->nbStates; i++)
        {
            free(aut->branchement[i]);
        }
    }
    free(aut->branchement);
    if (aut->decale != NULL)
    {
        for (int i = 0; i < aut->nbStates; i++)
        {
            free(aut->decale[i]);
        }
    }
    free(aut->decale);
    free(aut->actions);
    free(aut->reduit1);
    free(aut->reduit2);
    free(aut);
}

bool readFile(FILE * const file,automaton *tmp)
{
    //Nombre d'états
    tmp->nbStates = 0;
    tmp->decale = NULL;
    tmp->branchement = NULL;
    tmp->actions = NULL;
    char *line=calloc(7,sizeof(char));
    fgets(line,7,file);
    char *shortline=substring(line,2,size(line)-1);
    sscanf(shortline,"%d",&(tmp->nbStates));
    free(shortline);
    shortline=NULL;
    if (line[0] != 'a' || line[1] != ' ' || tmp->nbStates <=0 || tmp->nbStates > 256)
    {
        free(line);
        return false;
    }
    free(line);
    line=NULL;
    //Initialisation des attributs de l'automate
    tmp->actions = calloc(tmp->nbStates,sizeof(int *));
    if (tmp->actions == NULL)
    {
        fprintf(stderr,"Unable to allocate memory. Major failure. Aborting task.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < tmp->nbStates; i++)
    {
        tmp->actions[i]=calloc(128,sizeof(int));
        if (tmp->actions[i] == NULL)
        {
            fprintf(stderr,"Unable to allocate memory. Major failure. Aborting task.\n");
            exit(EXIT_FAILURE);
        }
    }
    tmp->reduit1 = calloc(tmp->nbStates,sizeof(int));
    if (tmp->reduit1 == NULL)
    {
        fprintf(stderr,"Unable to allocate memory. Major failure Aborting task.\n");
        exit(EXIT_FAILURE);
    }
    tmp->reduit2 = calloc(tmp->nbStates,sizeof(int));
    if (tmp->reduit1 == NULL)
    {
        fprintf(stderr,"Unable to allocate memory. Major failure Aborting task.\n");
        exit(EXIT_FAILURE);
    }
    //Fonction action
    line=calloc(128*tmp->nbStates + 1,sizeof(char));
    if (line == NULL)
    {
        fprintf(stderr,"Unable to allocate memory. Major failure Aborting task.\n");
        exit(EXIT_FAILURE);
    }
    fread(line,sizeof(char),128*(tmp->nbStates) +1,file);//Lecture des actions
    for (int i = 0; i < 128*tmp->nbStates; i++)//Vérification des actions
    {
        tmp->actions[i/128][i%128]=line[i];
        if (tmp->actions[i/128][i%128] != 0 && tmp->actions[i/128][i%128] != 1 && tmp->actions[i/128][i%128] != 2 && tmp->actions[i/128][i%128] != 3)
        {
            free(line);
            return false;
        }
    }
    if (line[128*tmp->nbStates] != '\n')//Saut de ligne à la fin des actions
    {
        free(line);
        return false;
    }
    free(line);
    //Fonction réduit (première composante)
    line=calloc(tmp->nbStates + 1,sizeof(char));
    fread(line,sizeof(char),tmp->nbStates + 1,file);
    for (int i = 0; i < tmp->nbStates; i++)
    {
        tmp->reduit1[i]=line[i];
        if (tmp->reduit1[i]>= tmp->nbStates)
        {
            free(line);
            return false;
        }
    }
    if (line[tmp->nbStates] != '\n')
    {
        free(line);
        return false;
    }
    //Fonction réduit (deuxième composante)
    fread(line,sizeof(char),tmp->nbStates + 1,file);
    for (int i = 0; i < tmp->nbStates; i++)
    {
        tmp->reduit2[i]=line[i];
        if (tmp->reduit2[i] > 127 || tmp->reduit2[i] < 0)
        {
            free(line);
            return false;
        }
    }
    if (line[tmp->nbStates] != '\n')
    {
        free(line);
        return false;
    }
    free(line);
    //Fonction décale. On va considérer que, si la case tmp->decale[i][j] ne peut pas être atteinte, alors elle prend la valeur -1.
    tmp->decale = malloc(tmp->nbStates*sizeof(int*));
    if (tmp->decale == NULL)
    {
        fprintf(stderr,"Unable to allocate memory. Aborting task.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < tmp->nbStates; i++)
    {
        tmp->decale[i]=malloc(128*sizeof(int));
        if (tmp->decale[i] == NULL)
        {
            fprintf(stderr,"Unable to allocate memory. Aborting task.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < 128; j++)
        {
            tmp->decale[i][j] = -1;
        }
    }
    line=calloc(3,sizeof(char));
    fread(line,sizeof(char),3,file);
    int i = 0;
    while ((line[0] != '\255' || line[1]!='\255' || line[2]!='\255') && i < tmp->nbStates * 128)
    {   
        //Il y a au maximum n*128 possibilités pour décale. On a un compteur qui doit être inférieur à cette valeur.
        if (line[0] < 0 || line[0] >= tmp->nbStates || line[2] < 0 || line[2] >= tmp->nbStates || line[1] < 0 || line[1] >= 128)
        {
            free(line);
            return false;
        }
        tmp->decale[(int)line[0]][(int)line[1]] = line[2];
        fread(line,sizeof(char),3,file);
        i++;
    }
    if (i >= tmp->nbStates * 128)
    {
        free(line);
        return false;
    }
    //Fonction branchement. Même convention que décale
    tmp->branchement = malloc(tmp->nbStates * sizeof(int *));
    if (tmp->branchement == NULL)
    {
        fprintf(stderr,"Unable to allocate memory. Aborting task.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < tmp->nbStates; i++)
    {
        tmp->branchement[i]=malloc(128*sizeof(int));
        if (tmp->branchement[i] == NULL)
        {
            fprintf(stderr,"Unable to allocate memory. Aborting task.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < 128; j++)
        {
            tmp->branchement[i][j] = -1;
        }
    }
    fread(line,sizeof(char),3,file);
    i=0;
    while ((line[0] != '\255' || line[1]!='\255' || line[2]!='\255') && i < tmp->nbStates * 128)
    {   
        //Pareil que la boucle précédente
        if (line[0] < 0 || line[0] >= tmp->nbStates || line[2] < 0 || line[2] >= tmp->nbStates || line[1] < 0 || line[1] >= 128)
        {
            free(line);
            return false;
        }
        tmp->branchement[(int)line[0]][(int)line[1]] = line[2];//Cast pour éviter le warning array subscript has type char
        fread(line,sizeof(char),3,file);
    }
    if (i >= tmp->nbStates * 128)
    {
        free(line);
        return false;
    }
    free(line);
    return true;
}

void clearStatesStack(automaton *aut)
{
    deleteStack(aut->states);
    aut->states = newStack();
}