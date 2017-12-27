USE mydb;

DELIMITER $

DROP TRIGGER IF EXISTS PRODAJA$

CREATE TRIGGER PRODAJA
AFTER INSERT ON KUPOVNIA
FOR EACH ROW
BEGIN
	IF( new.kolicina > ( SELECT sum(M0.kolicina) FROM MAGACIN M0 WHERE M0.id_proizvoda = new.id_proizvoda) THEN 
		SIGNAL sqlstate='45000' SET message_text='NEMA DOVOLJNO TRAZENOG PROIZVODA U MAGACINU';
	ELSE 
		UPDATE MAGACIN M1 SET M1.kolicina = new.kolicina 
		WHERE M1.id_proizvoda = new.id_proizvoda AND M1.rok_trajanja IN(SELECT min(M2.rok_trajanja)
										FROM MAGACIN M2
										WHERE M2.id_proizvoda = M1.id_proizvoda
										GROUP BY M2.id_proizvoda);
	END IF;
END$
