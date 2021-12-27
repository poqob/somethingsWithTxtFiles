# somethingsWithTxtFiles
first school project
SomethingWithTxtFiles.exe

Programın amacı: İçerisine müşteri bilgisi , ürün bilgisi , sipariş bilgisi gibi bilgiler almak ve bunların kontrolünü dosya yönetim sistemi ile sağlamak. Kullanıcıları kayıtlı bilgiler üzerinde yetkili ve sağlıklı hareket edebilir kılmak.

Programın tasarımı: Proje şartlarını göz önünde bulundurduğum zaman programın iki farklı kullanım şeklinin olması gerektiğine karar verdim. Firma ve Müşteri olmak üzere iki farklı giriş bulunmaktadır. Her giriş kendi sınıfları içerisinde özelleştirilmiş methodlara sahiptir. Aynı zamanda bu iki girişin buluştuğu ortak bir payda vardır . Siparişler , müşteriler sipariş sınıfına erişip sipariş verebilirler. Verilen siparişler müşteri adına açılan bir dosyada depolanır . Sipariş alındıktan hemen sonra firmaya bildirilmek üzere genel bir sipariş dosyası oluşturulur içerisine her müşterinin siparişlerinin müşteri numarası ile birlikte toplam tutarları ve sipariş tarihleri girilir. Firma isterse bu son dosya üzerinde değişiklik yapabilir . Müşterilerin siparişlerini silebilir. Müşteri de aynı şekilde hem firmaya giden sipariş bilgilerini silebilir hem de kendi müşteri numarası ile oluşturulmuş dosyasında siparişleri arasında silme işlemi yapabilir . Müşterinin yaptığı her sipariş işleminin akabinde firmaya sipariş listesi ve ücreti güncel olarak tekrar tekrar bildirilir.
Tasarımımda sisteme sınırsız sayıda ürün ve müşteri eklenebilmektedir. Program kapandığında bilgileri unutmaz tekrar tekrar çalıştırıldığında kaldığı yerden devam eder çünkü yapılan her işlem ardından dosya sistemine kayıt söz konusudur.

Dosya tasarımım: Projemde, belirli veri bloklarını dosyalara yazarken bazı anahtar karakterleri okuma ve yazma sırasında yardımcı olsun diye kullandım. Örnek olarak ürünler dosyasının içindeki iki ürüne ait veri bloğunu göstermek gerekirse.

&
*Product ID : p01#
*Product name : p01cellPhone#
*Producter : p01samsung#
*Estimated deliver time : p01t4#
*production date : p01d12.12.12#
*Price : p01$55#
*Special price : p01$50#
*Kdv : 18#
*In Stock : p01N89999#
&
*Product ID : p02#
*Product name : p02cellPhone#
*Producter : p02apple#
*Estimated deliver time : p02t5#
*production date : p02d12.12.12#
*Price : p02$59.90#
*Special price : p02$55#
*Kdv : 18#
*In Stock : p02N25000#





Uygulamadaki her dosya oluşturduğum bu formata sahiptir. Formatı açıklamam gerekirse.

    ‘&’ sembolü bir ürün bloğunun başlangıcını ifade eder. 
           Aynı zamanda bir ürünün başlangıcı bir öncekinin bitişidir.

    ‘*’ sembolü bir veri satırının başladığını ifade eder.

    ‘#’ sembolü bir veri satırının bittiğini ifade eder.

Yukarıdaki veri bloklarında kdv hariç neredeyse her satırda görülen ürün kodu , ardından gelen miktar bilgilerinin ,tarihin ,aynı olabilecek üretici isimlerinin karışıklığını önlüyor ve bilgiyi eşsiz kılıyor. Her satır barındırdığı ürün kimliği numarası ile eşsizlik kazanıyor. Örneğin p01 numaralı ürün ile p02 numaralı ürünün stok adetleri aynı olsun . Eğer program içinden firma arayüzünde bu iki stok adedi için bir değişiklik yapmak istersek algoritmam şu şekilde :

********************************************************************************
ürün düzenleme fonksiyonuna gidilsin-> ürün kodu girilsin->stok adedi üzerinde değişiklik seçilsin->eski stok adedi girilsin->yeni stok adedi girilsin(arayüzde işlem tamam)->

(programın arkaplanında olanlar)
ürünler dosyası program içerisine geçici bir stringe aktarılsın->string içerisinde ürün kodu+eski stok adedi bulunsun->bulunan ürün bilgisi satırı , başlangıç adlı değişkene kayıt edilsin->başlangıç konumundan sonraki ilk ‘#’ işareti bulunsun ve son isimli değişkene kayıt edilsin->replace komutu çalıştırılsın -replace(başlangıç,yeni stok adedi,son-başlangıç);->(eski stok adedi yenisiyle değiştirildi) string uygun formatta dosyaya out modunda yazılsın. 
********************************************************************************



Eğer ürünler dosyamda kaç ürün var öğrenmek istersem algoritmam:
********************************************************************************
ürünler dosyasını içe aktar (geçici bir string)->stringi bir ‘&’ sayacına okut->sayacın sonucunu döndür.
********************************************************************************

tüm bunların yanı sıra dosyamın okunabilir olması için her değişiklik işleminin ardından dosyaya yazdırma işlemini belli bir formatta yaptım ki veri takibi konsol dışından da kolayca yapılabilsin.
Ayrıca geliştirme aşamasında formatlamanın birçok karışıklığı önlediğini söyleyebilirim.

Oluşturmuş olduğum anahtar karakterli dosya düzeni sayesinde hedef bilgi satırını kolayca bulabilmekte ve üzerinde gerekli değişiklikleri methodlarım vasıtasıyla yapabilmekteyim.












Programın anatomisi: Programım içerisinde üç farklı sınıf bulundurmaktadır. Bu üç sınıfı karmaşıklığı önlemek adına üç farklı sayfada topladım. Bu sınıflar/sayfalar ve görevleri.

company.h    içerisinde CompanyPage sınıfı ve metotları bulunmaktadır.
customer.h    içerisinde CustomerPage sınıfı ve metotları bulunmaktadır.
orders.h         içerisinde Orders sınıfı ve metotları bulunmaktadır
somethingWithTxtFiles.cpp    main cpp dosyam .

-company.h-

içerisinde firma girişine özel fonksiyonlar bulunmaktadır bunlar.
void authorization(),void companyMainScr(),void productScr(),void orderScr(),void customerScr(),

Doğrulama fonksiyonu: firma sayfasına giriş yaparken çalışır kullanıcı adı ve şifre ister.

Firma ana sayfası: Doğrulama ekranından hemen sonra gelir ve ürünler , siparişler ,müşteriler 		            sayfalarına erişimi sağlar.

Ürünler sayfası: Firma için ürün operasyonlarını görüntüleyen ve yöneten ürünler fonksiyonuna 	        erişimi sağlar.

Siparişler sayfası: Firmanın verilen siparişleri fiyatları ve siparişi verenin müşteri kodu ve sipariş 	           dosyası ile birlikte görmesini sağlar.

Müşteri sayfası: Firmanın müşteriler dosyasına müdahale edip müşteri eklemesini , müşteri 	        	        silmesini ve müşteri bilgilerini düzenlemesini sağlar.

Ürünlere yönelik fonksiyonlar:
void addProduct(),void writeProduct(),void searchInProduct(bool style),void listing(),
void editing(bool style),void deleteProduct(bool style)

Ürün ekleme: firmadan/konsoldan ürün hakkında bilgileri toplar.

Ürün yazdırma: toplanan verileri bir şablona döker ve bu şablonu products.txt dosyasına yazar.

 Ürünlerde arama: products.txt dosyası içerisinde ürün kodu ile arama yapma olanağı sağlar.
	           Gerekli bilgileri ekrana yazdırır.

Listeleme : products.txt dosyasının içerisindeki tüm ürünleri konsola yazdırır.

Düzenleme :products.txt dosyası üzerinde ürün blokları ile oynama , düzenleme olanağı sunar.

Ürün silme: products.txt dosyasında bulunan hedef ürün bloğunun silinmesinde görev alır.
products.txt örneği:
&
*Product ID : p01#
*Product name : p01cellPhone#
*Producter : p01samsung#
*Estimated deliver time : p01t4#
*production date : p01d12.12.12#
*Price : p01$55#
*Special price : p01$50#
*Kdv : 18#
*In Stock : p01N89999#
--customer.h--

içerisinde müşteri giriş ekranına ait fonksiyonlar bulunmaktadır.

void entranceScr(),bool authorization(bool style),void cMainScr(),void cRegister()

Giriş ekranı : giriş yap , kayıt ol , programdan çık seçenekleri mevcuttur.

Doğrulama : eğer giriş yap seçilmişse doğrulama için müşteri kodu istenmektedir.

Müşteri ana ekranı : eğer giriş başarı ile gerçekleştirilmişse bu sayfaya yönlendirilir.
	              Bu sayfada çeşitli müşteri fonksiyonları bulunmaktadır.

Müşteri kayıt : gerekli müşteri bilgilerini konsoldan toplar ve yeni müşteriyi oluşturur.

Müşteri dosya operasyonları.

void cWrite(),void cEdit(bool style),void cSearch(bool style),void cList(),void cRemove(bool style)

Müşteri yazdırma : cRegister’dan gelen bilgileri customers.txt’ye yazdırır.

Müşteir düzenleme : customers.txt dosyasında hedef müşteriye ait bilgileri değiştirmemize yarar.

Müşteri arama : customers.txt dosyasında müşteri numarası ile arama yapmamızı sağlar.

Müşteri listeleme : customers.txt dosyasının içindeki tüm müşterileri konsola yazdırır.

Müşteri silme : customers.txt dosyasındaki hedef müşteriye ait veri bloğunu siler.

void remote(short whichFuncIllRun)

Uzaktan kontrol: Firmanın , bazı müşteri metotlarına erişmesini sağlamaktadır.

customers.txt örneği :
&
*Customer ID : C09#
*Customer name : C09turkcell#
*Customer phone number : C09N2236545861#
*Person in charge : C09vesbi#
*Customer type : C09Tcommon#
*Adress : C09Wistanbul#
&
*Customer ID : C088#
*Customer name : C088corpa#
*Customer phone number : C088N02252445897#
*Person in charge : C088ali#
*Customer type : C088Tcommon#
*Adress : C088Wizmit#

void remote2(short choosem)
Uzaktan kontrol 2: Firmanın bazı sipariş fonksiyonlarına erişimini sağlar.

--orders.h--

içerisinde siparişlere yönelik fonksiyonlar bulunmaktadır.

Müşteri yanı:

void seeProducts(),void searchProducts(),

Ürünleri gör : ürün sipariş etme ekranında firmanın sipariş edilebilecek ürünlerini listeler.

Ürünleri ara : Bu bir arka plan fonksiyonudur. Sipariş etmek istediğimiz ürünün ürünler 	  	    dosyasından bilgilerini çeker ve bir string şablonuna kaydeder.


void addOrder(string Id),void searchInOrders(string id),void deleteOrder(string id, bool style),
void listOrders(string id)

Sipariş ekleme : Müşteri numarası ile müşteri adına açılan bir dosyaya müşterinin siparişini 		     doğrulama aşaması ardından ekler. Sipariş string şablonunda durmaktadır.
	     SearchProducts() fonksiyonundan gelmiştir.

Siparişlerde arama : Müşteri numarası ile oluşturulan ve siparişlerin içerisine kaydedildiği dosya 	              içerisinde müşterinin ürün numarası ile arama yapmasını sağlar.

Sipariş silme : Müşterinin siparişini verdiği ürünü, kendi sipariş listesinden silmesine yarıyor.

Siparişleri listeleme : Müşteri numarası ile açılmış olan siparişler dosyasının içeriğini ekrana çizer.

Firma yanı :

bool customerType(string id),double pricing(string id),

Müşteri tipi : Bu bir arkaplan fonksiyonudur, müşterinin özel mi yoksa sıradan mı olduğunu tespit 	   eder. True->özel , false->sıradan

Ücretlendirme : Müşteri türünün tespitinin ardından çalışır ve müşterinin siparişini ona göre 		        ücretlendirir. Özel müşteri özel fiyat , sıradan müşteri sıradan fiyat.
	        Müşteri numaralı dosyayı okur ve içerisindeki ürünlerin hedef fiyatlarını okuyup 	        bir toplam çıkartır ve döndürür.

void writeOrders(string id),void minusProductStockNum()

Sipariş yaz : Her değişikliğin ardından çalışan bu fonksiyon müşteri siparişlerini firmaya 	    	  gönderilmek üzere bir başlık altında toplar içerisinde dinamik olarak sipariş tarihi ve 	  sipariş totali bulunmaktadır.

Ürün stok numarası eksiltme : Her ürün satın alma işleminin ardından çalışır ve ilgili ürünün, ürün 	  kodu sayesinde products.txt dosyasında stok numarası bilgisinin bulunduğu satıra 	  müdahale eder ve bir azaltır.






string searchInOrdersTxt(string id),void removeOrders(string id)

Siparişler dosyası içerisinde arama : Bu fonksiyon orders.txt dosyasından silinmek istenen hedef 	total sipariş bilgi bloğunun tespitini sağlar. Onun başlangıç ‘&’ bitiş ‘&’ karakterlerinin 	dosyadaki konumunu tutar ver string olarak döndürür.

Siparişleri sil : Silinmek istenen hedef veri bloğunu silmek üzere searchInOrdersTxt() fonksiyonuna 	erişir. Hedef veri bloğunun konumunu string olarak elde eder ve dosyada ilgili 	konumlar arasını yerleşik olarak gelen erase() fonksiyonu yardımı ile siler. Silme 	işleminin ardından değişiklikler dosyaya orders.txt ye kaydedilir.


void remote(short whichFuncIllRun, string id),void formating(string fileNameTxt)

Uzaktan kontrol : müşteriler sınıfından siparişler sınıfına erişim sağlandığı zaman tek public 	fonksiyon olan remote() yukarıda bahsi geçen ilgili bazı metotlara erişim sağlamaktadır.

Formatlama : Her düzenleme işleminden sonra dosyalara tekrar tekrar yazdırılan veriler 	okunabilirlik kazanmaları adına formating() fonksiyonundan geçerler ve txt dosyalarına 	belli bir düzen ile yazdırılırlar.

void remote2(short whichFuncIllRun),void deleteAllOrders()

Uzaktan kontrol 2: Firmanın bazı sipariş fonksiyonlarına erişimini sağlar.

Tüm siparişleri silmek : Firma orders.txt dosyasındaki tüm siparişleri silebilir.

void listMainOrders(),void searchInOrderstxt()

Genel sipariş listeleme : Firma orders.txt dosyasındaki siparişlerin tümünü ekranda okuyabilir.

Siparişler içerisinde arama : Firma orders.txt dosyasında müşteri numarası ile arama yapabilir.



müşteriNumarası.txt örneği : --C09.txt
&
*Product ID : p01#
*Product name : p01cellPhone#
*Producter : p01samsung#
*Estimated deliver time : p01t4#
*production date : p01d12.12.12#
*Price : p01$55#
*Special price : p01$50#
*Kdv : 0#
*In Stock : p01N90000#
&
*Product ID : p02#
*Product name : p02cellPhone#
*Producter : p02apple#
*Estimated deliver time : p02t5#
*production date : p02d12.12.12#
*Price : p02$59.90#
*Special price : p02$55#
*Kdv : 0# ................

orders.txt örneği : 
&
*Orderer ID : C09#
*Order date : C09TDec 23 2021#
*Order total : C09$248#
*Order file : C09.txt#
*Order owner : tech company#

Programın kullanımı : Program çalıştırıldığında iki farklı giriş seçeneği görülecektir.


1.company	--> firma anasayfasına yönlendirilmek üzere giriş doğrulama sayfasına gideriz.

2.customer --> müşteri anasayfasına yönlendirilmek üzere müşteri giriş doğrulamaya gideriz.

3.exit --> programdan çıkışı sağlar.


-1.company için :

    seçilir seçilmez bizden firma girişi için kullanıcı adı ve şifre girmemizi ister.
Giriş başarıyla sağlandıktan sonra firma anasayfası önümüze gelir. Burada :

1.products	-->firma için ürün fonksiyonlarını barındırır.
2.orders		-->firma için siparişler fonksiyonlarını barındırır.
3.customers	-->firma için müşterileri fonksiyonlarını tanıtır.
4.go back	-->bir önceki sayfaya geri dönüş sağlar.

-1.products için : 
		1. add product	-->products.txt dosyasına yeni ürün ekle.
 	2. search in products	--> products.txt dosyasında ürün kodu ile arama yapma.
 	3. see products	--> products.txt dosyasındaki tüm ürünler listeleme.
 	4. edit product	--> products.txt dosyasındaki ürün bilgilerini düzenleme.
 	5. delete product	--> products.txt dosyasından ürün silme.
 	6. go back to main menu --> Firma ana menüsüne geri dönüşü sağlar.
 -2.orders için : 
	1.see taken orders	--> orders.txt dosyasındaki alınan siparişleri gösterir .
 	2.search in taken orders-->orders.txt dosyası içerisinde arama yapma imkanı sunar.
 	3.delete an order	--> orders.txt dosyasından sipariş silmeye yarar.
 	4.delete all olders	-->orders.txt dosyasının tamamını silmeye yarar.
      -3.customers için :
	        1.add customer	--> customers.txt dosyasına yeni müşteri ekler.
        	2.searching for customers--> customers.txt dosyasında arama yapma imkanı sunar.
        	3.edit customers	-->customers.txt dosyasında müşteriler üstünde değişiklik yapar.
        	4.removing customers	-->customers.txt dosyasından müşteri siler.
        	5.see all customers	-->customers.txt dosyasındaki tüm müşterileri konsola çizdirir.
        	6.go back		-->bir önceki sayfaya dönme imkanı sunar.
	



-2.customer için : 

seçildiğinde müşteri işlemlerine erişmek üzere bir giriş ya da kayıt ol sayfasına yönlendiriliriz.

1-LogIn	-->eğer müşteri customers.txt dosyasında kayıtlı ise müşteri numarasıyla giriş yapabilir
2-Register --> yeni müşteri kaydı oluşturulur.
3-Exit Program --> programdan çıkar.

 -1.LogIn için : 
	-->müşteri numarası ile giriş sağlanır ve müşteri numarası girilen müşterinin 	  	     fonksiyonlarına erişim sağlanır.
	1. give orders -->müşterinin sipariş vermesini sağlar 
 	2. search in orders -->müşteri siparişler içerisinde arama işlemi yapma imkanı sunar.
 	3. delete orders -->müşteri siparişleri içerisinde silme operasyonu yapma imkanı sunar.
 	4. see given orders -->müşteri siparişlerini konsola yazdırır.
 	5. my data -->müşterinin bilgilerini görmesini sağlar.
	6. delete my orders -->müşterinin siparişlerinin tümünü silmesi imkanı sunar.
	7. exit program -->programdan çıkış.
	     
-2.Register için : 
	-->yen müşteri kaydı için konsoldan bilgi toplar.
	
-3.Exit Program : 
	-->programdan çıkışı sağlar.


				SomethingWithTxtFiles.exe
