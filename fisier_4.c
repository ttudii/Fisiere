#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    FILE *txt,*bin;

    int **matrix;
    int l,c;

    printf("Numar de linii: ");
    scanf("%d",&l);

    printf("Numar de coloane: ");
    scanf("%d",&c);

    matrix=(int**)malloc(sizeof(int*)*l);

    for(int i=0;i<l;i++) matrix[i]=(int*)malloc(sizeof(int)*c);

    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            scanf("%d",matrix[i]+j);
        }
    }

    //scriere in fisier text

    if((txt=fopen("text_4.txt","wt"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            fprintf(txt,"%3d ",*(matrix[i]+j));
        }
    fprintf(txt,"\n");
    }

    fseek(txt,0L,SEEK_CUR);
    fprintf(txt,"\n\nNumarul de elemente ale matricei este: %d",l*c);

    fclose(txt);


    //scriere in fisier binar

    if((bin=fopen("binar_4.bin","wb"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    fwrite(matrix,sizeof(int),l*c,bin);

    char sir[100]="Numarul de elemente ale matricei este: ";
    fwrite(sir,sizeof(char),strlen(sir),bin);

    fclose(bin);

    //citire matrice din fisiere si afisare pe ecran

    int **new;
    char str[100];


    new=(int**)malloc(sizeof(int*)*l);
    for(int i=0;i<l;i++) new[i]=(int*)malloc(sizeof(int)*c);

    //citire in fisier binar

    if((bin=fopen("binar_4.bin","rb"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    fread(new,sizeof(int),l*c,bin);
    fread(str,sizeof(char),30,bin);

    printf("\nMartricea din fisierul binar este:\n");

    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            printf("%3d ",*(new[i]+j));
        }
    printf("\n");
    }

    puts(str);

    fclose(bin);

    printf("\n\n");

    //citire din fisier text

    if((bin=fopen("text_4.txt","rt"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    char car;

    printf("Martricea din fisierul text este:\n");

    while(!feof(txt)){
        fscanf(txt,"%c",&car);
        putchar(car);
    }

    fclose(txt);

    return 0;

}