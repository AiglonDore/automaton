#include "loop.h"
#include <string.h> //Fournit la fonction strcmp

void processLoop(automaton *used)
{
    char input[256];
    char word[256];
    while (1)
    {
        /*
        Cette boucle s'interrompt uniquement lorsque l'utilisateur le veut, pour lui permettre de fermer le programme
        */
        fgets(input,256,stdin);
        sscanf(input,"%s",word);
        if (!strcmp(word,"exit") || !strcmp(word,"quit"))
        {
            char tmp = '\0';
            printf("Do you want to exit? [y/n]\n");
            scanf("%c",&tmp);
            if (tmp == 'y' || tmp == 'Y')
            {
                break;
            }
        }
        processWord(used,input);
        clearStatesStack(used);
        printf("Another word?\n");
    }
}

void processWord(automaton * used, char *word)
{
    int count = 0;
    int ended = 0;
    pushBack(used->states,0);
    while (!ended)
    {
        //Le mot est de longueur finie et le fichier est conforme donc l'état "Accepté" ou "Rejeté" est forcément atteint à un moment donné
        int x =used->actions[top(used->states)][(int)word[count]];
        if (x == 0)//Rejette
        {
            printf("Rejected.\n");
            if (word[count] == '\n') printf("Error when encountered a \"\\n\" at position %d (ASCII code %i).\n",count + 1,(int)word[count]);
            else if (word[count] == ' ') printf("Error when encountered a blank space at position %d (ASCII code %i).\n",count + 1,(int)word[count]);
            else  printf("Error at letter %d: \"%c\" (ASCII code %i).\n",count + 1,word[count],(int)word[count]);
            printf("Failure to find a correct letter.\nThis letter is not part of the recognized alphabet or this character is not expected at this position.\n");
            ended = 1;
        }
        else if (x == 1)//Accepte
        {
            printf("Accepted.\n");
            ended = 1;
        }
        else if (x == 2)//Décale
        {
            pushBack(used->states,used->decale[top(used->states)][(int)word[count]]);
            count++;
        }
        else//Réduit. Pas besoin de tester si ça vaut 3 car le fichier est conforme et la fonction action ne peut renvoyer que 0, 1, 2 ou 3
        {
            int n = used->reduit1[top(used->states)];
            int A = used->reduit2[top(used->states)];
            for (int i = 0; i < n; i++)
            {
                popBack(used->states);
            }
            pushBack(used->states,used->branchement[top(used->states)][A]);
        }
    }
}