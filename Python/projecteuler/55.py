def is_palindrome(number): #karmimy to stringiem rzecz jasna
    for i in range(int(len(number)/2)):
        if number[i] != number[-i-1]: #indeksując z dwóch stron schodzimy do środka liczby
            return False
    return True

def reverse(number): #karmimy stringiem
    newnum = []
    for i in range(len(number)):
        newnum.append(number[-i-1]) #na pierwszym miejscu nowej liczby bedzie ostatnia cyfra starej
    return str("".join(newnum)) #scalamy elementy z tablicy przechowującej cyfry nowej liczby (w porządanej kolejności) a później robimy z tego stringa i go zwracamy

def is_lynchrel(num): #inputujemy inta
    prevt = str(num)
    nextt = reverse(str(num))
    for _ in range(50): #a
        if is_palindrome(str(int(prevt) + int(nextt))) == True: #sprawdzamy liczba + jej odwrotnosc sa palindromem
            return False #to znaczy, ze liczba nie jest lynchrelem (bo znalezlismy palindrom)
        prevt = str(int(prevt) + int(nextt)) #nowym poprzednikiem staje sie suma starego poprzednika i jego reversea
        nextt = reverse(prevt) #a nowym nastepnikiem reverse nowego poprzednika
    return True #jesli w 50 obrotach nie udalo sie znalezc palindromu, to liczba jest lynchrelem

def lynchrel_numbers(nrange): #tu podajemy zakres liczby, do ktorej chcemy szukac
    counter = 0
    for i in range(0, nrange):
        if is_lynchrel(i) == True:
            counter += 1
    return counter

print(is_palindrome("12344321"))
print(is_palindrome("12345321"))
print(reverse("567"))
print(is_lynchrel(47))
print(is_lynchrel(196))
print(lynchrel_numbers(10000))
