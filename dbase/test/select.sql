use mydb;

select *
from MAGACIN;

select id_proizvoda, sum(kolicina) 
from MAGACIN
group by id_proizvoda;

select R.id_racuna, id_korisnika, datum_izdavanja, iznos, id_proizvoda, kolicina
from RACUN R join KUPOVINA K on K.id_racuna = R.id_racuna
order by datum_izdavanja;
