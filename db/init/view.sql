use mydb;

--POGLED KOJI IZDVAJA KOLICINU PRODATIH PROIZVODA PO RADNIKU I PROIZVODU
drop view if exists radnik_statistika;

create view radnik_statistika as
select K.id_korisnika, K.ime, K.prezime, P.naziv, sum(KU.kolicina) as kolicina
from KORISNIK K	join RACUN R on K.id_korisnika=R.id_korisnika
		join KUPOVINA KU on KU.id_racuna=R.id_racuna
		join PROIZVOD P on P.id_proizvoda=KU.id_proizvoda
group by K.id_korisnika, K.ime, K.prezime, P.naziv;


--POGLED KOJI IZDVAJA KOLICINU PRODATIH PROIZVODA PO GODINI, MESECU I PROIZVODU
drop view if exists mesecna_statistika;

create view mesecna_statistika as
select year(R.datum_izdavanja) as godina, monthname(R.datum_izdavanja) as mesec, P.id_proizvoda, P.naziv, sum(K.kolicina) as 
kolicina 
from PROIZVOD P join PREPARAT Q	on Q.id_proizvoda=P.id_proizvoda 
		left outer join KUPOVINA K on K.id_proizvoda=Q.id_proizvoda
		join RACUN R ON R.id_racuna=K.id_racuna
group by godina, mesec, P.id_proizvoda, P.naziv;
