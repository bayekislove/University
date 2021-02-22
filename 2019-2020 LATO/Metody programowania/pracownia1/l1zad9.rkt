#lang racket

(provide cube-root)

(define (abs a) ;;zwraca wartosc bezwzglenda
  (if (< a 0)
      (- a)
      a))

(define (square num) ;; procedura podnosząca liczbę do kwadratu
  (* num num))

(define (cube num) ;; procedura podnosząca liczbę do szcześcianu
  (* num num num))

(define (cube-root x)
  (define (approximation y)
    (/ (+ (/ x (square y)) (* 2 y)) 3))
  (define (okay p)
    (< (abs(- x (cube p)))
       0.0001))
  (define (search y)
    (if (okay y)
        y
        (search (approximation y))))
  (if (> x 0) (search 1.0) (search -1.0))) ;; jesli liczba jest dodatnia to przyblizamy do 1ki, jesli ujemna to do -1
;; w drugiej wysłanej próbie dodałem warunek, który wyklucza zapętlenie się przy wywołaniu cube roota dla -2 (za radą Oskara Kowalczyka)
;; ponadto dodałem komentarze
(cube-root 1)
(cube-root -2)
(cube-root 0.125)
(cube-root 343)
(cube-root -8)
(cube-root -125)
(cube-root 0.000)
(cube-root -64)
(cube (cube-root 7))