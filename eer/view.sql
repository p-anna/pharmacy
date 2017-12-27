--POGLED KOJI IZDVAJA KOLICINU PRODATIH PROIZVODA PO RADNIKU I PROIZVODU
CREATE VIEW RADNIK_STATISTIKA AS
SELECT K.id_korisnika, K.ime, K.prezime, P.naziv, sum(K.kolicina) AS kolicina
FROM KORISNIK K	JOIN RACUN R ON K.id_korisnika=R.id_korisnika
		JOIN KUPOVINA KU ON KU.id_racuna=R.id_racuna
		JOIN PROIZVOD P ON P.id_proizvoda=KU.id_proizoda
GROUP BY K.id_korisnika, K.ime, K.prezime, P.naziv;


--POGLED KOJI IZDVAJA KOLICINU PRODATIH PROIZVODA PO GODINI, MESECU I PROIZVODU
CREATE VIEW MESECNA_STATISTIKA AS
SELECT year(R.datum_izdavanja) AS godina, month_name(R.datum_izdavanja) AS mesec, P.id_proizvoda, P.naziv, sum(K.kolicina) AS kolicina 
FROM PREPARAT P	LEFT OUTER JOIN KUPOVINA K ON K.id_proizvoda=P.ID_proizvoda
		JOIN RACUN R ON R.id_racuna=K.id_racuna
GROUP BY godina, mesec, P.id_proizvoda, P.naziv;
