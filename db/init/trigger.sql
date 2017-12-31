use mydb;

delimiter $

drop trigger if exists prodaja$

create trigger prodaja
after insert on KUPOVINA
for each row
begin
	declare k int;
	set k = new.kolicina;
	if (new.kolicina > ( 	select sum(M0.kolicina)
				from MAGACIN M0
				where M0.id_proizvoda = new.id_proizvoda
					and M0.rok_upotrebe > current_date) 
	) then
		signal sqlstate '45000' set message_text='Nema dovoljno trazenog proizvoda';
	else
		while k > 0 do
		begin
			declare l int;
			declare u date;
			declare n date;
			set l = (	select min(M1.kolicina) 
					from MAGACIN M1 
					where M1.id_proizvoda=new.id_proizvoda 
						and not exists (select * from MAGACIN M2 
								where M2.id_proizvoda=M1.id_proizvoda 
									and (	M2.rok_upotrebe < M1.rok_upotrebe or
										M2.datum_nabavke < M1.datum_nabavke))
				);
			set u = (
					select min(M1.rok_upotrebe) 
					from MAGACIN M1 
					where M1.id_proizvoda=new.id_proizvoda
						and M1.rok_upotrebe > current_date
				);
			set n = (
					select min(M1.datum_nabavke) 
					from MAGACIN M1 
					where M1.id_proizvoda=new.id_proizvoda
						and M1.rok_upotrebe = u
				);
			if k >= l then
				delete from MAGACIN
				where id_proizvoda=new.id_proizvoda
					and rok_upotrebe=u and datum_nabavke=n;
			else
				update MAGACIN SET kolicina = kolicina-k
				where id_proizvoda=new.id_proizvoda
					and rok_upotrebe=u and datum_nabavke=n;
			end if;
			set k = k-l;
		end;
		end while;

	end if;
end$

