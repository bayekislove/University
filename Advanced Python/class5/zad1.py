from typing import Dict


class Wyrazenie:

    def __init__(self, left, right, operator, operatorSign) -> None:
        self.left = left
        self.right = right
        self.operator = operator
        self.operatorSign = operatorSign

    def oblicz(self, zmienne):
        return self.operator(self.left.oblicz(zmienne), self.right.oblicz(zmienne))

    def __str__(self) -> str:
        return f"({str(self.left)} {str(self.operatorSign)} {str(self.right)})"

    def __add__(self, right):
        return Dodaj(self, right)

    def __mult__(self, right):
        return Razy(self, right)

    def countVariables(self):
        right = self.right.countVariables() if self.right != None else []     
        return right + self.left.countVariables()

class Dodaj(Wyrazenie):

    def __init__(self, left, right) -> None:
        super().__init__(left, right, lambda x, y: x + y, "+")

class Razy(Wyrazenie):

    def __init__(self, left, right) -> None:
        super().__init__(left, right, lambda x, y: x * y, "*")

class Zmienna(Wyrazenie):

    def __init__(self, left) -> None:
        super().__init__(left, None, None, "")

    def oblicz(self, zmienne):
        if self.left in zmienne:
            return zmienne[self.left]
        else:
            raise UnresolvedVariable

    def __str__(self) -> str:
        return str(self.left)

    def countVariables(self):
        return [self.left]

class Stala(Wyrazenie):

    def __init__(self, left) -> None:
        super().__init__(left, None, None, "")

    def oblicz(self, zmienne):
        return self.left

    def __str__(self) -> str:
        return str(self.left)

    def countVariables(self):
        return []

class Pochodna(Wyrazenie):

    # Lewa strona wywołania to funkcja, prawa to punkt w którym chcemy policzyć pochodną
    def __init__(self, left, right) -> None:
        super().__init__(left, right, None, "")

    def oblicz(self, zmienne):
        vars = set(self.left.countVariables())
        if len(vars) != 1:
            raise WrongNumberOfVariables
        x = self.right.oblicz(zmienne)
        fx = self.left.oblicz({list(vars)[0] : x})
        fxh = self.left.oblicz({list(vars)[0] : x + 0.000000001})
        return (fxh - fx) / 0.000000001

    # (funkcja)'(miejsce do policzenia pochodnej)
    def __str__(self) -> str:
        return f"({str(self.left)})'({str(self.right)})"

class UnresolvedVariable(Exception):
    pass

class WrongNumberOfVariables(Exception):
    pass

if __name__ == "__main__":
    k = Razy(Dodaj(Zmienna("x"), Stala(2)), Zmienna("y"))
    print(k)
    print(k.oblicz({"x" : 3, "y" : 2}))
    print(Pochodna(Razy(Zmienna("x"), Zmienna("x")), Stala(4)))
    print(Pochodna(Razy(Zmienna("x"), Zmienna("x")), Stala(4)).oblicz({}))
