#lang racket
(provide quicksort partition)

(define (length tab)
    (if (null? tab)
        0
        (+ 1.0 (length (cdr tab)))))

(define (partition tab)
  (define (sorter sval tabless tabgreater tabinp)
    (if (null? tabinp)
        (cons tabless tabgreater)
        (if (< (car tabinp) (car tab))
            (sorter sval
                    (insert tabless (car tabinp))
                    tabgreater
                    (cdr tabinp))
            (sorter sval
                    tabless
                    (insert tabgreater (car tabinp))
                    (cdr tabinp)))))
   (if (null? tab)
      tab
  (sorter (car tab) '() '() (cdr tab))))

(define (insert l x) 
    (if (null? l)
        (list x)
        (if (> x (car l))
            (cons (car l) (insert (cdr l) x))
            (cons x l))))

(define (quicksort tab)
  (define (pom pomtab)
    (define pompart (partition pomtab))
    (if (< (length pomtab) 2)
        pomtab
        (append (pom (car pompart))
                (list (car pomtab))
                (pom (cdr pompart)))))
  (pom tab))

;;o zapętleniu quicksorta rozmawiałem z Jakubem Szajnerem

(quicksort (list 4 6 7 1 2))
(quicksort (list 1 7 8 9 10))
(quicksort '())
(quicksort (list 1))
(quicksort (list -2 4 5 -3 3 2))


