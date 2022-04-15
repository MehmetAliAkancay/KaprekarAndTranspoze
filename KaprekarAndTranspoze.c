#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

FILE *transpoze;
FILE *Kaprekar;
int **dizi,**transpozedizi,*bubbledizi;
int satir_sayisi,sutun_sayisi,tsatir_sayisi,tsutun_sayisi,eleman_sayisi,i,j,gecici,x=0,sayac=0;

int main()
{
    DinamikBellekMatris();
    BubbleSort();
    DiziTranspoze();
    TranspozeYazdirma();
    KaprekarYazdirma();
    MatrisBosaltma();
    return 0;
}
void DinamikBellekMatris()
{
    srand(time(NULL));      //random sayilarin program her calistiginda farkli degerler vermesi icin.
    printf("Satir sayisini giriniz:");
    scanf("%d",&satir_sayisi);                 //kullanicinin girdigi degerlere gore matris aciyoruz.
    printf("Sutun sayisini giriniz:");
    scanf("%d",&sutun_sayisi);
    eleman_sayisi=satir_sayisi*sutun_sayisi;

    dizi=(int **)malloc(sizeof(int)*satir_sayisi+20000); //satir sayisina gore bellekten yer ayiriyoruz eger yer yok ise hata veriyor.
        if(dizi==NULL)
        printf("Yetersiz bellek.!");

    for(i=0;i<satir_sayisi;i++)   //her satir icin sutun ayarliyoruz.
    {
        dizi[i]=malloc(sizeof(int)*sutun_sayisi+20000);
           if(dizi[i]==NULL)
           printf("Yetersiz bellek.!");
    }
    bubbledizi=(int *)malloc(sizeof(int)*eleman_sayisi);   //bubble sort yapmak icin dinamik bellek yöntemiyle 1D dizi aciyoruz.
        if(bubbledizi==NULL)
        printf("Yetersiz bellek.!");
}

void BubbleSort()
{
    for(i=0;i<satir_sayisi;i++)       //matrisimize 5-40000 arasi rastgele  deger atiyoruz
    {
		for(j=0;j<sutun_sayisi;j++)
        {
           dizi[i][j]=rand()%39995+5;
        }
    }
    for(i=0;i<satir_sayisi;i++)       //2D dizimizdeki elemanlari 1D diziye aktariyoruz.
    {
       for(j=0;j<sutun_sayisi;j++)
       {
         bubbledizi[x++]=dizi[i][j];
       }
    }
   for(i=0;i<eleman_sayisi;i++)          //bubble sort ile 1D dizimizi siraliyoruz.
    {
     for(j=0;j<eleman_sayisi-1;j++)
     {
       if(bubbledizi[j]>bubbledizi[j+1])
        {
         gecici=bubbledizi[j];
         bubbledizi[j]=bubbledizi[j+1];
         bubbledizi[j+1]=gecici;
        }
      }
    }
    x=0;
    for(i=0;i<satir_sayisi;i++)         //1D dizimizden 2D dizimize sirali sekilde aktarip yazdiriyoruz.
    {
      for(j=0;j<sutun_sayisi;j++)
      {
        dizi[i][j]=bubbledizi[x++];
      }
    }
}

void DiziTranspoze()
{
    tsatir_sayisi=sutun_sayisi;
    tsutun_sayisi=satir_sayisi;
    transpozedizi=(int **)malloc(sizeof(int)*tsatir_sayisi+20000);
        if(transpozedizi==NULL)                //dinamik bellek yöntemiyle transpoze etcegimiz diziyi aktarmak icin baska birdizi aciyoruz.
        printf("Yetersiz bellek.!");

    for(i=0;i<tsatir_sayisi;i++)
    {
        transpozedizi[i]=malloc(sizeof(int)*tsutun_sayisi+20000); //her satira bir sutun aciyoruz.
           if(transpozedizi[i]==NULL)
           printf("Yetersiz bellek.!");
    }
    for(i=0;i<satir_sayisi;i++)
     {
         for(j=0;j<sutun_sayisi;j++)            //dizimizin transpozesini aliyoruz.
         {
            transpozedizi[j][i]=dizi[i][j];
         }
     }
}

void TranspozeYazdirma()
{
    transpoze=fopen("transpoze.txt","w+");         //yazdirmak icin metin belgesi aciyoruz.
    if(transpoze==NULL)
    {
        printf("transpoze.txt dosyasi acilamadi.!\n");
        exit(1);
    }
    fprintf(transpoze,"         *****Matrisin ilk hali*****         \n");
    for(i=0;i<satir_sayisi;i++)
    {
        for(j=0;j<sutun_sayisi;j++)                            //metin belgemize dizimizin ilk halini yazdiriyoruz.
        {
            fprintf(transpoze,"%d\t",dizi[i][j]);
        }
        fprintf(transpoze,"\n");
    }
    fprintf(transpoze,"\n");
    fprintf(transpoze,"      *****Matrisin transpozeli hali*****         \n");
    for(i=0;i<sutun_sayisi;i++)
    {
        for(j=0;j<satir_sayisi;j++)
        {
            fprintf(transpoze,"%d\t",transpozedizi[i][j]);     //metin belgemize dizimizin transpozeli halini yazdiriyoruz.
        }
        fprintf(transpoze,"\n");
    }
    if(transpoze!=NULL)
    {
        printf("\nYazdirma islemi tamam.!\n");               //yazdirma islemini kontrol ediyoruz.
    }
    fclose(transpoze);
}

bool KaprekarBulma(int degisken)                    //kaprekar sayi kontrolü.
{
    if(degisken==1)
        return true;
    int kare_degisken=degisken*degisken;
    int basamak=0,sayac;
    while(kare_degisken)
    {
        basamak++;
        kare_degisken/=10;
    }
    kare_degisken=degisken*degisken;
    for(int basamak2=1;basamak2<basamak;basamak2++)
    {
        int bolum=pow(10,basamak2);
        if(bolum==degisken)
            continue;
        int toplam=kare_degisken/bolum+kare_degisken%bolum;
        if(toplam==degisken)
            return true;
    }
    return false;
}

void KaprekarYazdirma()
{
    Kaprekar=fopen("kaprekar.txt","w+");         //kaprekar sayilari yazdirmak icin metin belgesi aciyoruz.
    if(Kaprekar==NULL)
    {
        printf("kaprekar.txt dosyasi acilamadi.!\n");
        exit(1);
    }
    for(i=0;i<tsatir_sayisi;i++)
    {
        for(j=0;j<tsutun_sayisi;j++)
        {
            if(KaprekarBulma(transpozedizi[i][j]))
            {
                fprintf(Kaprekar,"%d\t",transpozedizi[i][j]);  //kaprekar sayilari dosyamiza yazdiriyoruz.
                sayac++;
            }
        }
    }
    if(sayac==0)
    {
        fprintf(Kaprekar,"Kaprekar Sayi YOktur.!\n");
        printf("Kaprekar Sayi YOktur.!\n");
    }
    else
    {
        printf("%d tane kaprekar sayi vardir.!\n",sayac);
    }
    fclose(Kaprekar);
}

void MatrisBosaltma()
{
    for(i=0;i<satir_sayisi;i++)          //bellegi bosaltmak icin ilk once satirlari bosaltiyoruz.
    {
		free(dizi[i]);
	}
	free(dizi);                         //satirlar bosaldiktan sonra bosaldigini soyluyoruz.

	for(i=0;i<tsatir_sayisi;i++)        //bellegi bosaltmak icin ilk once satirlari bosaltiyoruz.
    {
		free(transpozedizi);
	}
    free(transpozedizi);                 //satirlar bosaldiktan sonra bosaldigini soyluyoruz.
}
