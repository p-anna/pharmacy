-- MySQL Script generated by MySQL Workbench
-- Tue Dec 26 13:05:32 2017
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`KORISNIK`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`KORISNIK` (
  `id_korisnika` INT NOT NULL,
  `lozinka` VARCHAR(45) NOT NULL,
  `ime` VARCHAR(45) NOT NULL,
  `prezime` VARCHAR(45) NOT NULL,
  `jmbg` VARCHAR(45) NOT NULL,
  `adresa` VARCHAR(45) NOT NULL,
  `telefon` VARCHAR(45) NOT NULL,
  `e-mail` VARCHAR(45) NULL,
  PRIMARY KEY (`id_korisnika`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`APOTEKAR`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`APOTEKAR` (
  `id_korisnika` INT NOT NULL,
  `datum_zaposlenja` DATE NOT NULL,
  `strucna_sprema` VARCHAR(45) NOT NULL,
  `smena` SMALLINT(3) NULL,
  PRIMARY KEY (`id_korisnika`),
  CONSTRAINT `fk_APOTEKAR_KORISNIK`
    FOREIGN KEY (`id_korisnika`)
    REFERENCES `mydb`.`KORISNIK` (`id_korisnika`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`UPRAVNIK`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`UPRAVNIK` (
  `id_korisnika` INT NOT NULL,
  PRIMARY KEY (`id_korisnika`),
  CONSTRAINT `fk_UPRAVNIK_KORISNIK1`
    FOREIGN KEY (`id_korisnika`)
    REFERENCES `mydb`.`KORISNIK` (`id_korisnika`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`ADMINISTRATOR`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`ADMINISTRATOR` (
  `id_korisnika` INT NOT NULL,
  PRIMARY KEY (`id_korisnika`),
  CONSTRAINT `fk_ADMINISTRATOR_KORISNIK1`
    FOREIGN KEY (`id_korisnika`)
    REFERENCES `mydb`.`KORISNIK` (`id_korisnika`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`DOBAVLJAC`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`DOBAVLJAC` (
  `id_dobavljaca` INT NOT NULL,
  `naziv` VARCHAR(45) NOT NULL,
  `telefon` VARCHAR(45) NOT NULL,
  `e-mail` VARCHAR(45) NOT NULL,
  `url` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id_dobavljaca`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`PROIZVOD`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`PROIZVOD` (
  `id_proizvoda` INT NOT NULL,
  `id_dobavljaca` INT NULL,
  `naziv` VARCHAR(45) NOT NULL,
  `specijalni_uslovi` VARCHAR(200) NULL,
  `dodatna_informacija` VARCHAR(200) NULL,
  PRIMARY KEY (`id_proizvoda`),
  INDEX `fk_PROIZVOD_DOBAVLJAC1_idx` (`id_dobavljaca` ASC),
  CONSTRAINT `fk_PROIZVOD_DOBAVLJAC1`
    FOREIGN KEY (`id_dobavljaca`)
    REFERENCES `mydb`.`DOBAVLJAC` (`id_dobavljaca`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`PREPARAT`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`PREPARAT` (
  `id_proizvoda` INT NOT NULL,
  `cena` DOUBLE NOT NULL,
  `barkod` VARCHAR(45) NOT NULL,
  `na_recept` TINYINT NOT NULL,
  PRIMARY KEY (`id_proizvoda`),
  CONSTRAINT `fk_PREPARAT_PROIZVOD1`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PROIZVOD` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`GOTOV`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`GOTOV` (
  `id_proizvoda` INT NOT NULL,
  `alternativni_preparat` VARCHAR(45) NULL,
  PRIMARY KEY (`id_proizvoda`),
  CONSTRAINT `fk_GOTOV_PREPARAT1`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PREPARAT` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`PRIPREMLJEN`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`PRIPREMLJEN` (
  `id_proizvoda` INT NOT NULL,
  PRIMARY KEY (`id_proizvoda`),
  CONSTRAINT `fk_PRIPREMLJEN_PREPARAT1`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PREPARAT` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`SIROVINA`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`SIROVINA` (
  `id_proizvoda` INT NOT NULL,
  PRIMARY KEY (`id_proizvoda`),
  INDEX `fk_SIROVINA_PROIZVOD1_idx` (`id_proizvoda` ASC),
  CONSTRAINT `fk_SIROVINA_PROIZVOD1`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PROIZVOD` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`MAGACIN`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`MAGACIN` (
  `id_proizvoda` INT NOT NULL,
  `rok_trajanja` DATE NOT NULL,
  `datum_nabavke` DATE NOT NULL,
  `kolicina` SMALLINT NOT NULL,
  PRIMARY KEY (`id_proizvoda`, `rok_trajanja`, `datum_nabavke`),
  CONSTRAINT `fk_SANJE_MAGACINA_APOTEKE_PROIZVOD1`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PROIZVOD` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`STANJE_MAGACINA_APOTEKE_copy1`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`STANJE_MAGACINA_APOTEKE_copy1` (
  `id_proizvoda` INT NOT NULL,
  PRIMARY KEY (`id_proizvoda`),
  CONSTRAINT `fk_SANJE_MAGACINA_APOTEKE_PROIZVOD10`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PROIZVOD` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`NARUDZBENICA`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`NARUDZBENICA` (
  `id_narudzbenice` INT NOT NULL,
  `id_korisnika` INT NOT NULL,
  `id_dobavljaca` INT NOT NULL,
  `datum_narudzbine` DATE NOT NULL,
  `status` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id_narudzbenice`),
  INDEX `fk_NARUDZBENICA_UPRAVNIK1_idx` (`id_korisnika` ASC),
  INDEX `fk_NARUDZBENICA_DOBAVLJAC1_idx` (`id_dobavljaca` ASC),
  CONSTRAINT `fk_NARUDZBENICA_UPRAVNIK1`
    FOREIGN KEY (`id_korisnika`)
    REFERENCES `mydb`.`UPRAVNIK` (`id_korisnika`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_NARUDZBENICA_DOBAVLJAC1`
    FOREIGN KEY (`id_dobavljaca`)
    REFERENCES `mydb`.`DOBAVLJAC` (`id_dobavljaca`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`OTPREMNICA`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`OTPREMNICA` (
  `id_otpremnice` INT NOT NULL,
  `id_korisnika` INT NOT NULL,
  `id_dobavljaca` INT NOT NULL,
  `id_narudzbenice` INT NOT NULL,
  `datum_otpreme` DATE NOT NULL,
  `ukupan_iznos` DOUBLE NOT NULL,
  PRIMARY KEY (`id_otpremnice`),
  INDEX `fk_OTPREMNICA_APOTEKAR1_idx` (`id_korisnika` ASC),
  INDEX `fk_OTPREMNICA_DOBAVLJAC1_idx` (`id_dobavljaca` ASC),
  INDEX `fk_OTPREMNICA_NARUDZBENICA1_idx` (`id_narudzbenice` ASC),
  CONSTRAINT `fk_OTPREMNICA_APOTEKAR1`
    FOREIGN KEY (`id_korisnika`)
    REFERENCES `mydb`.`APOTEKAR` (`id_korisnika`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_OTPREMNICA_DOBAVLJAC1`
    FOREIGN KEY (`id_dobavljaca`)
    REFERENCES `mydb`.`DOBAVLJAC` (`id_dobavljaca`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_OTPREMNICA_NARUDZBENICA1`
    FOREIGN KEY (`id_narudzbenice`)
    REFERENCES `mydb`.`NARUDZBENICA` (`id_narudzbenice`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`OTPREMA`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`OTPREMA` (
  `id_otpremnice` INT NOT NULL,
  `id_proizvoda` INT NOT NULL,
  `kolicina` SMALLINT NOT NULL,
  `rok_trajanja` DATE NOT NULL,
  PRIMARY KEY (`id_otpremnice`, `id_proizvoda`),
  INDEX `fk_OTPREMNICA_has_PROIZVOD_PROIZVOD1_idx` (`id_proizvoda` ASC),
  INDEX `fk_OTPREMNICA_has_PROIZVOD_OTPREMNICA1_idx` (`id_otpremnice` ASC),
  CONSTRAINT `fk_OTPREMNICA_has_PROIZVOD_OTPREMNICA1`
    FOREIGN KEY (`id_otpremnice`)
    REFERENCES `mydb`.`OTPREMNICA` (`id_otpremnice`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_OTPREMNICA_has_PROIZVOD_PROIZVOD1`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PROIZVOD` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`RACUN`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`RACUN` (
  `id_racuna` INT NOT NULL,
  `id_korisnika` INT NOT NULL,
  `iznos` DOUBLE NOT NULL,
  `datum_izdavanja` DATE NOT NULL,
  `uslovi_placanja` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id_racuna`),
  INDEX `fk_RACUN_APOTEKAR1_idx` (`id_korisnika` ASC),
  CONSTRAINT `fk_RACUN_APOTEKAR1`
    FOREIGN KEY (`id_korisnika`)
    REFERENCES `mydb`.`APOTEKAR` (`id_korisnika`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`PACIJENT`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`PACIJENT` (
  `id_pacijenta` INT NOT NULL,
  `ime` VARCHAR(45) NOT NULL,
  `prezime` VARCHAR(45) NOT NULL,
  `jmbg` VARCHAR(45) NOT NULL,
  `lbo` INT NOT NULL,
  `broj_kartice` INT NOT NULL,
  `filijala` VARCHAR(45) NOT NULL,
  `ime_lekara` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`id_pacijenta`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`KUPOVINA`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`KUPOVINA` (
  `id_racuna` INT NOT NULL,
  `id_proizvoda` INT NOT NULL,
  `id_pacijenta` INT NULL,
  `kolicina` SMALLINT NOT NULL,
  `recept` VARCHAR(200) NULL,
  PRIMARY KEY (`id_racuna`, `id_proizvoda`),
  INDEX `fk_RACUN_has_PREPARAT_PREPARAT1_idx` (`id_proizvoda` ASC),
  INDEX `fk_RACUN_has_PREPARAT_RACUN1_idx` (`id_racuna` ASC),
  INDEX `fk_KUPOVINA_PACIJENT1_idx` (`id_pacijenta` ASC),
  CONSTRAINT `fk_RACUN_has_PREPARAT_RACUN1`
    FOREIGN KEY (`id_racuna`)
    REFERENCES `mydb`.`RACUN` (`id_racuna`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_RACUN_has_PREPARAT_PREPARAT1`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PREPARAT` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_KUPOVINA_PACIJENT1`
    FOREIGN KEY (`id_pacijenta`)
    REFERENCES `mydb`.`PACIJENT` (`id_pacijenta`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`PRIPREMANJE`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`PRIPREMANJE` (
  `id_korisnika` INT NOT NULL,
  `id_proizvoda` INT NOT NULL,
  `kolicina` SMALLINT NOT NULL,
  `datum_proizvodnje` DATE NOT NULL,
  `rok_trajanja` DATE NULL,
  PRIMARY KEY (`id_korisnika`, `id_proizvoda`),
  INDEX `fk_APOTEKAR_has_PRIPREMLJEN_PRIPREMLJEN1_idx` (`id_proizvoda` ASC),
  INDEX `fk_APOTEKAR_has_PRIPREMLJEN_APOTEKAR1_idx` (`id_korisnika` ASC),
  CONSTRAINT `fk_APOTEKAR_has_PRIPREMLJEN_APOTEKAR1`
    FOREIGN KEY (`id_korisnika`)
    REFERENCES `mydb`.`APOTEKAR` (`id_korisnika`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_APOTEKAR_has_PRIPREMLJEN_PRIPREMLJEN1`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PRIPREMLJEN` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`POVRATNICA`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`POVRATNICA` (
  `id_povratnice` INT NOT NULL,
  `id_otpremnice` INT NOT NULL,
  `id_korisnika` INT NOT NULL,
  PRIMARY KEY (`id_povratnice`),
  INDEX `fk_POVRATNICA_APOTEKAR1_idx` (`id_korisnika` ASC),
  INDEX `fk_POVRATNICA_OTPREMNICA1_idx` (`id_otpremnice` ASC),
  CONSTRAINT `fk_POVRATNICA_APOTEKAR1`
    FOREIGN KEY (`id_korisnika`)
    REFERENCES `mydb`.`APOTEKAR` (`id_korisnika`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_POVRATNICA_OTPREMNICA1`
    FOREIGN KEY (`id_otpremnice`)
    REFERENCES `mydb`.`OTPREMNICA` (`id_otpremnice`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`POVRACAJ`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`POVRACAJ` (
  `id_povratnice` INT NOT NULL,
  `id_proizvoda` INT NOT NULL,
  `kolicina` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id_povratnice`, `id_proizvoda`),
  INDEX `fk_POVRATNICA_has_PROIZVOD_PROIZVOD1_idx` (`id_proizvoda` ASC),
  INDEX `fk_POVRATNICA_has_PROIZVOD_POVRATNICA1_idx` (`id_povratnice` ASC),
  CONSTRAINT `fk_POVRATNICA_has_PROIZVOD_POVRATNICA1`
    FOREIGN KEY (`id_povratnice`)
    REFERENCES `mydb`.`POVRATNICA` (`id_povratnice`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_POVRATNICA_has_PROIZVOD_PROIZVOD1`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PROIZVOD` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`NARUDZBINA`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`NARUDZBINA` (
  `id_narudzbenice` INT NOT NULL,
  `id_proizvoda` INT NOT NULL,
  `kolicina` SMALLINT NOT NULL,
  PRIMARY KEY (`id_narudzbenice`, `id_proizvoda`),
  INDEX `fk_NARUDZBENICA_has_PROIZVOD_PROIZVOD1_idx` (`id_proizvoda` ASC),
  INDEX `fk_NARUDZBENICA_has_PROIZVOD_NARUDZBENICA1_idx` (`id_narudzbenice` ASC),
  CONSTRAINT `fk_NARUDZBENICA_has_PROIZVOD_NARUDZBENICA1`
    FOREIGN KEY (`id_narudzbenice`)
    REFERENCES `mydb`.`NARUDZBENICA` (`id_narudzbenice`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_NARUDZBENICA_has_PROIZVOD_PROIZVOD1`
    FOREIGN KEY (`id_proizvoda`)
    REFERENCES `mydb`.`PROIZVOD` (`id_proizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`ODLAGANJE`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`ODLAGANJE` (
  `id_korisnika` INT NOT NULL,
  `id_proizvoda` INT NOT NULL,
  `rok_trajanja` DATE NOT NULL,
  `datum_nabavke` DATE NOT NULL,
  `datum_odlaganja` DATE NOT NULL,
  `kolicina` SMALLINT NOT NULL,
  PRIMARY KEY (`id_korisnika`, `id_proizvoda`, `rok_trajanja`, `datum_nabavke`),
  INDEX `fk_APOTEKAR_has_MAGACIN_MAGACIN1_idx` (`id_proizvoda` ASC, `rok_trajanja` ASC, `datum_nabavke` ASC),
  INDEX `fk_APOTEKAR_has_MAGACIN_APOTEKAR1_idx` (`id_korisnika` ASC),
  CONSTRAINT `fk_APOTEKAR_has_MAGACIN_APOTEKAR1`
    FOREIGN KEY (`id_korisnika`)
    REFERENCES `mydb`.`APOTEKAR` (`id_korisnika`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_APOTEKAR_has_MAGACIN_MAGACIN1`
    FOREIGN KEY (`id_proizvoda` , `rok_trajanja` , `datum_nabavke`)
    REFERENCES `mydb`.`MAGACIN` (`id_proizvoda` , `rok_trajanja` , `datum_nabavke`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
