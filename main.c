
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// initialisation de la table de frequence
struct tab_freq{
    float freq;
    int occ;
    char lettre;
    char bin[8];
};
typedef struct tab_freq tab_freq;

tab_freq*Calcul_frequence(FILE*input);
tab_freq*deCroissant(tab_freq*tab,int n);
tab_freq*CodageHuffman(tab_freq*tab);
void affichetab(tab_freq*tab);
void affiche_codeHuffman(tab_freq*tab);
int NombreElementTableau(tab_freq*tab);


int main()
{
    printf(" \t -- Codage de Huffman -- \n\n");
    FILE*fichier = fopen("tp.txt", "r");
    tab_freq*table,*t;
    table = (tab_freq*)malloc(sizeof(tab_freq)*100);
    t = (tab_freq*)malloc(sizeof(tab_freq)*100);
    table = Calcul_frequence(fichier);
    t = deCroissant(table,26);
    affichetab(t);
    t = CodageHuffman(table);
    affiche_codeHuffman(t);
    return 0;
    system("pause");
}

        // ---- Ecriture des fonctions -----

//tri decroissant du tableau
tab_freq*deCroissant(tab_freq*tab,int n){
    int i,j,min;
    tab_freq*temp;
    temp = (tab_freq*)malloc(sizeof(tab_freq)*100);
    for(i=0;i<n;i++){
        min = i;
        for(j = i+1;j<n;j++){
            if(tab[j].occ > tab[min].occ){
                min = j;
            }
        }
        temp[i] = tab[i];
        tab[i] = tab[min];
        tab[min] = temp[i];
     }

    return tab;
}

//Détermination du nombre d'element du tableau
int NombreElementTableau(tab_freq*tab){
    int i=0,s=0;

    while(tab[i].lettre != '\0' && i<=s){
        s++;
        i++;
    }
    return s;
}

//Calcul des frequences
tab_freq*Calcul_frequence(FILE*input){
    char c;
    int i,s=0;
    char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    tab_freq *t,*t1;
    t = (tab_freq*)malloc(sizeof(tab_freq)*100);
    t1 = (tab_freq*)malloc(sizeof(tab_freq)*100);


    if(input){

        for(int j=0;j<26;j++){
            t[j].occ = 0;

        }

        while((c=fgetc(input)) != EOF){
            for(i=0;i<26;i++){
                 if(c == alphabet[i]){
                    t[i].occ++;
                    t[i].lettre = c;
                    s++;
                }
            }
        }
        fclose(input);
        for(i=0;i<26;i++){
            t[i].freq = t[i].occ;
        }
         for(i=0;i<26;i++){
                 if(t[i].lettre != ' '){
                    t1[i].occ = t[i].occ;
                    t1[i].freq = t[i].freq/s;
                    t1[i].lettre = t[i].lettre;
                }
            }
    }
    return t1;
}

// affichage de la table
void affichetab(tab_freq*tab){
     printf("\n Table des occurrences et frequences des lettres \n\n");
    for(int a=0;a<26;a++){
            if(tab[a].occ != 0){
                 printf("%c \t %d \t %f \n",tab[a].lettre,tab[a].occ,tab[a].freq);
            }

    }
    return;

}

//affichage code de huffman
void affiche_codeHuffman(tab_freq*tab){
    printf("\n Table de codage de Huffman des caracteres \n\n");
    for(int a=0;a<26;a++){
            if(tab[a].occ != 0){
                 printf("%c\t %s \n",tab[a].lettre,tab[a].bin);
            }

    }
    return;
}

//Codage de huffman

tab_freq*CodageHuffman(tab_freq*tab){

    //declaration des tableaux pout le codage
    int i,j,taille,s=0,cpt = 0,temp,n,a=0,b=0,c=0;

    tab_freq*tabHuff;
    taille = NombreElementTableau(tab);
    n = taille;
    tabHuff = (tab_freq*)malloc(sizeof(tab_freq)*taille);

    //Je met tab dans TabHuff

    for(i=0;i<taille;i++){

    tabHuff[i].occ = tab[i].occ;
    tabHuff[i].freq = tab[i].freq;
    tabHuff[i].lettre = tab[i].lettre;

    }

    // Détermination du nombre d'occurences total
    for(i=0;i<taille;i++){
        s = s + tab[i].occ;
    }

    //Je met le vide dans bin des caractères
    for(i=0;i<taille;i++){
        for(j=0;j<8;j++){
            tab[i].bin[j] = ' ';
        }
    }

    // Addition des occurences des 02 dernières valeurs du tableau tab
    //Attribution du code de Huffman à chaque caractère de tab

    while(taille != 0 && tab[taille].occ != s){
        temp = tab[taille - 1].occ;
        tab[taille - 1].occ += tab[taille].occ;
           for(i = 0;i < n;i++){
                if(tab[taille - 1].occ == (temp + tab[taille].occ)){
                    tab[taille].bin[cpt-1] = '1';

                    tab[taille - 1].bin[cpt+a+b+c] = '0';

            }if(i > taille){
                    tab[i].bin[cpt-1] = '1';
            }
        }
        taille--;
        if(taille > 1){
            tab = deCroissant(tab,taille);
        }
        cpt++;
        a++;
        c = 1;

    }





    return tab;

}

