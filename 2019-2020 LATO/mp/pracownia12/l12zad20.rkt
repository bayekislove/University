#lang racket
(provide bag-stack@ bag-fifo@)
(require racket/contract)
(require "graph.rkt")


;; struktura danych - stos
(define-unit bag-stack@
  (import)
  (export bag^)

  (define (bag? inp)
    (and (list? inp)
         (eq? (length inp) 2)
         (eq? (car inp) 'bag-stack)
         (list? (cdr inp))))

  (define (bag-empty? inp)
    (null? (cadr inp)))

  (define (bag-stack-cons inp)
    (list 'bag-stack inp))

  (define (bag-stack-list inp)
    (cdr inp))

  (define empty-bag
    (bag-stack-cons '()))

  (define (bag-insert inp el)
    (bag-stack-cons (cons el inp)))

  (define (bag-peek inp)
    (car (bag-stack-list inp)))

  (define (bag-remove inp)
    (bag-stack-cons (cdr (bag-stack-list inp))))
)

;; struktura danych - kolejka FIFO
(define-unit bag-fifo@
  (import)
  (export bag^)

  (define (bag? inp)
    (and (list? inp)
         (list? (second inp))
         (list? (third inp)))
         (= (length inp) 3)
         (eq? (first inp) 'bag-fifo))

  (define empty-bag (list 'bag-fifo '() '()))

  (define (bag-empty? bagger)
    (and (null? (bag-fifo-out bagger))
         (null? (bag-fifo-inp bagger))))

  (define (bag-fifo-cons inp out)
    (list 'bag-fifo inp out))

  (define (bag-fifo-out xs) ;;(cons out inp)
    (second xs))

  (define (bag-fifo-inp xs)
    (third xs))

  ;;Kolejne elementy odkładamy na poczatek listy wejściowej (cons el xs) i na koniec listy wyjściowej (cons xs el)
  (define (bag-insert bagger el)
    (bag-fifo-cons (bag-fifo-out bagger)
                   (cons el (bag-fifo-inp bagger))))

  (define (bag-peek bagger)
    (if (null? (bag-fifo-out bagger))
        (car (reverse (bag-fifo-inp bagger)))
        (car (bag-fifo-out bagger))))

  (define (bag-remove bagger)
    (if (null? (bag-fifo-out bagger))
        (bag-fifo-cons (cdr (reverse (bag-fifo-inp bagger))) '())
        (bag-fifo-cons (bag-fifo-inp bagger) (cdr (bag-fifo-out bagger)))))
  
)

;; otwarcie komponentów stosu i kolejki

(define-values/invoke-unit bag-stack@
  (import)
  (export (prefix stack: bag^)))

(define-values/invoke-unit bag-fifo@
  (import)
  (export (prefix fifo: bag^)))

;; testy w Quickchecku
(require quickcheck)

;; testy kolejek i stosów
(define-unit bag-tests@
  (import bag^)
  (export)
  
  ;; test przykładowy: jeśli do pustej struktury dodamy element
  ;; i od razu go usuniemy, wynikowa struktura jest pusta
  (quickcheck
   (property ([s arbitrary-symbol])
             (bag-empty? (bag-remove (bag-insert empty-bag s)))))
  ;; TODO: napisz inne własności do sprawdzenia!
  (quickcheck
   (property ([s arbitrary-symbol])
            (eq? s (bag-peek (bag-insert (bag-insert empty-bag s) s)))))
)

;; uruchomienie testów dla obu struktur danych

(invoke-unit bag-tests@ (import (prefix stack: bag^)))
(invoke-unit bag-tests@ (import (prefix fifo: bag^)))

;; TODO: napisz też testy własności, które zachodzą tylko dla jednej
;; z dwóch zaimplementowanych struktur danych

;; otwarcie komponentu grafu
(define-values/invoke-unit/infer simple-graph@)

;; otwarcie komponentów przeszukiwania 
;; w głąb i wszerz
(define-values/invoke-unit graph-search@
  (import graph^ (prefix stack: bag^))
  (export (prefix dfs: graph-search^)))

(define-values/invoke-unit graph-search@
  (import graph^ (prefix fifo: bag^))
  (export (prefix bfs: graph-search^)))

;; graf testowy
(define test-graph
  (graph
   (list 1 2 3 4)
   (list (edge 1 3)
         (edge 1 2)
         (edge 2 4))))
;; TODO: napisz inne testowe grafy

;; uruchomienie przeszukiwania na przykładowym grafie
(bfs:search test-graph 1)
(dfs:search test-graph 1)
;; TODO: uruchom przeszukiwanie na swoich przykładowych grafach
