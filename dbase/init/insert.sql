use mydb;

drop trigger if exists prodaja;


insert into KORISNIK values 
(0, 'admin1', 'Zeljko', 'Maksimovic', '2508985456980', 'Marsala Tita 34, Beograd', '0652033112', 'primer@math.com'),
(1, 'upravnik1', 'Angela', 'Forkos', '1007962825123', 'Japanska 2, Novi Beograd', '0623302611', 'forkos@apoteka.com'),
(2, 'apotekar1', 'Vesna', 'Todic', '1712980459871', 'Evropska 14, Zemun', '0673245316', 'todic@apoteka.com'),
(3, 'apotekar2', 'Milorad', 'Jovanovic', '2902988163452', 'Gandijeva 57, Novi Beograd', '0663345316', 'mile@apoteka.com');

insert into ADMINISTRATOR values (0, 'IT');
				
insert into UPRAVNIK values (1);

insert into APOTEKAR values 	(1, '2017-3-14', 'Farmaceut', NULL),
				(2, '2017-8-8', 'Tehnicar', NULL),
				(3, '2018-1-9', 'Farmaceut', NULL);

insert into DOBAVLJAC values 	(222, 'Dodofarma', '0112753144', 'dodo@farma.com', 'www.dodofarma.com'),
				(333, 'Cedral', '0112005942', 'cedral.farma@farma.com', 'www.cedral.com'),
				(444, 'Magic Rose', '0111203985', 'magic@farma.com', 'www.magic-rose.com');
				

insert into PROIZVOD values 	(1111, 222, 'Bronhocea', 'Cuvati na suvom i tamnom', 'Prasak za oralni rastvor'),
				(1112, 222, 'Ginko 40', NULL, 'Rastvor za poboljsanje cirkulacije i koncentracije'),
				(1113, 333, 'Vendoksin kapi 50ml', 'Cuvati na hladnom', 'Kapi za odrzavanje fizioliskog protoka krvi'),
				(1114, 333, 'Unkarija', NULL, 'Pilule za lecenje herpesa'),
				(1115, 333, 'Koenzim Q10', NULL, 'Kapsule za jacanje imuniteta i protiv holesterola'),
				(1116, 444, 'Gynkgobil kapsule', NULL, 'Prirodna neuro i kardio zastita'),
				(1117, NULL, 'Pavloviceva mast', 'Cuvati na tamnom, hladnom i suvom', 'Mast za kozu bebe');

insert into PREPARAT values	(1111, 492.50, '8011636672', 0),
				(1112, 212.43, '5803654717', 0),
				(1113, 1320.00, '9677597827',1),
				(1114, 1880.40, '8308123941',1),
				(1115, 1023.00, '3746525145', 0),
				(1116, 477.20, '0557683417', 0),
				(1117, 451.00, '8459943551', 0);

insert into GOTOV values	(1111, NULL),
				(1112, 'Gynkgobil kapsule'),
				(1113, NULL),
				(1114, NULL),
				(1115, NULL),
				(1116, 'Ginko 40');

insert into PRIPREMLJEN values 	(1117, '...');

insert into MAGACIN values	(1111, '2018-1-21', '2017-8-21', 5),
				(1111, '2018-5-21', '2017-11-21', 10),
				(1112, '2018-7-12', '2018-1-9', 37),
				(1113, '2018-8-13', '2018-3-3', 55),
				(1113, '2018-2-16', '2017-6-12', 3),
				(1115, '2018-7-3', '2018-5-3', 12),
				(1115, '2018-8-5', '2018-6-5', 5),
				(1115, '2018-6-25', '2017-4-25', 15),
				(1116, '2018-5-11', '2017-11-11', 52),
				(1117, '2019-2-13', '2018-2-13', 11),
				(1117, '2019-5-15', '2018-5-15', 22);

----------------------------------------------------------------------------------------------------------------------

--INSERT INTO RACUN VALUES
--INSERT INTO KUPOVINA VALUES
