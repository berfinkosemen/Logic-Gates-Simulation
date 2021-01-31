# Logic-Gates-Simulation

Lojik Devre Benzetimi

Fatma Değirmenci  -	170201008
Berfin Kösemen	  -	170201058

Bu readme.txt dosyası, Lojik Devre Benzetimi projesine aittir.
Bu paket, kaynak kodu ile aynı dizin içerisinde bulunacaktır.


1-PAKETİN İÇERİĞİ:
-------------------
170201008-170201058.txt - Projenin tek dosyaya indirgenmiş salt kaynak kodu.
README.md - Bu dosya.
-------------------


2-SİSTEM GEREKSİNİMLERİ:
-------------------
gcc - GNU Compiler Colection - http://gcc.gnu.org/
-------------------


3-KURULUM:
-------------------
Paket içeriğini yukarıda görebilirsiniz.

Bu kod, iki adet Windows kurulu makinede çalıştırıldı:
- Fatma'nın Windows 10 yüklü dizüstü bilgisayarında.
- Berfin'in Windows 10 yüklü masaüstü bilgisayarında.

Bu iki durumda da kod, herhangi bir hata vermeden, daha önceden belirlenen kriterlere
uygun çalıştı.

Windows harici bir makinede çalıştırmak istiyorsanız, kaynak kodu Windows
bağımlılıklarından ayırıp derlemeniz gerekiyor.

-------------------


4-KODU DERLEMEK:
------------------
Artık bilgisayarımızda kurulu olan GCC ile kodu kolayca derleyebiliriz.

Windows için:

>gcc 170201008-170201058.cpp –o 170201008-170201058.exe

Linux / Unix için:

>gcc 170201008-170201008.cpp -o 170201008-170201058


Derleme bittikten sonra kolayca programı çalıştırabilirsiniz.
------------------


5- PARAMETRELER
-------------------
////Kodun çalışması için başlangıçta herhangi bir parametre gerekmiyor.

Kodun çalışması için başlangıçta "devre.txt" ve "deger.txt" dosyalarının
kaynak kodun olduğu dizin/klasörde bulunması gerekmektedir.
------------------


6- PROGRAMIN KULLANIMI
-----------------------------
Lojik Devre Benzetimi, "devre.txt" dosyasından mantıksal bir devreyi 
ve "deger.txt" dosyasından giriş ve çıkışların değerlerini okuyarak, 
kullanıcının girdiği komutlara göre, kapı yayılım gecikmeleri de 
dikkate alınarak devreyi simule eder.

Program ilk çalıştırıldığında "devre.txt" içindeki satırları yorumlayıp
komut çalıştırabilir hale gelir.

Kullanıcının komut girmesi gerektiğini bildirmek amacı ile ekrana 
prompt(uyarı) karakteri '>' yazdırılır. Kullanıcı herhangi bir komut 
girdikten sonra gereken işlemler yapılınca -sonlandırma komutu olan 
C/c komutu girilmediği sürece- tekrar prompt(uyarı) karakteri '>' ekrana 
yazdırılır.

Komutlar büyük veya küüçük harf olabilir (not case-sensitive).

Devre yükleme (Y/y) ve ilklendirme(I/i) komutu girilmeden diğer komutlar
(H/h, L/l, S/s, G/g, G*/g*, K/k, C/c) aktifleşmemektedir. Öncelikle Y ve I
komutlarının girilmesi gereklidir.

Var olan komutlar dışında farklı bir komut girilmeye çalışıldığında hata
mesajı ekrana yazdırılır ve kullanıcıdan tekrar komut girilmesi beklenir.

Kullanıcının girdiği her komut, komut.txt dosyasına yazdırılır. Tüm yapılan
işlemler ise tarih/saat kaydedilerek log.txt dosyasına yazdırılır.

C/c komutu girildiğinde program sonlandırılır.

Komutlar 			   ve 		İcraları
Y <devre.txt> 					“devre.txt” dosyasından devreyi yükler
I 						“deger.txt” icindeki degerlerle devre ilklendirilir
H <giris ucundan biri/birileri> 		Ilgili uç/uçları Lojik-1 yapar
L <giris ucundan biri/birileri> 		Ilgili uç/uçları Lojik-0 yapar
S 						Devreyi simüle eder
G <giris/çıkıs ucundan biri/birileri> 		Ilgili uç/uçların seviyesini (0 veya 1) konsolda gösterir
G* 						Tüm uçların seviyesini (0 veya 1) konsolda gösterir
K <komut.txt> 					“komut.txt” dosyası içindeki komutları konsoldan oldugu gibi icra eder
C 						 Benzetimden çıkıs yapar
