USE Test

DROP TABLE IF EXISTS Wizyty
GO

CREATE TABLE Wizyty(
	[ID]					INT PRIMARY KEY,
	[Pacjent]				VARCHAR(50),
	[Adres Pacjenta]		VARCHAR(50),
	[Data i miejsce wizyty] VARCHAR(500),
	[Kwota]					VARCHAR(50),
	[Lekarz]				VARCHAR(50),
	[Pow�d wizyty]			VARCHAR(200))

INSERT INTO Wizyty VALUES
(1, 'Jan Kot',    'ul. Dolna 6, 44-444 B�r', '2029-02-01 12:30, pok. 12', '300 z�', 'Marek Z�bek', 'Dentystyczny: za�o�enie protezy w (...)'),
(2, 'Maria Mysz', 'ul. G�rna 9, 55-555 Las', '2030-01-04 11:45, pok. 7',  '300 z�', 'Ewa Blacka',  'Dermatologiczny: ogl�dziny znamiona (...)')
GO

--1NF - atomowe wiersze

CREATE TABLE Wizyty(
	[ID]					INT PRIMARY KEY,
	[Imie]					VARCHAR(50),
	[Nazwisko]				VARCHAR(50),
	[Adres]					VARCHAR(100),
	[Kod pocztowy]			VARCHAR(10),
	[Miasto]				VARCHAR(100),
	[Data]					VARCHAR(50),
	[Pok�j wizyty]			VARCHAR(50),
	[Kwota]					VARCHAR(50),
	[Imie Lekarza]			VARCHAR(50),
	[Nazwisko Lekarza]		VARCHAR(50),
	[Typ wizyty]			VARCHAR(20),
	[Pow�d wizyty]			VARCHAR(100))


--2NF - jeden obiekt to tabela
CREATE TABLE Pacjenci(
	[ID]					INT PRIMARY KEY,
	[Imie]					VARCHAR(50),
	[Nazwisko]				VARCHAR(50),
	[Adres]					VARCHAR(50),
	[Kod pocztowy]			VARCHAR(10),
	[Miasto]				VARCHAR(30))

CREATE TABLE Lekarze(
	[ID]					INT PRIMARY KEY,
	[Imie]					VARCHAR(50),
	[Nazwisko]				VARCHAR(50))

CREATE TABLE Wizyty(
	[ID]					INT PRIMARY KEY,
	[ID_Pacjenta]			INT FOREIGN KEY REFERENCES Pacjenci(ID),
	[Data]					DATE,
	[Miejsce wizyty]		INT,
	[Kwota]					MONEY,
	[ID_Lekarza]			INT FOREIGN KEY REFERENCES Lekarze(ID),
	[Typ wizyty]			VARCHAR(20),
	[Pow�d wizyty]			VARCHAR(100))

-- 3NF - kolumny nieb�d�ce kluczem g��wnym mog� zale�e� tylko od klucza g��wnego

CREATE TABLE Pacjenci(
	[ID]					INT PRIMARY KEY,
	[Imie]					VARCHAR(50),
	[Nazwisko]				VARCHAR(50),
	[Adres]					VARCHAR(50),
	[Kod pocztowy]			VARCHAR(10),
	[Miasto]				VARCHAR(30))

CREATE TABLE Lekarze(
	[ID]					INT PRIMARY KEY,
	[Imie]					VARCHAR(50),
	[Nazwisko]				VARCHAR(50),
	[Kwota]					VARCHAR(50),
	[Pok�j]					VARCHAR(50)
	)

CREATE TABLE Wizyty(
	[ID]					INT PRIMARY KEY,
	[ID_Pacjenta]			INT FOREIGN KEY REFERENCES Pacjenci(ID),
	[Data]					VARCHAR(50),
	[ID_Lekarza]			INT FOREIGN KEY REFERENCES Lekarze(ID),
	[Typ wizyty]			VARCHAR(20),
	[Pow�d wizyty]			VARCHAR(100))