#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct DATA {
    int luna;
    int an;
};

struct AUTOMOBIL{
    char marca[30];
    char tip;
    char model[30];
    struct DATA data;
};

struct INDEX{
    int indice;
    struct DATA data;
};

struct AUTOMOBIL citire(){

    struct AUTOMOBIL automobil;
    
        printf("Marca: ");
        scanf("%s",automobil.marca);
        getchar();

        do{
        printf("Tip(Motorina/Benzina): ");
        scanf("%c",&automobil.tip);
        getchar();
        }while(tolower(automobil.tip)!='b' && tolower(automobil.tip)!='m');

        do{
        printf("Model(berlina/break/decapotabila): ");
        scanf("%s",automobil.model);
        getchar();
        }while(strcmp(automobil.model,"berlina")!=0 && strcmp(automobil.model,"break")!=0 && strcmp(automobil.model,"decapotabila")!=0);
        //se poate face verificarea si pentru sirul format dupa aplicarea strlwr();

        printf("Data fabricatiei\n");
        //anul mai mare de 2000
        printf("An: ");
        scanf("%d",&automobil.data.an);
        //luna intre valorile 1 si 12
        printf("Luna: ");
        scanf("%d",&automobil.data.luna);

        printf("\n\n");

    return automobil;

    
}

struct AUTOMOBIL adaugare(FILE *fp){

    struct AUTOMOBIL adaugat;

    adaugat=citire();

    if((fp=fopen("fisier_7.bin","ab"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    fseek(fp,0L,SEEK_END);

    fwrite(&adaugat,sizeof(struct AUTOMOBIL),1,fp);

    fclose(fp);

    return adaugat;

}

int find(char sasiu[],char type,struct AUTOMOBIL temp[],int nr_auto){

    int found=0;

    for(int i=0;i<nr_auto;i++){
        if(strcmp(sasiu,temp[i].marca)==0 && tolower(type)==tolower(temp[i].tip))
        {
            found=1;
            break;
        }
    }

    return found;

}

void vechime(FILE *fp,struct AUTOMOBIL temp[],int nr_auto, int *nr_old){

    if((fp=fopen("vechime_7.bin","wb"))==NULL){
        printf("fisierul nu a putut fi deschis!");
        exit(1);
    }

    int year=2023,month=5;

    for(int i=0;i<nr_auto;i++){
        if((year-5)>temp[i].data.an){
        fwrite(&temp[i],sizeof(struct AUTOMOBIL),1,fp);
        *nr_old=*nr_old+1;
        }
        else
        if((year-5)==temp[i].data.an && temp[i].data.luna-month<0){
        fwrite(&temp[i],sizeof(struct AUTOMOBIL),1,fp);
        *nr_old=*nr_old+1;
        }
    }

    fclose(fp);

}

void ordonare(struct INDEX *index,struct AUTOMOBIL temp[],int nr_auto){
    
    int i,j;
    
    for(i=0;i<nr_auto;i++){
        index[i].data.an=temp[i].data.an;
        index[i].data.luna=temp[i].data.luna;
        index[i].indice=i;
    }

    struct INDEX aux;

    for(i=0;i<nr_auto;i++){
        for(j=i+1;j<nr_auto;j++){
            if((index[i].data.an>index[j].data.an) || ((index[i].data.an==index[j].data.an) && (index[i].data.luna>index[j].data.luna)))
            {
                aux=index[i];
                index[i]=index[j];
                index[j]=aux;
            }
        }
    }

    printf("\n\n");

    for(i=0;i<nr_auto;i++) printf("%d ",index[i].indice);

}

int main(){

    FILE *fp;

    printf("Evidenta automobilelor din parcului auto\n\n");

    struct AUTOMOBIL automobil;
    struct AUTOMOBIL adaugat;
    int i;

    if((fp=fopen("fisier_7.bin","wb"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }
    
    for(i=0;i<3;i++){

    printf("Automobilul %d\n\n",i+1);

    automobil=citire();

    fwrite(&automobil,sizeof(struct AUTOMOBIL),1,fp);

    }

    fclose(fp);

    int nr_auto=3;

    //adaugarea unor alte automobile

    char car;
    int out=0;

    getchar();

    do{

        printf("Adaugare element: \n\n");

        adaugat=adaugare(fp);

        nr_auto++;

        getchar();

        do{
            printf("Mai adaugi?(y or n)\n");
            scanf("%c",&car);
            getchar();
        }while(tolower(car)!='y' && tolower (car!='n'));

        if(tolower(car)=='n') out=1;

        printf("\n\n");

    }while(!out);

    //verificare introducerea datelor si retinerea lor intr-un vector de structuri

    if((fp=fopen("fisier_7.bin","rb"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    struct AUTOMOBIL *temp;

    temp=(struct AUTOMOBIL*)malloc(sizeof(struct AUTOMOBIL)*nr_auto);

    i=0;

    while(!feof(fp)){
        fread(&temp[i],sizeof(struct AUTOMOBIL),1,fp);
        i++;
    }

    fclose(fp);

    //printf("\n\n");

    printf("Scriere pentru verificare:\n\n");
    for(i=0;i<nr_auto;i++){
    printf("%s ",temp[i].marca);
    printf("%c ",temp[i].tip);
    printf("%s ",temp[i].model);
    printf("%d %d",temp[i].data.an,temp[i].data.luna);
    printf("\n");
    }

    //cautare in fisier

    char sasiu[30];
    char type;

    printf("Introduceti marca cautata: ");
    scanf("%s",sasiu);
    getchar();

    do{
    printf("Introduceti tipul de carburant: ");
    scanf("%c",&type);
    getchar();
    }while(tolower(type)!='b' && tolower(type)!='m');

    int rez=find(sasiu,type,temp,nr_auto);
    
    if(rez==1) printf("Valoarea exista in evidenta!");
    else
    printf("Valoarea nu exista in evidenta");

    //lista a automobilelor cu vechime mai mare de 5 ani
    //Consideram anul de infiintare 2023 luna a 12-a

    int nr_old=0;

    vechime(fp,temp,nr_auto,&nr_old);

    struct AUTOMOBIL *old;

    old=(struct AUTOMOBIL*)malloc(sizeof(struct AUTOMOBIL)*nr_old);

    if((fp=fopen("vechime_7.bin","rb"))==NULL){
        printf("fisierul nu a putut fi deschis!");
        exit(1);
    }

    i=0;

    while(!feof(fp)){
        fread(&old[i],sizeof(struct AUTOMOBIL),1,fp);
        i++;
    }

    fclose(fp);

    printf("\n\n");

    printf("Lista automobilelor cu vechime mai mare de 5 ani este:\n\n");

    for(i=0;i<nr_old;i++){
        printf("%s ",old[i].marca);
        printf("%c ",old[i].tip);
        printf("%s ",old[i].model);
        printf("%d %d",old[i].data.an,old[i].data.luna);
        printf("\n");
    }

    //ordonarea automobilelor crescator dupa data de fabricatie

    struct INDEX *index;

    index=(struct INDEX*)malloc(sizeof(struct INDEX)*nr_auto);

    ordonare(index,temp,nr_auto);

    if((fp=fopen("ordonare_7.bin","wb"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    for(i=0;i<nr_auto;i++){
        fwrite(&temp[index[i].indice],sizeof(struct AUTOMOBIL),1,fp);
    }

    fclose(fp);

    //verificare

    if((fp=fopen("ordonare_7.bin","rb"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    struct AUTOMOBIL *verif;

    verif=(struct AUTOMOBIL*)malloc(sizeof(struct AUTOMOBIL)*nr_auto);

    i=0;

    while(!feof(fp)){
        fread(&verif[i],sizeof(struct AUTOMOBIL),1,fp);
        i++;
    }

    fclose(fp);

    printf("\n\n");

    printf("Ordonarea dupa data de fabricatie:\n\n");
    for(i=0;i<nr_auto;i++){
    printf("%s ",verif[i].marca);
    printf("%c ",verif[i].tip);
    printf("%s ",verif[i].model);
    printf("%d %d",verif[i].data.an,verif[i].data.luna);
    printf("\n");
    }

    return 0;

}