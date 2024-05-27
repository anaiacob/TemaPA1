#include "functii.h"
//AM CEDAT NERVOS CU \r\n, fiindca asta era singura diferenta si am stat 2 zile sa o depistez
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
    echipa* lista_team=NULL;
    int nr_echipe_ramase,r;
    echipa* lista_arbore=NULL;
    citeste_cerinte(fisier_cerinte,cerinte);
    if(cerinte[0]==1 && cerinte[1]==0 && cerinte[2]==0 && cerinte[3]==0 && cerinte[4]==0)
    {
        cerinta1(fisier_echipe,rez_cerinte);
    }
    else if(cerinte[0]==1 && cerinte[1]==1 && cerinte[2]==0 && cerinte[3]==0 && cerinte[4]==0)
    {
        cerinta2(fisier_echipe,rez_cerinte,&lista_team,&nr_echipe_ramase);
    }
    else if(cerinte[0]==1 && cerinte[1]==1 && cerinte[2]==1 && cerinte[3]==0 && cerinte[4]==0)
    {
        cerinta2(fisier_echipe,rez_cerinte,&lista_team,&nr_echipe_ramase);
        fprintf(rez_cerinte,"\n");
        r=0;
        cerinta3(fisier_echipe,rez_cerinte,&lista_team,&nr_echipe_ramase,&lista_arbore,&r);

    }
    else if(cerinte[0]==1 && cerinte[1]==1 && cerinte[2]==1 && cerinte[3]==1 && cerinte[4]==0)
    {
        cerinta2(fisier_echipe,rez_cerinte,&lista_team,&nr_echipe_ramase);
        fprintf(rez_cerinte,"\n");
        r=0;
        cerinta3(fisier_echipe,rez_cerinte,&lista_team,&nr_echipe_ramase,&lista_arbore,&r);
        int nrechip=8;
        cerinta4(rez_cerinte,&lista_arbore,&nrechip,r);
    }
    else if(cerinte[0]==1 && cerinte[1]==1 && cerinte[2]==1 && cerinte[3]==1 && cerinte[4]==1)
    {
        cerinta2(fisier_echipe,rez_cerinte,&lista_team,&nr_echipe_ramase);
        fprintf(rez_cerinte,"\n");
        r=0;
        cerinta3(fisier_echipe,rez_cerinte,&lista_team,&nr_echipe_ramase,&lista_arbore,&r);
        int nrechip=8;
        cerinta4(rez_cerinte,&lista_arbore,&nrechip,r);
        cerinta5(rez_cerinte,&lista_arbore,&nrechip);
    }
    else
    {
        printf("Eroare.\n");
    }
    free(cerinte);
    fclose(fisier_cerinte);
    fclose(fisier_echipe);
    fclose(rez_cerinte);
    return 0;
}
