use mydb;

select *
from MAGACIN;

select id_proizvoda, sum(kolicina) 
from MAGACIN
group by id_proizvoda;

select * from KUPOVINA;
