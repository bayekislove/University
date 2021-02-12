from turtle import begin_fill, end_fill, fillcolor, ht, fd, rt, lt, up, down, speed, tracer, goto
from random import randint, random
cyfry = {}

speed('fastest')
tracer(0, 1)
ht()

cyfry[0] = """
 ###
#   #
#   #
#   #
 ###
"""

cyfry[1] = """
  #
 ##
  #
  #
 ###
"""

cyfry[4] = """
 #
#
#####
  #
  #
"""


cyfry[2] = """
 ###
#   #
  ##
 #
#####
"""

cyfry[5] = """
#####
#
####
    #
####
"""

cyfry[8] = """
 ###
#   #
 ###
#   #
 ###
"""

cyfry[6] = """
 ###
#
####
#   #
 ###
"""

cyfry[9] = """
 ###
#   #
 ####
    #
 ###
"""

cyfry[3] = """
####
    #
 ###
    #
####
"""

cyfry[7] = """
#####
   #
 ###
 #
#
"""

def num_tab(k):
   zapis = []
   pojedyncze_elementy = list(cyfry[k])
   i = 1
   while(i<len(pojedyncze_elementy)):
      temp_zapis = []
      if pojedyncze_elementy[i] != '\n':
         while(str(pojedyncze_elementy[i]) != '\n'):
            temp_zapis.append(pojedyncze_elementy[i])
            i += 1
         zapis.append(temp_zapis)
      if pojedyncze_elementy[i] == '\n':
         i += 1
   return zapis

def drukuj_liczbe(k):
   a = num_tab(k)
   fillcolor(random(),random(),random())
   begin_fill()
   for i in range(len(a)):
      for j in range(len(a[i])):
         if a[i][j] == "#":
            drukuj_kwadracik()
         elif a[i][j] == " ":
               up()
               fd(10)
               down()
      rt(180)
      up()
      fd(10 * len(a[i]))
      lt(90)
      fd(10)
      lt(90)
      down()
   end_fill()


def drukuj_kwadracik():
   for i in range(4):
      fd(10)
      lt(90)
   up()
   fd(10)
   down()
drukuj_liczbe(3)


def drukuj_liczby(p, b):
   for i in range(p+1):
      x = randint(-b, b)
      y = randint(-b, b)
      liczba = randint(0,9)
      drukuj_liczbe(liczba)
      up()
      goto(x,y)
      down()

drukuj_liczby(30, 170)
input()
