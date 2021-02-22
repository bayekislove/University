#lang racket
(require "leftist.rkt")
(provide heapsort)
(define (heapsort inplist)
  (define (zrob-kopiec lista kopiec)
    (if (null? lista)
        kopiec
        (zrob-kopiec (cdr lista)
                     (heap-insert (make-elem (car lista)
                                             (car lista))
                                  kopiec))))
  (define (powrot lista kopiec)
    (if (heap-empty? kopiec)
        lista
        (powrot (append (list (elem-val
                              (heap-min kopiec)))
                        lista)
                (heap-pop kopiec))))
  (powrot '() (zrob-kopiec inplist empty-heap)))
