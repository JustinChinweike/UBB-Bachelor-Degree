; 8. Return the list of nodes of a tree of type (2) accessed inorder.

; (car l) - the first element of the list is the root of the tree
; (cadr l) - the second element of the list, at superficial level, is the left subtree
; (caddr l) - the third element of the list, at the superficial level, is the right subtree


; myAppend(l1l2...ln, p1p2...pm) = 
; = p1p2...pm, if n = 0
; = {l1} U myAppend(l2...ln, p1p2...pm), otherwise


(defun myAppend (l p)
  (cond
    ((null l) p)
    (t (cons (car l) (myAppend (cdr l) p)))
  )
)

; inorder(l1l2l3) = 
; = nil, if n = 0 
; = myAppend(inorder(l2), myAppend(list(l1), inorder(l3))), otherwise


(defun inorder(l)     
  (cond
    ((null l) nil)
    (t (myAppend (inorder (cadr l)) (myAppend (list (car l)) (inorder (caddr l)))))
  )
)


(  print ( inorder '(A (B (F (I) (J))) (C (D (G) (H)) (E)))))


;; (       A      )
;; (      / \     )
;; (     B   C    )
;; (    /   / \   )
;; (   F   D   E  )
;; (  /\   /\     )
;; ( I  J G  H    )



