#lang racket
(provide cont-frac)
(define (cont-frac num den)
  (define (reckon-el w1 w2 i)
    (+ (* (den i) w2)
       (* (num i) w1))) 
  (define (reckon-approx a1 a2 b1 b2 z)
    (/ (reckon-el a1 a2 z)
       (reckon-el b1 b2 z)))
  (define (iterator ac an bc bn k prev_result);c-current, n-next
    (define new_result (reckon-approx ac an bc bn k))
    (if (< (abs (- new_result prev_result)) 0.0001)
        new_result
        (iterator an
                  (reckon-el ac an k)
                  bn
                  (reckon-el bc bn k)
                  (+ k 1)
                  new_result)))
  (iterator 1.0 0.0 0.0 1.0 0 0))

(cont-frac (lambda (x) * (+ 1 (* 2 x)) (+ 1 (* 2 x))) (lambda (x) 6.0))
(cont-frac (lambda(i) 1)  (lambda(i) 1))
(define (atan-cf x)
  (cont-frac (lambda (k)
               (if (= k 0)
                   x
                   (* (* k x) (* k x))))
              (lambda (k) (+ (* 2 k) 1))))
(atan-cf 0)
(atan-cf 5)
 
;;Jakub Szajner polecił mi, żeby przechowywać wartość poprzedniego wywołania funkcji a nie liczyć to na nowo
    
  
        