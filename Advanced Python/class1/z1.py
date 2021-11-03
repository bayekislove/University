from decimal import *
from typing import List

def vat_faktura(lista):
    return sum(lista) * 0.23

def vat_faktura_decimal(lista):
    return sum(lista) * Decimal('0.23')

def vat_paragon(lista):
    return sum(map(lambda x : 0.23*x, lista))

def vat_paragon_decimal(lista):
    return sum(map(lambda x : Decimal('0.23') * x, lista))

zakupy = [0.2, 0.5, 4.59, 6]
print(vat_faktura(zakupy) == vat_paragon(zakupy))

zakupyDecimal = [ Decimal(i) for i in zakupy ]
print(vat_faktura_decimal(zakupyDecimal) == vat_paragon_decimal(zakupyDecimal))

# Nie daje? W tym przypadku nie daje