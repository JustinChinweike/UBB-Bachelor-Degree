
;; A binary tree is stored as (root(subtree-1) (subtree-2)). Determine th list of nodes on level 
;; k of the tree. The root is considered 0. For example: 

; (A(B)(C)) -> (A)


(defun nodesAtLevel (tree k &optional (current-level 0))
  (cond
    ((null tree) nil)  
    ((atom tree)  
     (if (= current-level k)
         (list tree)  
         nil))  
          (t  
     (append (nodesAtLevel (car tree) k current-level) ; check root 
     (nodesAtLevel (cadr tree) k (+ current-level 1))  ; here Check left
             (nodesAtLevel (caddr tree) k (+ current-level 1))))))  ; and Check right


(print(nodesAtLevel'(A(B)(C)) 0))

(print(nodesAtLevel'(A ( B (C) (D))(E)) 2))

(print(nodesAtLevel'(A ( B ) (C(D)(E)))1))



(print(nodesAtLevel '(A (B (D) (E)) (C (F) (G))) 0)) ;; Root level 

(print(nodesAtLevel '(A (B (D) (E)) (C (F) (G))) 1));; level 1

(print(nodesAtLevel ' (A (B (D) (E)) (C (F) (G))) 2));; level 2 

(print(nodesAtLevel ' (A (B (D) (E)) (C (F) (G))) 2));; level 2 

(print(nodesAtLevel '(A) 0 )) ;; single leve

(print(nodesAtLevel '() 1))
























    
