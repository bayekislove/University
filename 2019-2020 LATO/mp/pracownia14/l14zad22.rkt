#lang racket
(require racklog)

(provide solve)
;;Zadanie rozwiązane wspólnie z Kacprem Gawdzińskim i Jakubem Szajnerem <---!!!

;; transpozycja tablicy zakodowanej jako lista list
(define (transpose xss)
  (cond [(null? xss) xss]
        ((null? (car xss)) (transpose (cdr xss)))
        [else (cons (map car xss)
                    (transpose (map cdr xss)))]))

;; procedura pomocnicza
;; tworzy listę n-elementową zawierającą wyniki n-krotnego
;; wywołania procedury f
(define (repeat-fn n f)
  (if (eq? 0 n) null
      (cons (f) (repeat-fn (- n 1) f))))

;; tworzy tablicę n na m elementów, zawierającą świeże
;; zmienne logiczne
(define (make-rect n m)
  (repeat-fn m (lambda () (repeat-fn n _))))

;; predykat binarny
;; (%row-ok xs ys) oznacza, że xs opisuje wiersz (lub kolumnę) ys

(define %row-ok
  (%rel (x xaug xs ys)
  [(null null)]
  [(xs (cons '_ ys))
   (%row-ok xs ys)]
  [((cons xaug xs) (cons '* (cons '* ys)))
   (%> xaug 1)
   (%is x (- xaug 1))
   (%row-ok (cons x xs) (cons '* ys))]
  [((cons xaug xs) (cons '* (cons '_ ys)))
   (%= xaug 1)
   (%row-ok xs (cons '_ ys))]
  [('(1) '(*))]))

;; TODO: napisz potrzebne ci pomocnicze predykaty
(define %alright
  (%rel (xs x row x1 y ys)
        [(null null)]
        [((cons x xs) (cons y ys))
         (%row-ok y x)
         (%alright xs ys)]))

;; funkcja rozwiązująca zagadkę
(define (solve rows cols)
  (define board (make-rect (length cols) (length rows)))
  (define tboard (transpose board))
  (define ret (%which (xss) (%and (%= xss board)
                                  (%alright board rows)
                                  (%alright tboard cols))))
  (and ret (cdar ret)))
;; testy
(equal? (solve '((2) (1) (1)) '((1 1) (2)))
        '((* *)
          (_ *)
         (* _)))

(equal? (solve '((2) (2 1) (1 1) (2)) '((2) (2 1) (1 1) (2)))
        '((_ * * _)
          (* * _ *)
          (* _ _ *)
          (_ * * _)))

(equal? (solve '((4) (6) (2 2) (2 2) (6) (4) (2) (2) (2))
               '((9) (9) (2 2) (2 2) (4) (4)))
        '((* * * * _ _)
          (* * * * * *)
          (* * _ _ * *)
          (* * _ _ * *)
          (* * * * * *)
          (* * * * _ _)
          (* * _ _ _ _)
          (* * _ _ _ _)
          (* * _ _ _ _)))

;; TODO: możesz dodać własne testy

