import sqlite3
from sqlite3.dbapi2 import Date

from sys import argv

from sqlalchemy import Table, Column, Integer, ForeignKey, String, create_engine
from sqlalchemy.orm import relationship, sessionmaker
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.sql.expression import null


Base = declarative_base()

class Person(Base):
    __tablename__ = 'Person'
    id = Column(Integer, primary_key=True)
    name = Column(String)
    email = Column(String)
    borrowed = relationship('Book')

class Book(Base):
    __tablename__ = 'Book'
    id = Column(Integer, primary_key=True)
    borrower_id = Column(Integer, ForeignKey('Person.id'))
    author = Column(String)
    title = Column(String)
    publication_date = Column(String) 

engine = create_engine("sqlite:///biblioteka.db", echo=True)
Base.metadata.create_all(engine)

Session = sessionmaker(bind=engine)
session = Session()

class DBManagement:

    def add_book(title : str, author : str, publication_date : str):
        if len(session.query(Book).filter(Book.title == title and Book.author == author).all()) > 0:
            return
        b = Book(title=title, author=author, publication_date=publication_date)
        session.add(b)
        session.commit()

    def add_person(name : str, email : str):
        if len(session.query(Person).filter(Person.name == name and Person.email == email).all()) > 0:
            return
        p = Person(name=name, email=email) 
        session.add(p)
        session.commit()

    def lend(borrower_name, book_name):
        b : Book = session.query(Book).filter(Book.name == book_name)
        if b == null:
            raise "There is no such book in this database"
        p = session.query(Person).filter(Person.name == borrower_name)
        if p == null:
            raise "There is no such person in this database"
        if p.id > 0:
            raise "Book is already borrowed!"
        b.borrower_id = p.id
        session.commit()
          
    def give_back(book_name):
        b : Book = session.query(Book).filter(Book.name == book_name)
        if b == null:
            raise "There is no such book in this database"
        b.borrower_id = null
        session.commit()

    def people_all():
        k = session.query(Person).all()
        for person in k:
            print(f"[{person.id}] {person.name} with email: {person.email}")

    def books_all():
        for book in session.query(Book):
            print(f"[{book.id}] {book.title} written by {book.author}, publicated {book.publication_date}")

if __name__ == "__main__":
    argv = ["", "--dodaj", "osoba", "c,b"]
    polecenie = argv[1].replace("-", "")
    if polecenie == "wypisz":
        if argv[2] == "ksiazka":
            DBManagement.books_all()
        elif argv[2] == "osoba":
            DBManagement.people_all()
    if polecenie == "dodaj":
        if argv[2] == "ksiazka":
            p = argv[3].split(",")
            DBManagement.add_book(p[0], p[1], p[2])
        if argv[2] == "osoba":
            p = argv[3].split(",")
            DBManagement.add_person(p[0], p[1])
        else:
            raise "python3 zad1.py --dodaj ksiazka tytul,autor,data_publikacji | python3 zad1.py --dodaj osoba imie,email"
    try:
        if polecenie == "oddaj":
            DBManagement.give_back( argv[3] )
    except:
        raise "python3 zad1.py --oddaj tytul_oddawanej_ksiazki"

    try:
        if polecenie == "wypozycz":
            rel = argv[3].split()
            DBManagement.lend(rel[0], rel[1])
    except:
        raise "python3 zad1.py --wypozycz wypozyczajacy,tytul_ksiazki"
    session.close()

