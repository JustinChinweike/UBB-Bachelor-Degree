
;; 14 

;; a ) Write a Function to return the union of two sets 

;; Recursive Model

;;Contains
;;;    Checks if an element x is present in a list l = [l1,l2,....ln]

#|                      { 0                        if l = []  (if l is empty)
contains (l1..ln, x)  = { 1                        if l1 = x 
                        {contains(l2....ln, x)     otherwise   
|#

(defun contains (lst x)
  (cond 
    ((null lst) 0)                             
    ((eq (car lst) x) 1)                       
    (t (contains (cdr lst) x))
  )
)              
                
    
;(print(contains '(1 2 3 4 5) 3))  
;(print(contains '() 3) )         
  
#|                         {    v  if l1..ln= []
unionRec(l1..ln, v1..vn) = { unionRec(l2..ln , v1..vn U {l1}) if contains(v1..vn, l1) = 0
                           { unionRec(l2..ln, v1..vn)  otherwise
|#

(defun unionRec (l v)
    (cond 
        ((null l) v)                                    
        ((= (contains v (car l)) 0)                     
         (unionRec (cdr l) (append v (list (car l)))))  
        (t (unionRec (cdr l) v))                        
    )
)


(defun union2 (a b)
    (unionRec b a)
)

(print (union2 '(1 2 3) '(1 2 3 4)))



;;) b) Write a function to return the product of all numerical atoms in a list, at any level

;; product-numerical-atoms 
;;     Compute the product of all numeric elements in a nested list 

;;Recursive Model 
|#                                   { 1      if l1 = []
 product-numerical-atoms(l1...ln) =  { product-numerical-atoms (l1) x product-numerical-atoms(l2...ln)
                                                                     if l1 is a number 
                                     { product-numerical-atoms(l1) x product-numerical-atoms(l2...ln)
                                                                      if l1 is a list 
                                     { product-numerical-atoms(l2...ln)        otherwise(skip non mumeric elements )

#|

(defun product-numerical-atoms (lst)
  "Calculate the product of all numerical atoms in a list, at any level."
  (cond
    ((null lst) 1)                               
    ((numberp (car lst))                         
     (* (car lst) (product-numerical-atoms (cdr lst)))) 
    ((listp (car lst))                           
     (* (product-numerical-atoms (car lst))      
        (product-numerical-atoms (cdr lst))))     
    (t (product-numerical-atoms (cdr lst)))))     

;; Examples
;;(print (product-numerical-atoms '(1 2 3)))             ; print: 6
;;(print (product-numerical-atoms '(1 (2 3) 4)))         ; print: 24
;;(print (product-numerical-atoms '(1 (2 (3 4)) 5)))     ; print: 120
(print (product-numerical-atoms '(1 (2 (a b 3) 4) 5))) ; print: 120
;;(print (product-numerical-atoms '()))                  ; print: 1







;;c) Write a function to sort a linear list with keeping the double values: 

;; insertOk 
;;     Inserts an element e into the correct position in a sorted list l keeping duplicates 

;;Mathematical Model 
|#                     { [e]                              if l1...ln = [] 
insertOk(l1...ln, e) = { [e, l1....ln]                    if e < l1
                       { [l1] U insertOk(l2....ln, e)     otherwise
#| 

(defun insertOk (l e)
  (cond
    ((null l) (list e))                      
    ((< e (car l)) (cons e l))              
    (t (cons (car l) (insertOk (cdr l) e))))) 
    
(print (insertOk '(2 4 6) 3))  



;; sort2 
     ;; sort2 a list l1...ln while preserving duplicates 

;;Mathematical model      
|#               {[]         if l = [] 
sort2(l1...ln) = {insertOk(sort2(l2...ln), l1)  otherwise
#|

(defun sort2 (l)
  (cond
    ((null l) nil)                           
    (t (insertOk (sort2 (cdr l)) (car l)))  
    )
  )
    

;;(print (sort2 '(1 3 3 2 4 5 10 5)))        



;;d) Build a list which contains positions of a minimum numeric element from a given linear list.

;; buildListRec
;;     Build a list of positions where the minimum numeric value m occurs in the list. 

;; Mathematical model 
|#                      { v                         if l1....ln = [] 
getminRec(l1...ln, v) = { getminRec(l2, l1)         if l1 is a number and l1 < v 
                        { getminRec(l2, v)          otherwise
#| 

(defun getminRec (l v) 
  (cond
    ((null l) v ) ;; if the list is empty, Return the current minimun 'v' 
    ((and (numberp (car l)) (< (car l) v)) ;; if the first element is a number and less than v 
    (getminRec( cdr l ) (car l))) ; Update the minimun and continue with the rest of the list
    (t (getminRec (cdr l) v))))  ;; otherwise skip the element and continue
 
    

(defun getmin (l) 
  (getminRec (cdr l) (car l))
  
  )

    |#
    getmin:
          getmin(l1....ln) = getminRec(l2, l1)
    #|


;; buildListRec 
;;   Builds a list of positions where the minimum numeric value m occurs in the list 

;;Mathematical model 

|#                      {[]    if l = []
buildListRec(l, i, m) = {[i]  U buildListRec(l2...ln, i + 1 , m)
                                                                 if l1 = m 
                        {buildListRec(l2....ln, i + 1, m)        otherwise
#|

(defun buildListRec( l i m) 
  (cond 
    ((null l) nil) ; If the list is empty, return an empty list. 
    ((eq (car l) m) ;; if the first element equals the minimum value
    (cons i (buildListRec (cdr l ) (+ i 1) m ))) ;; Add the current position 'i' to the result
    (t (buildListRec (cdr l) (+ i 1) m)) ;; otherwise , skip the element and continue
    
)
  )


(defun buildList (l) 
  (buildListRec l 1 (getmin l)) 
  )

|#
    buildList:
          buildList(l1....ln) = buildListRec(l1...ln, 1, getmin(l1...ln))
#|


;;print (buildList '(0 3 4 5 0 0)))




