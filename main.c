#include "functii.h"
//#include "liste.h"
//void citireFisiere(char* ar1, FILE** f1, char* ar2, FILE** f2, char* ar3, FILE** f3);

int main(int argc, char* argv[])
{
    FILE* fisier_cerinte,*fisier_echipe,*rez_cerinte;
    /*printf("%d \n",argc);
    printf("%s \n",argv[1]);
    printf("%s \n",argv[2]);
    printf("%s \n",argv[3]);*/
    if (argc < 4) {
        fprintf(stderr, "Usage: %s file1 file2 file3\n", argv[0]);
        return 1;
    }

    deschidere_fisiere(argv[1],&fisier_cerinte,argv[2],&fisier_echipe,argv[3],&rez_cerinte);
    int* cerinte=(int*)malloc(5*sizeof(int));
    citeste_cerinte(fisier_cerinte,cerinte);
    echipa* lista_echipe=NULL;
    if(cerinte[0]==1)
    {
        cerinta1(fisier_echipe,&lista_echipe,rez_cerinte);
    }
    if(cerinte[2]==1)
    {
        printf("In executare.\n");
    }
    if(cerinte[3]==1)
    {
        printf("In executare.\n");
    }
    if(cerinte[4]==1)
    {
        printf("In executare.\n");
    }
    //citireFisiere(argv[1],&f1,argv[2],&f2,argv[3],&f3);
    /*fseek(f1,0,2);
    int filesize=ftell(f1);
    int nr_elem=filesize/sizeof(int);
    printf("%d ",nr_elem);
    int cerinta[5];
    nr_elem=5;
    citeste_cerinte(cerinta,&f1,&nr_elem);
    if(cerinta[0]==1)
    {
        cerinta1(f2,f3);
    }
    /*
    if(cerinta[1]==1)
    {

    }
    if(cerinta[2]==1)
    {

    }
    if(cerinta[3]==1)
    {

    }
    if(cerinta[4]==1)
    {

    }*/
    free(cerinte);
    fclose(fisier_cerinte);
    fclose(fisier_echipe);
    fclose(rez_cerinte);
    return 0;
}
