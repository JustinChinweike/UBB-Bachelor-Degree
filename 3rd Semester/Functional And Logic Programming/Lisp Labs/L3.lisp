;; Problem 1

;; Write a function to check if an atom is a member 
;; of a list (the list is non-linear)


; checkExistence( l elem ) = 
; = true ,   if  l = elem and l is an atom 
; = false,   if  l != elem and  l is an atom 
; = checkExistence(l1 elem) or checkExistence(l2 elem) or... or checkExistence(ln elem) , otherwise


(defun checkExistence(l elem)
  (cond
    ((and (atom l) (equal l elem)) t)
    ((atom l) nil) 
    (t (some #'identity (mapcar #'(lambda (a) (checkExistence a elem)) l)))
  )
)


( print (checkExistence '(a (b (c d)) (e f (g h))) 'd))

( print (checkExistence '(a (b (c d)) (e f (g h))) 'z)) 

(print(checkExistence '(a (b c) d) 'a)) 

(print (checkExistence '() 'a)) 

(print(checkExistence '(a b (c (d b) e)) 'b))




