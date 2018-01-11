Ovaj dokument sadrzi opis postupka podesavanja baze podataka. Za uspesnu 
izgradnju i upotrebu baze potrebno je instalirati serverski softver 
Apache i relacioni sistem za upravljanje bazom podataka MySQL (MariaDB). 
U nastavku je dat opis instalacije na operativnom sistemu Linux 
distibucije Manjaro (Arch), za instalaciju na drugim sistemima pogledati 
internet ili probati zamenu komande "sudo pacman -S <naziv_paketa>" sa 
odgovarajucom komandom na posmatranom operativnom sistemu, npr. sa 
"apt-get install <naziv_paketa>" na sistemu debian/ubuntu. Pozeljno je 
uraditi i azuriranje ili unapredjivanje sistema pre instalacije bilo 
kakvih paketa.

Apache:
	1. sudo pacman -S apache (instalacija servera Apache)
	2. sudo nano /etc/httpd/conf/httpd.conf (iskomenatarisati liniju: 
		LoadModule unique_id_module modules/mod_unique_id.so)
	3. sudo systemctl enable httpd
	   sudo systemctl restart httpd (za pokretanje servera)
	4. sudo systemctl status httpd  (za proveru servera)


MySQL:
	1. sudo pacman -S mysql
	2. mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
	3. sudo systemctl enable mysqld
	   sudo systemctl start mysqld  (za pokretanje RSUBP)
	4. sudo systemctl status mysqld (za proveru RSUBP)


Vazna Napomena:
	Ako se negde navodi stavljanje lozinke za pristup za 
	MySQL(MariaDB) ili izvrsavanje komande mysql_secure_installation 
	onda zanemariti taj deo jer u suprotnom skriptovi init.sh, 
	reinit.sh i deinit.sh nece raditi i onda bi kreiranje baze moralo 
	rucno da se uradi.


Nakon instalacije Apache-a i MySQL-a (MariaDB) pokrenuti kreiranje baze 
izvrsavanjem skripta init.sh.
