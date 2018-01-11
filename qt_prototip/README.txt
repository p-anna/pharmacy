Za uspesno pokretanje aplikacije pogledati README.txt u ../dbase/ direktorijumu. Takodje je 
potrebno promeniti putanju u kodu od odgovarajuceg direktorijuma izgradnje aplikacije do 
select.sql skripta koji se nalazi u ovom (izvornom) direktorijumu. Putanju u liniji koda 
c.setQuerry("../Pharmacy/select.sql") promeniti na tri mesta:

	1. Konstruktor Connection u connection.cpp
	2. Funkcija buttonPrint_clicked u mainwindow.cpp
	3. Funkcija lineEditSearch_changed u mainwindow.cpp
