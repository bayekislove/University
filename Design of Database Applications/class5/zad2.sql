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
	[Powód wizyty]			VARCHAR(200))

INSERT INTO Wizyty VALUES
(1, 'Jan Kot',    'ul. Dolna 6, 44-444 Bór', '2029-02-01 12:30, pok. 12', '300 z³', 'Marek Z¹bek', 'Dentystyczny: za³o¿enie protezy w (...)'),
(2, 'Maria Mysz', 'ul. Górna 9, 55-555 Las', '2030-01-04 11:45, pok. 7',  '300 z³', 'Ewa Blacka',  'Dermatologiczny: oglêdziny znamiona (...)')
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
	[Pokój wizyty]			VARCHAR(50),
	[Kwota]					VARCHAR(50),
	[Imie Lekarza]			VARCHAR(50),
	[Nazwisko Lekarza]		VARCHAR(50),
	[Typ wizyty]			VARCHAR(20),
	[Powód wizyty]			VARCHAR(100))


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
	[Powód wizyty]			VARCHAR(100))

-- 3NF - kolumny niebêd¹ce kluczem g³ównym mog¹ zale¿eæ tylko od klucza g³ównego

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
	[Pokój]					VARCHAR(50)
	)

CREATE TABLE Wizyty(
	[ID]					INT PRIMARY KEY,
	[ID_Pacjenta]			INT FOREIGN KEY REFERENCES Pacjenci(ID),
	[Data]					VARCHAR(50),
	[ID_Lekarza]			INT FOREIGN KEY REFERENCES Lekarze(ID),
	[Typ wizyty]			VARCHAR(20),
	[Powód wizyty]			VARCHAR(100))