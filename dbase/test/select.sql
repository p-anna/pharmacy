use mydb;

select *
from MAGACIN;

select id_proizvoda, sum(kolicina) 
from MAGACIN
group by id_proizvoda;

select R.id_racuna, id_proizvoda, kolicina, iznos, datum_izdavanja, id_korisnika
from RACUN R join KUPOVINA K on K.id_racuna = R.id_racuna
order by datum_izdavanja;

select * from RACUN;
