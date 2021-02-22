#lang racket
(provide merge split mergesort)
(define (length tab)
    (if (null? tab)
        0
        (+ 1.0 (length (cdr tab)))))

(define (find-mid beg end)
  (if (integer? (/ (- end beg) 2))
      (/ (- end beg) 2)
      (/ (- end beg 1) 2)))

(define (split tab) ;;Po dwóch godzinach zmarnowanych na tę funkcję spytałem Kacpra Gawdzińskiego, który polecił rozdzielić zadanie na dwie funkcje szukające pierwszej i drugiej
  (define mid (find-mid 0 (length tab)))   ;;tablicy (wcześniej próbowałem wszystko "załatwić" jednym przejściem, jak widać bezskutecznie).
  (define (get_first tabby curr)
    (if (= curr mid)
        '()
        (cons (car tabby)
              (get_first (cdr tabby)
                         (+ curr 1)))))
  (define (get_second curr tabby)
    (if (= curr mid)
        tabby
        (get_second (+ 1 curr)
                    (cdr tabby))))
  (list (get_first tab 0) (get_second 0 tab)))

(define (merge tab1 tab2)
  (define (insert l x) 
    (if (null? l)
        (list x)
        (if (> x (car l))
            (cons (car l) (insert (cdr l) x))
            (cons x l))))
  (define insertions (length tab2))
  (define (pom curr tab1 tab2)
    (if (= curr 0)
        tab1
        (pom (- curr 1)
             (insert tab1 (car tab2))
             (cdr tab2))))
  (pom insertions tab1 tab2))

(define (mergesort tab1)
  (define (pair? list)
    (if (or (= (length tab1) 0) (null? (car list)) (null? (cdr list)))
        #f
        #t))
  (if (pair? tab1)
      (merge (mergesort (car (split tab1))) (mergesort (car (cdr (split tab1)))))
      tab1))

(merge (list 1 2 4 9) (list 3 0 -1 4))
(car (cdr (split (list 1 2 3 4 5 6 7 8))))
(car (split (list 1 2 3 4 5 6 7 8)))
(mergesort (list 5 3 7 1 9))
(mergesort (list 5 1 3 25 100 -4 213 41))
(mergesort '())
(mergesort (list 1))

                      
                   
