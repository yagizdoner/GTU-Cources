; ******************************
; *  CSE 341 - HW2 - PART 2    *
; *  Author: Yağız DÖNER       *
; *  No: 141044062			   *
; ******************************

;dosyadaki verileri satır satır işleme alır.
;aldığı her satırı read-eval-print'e yönlendirerek
;lexical analizin yapılmasını başlatır.
(defun get-file (filename)
	(let ((in (open filename :if-does-not-exist nil)))
		(when in
			(loop for line = (read-line in nil)
			while line do (read-eval-print line)))
	)
)

;file'dan gelen her satırın lexical analizine başlanır.
(defun read-eval-print (line)
	(if (and (>= (length line) 2)(isComment line))
		(print (list "COMMENT"))
		(if (not(equal "" line))
			(print (lexer (lex line))))
		; lexer 'a   tab("	") ve boşluk(" ") lar silinerek, ayrıca aç ve kapa parantezler ayrılarak yollanır.
	)
)

; string bir Number mı değil mi? G++ syntax pdf ine göre.
; 01 | 0012 | 1asd gibi durumlar kabul edilmez.
(defun isNumber (str num)
	(cond
		((and (equal num 0) (equal "" str)) nil) ; ilk durumda"" ise
		((and (equal num 0) (> (length str) 1) (equal "0" (subseq str 0 1))) nil) ;ilk durumda 0... şeklinde başlıyorsa.
		(t (if (equal str "")
			t
			(if (digit-char-p (coerce (subseq str 0 1) 'character)) 
				(isNumber (subseq str 1 (length str)) (+ num 1))
				nil
			)
			))
	)
)

; string bir Identifier mı değil mi? G++ syntax pdf ine göre.
; 1asd | ad:!asd  gibi durumlar kabul edilmez
(defun isIdentifier (str num)	
	(if (and (equal num 0) (equal str "")) ; num 0 ilk durumda geçerli. Birinci harfi temsil ediyor.
		nil
	)
	(if (equal num 0) 
		(if (alpha-char-p (coerce (subseq str 0 1) 'character)) 
			(isIdentifier (subseq str 1 (length str)) (+ num 1))
			nil
		)
		(if (equal str "")
			t
			(if (or (alpha-char-p (coerce (subseq str 0 1) 'character)) (digit-char-p (coerce (subseq str 0 1) 'character))) 
				(isIdentifier (subseq str 1 (length str)) (+ num 1))
				nil
			)
		)
	)
)

;verilen stringin ilk 2 harfine bakarak bunun bir yorum satırı
;olup-olmama durumunu inceliyor.
(defun isComment (str)
	(if (equal (subseq str 0 2) ";;")
		t
		nil
	)
)

; verilen string'i  uygun token olarak listeler
(defun tokenzier (str)
	(if(equal str "and")(list "KW_AND")
	(if(equal str "or")(list "KW_OR")
	(if(equal str "not")(list "KW_NOT")
	(if(equal str "equal")(list "KW_EQUAL")
	(if(equal str "less")(list "KW_LESS")
	(if(equal str "nil")(list "KW_NIL")
	(if(equal str "list")(list "KW_LIST")
	(if(equal str "append")(list "KW_APPEND")
	(if(equal str "concat")(list "KW_CONCAT")
	(if(equal str "set")(list "KW_SET")
	(if(equal str "deffun")(list "KW_DEFFUN") 
	(if(equal str "for")(list "KW_FOR")
	(if(equal str "if")(list "KW_IF")
	(if(equal str "exit")(list "KW_EXIT")
	(if(equal str "load")(list "KW_LOAD")
	(if(equal str "disp")(list "KW_DISP")
	(if(equal str "true")(list "KW_TRUE")
	(if(equal str "false")(list "KW_FALSE")
	(if(equal str "+")(list "OP_PLUS")
	(if(equal str "-")(list "OP_MINUS")
	(if(equal str "/")(list "OP_DIV")
	(if(equal str "*")(list "OP_MULT")
	(if(equal str "(")(list "OP_OP")
	(if(equal str ")")(list "OP_CP")
	(if(equal str "**")(list "OP_DBLMULT")
	(if(equal str "\"")(list "OP_OC")
	(if(equal str "\"")(list "OP_CC")
	(if(equal str ",")(list "OP_COMMA")
	(if(isIdentifier str 0)(list "IDENTIFIER")
	(if(isNumber str 0)(list "VALUE")(list "This is not Acceptable !")))))))))))))))))))))))))))))))
)


; verilen listeyi, verilen elemana göre ayırır. Bunu için yardımcı fonksiyonu kullanır.
(defun splitter (lst sp del)
	(cond 
		((null lst) nil)
		((atom (car lst))(if (atom (car lst))
			(append (splitHelper (car lst) sp del) (splitter (cdr lst) sp del))
			(append (splitter (car lst) sp del) (splitter (cdr lst) sp del)) ; atom değilse, içerisi için tekrar çağırılır.
		))
	)
)

; del t ise; verilen string(str) den yine verilen sp(split edilecek eleman) yi silerek parçalar.
; del nil ise; verilen string(str) den yine verilen sp(split edilecek eleman) yi silmeden parçalar.
(defun splitHelper (str sp del)
	(if (not(equal "" str))
		(let ((index (search sp str))) ; sp yi str içinde arar.
			(if (equal index nil)
				(list str)	 ; sp str de yoksa		
				(if (equal del t)
					(append (list (subseq str 0 index)) (splitHelper (subseq str (+ index 1) (length str)) sp del)) 	; sp listeye eklenmez
					(append (list (subseq str 0 index)) (list sp) (splitHelper (subseq str (+ index 1) (length str)) sp del)) ; sp eklenir
				)	
			)
		)
	)
)

; hangi durumlara göre listenin bölünmesi gerektiği ile ilgili fonksiyon.
;içinde splitter'ı kullanır.
(defun lex (lst)
	(splitter (splitter (splitter (splitter (list lst) " " t) "	" t) ")" nil) "(" nil)
)

; listedeki her bir string'in tokenzier fonksiyonu ile token'ini belirler
; eğer token' de sıkıntı varsa  mesajı basar ve durur.
(defun lexer(lst)
	(if  (null lst)
		nil
		(if (equal "" (car lst))
			(lexer (cdr lst))
			(let ((token (tokenzier (car lst))))
				(if (equal token nil)
					nil
					(cons token (lexer (cdr lst)) )
				)
			)
		)
	)
)

;eğer filename argüman olarak gelirse, öncelikle dosyanın lexical analizi
;tamamlanacak. Bunun için get-file çağrılıyor ve işlem ordan devam ediyor.
;Bu işlemden sonra interpreter açılıyor ve satır satır girilen değerleri
;çevirmek için değer girilmesi bekleniyor. quit yazıp çıkıncaya kadar program
;işleme devam edecektir. PDF de dosyayı okuduktan sonra girdileri beklemeye
;geçilmesi gerektiği şeklinde algıladığım için böyle yaptım.
;eğer filename gelmeden sadece interpreter çağrılırsa, dosya okuma olmadan
;sadece interpreter olarak çalışacak. Yine quit girilene kadar işlem için
;bekleyecektir.
(defun gppinterpreter (&optional filename) 
	(if (not(equal filename nil))
		(get-file filename)  					 	 
	)
	(print "Read - Eval - Exe Operation has been started. (For Exit: quit)")
	(loop (print "->") (let ((line (read-line)))  
		(if (equal line "quit") ;quit girilirse interpreter kapatılarak, programdan çıkılır.
			(return)
			(if (and (>= (length line) 2)(isComment line))
				(print (list "COMMENT"))
				(if (not(equal line nil))
					(write(lexer (lex line)))
				)
			)
		)
	))
)

(gppinterpreter (car *args*))