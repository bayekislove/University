#lang typed/racket
(provide typecheck parse)
;;Środowisko wzięte z ćwiczeń p. Lisowskiego, parser wzięty z ćwiczeń, wykorzystałem parę testów Jakuba Szajnera
(struct const    ([val : (U Number Boolean 'true 'false)])            #:transparent)
(struct binop    ([op : Binop-sym] [l : Expr] [r : Expr])             #:transparent)
(struct var-expr ([id : Symbol])                                      #:transparent)
(struct let-expr ([id : Symbol] [e1 : Expr] [e2 : Expr])              #:transparent)
(struct if-expr  ([eb : Expr] [et : Expr] [ef : Expr])                #:transparent)
(define-type EType (U 'real 'boolean))

(define-type Expr (U const binop var-expr let-expr if-expr))
(define-type Binop-sym (U 'and 'or '/ '+ '- '* '= '< '> '<= '>=))
(define-type Ide Symbol)
(define-predicate ide? Ide)
(define-predicate expr? Expr)
(define-predicate binop-sym? Binop-sym)

(: parse (-> Any Expr))
(define (parse q)
  (match q
    [_ #:when (or (number? q) (boolean? q) (eq? q 'true) (eq? q 'false))
       (const q)]
    [_ #:when (ide? q)
       (var-expr q)]
    [`(,op ,e1 ,e2) #:when (binop-sym? op)
                    (binop op
                           (parse e1)
                           (parse e2))]
    [`(let (,x ,e1) ,e2) #:when (ide? x)
     (let-expr x 
               (parse e1)
               (parse e2))]
    [`(if ,f ,e1, e2)
     (if-expr (parse f)
              (parse e1)
              (parse e2))]))

(define-type Val (U Number Boolean))

(define-type Env (Listof (Pairof Symbol EType)))

(: env-empty Env)
(define env-empty null)

(: env-add (-> Symbol EType Env Env))
(define (env-add x v env)
   (cons (cons x v) env))

(: env-lookup (-> Symbol Env EType))  
(define (env-lookup x env)
  (: assoc-lookup (-> Env EType))
  (define (assoc-lookup xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (car (car xs))) (cdr (car xs))]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup  env))

(: boolexpr? (-> Binop-sym Boolean))
(define (boolexpr? symb)
  (or (eq? symb 'and) (eq? symb 'or)))

(: boolresult? (-> Binop-sym Boolean))
(define (boolresult? symb)
  (or (eq? symb '<) (eq? symb '>) (eq? symb '<=) (eq? symb '>=) (eq? symb '=)))

(: typecheck (-> Expr (U EType #f)))
(define (typecheck ex)
  (: checker (-> Expr Env (U EType #f)))
  (define (checker exp envie)
    (match exp
        [(const exp1)
         (if (real? exp1)
             'real
             'boolean)] ;;jeśli nie jest real, to jest Boolean lub true lub false, działa
      
      [(var-expr v) (env-lookup v envie)]
      
      [(binop op l r) (cond
                        [(or (eq? #f (checker l envie))
                             (eq? #f (checker r envie)))
                         #f]
                        [(not (eq? (checker l envie)
                                   (checker r envie)))
                         #f]
                        [(eq? (checker l envie) (checker r envie))
                         (cond [(and (eq? (checker l envie) 'boolean)
                                     (boolexpr? op))
                                'boolean]
                               [(and (eq? (checker l envie) 'real)
                                     (boolresult? op))
                                'boolean]
                               [(and (eq? (checker l envie) 'real)
                                     (not (boolexpr? op)))
                                'real]
                               [else #f])]
                        [else #f])]
      
      [(let-expr id e1 e2) (let ([pom (checker e1 envie)])
                               (cond [(eq? pom #f) #f]
                                     [else (checker e2 (env-add id pom envie))]))]
      
      [(if-expr eb et ef) (cond [(not (eq? (checker eb envie) 'boolean)) #f]
                                [(or (eq? (checker et envie) #f)
                                     (eq? (checker ef envie) #f)) #f]
                                [(not (eq? (checker et envie) (checker ef envie))) #f]
                                [else (checker et envie)])]))
                                          
  (checker ex env-empty))

(typecheck (parse '(< 1 2)))
(typecheck (parse '(and true false)))
(typecheck (parse '(or true false)))
(typecheck (parse '(* (+ 1 2) 1)))
(typecheck (parse '(- (+ 1 2) 1)))
(typecheck (parse '(+ (+ 1 2) 1)))
(typecheck (parse '(/ (+ 1 true) 1)))
(typecheck (parse '(let (x 1) x)))
(typecheck (parse '(if (= 1 1) 2 1)))
(typecheck (parse '(* (< 1 2) 1)))