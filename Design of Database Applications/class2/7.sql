CREATE TABLE Test1 (
    ID int NOT NULL IDENTITY(1000, 10),
    Letter char(1),
    PRIMARY KEY (ID)
);

INSERT INTO dbo.Test (letter) VALUES ('b');