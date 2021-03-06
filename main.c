#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Ad: Lojik Devre Benzetimi
 * Aciklama: Basit devre elemanlaryndan olusan bir devreyi dosyadan
 *			 okuyarak girilen komutlara gore islem yapar.
 * Tarih: 14 Kasim 2018
 * Yapimci: Fatma Degirmenci & Berfin Kosemen
 * Numaralar: 170201008 & 170201058
 *
 * =============================================================================
 *
 * LISANS: MIT Ozgur Lisansi, Kaynak: http://ozgurlisanslar.org.tr/mit/
 *
 * Telif Hakki (c) 1998, 1999, 2000 Thai Acik Kaynak Yazilim Merkezi Ltd.
 *
 * Hicbir ucret talep edilmeden burada isbu yazilimin bir kopyasini ve
 * belgelendirme dosyalarini (�Yazilim�) elde eden herkese verilen izin;
 * kullanma, kopyalama, degistirme, birlestirme, yayimlama, dagitma, alt
 * lisanslama, ve/veya yazilimin kopyalarini satma eylemleri de dahil
 * olmak uzere ve bununla kisitlama olmaksizin, yazilimin sinirlama
 * olmadan ticaretini yapmak icin verilmis olup, bunlari yapmalari icin
 * yazilimin saglandigi kisilere asagidakileri yapmak kosuluyla sunulur:
 *
 * Yukaridaki telif hakki bildirimi ve isbu izin bildirimi yazilimin tum
 * kopyalarina veya onemli parcalarina eklenmelidir.
 *
 * YAZILIM �HICBIR DEGISIKLIK YAPILMADAN� ESASINA BAGLI OLARAK, TICARETE
 * ELVERISLILIK, OZEL BIR AMACA UYGUNLUK VE IHLAL OLMAMASI DA DAHIL VE
 * BUNUNLA KISITLI OLMAKSIZIN ACIKCA VEYA USTU KAPALI OLARAK HICBIR TEMINAT
 * OLMAKSIZIN SUNULMUSTUR. HICBIR KOSULDA YAZARLAR VEYA TELIF HAKKI SAHIPLERI
 * HERHANGI BIR IDDIAYA, HASARA VEYA DIGER YUKUMLULUKLERE KARSI, YAZILIMLA
 * VEYA KULLANIMLA VEYA YAZILIMIN BASKA BAGLANTILARIYLA ILGILI, BUNLARDAN
 * KAYNAKLANAN VE BUNLARIN SONUCU BIR SOZLESME DAVASI, HAKSIZ FIIL VEYA
 * DIGER EYLEMLERDEN SORUMLU DEGILDIR.
 */




struct kapi {
	char girisler[6][2]; //orn uc tane 20 karakterlik
	char cikis[2];
	char isim[5];
	int girisSayisi;
	int yayilimGecikmesi;
}kapilar[15];

struct anaGirisCikisOkuma {
	char girisler[5][2];
	char cikis[5][2];
}anaGirisCikis;

int devreDosyasiniOku();
void komutGir();
void degisim(char[],int,int);
void setlemeYap(char[], int );

int main()
{
	devreDosyasiniOku();
	komutGir();

    return 0;
}

void setlemeYap(char x[2], int setlenecekDeger) {

	FILE *deger = fopen("deger.txt", "r");

	char tumKelimeler[30][2] = {""};
	int i=0, kelimeSayisi=0, j=0;
	char kelime[50] = {""};

	rewind(deger);
	while(!feof(deger)) {
		fscanf(deger,"%s", &kelime);
		strcpy(tumKelimeler[i], kelime);
		i++;
	}

	kelimeSayisi = i;

	fclose(deger);
	deger = fopen("deger.txt", "w");
	rewind(deger);

	for(i=1; i<kelimeSayisi; i+=2) {

		if((strcmp(tumKelimeler[i-1], x) == 0)) {
			if((atoi(tumKelimeler[i])!=setlenecekDeger)) {
				if(i!=kelimeSayisi-1)  {
					fprintf(deger, "%s\t%d\n", tumKelimeler[i-1], setlenecekDeger);
				}
				else {
					fprintf(deger, "%s\t%d", tumKelimeler[i-1], setlenecekDeger);
				}
			}

			else {
				if(i!=kelimeSayisi-1) {
					fprintf(deger, "%s\t%s\n", tumKelimeler[i-1], tumKelimeler[i]);
				}

				else {
					fprintf(deger, "%s\t%s", tumKelimeler[i-1], tumKelimeler[i]);
				}
			}
		}

		else {

			if(i!=kelimeSayisi-1){
				fprintf(deger, "%s\t%s\n", tumKelimeler[i-1], tumKelimeler[i]);
			}
			else {
				fprintf(deger, "%s\t%s", tumKelimeler[i-1], tumKelimeler[i]);
			}
		}
	}
	fclose(deger);
}

void komutGir() {
	time_t rawtime;
	struct tm * timeinfo;
	char zaman [80];

	FILE *devre;
    FILE *deger;
    FILE *komutf = fopen("komutf.txt", "r");
	FILE *komut;
	FILE *sKomutu;
	FILE *log = fopen("log.txt", "w");
	fclose(log);

	log = fopen("log.txt", "a+");
	fputs("zaman\t\t\tkomut\t\t\tcikti\n", log);

    int bufferSize = 100 , i = 0,j =0;;
    char buf[bufferSize], komutlar[10][3] = {""}, acilacakDevre[10], acilacakKomut[10];

	i=0;
    while(fgets(buf, bufferSize, komutf) != NULL)  {
		printf("   %s", buf);
    }

    printf("Komut giriniz: \n");

    i = 0;
    while(!(strcmp(komutlar[i], "C") == 0 || strcmp(komutlar[i], "c") == 0)) {
        printf("\n");
        printf("> ");
        scanf("%s", &komutlar[i]);

		while(!((strcmp(komutlar[i], "Y") == 0 || strcmp(komutlar[i], "y") == 0 ||
				(strcmp(komutlar[i], "I") == 0 || strcmp(komutlar[i], "i") == 0) ||
				(strcmp(komutlar[i], "H") == 0 || strcmp(komutlar[i], "h") == 0) ||
				(strcmp(komutlar[i], "L") == 0 || strcmp(komutlar[i], "l") == 0) ||
				(strcmp(komutlar[i], "S") == 0 || strcmp(komutlar[i], "s") == 0) ||
				(strcmp(komutlar[i], "G") == 0 || strcmp(komutlar[i], "g") == 0) ||
				(strcmp(komutlar[i], "G*") == 0 || strcmp(komutlar[i], "g*") == 0) ||
				(strcmp(komutlar[i], "K") == 0 || strcmp(komutlar[i], "k") == 0) ||
				(strcmp(komutlar[i], "C") == 0 || strcmp(komutlar[i], "c") == 0) ))) {

				printf("Hatali komut!\n\n");
				printf("> ");
				scanf("%s", &komutlar[i]);
		}

        if(i==0) {
			if((strcmp(komutlar[0], "Y") != 0) || (strcmp(komutlar[0], "y") != 0)) {
				if((strcmp(komutlar[0], "C") == 0 || strcmp(komutlar[0], "c") == 0)) {
						exit(1);
				}

				while(!((strcmp(komutlar[0], "Y" ) == 0) || (strcmp(komutlar[0], "y") == 0))) {
					printf("Once Y/y komutunu girmelisiniz\n\n");
					printf("> ");
					scanf("%s", &komutlar[0]);

					if((strcmp(komutlar[0], "Y" ) == 0) || (strcmp(komutlar[0], "y") == 0))
						break;
				}
			}
        }

        if((strcmp(komutlar[i], "Y") == 0) || (strcmp(komutlar[i], "y") == 0)) {
			printf("\tAcilacak devre dosyasinin adinin girin: ");
			scanf("%s", &acilacakDevre);
			devre = fopen(acilacakDevre, "r");

			if(devre){
                printf("\t%s acildi\n", acilacakDevre);
            }
            else {
                printf("\tDosya acilamadi\n");
            }

			komut = fopen("komut.txt", "w");
            fputs(komutlar[i], komut);
            fputc('\t', komut);

            fputs(acilacakDevre, komut);
            fputc('\n', komut);
            fclose(komut);

			time (&rawtime);
			timeinfo = localtime(&rawtime);
			strftime (zaman,80,"%X %x",timeinfo);

			fprintf(log, "%s\t%s %s\t\t%s yuklendi\n", zaman, komutlar[i], acilacakDevre, acilacakDevre);

        }

        if(i==1) {
			if(!((strcmp(komutlar[1], "I") == 0  ) || (strcmp(komutlar[1], "i") == 0 ))) {

				if((strcmp(komutlar[1], "C") == 0 || strcmp(komutlar[1], "c") == 0)) {
					exit(1);
				}

				while((strcmp(komutlar[1], "I") != 0 ) || (strcmp(komutlar[1], "i") != 0 )) {
					printf("Once I/i komutunu girmelisiniz\n\n");
					printf("> ");
					scanf("%s", &komutlar[1]);

					if((strcmp(komutlar[1], "I" ) == 0) || (strcmp(komutlar[1], "i") == 0))
						break;
				}
			}
        }

        if((strcmp(komutlar[i], "I") == 0) || (strcmp(komutlar[i], "i") == 0)) {
            deger = fopen("deger.txt", "r");

            if(deger == NULL) {
                printf("\tdeger.txt acilamadi.\n");
            }
            else {
                printf("\tdeger.txt acildi.\n");
            }

			komut = fopen("komut.txt","a");
			fputs(komutlar[i], komut);
			fputc('\t', komut);

            fputs("deger.txt", komut);
            fputc('\n', komut);
            fclose(komut);

            time (&rawtime);
			timeinfo = localtime(&rawtime);
			strftime (zaman,80,"%X %x",timeinfo);

            fprintf(log, "%s\t%s %s\t\t%s\n", zaman, komutlar[i], "deger.txt", "degerler atandi");
        }

        char xx[2] = {""}, degerKelime[50][50] = {""}, kelime[50] = {""};
		int b, u;

        if((strcmp(komutlar[i], "G") == 0) || (strcmp(komutlar[i], "g") == 0)) {
            rewind(deger);

            printf("\tGiris/cikis ucundan birilerini secin: ");
			deger = fopen("deger.txt", "r");
            while (getchar() != '\n');
            scanf("%s", &xx);

			b = 0;
			rewind(deger);

			while(!feof(deger)) {
				fscanf(deger,"%s", &kelime);
				strcpy(degerKelime[b], kelime);
				b++;
			}

			for(u=0; u<b; u++) {
				if(strcmp(degerKelime[u], xx)== 0){
					printf("\t%s: %s\n", degerKelime[u], degerKelime[u+1]);
					break;
				}
			}

			komut = fopen("komut.txt","a");
			fputs(komutlar[i], komut);
			fputc('\t', komut);

            fputs(xx,komut);
            fputc('\n', komut);
            fclose(komut);

            time (&rawtime);
			timeinfo = localtime(&rawtime);
			strftime (zaman,80,"%X %x",timeinfo);

            fprintf(log, "%s\t%s %s\t\t\t%s\n", zaman, komutlar[i], xx, degerKelime[u+1]);
        }

        if((strcmp(komutlar[i], "G*") == 0) || (strcmp(komutlar[i], "g*") == 0)) {
			rewind(deger);

			time (&rawtime);
			timeinfo = localtime(&rawtime);
			strftime (zaman,80,"%X %x",timeinfo);
			fprintf(log, "%s\t%s\t\t\t", zaman, komutlar[i]);

			u = 0;
            while(fgets(buf, bufferSize, deger) != NULL)  {
                printf("   %s", buf);
				fprintf(log, "%s", buf );
				fprintf(log, "\t\t\t\t\t\t");
				u++;
            }

            printf("\n");
			komut = fopen("komut.txt","a");
			fputs(komutlar[i], komut);

            fputc('\n', komut);
            fclose(komut);
            fprintf(log, "\n");
        }

        if((strcmp(komutlar[i], "C") == 0 || strcmp(komutlar[i], "c") == 0)) {
			komut = fopen("komut.txt","a");
			fputs(komutlar[i], komut);
			fputc('\n', komut);
            fclose(komut);

			time (&rawtime);
			timeinfo = localtime(&rawtime);
			strftime (zaman,80,"%X %x",timeinfo);

			fprintf(log, "%s\t%s\n", zaman, komutlar[i]);

            break;
        }

        if((strcmp(komutlar[i], "K") == 0 || strcmp(komutlar[i], "k") == 0)) {

			printf("\tYazdirilacak komut dosyasinin adinin girin: ");
			scanf("%s", &acilacakKomut);

			komut = fopen("komut.txt","a");
			fputs(komutlar[i], komut);
			fputc('\t', komut);

            fputs(acilacakKomut, komut);
            fputc('\n', komut);
            fclose(komut);

			time (&rawtime);
			timeinfo = localtime(&rawtime);
			strftime (zaman,80,"%X %x",timeinfo);
			fprintf(log, "%s\t%s %s\n", zaman, komutlar[i], acilacakKomut);

			komut = fopen("komut.txt", "r");

			while(fgets(buf, bufferSize, komut) != NULL)  {
                printf("   %s", buf);
            }

            fclose(komut);
            printf("\n");
        }

		if((strcmp(komutlar[i], "H") == 0) || (strcmp(komutlar[i], "h") == 0)) {
            rewind(deger);
            printf("\tGiris/cikis ucundan birilerini secin: ");

			deger = fopen("deger.txt", "r");
            char tumDegerler[100][2] =  {""};
			int p = 0, kSayisi = 0, flag = 0;

            while (getchar() != '\n');
            scanf("%s", &xx);

            rewind(deger);
            while(!feof(deger)) {
				fscanf(deger,"%s", &kelime);
				strcpy(tumDegerler[p], kelime);
				p++;
			}
			kSayisi = p;

			for(p=0; p<kSayisi; p++) {
				if(strcmp(tumDegerler[p], xx) == 0) {
					if(strcmp(tumDegerler[p+1],"1") ==0) {
						printf("\t%s in degeri zaten 1!\n", xx);
						flag = 0;
						break;
					}
					else {
						flag = 1;
					}
				}
			}


			if(flag == 1) {
				komut = fopen("komut.txt","a");
				fputs(komutlar[i], komut);
				fputc('\t', komut);
				fputs(xx, komut);
				fputc('\n', komut);
				fclose(komut);

				time (&rawtime);
				timeinfo = localtime(&rawtime);
				strftime (zaman,80,"%X %x",timeinfo);
				fprintf(log, "%s\t%s %s\t\t\t%s birlendi\n", zaman, komutlar[i], xx, xx);

				degisim(xx,2,devreDosyasiniOku());
				printf("\n");
			}
        }

        if((strcmp(komutlar[i], "L") == 0) || (strcmp(komutlar[i], "l") == 0)) {
            rewind(deger);
            printf("\tGiris/cikis ucundan birilerini secin: ");

			deger = fopen("deger.txt", "r");
            char tumDegerler[100][2] =  {""};
			int p = 0, kSayisi = 0, flag = 0;

            while (getchar() != '\n');
            scanf("%s", &xx);

            rewind(deger);
            while(!feof(deger)) {
				fscanf(deger,"%s", &kelime);
				strcpy(tumDegerler[p], kelime);
				p++;
			}
			kSayisi = p;

			for(p=0; p<kSayisi; p++) {
				if(strcmp(tumDegerler[p], xx) == 0) {
					if(strcmp(tumDegerler[p+1],"0") ==0) {
						printf("\t%s in degeri zaten 0!\n", xx);
						flag = 0;
						break;
					}
					else {
						flag = 1;
					}
				}
			}

			if(flag == 1) {
				komut = fopen("komut.txt","a");
				fputs(komutlar[i], komut);
				fputc('\t', komut);
				fputs(xx, komut);
				fputc('\n', komut);
				fclose(komut);

				time (&rawtime);
				timeinfo = localtime(&rawtime);
				strftime (zaman,80,"%X %x",timeinfo);
				fprintf(log, "%s\t%s %s\t\t\t%s sifirlandi\n", zaman, komutlar[i], xx,xx);

				degisim(xx,2,devreDosyasiniOku());
				printf("\n");
			}
        }

        if((strcmp(komutlar[i], "S") == 0) || (strcmp(komutlar[i], "s") == 0)) {
			komut = fopen("komut.txt","a");
			fputs(komutlar[i], komut);
            fputc('\n', komut);
            fclose(komut);

            sKomutu = fopen("sKomutu.txt", "r");

			time (&rawtime);
			timeinfo = localtime(&rawtime);
			strftime (zaman,80,"%X %x",timeinfo);

			fprintf(log, "%s\t%s\t", zaman, komutlar[i]);

			int u=0;
            while(fgets(buf, bufferSize, sKomutu) != NULL)  {

				if(u!= 0) {
					fprintf(log, "\t\t\t\t\t\t");
				}
				if(u==0){
					fprintf(log,"\t\t");
				}
				printf("   %s", buf);
				fprintf(log, "%s  ", buf );

				u++;

            }
			fprintf(log, "\n");

            fclose(sKomutu);
            printf("\n");
        }

		i++;
    }

    for(i=0; i<10; i++) {
        if((strcmp(komutlar[i], "I") == 0) || (strcmp(komutlar[i], "i") == 0) ) {
            int a = fclose(deger);

            if(a == 0) {
                break;
            }
            else
                printf("\tKapatma islemi basarisiz.");
        }
    }

    for(i=0; i<10; i++) {
        if((strcmp(komutlar[i], "Y") == 0) || (strcmp(komutlar[i], "y") == 0) ) {
            int b = fclose(devre);

            if(b == 0) {
                //printf("kapatma islemi basarili.");
                break;
            }
            else
                printf("\tKapatma islemi basarisiz.");
        }
    }

    fclose(komutf);
}

int devreDosyasiniOku() {
	int toplamKapiSayisi = 0;
	FILE *devre = fopen("devre.txt", "r");

	char kelime[10] = {""};
	char tumKelimeler[50][50] = {""};
	int i= 0, j=0, k=0, m=0,sayac = 0, kelimeSayisi = 0;

	rewind(devre);

	i=0;
	while(!feof(devre)) {
		fscanf(devre,"%s", &kelime);
		strcpy(tumKelimeler[i], kelime);
		i++;
	}

	kelimeSayisi = i;

	for(i=0; i<kelimeSayisi; i++) {
		if(strcmp(tumKelimeler[i], ".kapi")==0){
			strcpy(kapilar[j].isim, tumKelimeler[i+1]);
			kapilar[j].girisSayisi = atoi(tumKelimeler[i+2]);
			strcpy(kapilar[j].cikis, tumKelimeler[i+3]);
			strcpy(kapilar[j].girisler[0], tumKelimeler[i+4]);

			if(kapilar[j].girisSayisi == 1) {
				kapilar[j].yayilimGecikmesi = atoi(tumKelimeler[i+5]);
			}

			else if(kapilar[j].girisSayisi == 2) {
				strcpy(kapilar[j].girisler[1], tumKelimeler[i+5]);
				kapilar[j].yayilimGecikmesi = atoi(tumKelimeler[i+6]);
			}

			else if(kapilar[j].girisSayisi == 3) {
				strcpy(kapilar[j].girisler[1], tumKelimeler[i+5]);
				strcpy(kapilar[j].girisler[2], tumKelimeler[i+6]);
				kapilar[j].yayilimGecikmesi = atoi(tumKelimeler[i+7]);
			}

			else if(kapilar[j].girisSayisi == 4) {
				strcpy(kapilar[j].girisler[1], tumKelimeler[i+5]);
				strcpy(kapilar[j].girisler[2], tumKelimeler[i+6]);
				strcpy(kapilar[j].girisler[3], tumKelimeler[i+7]);
				kapilar[j].yayilimGecikmesi = atoi(tumKelimeler[i+8]);
			}

			else if(kapilar[j].girisSayisi == 5) {
				strcpy(kapilar[j].girisler[1], tumKelimeler[i+5]);
				strcpy(kapilar[j].girisler[2], tumKelimeler[i+6]);
				strcpy(kapilar[j].girisler[3], tumKelimeler[i+7]);
				strcpy(kapilar[j].girisler[4], tumKelimeler[i+8]);
				kapilar[j].yayilimGecikmesi = atoi(tumKelimeler[i+9]);
			}

			j++;
		}

		k=0, sayac = 0;

		if(strcmp(tumKelimeler[i],".giris") == 0) {
			while(strcmp(tumKelimeler[i+1+sayac], "#girisler")!=0) {
				sayac++;
			}

			for(k=0; k<sayac; k++) {
				strcpy(anaGirisCikis.girisler[k], tumKelimeler[k+1]);
			}
		}

		sayac = 0;
		if(strcmp(tumKelimeler[i],".cikis") == 0) {

			while(strcmp(tumKelimeler[i+1+sayac], "#cikis")!=0) {
				sayac++;
			}

			for(k=0; k<sayac; k++) {
				strcpy(anaGirisCikis.cikis[k], tumKelimeler[k+1]);
			}
		}
	}

	FILE * baskaDosya;
	int a =0;
	char tumKelimelerBaskaDosya[50][50] = {""};
	int kelimeSayisiBaskaDosya = 0;

	for(i=1; i<kelimeSayisi; i++) {
		if(strcmp(tumKelimeler[i-1], ".include") == 0) {
			baskaDosya = fopen(tumKelimeler[i], "r");

			a=0;
			while(!feof(baskaDosya)) {
				fscanf(baskaDosya,"%s", &kelime);
				strcpy(tumKelimelerBaskaDosya[a], kelime);
				a++;
			}
			kelimeSayisiBaskaDosya = a;

			for(a=0; a<kelimeSayisiBaskaDosya; a++) {
				if(strcmp(tumKelimelerBaskaDosya[a], ".kapi")==0){
					strcpy(kapilar[j].isim, tumKelimelerBaskaDosya[a+1]);
					kapilar[j].girisSayisi = atoi(tumKelimelerBaskaDosya[a+2]);
					strcpy(kapilar[j].cikis, tumKelimelerBaskaDosya[a+3]);
					strcpy(kapilar[j].girisler[0], tumKelimelerBaskaDosya[a+4]);

					if(kapilar[j].girisSayisi == 1) {
						kapilar[j].yayilimGecikmesi = atoi(tumKelimelerBaskaDosya[a+5]);
					}

					else if(kapilar[j].girisSayisi == 2) {
						strcpy(kapilar[j].girisler[1], tumKelimelerBaskaDosya[a+5]);
						kapilar[j].yayilimGecikmesi = atoi(tumKelimelerBaskaDosya[a+6]);
					}

					else if(kapilar[j].girisSayisi == 3) {
						strcpy(kapilar[j].girisler[1], tumKelimelerBaskaDosya[a+5]);
						strcpy(kapilar[j].girisler[2], tumKelimelerBaskaDosya[a+6]);
						kapilar[j].yayilimGecikmesi = atoi(tumKelimelerBaskaDosya[a+7]);
					}

					else if(kapilar[j].girisSayisi == 4) {
						strcpy(kapilar[j].girisler[1], tumKelimelerBaskaDosya[a+5]);
						strcpy(kapilar[j].girisler[2], tumKelimelerBaskaDosya[a+6]);
						strcpy(kapilar[j].girisler[3], tumKelimelerBaskaDosya[a+7]);
						kapilar[j].yayilimGecikmesi = atoi(tumKelimelerBaskaDosya[a+8]);
					}

					else if(kapilar[j].girisSayisi == 5) {
						strcpy(kapilar[j].girisler[1], tumKelimelerBaskaDosya[a+5]);
						strcpy(kapilar[j].girisler[2], tumKelimelerBaskaDosya[a+6]);
						strcpy(kapilar[j].girisler[3], tumKelimelerBaskaDosya[a+7]);
						strcpy(kapilar[j].girisler[4], tumKelimelerBaskaDosya[a+8]);
						kapilar[j].yayilimGecikmesi = atoi(tumKelimelerBaskaDosya[a+9]);
					}

					j++;
				}
			}

			fclose(baskaDosya);
		}
	}

	fclose(devre);

	toplamKapiSayisi = j;

	return toplamKapiSayisi;
}

void degisim(char setlenecekDeger[], int x,int kapiSayisi){
	FILE *devre = fopen("deger.txt", "r");
	FILE *sKomutu = fopen("sKomutu.txt","w");

	char tumKelimeler[50][50] = {""},okunandeger[50][50]={""},a[2],k1[2],k2[2],degisim[50][2]={""};
	int i= 0,j,k,t,n,n1,b=0,c=0,d=0,min,m,m1,y,z,h,s,l,r,r1,kelimeSayisi = 0,say,say1=0,sayac1=0;
	int sayac2=0,say3,b1,c1,nsn=0,dizi[20]={10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};

	rewind(devre);
	i=0;
	while(!feof(devre)) {
		fscanf(devre,"%s", &tumKelimeler[i]);
		i++;
	}
	kelimeSayisi = i;

	for(i=0;i<kelimeSayisi;i++){
		strcpy(okunandeger[i],tumKelimeler[i]);
	}

	strcpy(a, setlenecekDeger);

	for(i=0;i<kelimeSayisi-1;i+=2){
		if(strcmp(a,tumKelimeler[i]) == 0){
			if(strcmp(tumKelimeler[i+1],"0") == 0){
				strcpy(okunandeger[i+1],"1");
				break;
			}
			else{
				strcpy(okunandeger[i+1],"0");
				break;
			}
		}
	}

	fprintf(sKomutu,"%d ns   %s  giris/cikisi  %s-> %s\n",nsn, tumKelimeler[i],tumKelimeler[i+1],okunandeger[i+1]);
	nsn++;
	setlemeYap(tumKelimeler[i], atoi(okunandeger[i+1]));

	while(1){
		for(j=0;j<kapiSayisi;j++){
			for(r=0;r<kapilar[j].girisSayisi;r++){
				if(strcmp(kapilar[j].girisler[r],okunandeger[i]) == 0){
					if(strcmp(kapilar[j].isim,"NOT") == 0){
						for(n=0;n<kelimeSayisi;n+=2){
		    				if(n!=i){
		    					if(strcmp(kapilar[j].cikis,okunandeger[n]) == 0){
				    				strcpy(degisim[b],okunandeger[n]);
									b++;
		    						strcpy(degisim[b],okunandeger[n+1]);
				   					b++;
				    				if(strcmp(okunandeger[i+1],"1") == 0) {
										strcpy(tumKelimeler[n+1],"0");
				    				}
                            		else {
										strcpy(tumKelimeler[n+1],"1");
                            		}
                            		strcpy(degisim[b],tumKelimeler[n+1]);
                            		b++;
                            		dizi[c]=kapilar[j].yayilimGecikmesi;
                        			c++;
								}
							}
						}
					}
					b1=b;
					c1=c;
					for(r1=0;r1<kapilar[j].girisSayisi;r1++){
						if(r1!=r){
							for(k=0;k<kelimeSayisi;k+=2){
								if(k!=i){
									if(strcmp(kapilar[j].girisler[r1],okunandeger[k]) == 0){
										if(strcmp(kapilar[j].isim,"NOR") == 0){
											say1++;
											if(say1 != 1){
		    									b=b1;
		    									c=c1;
		    									n=n1;
		    									if(strcmp(k1,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(k2,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(okunandeger[k+1],"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(sayac2 == 0)
		    										strcpy(tumKelimeler[n+1],"1");
		   										else
		   											strcpy(tumKelimeler[n+1],"0");
		   										strcpy(degisim[b],okunandeger[n]);
												b++;
				   								strcpy(degisim[b],okunandeger[n+1]);
				   								b++;
				   								strcpy(degisim[b],tumKelimeler[n+1]);
                                    			b++;
                                    			dizi[c]=kapilar[j].yayilimGecikmesi;
                        						c++;
											}
											else{
												for(n=0;n<kelimeSayisi;n+=2){
				    								if(n!=k){
				    									if(strcmp(kapilar[j].cikis,okunandeger[n]) == 0){
				    										strcpy(degisim[b],okunandeger[n]);
															b++;
				    										strcpy(degisim[b],okunandeger[n+1]);
				    										b++;
				    										strcpy(k1,okunandeger[i+1]);
				   											strcpy(k2,okunandeger[k+1]);
	                    	            					if(strcmp(okunandeger[i+1],"1") == 0 || strcmp(okunandeger[k+1],"1") == 0) {
																strcpy(tumKelimeler[n+1],"0");
																n1=n;
	                                						}
                                    						else {
																strcpy(tumKelimeler[n+1],"1");
																n1=n;
                                    						}
                                    						strcpy(degisim[b],tumKelimeler[n+1]);
                            	        					b++;
                                	    					dizi[c]=kapilar[j].yayilimGecikmesi;
                        									c++;
														}
													}
												}
											}
										}
										if(strcmp(kapilar[j].isim,"NAND") == 0){
											say1++;
											if(say1 != 1){
		    									b=b1;
		    									c=c1;
		    									n=n1;
		    									if(strcmp(k1,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(k2,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(okunandeger[k+1],"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(sayac1 == 0)
		    										strcpy(tumKelimeler[n+1],"0");
		   										else
		   											strcpy(tumKelimeler[n+1],"1");
		   										strcpy(degisim[b],okunandeger[n]);
												b++;
				   								strcpy(degisim[b],okunandeger[n+1]);
				   								b++;
				   								strcpy(degisim[b],tumKelimeler[n+1]);
                                    			b++;
                                    			dizi[c]=kapilar[j].yayilimGecikmesi;
                        						c++;
											}
											else{
												for(n=0;n<kelimeSayisi;n+=2){
				    								if(n!=k){
					   									if(strcmp(kapilar[j].cikis,okunandeger[n]) == 0){
					   										strcpy(degisim[b],okunandeger[n]);
															b++;
					   										strcpy(degisim[b],okunandeger[n+1]);
				   											b++;
				   											strcpy(k1,okunandeger[i+1]);
				   											strcpy(k2,okunandeger[k+1]);
				   											if(strcmp(okunandeger[i+1],"1") == 0 && strcmp(okunandeger[k+1],"1") == 0) {
																strcpy(tumKelimeler[n+1],"0");
																n1=n;
				   											}
                                   							else {
																strcpy(tumKelimeler[n+1],"1");
																n1=n;
                                   							}
                	                   						strcpy(degisim[b],tumKelimeler[n+1]);
                    	                					b++;
                        	            					dizi[c]=kapilar[j].yayilimGecikmesi;
                        									c++;
														}
													}
												}
											}
										}
		    							if(strcmp(kapilar[j].isim,"XOR") == 0){
		    								say1++;
		    								if(say1 != 1){
		    									b=b1;
		    									c=c1;
		    									n=n1;
		    									if(strcmp(k1,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(k2,"0") == 0)
		   											sayac1++;
		   										else
		   		 									sayac2++;
		    									if(strcmp(okunandeger[k+1],"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		   										if(sayac1 != 0 && sayac2 !=0)
		   											strcpy(tumKelimeler[n+1],"1");
	 											else
		   											strcpy(tumKelimeler[n+1],"0");
		   										strcpy(degisim[b],okunandeger[n]);
												b++;
				    							strcpy(degisim[b],okunandeger[n+1]);
				   								b++;
				   								strcpy(degisim[b],tumKelimeler[n+1]);
                               					b++;
                           						dizi[c]=kapilar[j].yayilimGecikmesi;
                       							c++;
											}
											else{
		   										for(n=0;n<kelimeSayisi;n+=2){
			    									if(n!=k){
			    										if(strcmp(kapilar[j].cikis,okunandeger[n]) == 0){
				    										strcpy(degisim[b],okunandeger[n]);
															b++;
				    										strcpy(degisim[b],okunandeger[n+1]);
				   											b++;
				   					 						strcpy(k1,okunandeger[i+1]);
				   					 						strcpy(k2,okunandeger[k+1]);
				    										if(strcmp(okunandeger[i+1],okunandeger[k+1]) == 0) {
																strcpy(tumKelimeler[n+1],"0");
																n1=n;
				    										}
                                   							else {
																strcpy(tumKelimeler[n+1],"1");
																n1=n;
                                   							}
                                   							strcpy(degisim[b],tumKelimeler[n+1]);
                                   							b++;
                                   							dizi[c]=kapilar[j].yayilimGecikmesi;
                       										c++;
														}
													}
												}
											}
										}
										if(strcmp(kapilar[j].isim,"OR") == 0){
											say1++;
		    								if(say1 != 1){
		    									b=b1;
		    									c=c1;
		    									n=n1;
		    									if(strcmp(k1,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(k2,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(okunandeger[k+1],"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(sayac2 == 0)
		    										strcpy(tumKelimeler[n+1],"0");
		   										else
		   											strcpy(tumKelimeler[n+1],"1");
		   										strcpy(degisim[b],okunandeger[n]);
												b++;
				   								strcpy(degisim[b],okunandeger[n+1]);
				   								b++;
				   								strcpy(degisim[b],tumKelimeler[n+1]);
                                    			b++;
                                    			dizi[c]=kapilar[j].yayilimGecikmesi;
                        						c++;
											}
											else{
												for(n=0;n<kelimeSayisi;n+=2){
					    							if(n!=k){
					    								if(strcmp(kapilar[j].cikis,okunandeger[n]) == 0){
					    									strcpy(degisim[b],okunandeger[n]);
															b++;
				    										strcpy(degisim[b],okunandeger[n+1]);
				    										b++;
				    										strcpy(k1,okunandeger[i+1]);
				   											strcpy(k2,okunandeger[k+1]);
	                                						if(strcmp(okunandeger[i+1],"1") == 0 || strcmp(okunandeger[k+1],"1") == 0) {
																strcpy(tumKelimeler[n+1],"1");
																n1=n;
	                                						}
                                    						else {
																strcpy(tumKelimeler[n+1],"0");
																n1=n;
            	                        					}
                	                    					strcpy(degisim[b],tumKelimeler[n+1]);
                    	                					b++;
                        	            					dizi[c]=kapilar[j].yayilimGecikmesi;
                        									c++;
														}
													}
												}
											}
										}
										if(strcmp(kapilar[j].isim,"AND") == 0){
											say1++;
		    								if(say1 != 1){
		    									b=b1;
		    									c=c1;
		    									n=n1;
		    									if(strcmp(k1,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(k2,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(okunandeger[k+1],"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(sayac1 == 0)
		    										strcpy(tumKelimeler[n+1],"1");
		   										else
		   											strcpy(tumKelimeler[n+1],"0");
		   										strcpy(degisim[b],okunandeger[n]);

												b++;
				   								strcpy(degisim[b],okunandeger[n+1]);
				   								b++;
				   								strcpy(degisim[b],tumKelimeler[n+1]);
                                    			b++;
                                    			dizi[c]=kapilar[j].yayilimGecikmesi;
                        						c++;
											}
											else{
												for(n=0;n<kelimeSayisi;n+=2){
					    							if(n!=k){
					   									if(strcmp(kapilar[j].cikis,okunandeger[n]) == 0){
					   										strcpy(degisim[b],okunandeger[n]);
															b++;
					   										strcpy(degisim[b],okunandeger[n+1]);
				   											b++;
				   											strcpy(k1,okunandeger[i+1]);
				   											strcpy(k2,okunandeger[k+1]);
				   											if(strcmp(okunandeger[i+1],"1") == 0 && strcmp(okunandeger[k+1],"1") == 0) {
																strcpy(tumKelimeler[n+1],"1");
																n1=n;
				   											}
                                   							else {
																strcpy(tumKelimeler[n+1],"0");
																n1=n;
                                   							}
    	                               						strcpy(degisim[b],tumKelimeler[n+1]);
        	                            					b++;
            	                        					dizi[c]=kapilar[j].yayilimGecikmesi;
                	        								c++;
														}
													}
												}
											}
										}
										if(strcmp(kapilar[j].isim,"XNOR") == 0){
											say1++;
		    								if(say1 != 1){
		    									b=b1;
		    									c=c1;
		    									n=n1;
		    									if(strcmp(k1,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(k2,"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(strcmp(okunandeger[k+1],"0") == 0)
		    										sayac1++;
		    									else
		    										sayac2++;
		    									if(sayac1 != 0 && sayac2 !=0)
		    										strcpy(tumKelimeler[n+1],"0");
		   										else
		   											strcpy(tumKelimeler[n+1],"1");
		   										strcpy(degisim[b],okunandeger[n]);
												b++;
				    							strcpy(degisim[b],okunandeger[n+1]);
				   								b++;
				   								strcpy(degisim[b],tumKelimeler[n+1]);
                                				b++;
                            					dizi[c]=kapilar[j].yayilimGecikmesi;
                        						c++;
											}
											else{
												for(n=0;n<kelimeSayisi;n+=2){
				    								if(n!=k){
				    									if(strcmp(kapilar[j].cikis,okunandeger[n]) == 0){
				    										strcpy(degisim[b],okunandeger[n]);
															b++;
				    										strcpy(degisim[b],okunandeger[n+1]);
				   											b++;
				   											strcpy(k1,okunandeger[i+1]);
				   											strcpy(k2,okunandeger[k+1]);
				    										if(strcmp(okunandeger[i+1],okunandeger[k+1]) == 0) {
																strcpy(tumKelimeler[n+1],"1");
																n1=n;
				    										}
                                    						else {
																strcpy(tumKelimeler[n+1],"0");
																n1=n;
                                	    					}
                    						                strcpy(degisim[b],tumKelimeler[n+1]);
                        						            b++;
                  						                	dizi[c]=kapilar[j].yayilimGecikmesi;
                  	      									c++;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
					say1=0;
					sayac1=0;
					sayac2=0;
					break;
				}
			}
		}

		say3=0;
		min = dizi[0];
		m1=0;
		for(m=1;m<20;m++){
			if(dizi[m] < min){
				min = dizi[m];
				m1 = m;
			}
		}
		for(m=0;m<20;m++){
			if(dizi[m] != 10){
				if(dizi[m] == min){
					say3++;
					m1=m;
				}
			}
		}
		say = 0;
		for(m=0;m<20;m++){
            if(dizi[m]==10){
                say++;
            }
		}
		if(say == 20)
            break;

		for(s=0;s<20;s++){
			if(m1 == s){
				l=3*s;
				fprintf(sKomutu,"%d ns   %s  giris/cikisi  %s-> %s\n",nsn,degisim[l],degisim[l+1],degisim[l+2]);
				if(say3 == 1){
					nsn++;
				}
			   	for(h=0;h<kelimeSayisi;h+=2){
		    		if(strcmp(degisim[l],okunandeger[h]) == 0){
			    		i=h;
					}
				}
				strcpy(okunandeger[i+1],degisim[l+2]);
				setlemeYap(okunandeger[i],atoi(degisim[l+2]));
			}
		}
		d++;
		dizi[m1]=10;
		if(d != 0){
			for(m=0;m<10;m++){
				if(dizi[m] != 10){
					dizi[m]=(dizi[m]-min);
				}
			}
		}
	}
	fclose(sKomutu);
}
