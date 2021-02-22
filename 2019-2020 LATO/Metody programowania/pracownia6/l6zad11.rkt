#lang racket

(provide (struct-out const) (struct-out binop) rpn->arith)

;; -------------------------------
;; Wyrazenia w odwr. not. polskiej
;; -------------------------------

(define (rpn-expr? e)
  (and (list? e)
       (pair? e)
       (andmap (lambda (x) (or (number? x) (member x '(+ - * /))))
               e)))

;; ----------------------
;; Wyrazenia arytmetyczne
;; ----------------------

(struct const (val)    #:transparent)
(struct binop (op l r) #:transparent)

(define (arith-expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r)
     (and (symbol? op) (arith-expr? l) (arith-expr? r))]
    [_ false]))

;; ----------
;; Kompilacja
;; ----------

(struct stack (xs) #:transparent)
(define empty-stack (stack null))
(define (empty-stack? s) (null? (stack-xs s)))
(define (top s) (car (stack-xs s)))
(define (push a s) (stack (cons a (stack-xs s))))
(define (pop s) (stack (cdr (stack-xs s))))

(define (rpn->arith e)
  (define (pparse q)
    (cond [( number? q ) ( const q ) ]
          [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
           (binop (first q) (pparse (second q)) (pparse (third q)))]))
  (cond [(null? e) '()])
  (define (pom lista stos)
    (if (empty? lista)
        (pparse (first (stack-xs stos)))
        (if (not (eq? (member (car lista) '(+ / * -)) #f))
            (pom (cdr lista)
                 (push (list (car lista)
                             (top (pop stos))
                             (top stos))
                       (pop (pop stos))))
            (pom (cdr lista)
                 (push (car lista) stos)))))
  (pom e empty-stack))

; Mozesz tez dodac jakies procedury pomocnicze i testy
(rpn->arith '(1 2 + 3 4 + /))
(rpn->arith '(1 2 +))
(rpn->arith '(3 4 * 1 2 + - 5 7 / +))