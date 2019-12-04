# Avl ağacı ve stack veri yapısını bağlantılı liste yardımıyla uygulama örneği

Birisi avl ağacı ve diğeri ise yığın ( her iki veri yapısı da bağlantılı liste kullanığındadır) iki soyut veri yapısı ile temel işlemleri yapan uygulamadır.

  - AVL ağacının her bir düğümünde öğrencinin; numarası, adı, soyadı ve bölümü bilgileri var ve index öğrenci **soyadına** göre ayarlı.
  - Yığının her bir düğümünde öğrencinin; numarası, adı, soyadı ve bölümü bilgileri var ve index öğrenci **numarasına** göre ayarlı.

# Tanım

  - Avl ağacında *Veritabanı Yönetimi Sistemleri* dersinin sınıf listesi var.
  - Yığında ise *Veri Yapıları ve Algoritmalar* dersinin sınıf listesi var.
 
## İşlevleri

1) Her iki dersi de birden fazla kez alan öğrencileri listeler
2) **Sadece** Veritabanı Yönetim Sistemleri dersini alan öğrencileri listeler
3) Her iki dersi de A ve B grubu olarak ikiye ayırır:
 i) Veritabanı Yönetim Sistemleri dersini alan öğrenciler numaralarına göre gruplara ayrılır. A grubunda numarası tek sayı olan öğrenciler ve B grubunda ise numarası çift olan öğrenciler vardır.
ii) Veri Yapıları ve Algoritmalar dersini alan öğrenciler soyadlarına göre gruplara ayrılır. A grubunda adı [A-K] aralığındaki harflerle başlayan öğrenciler ve B grubunda ise adı [L-Z] aralığındaki harflerle başlayan öğrenciler vardır.
4) Her iki dersi de alan ve başka bölüm öğrencileri olan öğrencileri listeler. (Derslerde yandal ve çift anadal ile ders alan farklı bölüm öğrencileri vardır)
### NOT:
> Yapılan işlemler neticesinde Veri Yapıları ve Algoritmalar ile Veritabanı Yönetim Sistemleri dersleri esas sınıf listelerinde değişiklik olmamaktadır

### Kullanılan Sıralama Algoritmaları

Örnek amaçlı tanımlanan ve kullanılan sıralama algoritmaları ile kullanım amaçları aşağıdaki tabloda mevcuttur.

| Algoritma | Açıklama | Durum |
| ------ | ------ | ------ |
| Radiks Sıralama | Her iki dersi de alan öğrencileri soyadlarına göre sıralamak | Yok |
| Seçmeli Sıralama | Sadece Veritabanı Yönetim Sistemleri dersini alan öğrencileri adlarına göre sıralamak | Hazır |
| Hızlı Sıralama | Veri Yapıları ve Algoritmalar dersini alanları numaralarına göre sıralamak | Yok |

### Dil:
* [C++] 

### Kurulum

[Visual Studio](https://visualstudio.microsoft.com/) 2019 c++ çalıştıracak şekilde gerekli kütüphane ayarları yapılı şekilde kurulu olması yeterli. Sln dosyası ile açıp direk çalıştırılabilir.

### Yapılacaklar

 - Sıralama algoritmaları düzenlenecek

### Döküman
 - Akış diyagramı hazırlanacak
 - Karmaşıklığı analiz edilecek
 - Çalışan program ekran çıktıları hazırlanacak

Lisans
----

MIT
