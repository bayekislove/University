#lang racket
(provide (struct-out complex) parse eval)
(struct i () #:transparent)
(struct complex (re im) #:transparent)

(define value?
  complex?)

;; Ponizej znajduje sie interpreter zwyklych wyrazen arytmetycznych.
;; Zadanie to zmodyfikowac go tak, by dzialal z liczbami zespolonymi.

(struct const (val)    #:transparent)
(struct binop (op l r) #:transparent)

(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /]))

(define (eval e)
  (match e
    [(const n) n]
    [(binop op l r) (cond [(and (complex? l)
                                (complex? r))
                           [cond [(eq? op '+)
                                  (complex (+ (complex-re l)
                                              (complex-re r))
                                           (+ (complex-im l)
                                              (complex-im r)))]
                                 [(eq? op '-)
                                  (complex (- (complex-re l)
                                              (complex-re r))
                                           (- (complex-im l)
                                              (complex-im r)))]
                                 [(eq? op '*)
                                  (let ([a (complex-re l)]
                                        [b (complex-im l)]
                                        [c (complex-re r)]
                                        [d (complex-im r)])
                                    (complex (- (* a c) (* b d)) (+ (* a d) (* b c))))]
                                 [(eq? op '/)
                                  (let ([a (complex-re l)]
                                        [b (complex-im l)]
                                        [c (complex-re r)]
                                        [d (complex-im r)])
                                    (complex (/ (+ (* a c) (* b d)) (+ (* c c) (* d d)))
                                             (/ (- (* b c) (* a d)) (+ (* c c) (* d d)))))]]]
                          [(complex? l)
                           (eval (binop op l (eval r)))]
                          [(complex? r)
                           (eval (binop op (eval l) r))]
                          [else (eval (binop op (eval l) (eval r)))])]))
                                      
(define (parse q)
  (cond [(number? q) (complex q 0)]
        [(eq? 'i q) (complex 0 1)]
        [(and (list? q)
              (eq? (length q) 3)
              (symbol? (first q)))
         (binop (first q)
                (parse (second q))
                (parse (third q)))]))

(parse '(+ 2 (* 7 i)))
(eval (parse '(+ 2 (* 7 i))))
(eval (parse '(* i i)))
(eval (parse '(+ 3 (* i 8))))
(eval (parse '(+ (+ 2 2) i)))
(eval (parse (list '* 'i 'i)))
(equal? (eval (parse (list '* 'i 'i))) (complex -1 0))
(eval (parse '(/ (+ 1 (* 8 i)) (+ 2 (* 3 i)))))
