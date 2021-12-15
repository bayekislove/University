from re import A
import tkinter as tk
from tkinter.constants import CENTER, END, LEFT, RIDGE, RIGHT, TOP, Y
import tkinter.ttk as ttk

from sqlalchemy import Table, Column, Integer, ForeignKey, String, create_engine
from sqlalchemy.orm import relationship, sessionmaker
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.sql.expression import column, null, text

import sqlite3
from sqlite3.dbapi2 import Date

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

    def add_person(name : str, email : str):
        if len(session.query(Person).filter(Person.name == name and Person.email == email).all()) > 0:
            return
        p = Person(name=name, email=email) 
        session.add(p)
        session.commit()
        return p.id

    def people_all():
        people = session.query(Person).all()
        people.reverse()
        return people


class ViewManagement:

    def show_people():
        for person in DBManagement.people_all():
            peopleView.insert(parent='', index=0, text=str(person.id), values=(person.name, person.email))

    def new_item_selected(e):
        (name, email) = peopleView.item(peopleView.focus())['values']
        IDLabel.config(text=f"ID: {peopleView.item(peopleView.focus())['text']}")
        NameEdit.delete(0, END)
        NameEdit.insert(0, name)
        EmailEdit.delete(0, END)
        EmailEdit.insert(0, email)

    def change_handler():
        to_change = peopleView.focus()
        if to_change != "":
            person = session.query(Person).filter(Person.id == IDLabel.cget("text").split(" ")[1]).all()[0]
            person.name = NameEdit.get()
            person.email = EmailEdit.get()
            session.commit()
            peopleView.delete(to_change)
            peopleView.insert(parent="", index=0, text=str(person.id), values=(person.name, person.email))

    def add_handler():
        if NameEdit.get() != "" and EmailEdit.get() != "":
            id = DBManagement.add_person(NameEdit.get(), EmailEdit.get())
            peopleView.insert(parent="", index=0, text=str(id), values=(NameEdit.get(), EmailEdit.get()))
        

if __name__ == "__main__":
    win = tk.Tk()
    win.title("Zarządzanie bazą danych")
    win.geometry("600x350+10+20")

    label = tk.Label(win, text="Lista osób z bazy danych")
    label.pack()

    peopleView = ttk.Treeview(win)

    peopleView["columns"] = ('#0', '#1', '#2')
    peopleView.column("#0", anchor=CENTER)
    peopleView.column("#1", anchor=CENTER)
    peopleView.column("#2", anchor=CENTER)

    peopleView.heading("#0", text="ID")
    peopleView.heading("#1", text="Imię")
    peopleView.heading("#2", text="E-Mail")
    peopleView.pack()
    peopleView.bind("<<TreeviewSelect>>", ViewManagement.new_item_selected)
    ViewManagement.show_people()

    label = tk.Label(win, text="Informacje o aktualnie wybranej osobie")
    label.pack(fill=Y)

    IDLabel = tk.Label(win, text="ID ")
    IDLabel.pack(side=LEFT)

    NameLabel = tk.Label(win, text="Name")
    NameLabel.pack(side=LEFT)
    NameEdit = tk.Entry(win)
    NameEdit.pack(side=LEFT)

    EmailLabel = tk.Label(win, text="Email")
    EmailLabel.pack(side=LEFT)
    EmailEdit = tk.Entry(win)
    EmailEdit.pack(side=LEFT)

    ChangeButton = tk.Button(win, text ="Zmień wybrany rekord", command = ViewManagement.change_handler)
    ChangeButton.pack()

    AddButton = tk.Button(win, text ="Dodaj nowy rekord", command = ViewManagement.add_handler)
    AddButton.pack()

    win.mainloop()
