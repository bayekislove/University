#lang racket
(provide (struct-out const) (struct-out binop) (struct-out var-expr) (struct-out let-expr) (struct-out var-dead) find-dead-vars)
; --------- ;
; Wyrazenia ;
; --------- ;

(struct const    (val)      #:transparent)
(struct binop    (op l r)   #:transparent)
(struct var-expr (id)       #:transparent)
(struct var-dead (id)       #:transparent)
(struct let-expr (id e1 e2) #:transparent)

(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x) (symbol? x)]
    [(var-dead x) (symbol? x)]
    [(let-expr x e1 e2) (and (symbol? x) (expr? e1) (expr? e2))]
    [_ false]))

(define (parse q)
  (cond
    [(number? q) (const q)]
    [(symbol? q) (var-expr q)]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'let))
     (let-expr (first (second q))
               (parse (second (second q)))
               (parse (third q)))]
    [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
     (binop (first q)
            (parse (second q))
            (parse (third q)))]))

; ---------------------------------- ;
; Wyszukaj ostatnie uzycie zmiennych ;
; ---------------------------------- ;

(define (find-dead-vars e)
  (car (pom e env-empty)))

; mozesz tez oczywiscie dopisac tu jakies procedury
(struct environ (xs))

(define env-empty (environ null))

(define (env-add x env)
  (environ (cons x (environ-xs env))))

(define (env-lookup x env)
  (define (assoc-lookup xs)
    (cond [(null? xs) #f]
          [(eq? x (car xs)) (cdr xs)]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environ-xs env)))

(define (env-delete x env)
  (cond [(eq? env env-empty) env-empty]) 
  (define (pom nowy stary)
    (if (empty? stary)
        (environ nowy)
        (if (equal? x (car stary))
            (environ (append nowy (cdr stary)))
            (pom (append nowy (car stary)) (cdr stary)))))
  (pom '() (environ-xs env)))

(define (pom e envie)
  (match e
    [(const e) (cons (const e) envie)]
    [(var-expr k) (if (not (env-lookup k envie))
                      (cons (var-dead k)
                            (env-add k envie))
                      (cons (var-expr k)
                            envie))]
    [(binop op l r) (let* ([right (pom r envie)]
                           [left (pom l (cdr right))])
                      (cons (binop op (car left) (car right))
                            (cdr left)))]
    [(let-expr zm e1 e2) (let* ([e2help (pom e2 envie)]
                                [e1help (pom e1 (env-delete zm (cdr e2help)))])
                           (cons (let-expr zm (car e1help) (car e2help))
                                 (cdr e1help)))]))

;;testy!
                               
(find-dead-vars (let-expr 'x (const 3)
                          (binop '+ (var-expr 'x) (var-expr 'x))))

(find-dead-vars (let-expr 'x (const 3)
                      (binop '+ (var-expr 'x )
                              (let-expr 'x (const 5)
                                   (binop '+ (var-expr 'x)
                                           (var-expr 'x))))))

                                    