#lang racket
(require "props.rkt")
(provide falsifable-cnf?)
(define (literal? v)
        (and (list? v)
             (= 3 (length v))
             (eq? (car v) 'lit)))

(define (literal v)
    (if (neg? v)
         (list 'lit 'neg (neg-subf v))
         (list 'lit 'pos v)))

(define (neg for)
  (list 'neg for))

(define (disj a b)
  (list 'disj a b))

(define (conj a b)
  (list 'conj a b))

(define (disj-left f)
  (second f))

(define (disj-rght f)
  (third f))

(define (conj-left f)
  (second f))

(define (conj-rght f)
  (third f))

(define (neg-subf f)
  (second f))

(define (var? t)
   (symbol? t))

(define (neg? t)
  (and (list? t)
       (= 2 (length t))
       (eq? 'neg (car t))))

(define (conj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'conj ( car t ))))

(define (disj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'disj (car t))))

(define (convert-to-nnf f)
    (define (ctn f flag)
        (cond [(var? f)   (if flag 
                              (literal (neg f))
                              (literal f))]  
              [(neg? f)    (ctn (neg-subf f) (not flag))]
              [(conj? f)   (if flag ;; (A \/ B)
                                (disj (ctn (conj-left f) flag) (ctn (conj-rght f) flag))
                                (conj (ctn (conj-left f) flag) (ctn (conj-rght f) flag)))]
              [(disj? f)   (if flag 
                                (conj (ctn (disj-left f) flag) (ctn (disj-rght f) flag))
                                (disj (ctn (disj-left f) flag) (ctn (disj-rght f) flag)))]
                              ))
    (ctn f #f))

(define (convert-to-cnf f)
  (define cnf list)
  (define (cnf? f)
    (define (forall l p?)
      (if (null? l)
          true
          (and (p? (car l)) (forall (cdr l) p?))))
    (and (list? f)
         (forall f (lambda (l) (disj? l)))))
  (define (ctc-merge xss yss acc)
    (if (null? yss)
        acc
        (ctc-merge xss (cdr yss) 
                   (append (map (lambda (xs) (append (car yss) xs)) xss) acc))))
        
  (cond 
    [(literal? f)   (cnf (list f))]
    [(conj? f)      (let 
                        ([l (to-cnf (conj-left f))]
                         [r (convert-to-cnf (conj-rght f))])
                      (append  l r))]
    [(disj? f)      (let 
                        ([l (convert-to-cnf (disj-left f))]
                         [r (convert-to-cnf (disj-rght f))])
                      (ctc-merge l r '()))]))

;;
(define (falsifable-cnf? formula)
  (define (get-evaluation listp changed)
    (if (empty? listp)
        changed
        (if (eq? (second (car listp)) 'pos)
            (get-evaluation (cdr listp)
                            (append changed
                                    (list (neg (third (car listp))))))
            (get-evaluation (cdr listp)     
                            (append changed (list (third (car listp))))))))
  
  (define (check-if-opposite lista var ev) ;;sprawdza czy znajduje sie zmienna o innym wartosciowaniu niz podane
    (if (empty? lista) ;;jesli sie nie znajduje przeciwne wartosciowanie dla podanego literalu, to zwraca falsz 
        #f
        (if (and (eq? (third (car lista))
                      var)
                 (not (eq? (second (car lista))
                           ev)))
            #t ;;a jesli znajduje, to prawda
            (check-if-opposite (cdr lista) var ev))))
  (define (iterator lista)
    (cond [(empty? lista) #t] ;;jesli przeszlismy przez cala liste i nie znaleziono zadnego z przeciwnym wartosciowaniem, to da sie znalezc falszywe wartosciowanie dla CALEJ formuly
          [(check-if-opposite ;;jesli znalazlo literal z przeciwnym wartosciowaniem, to zwracamy falsz, to jest zawsze prawdziwe ergo nie da sie znalezc wartosciowania falszywego
            (cdr lista)
            (third (car lista))
            (second (car lista))) 
           #f]
          [else (iterator (cdr lista))])) ;;moze dla innych literalow znajdzie sie taki z przeciwnym wartosc? Sprawdzmy!

  (define (pom lista)
    (cond [(empty? lista) 'false] ;;przeszlismy wszystkie klauzule i dla zadnej z klauzul falszywego wartosciowania, to nie ma falszywego wartosciowania wcale
          [(iterator (car lista))
           (get-evaluation (car lista) '())] ;;jesli udalo nam sie znalezc falszywe wartosciowanie dla danej klauzuli, to zwracamy to wartosciowanie
          [(pom (cdr lista))])) ;;a jesli nie, to szukamy dalej :c
  
  (pom (convert-to-cnf (convert-to-nnf formula))))


(convert-to-cnf (convert-to-nnf (disj 'a (conj 'b 'c))))

(falsifable-cnf? (disj 'a (conj 'b 'c)))
(falsifable-cnf? (conj 'a (neg 'a)))
(falsifable-cnf? (disj 'a (neg 'a)))
(define p
  (list 'conj 'c (list 'neg (list 'disj (list 'conj 'a 'b) (list 'neg 'a)))))
(falsifable-cnf? p)


;;asymptotyczna złożoność czasowa procedury opierającej na konwersji do cnf jest mniejsza, ponieważ sprawdzamy mniej wartościowań, choć ja nie odczułem BARDZO widocznej
;;roznicy, algorytm nie sprawdza wszystkich wartościowań całej formuły a tylko całe wartościowania klauzul (w check-if-oppoiste przechodzimy po wszystkich zmiennych i szukamy dla nich
;;przeciwnego wartosciowania 
;;czyli zlozonosc calego alogrytmu to okolo: suma silni k (gdzie k to liczba różnych zmiennych w
;;klauzuli) a nie 2^p gdzie p to liczba zmiennych w formule.

;;Kacper Bajkiewicz
