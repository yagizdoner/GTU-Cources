; ******************************
; *  CSE 341 - HW3 - PART 2    *
; *  Author: Yağız DÖNER       *
; *  No: 141044062			   *
; ******************************

;INPUT: 
;	|EXPI      
;	|EXPB  
;	|EXPLISTI       

;EXPI:   
;	OP_OP KW_SET Id EXPI OP_CP           
;	| OP_OP KW_DEFVAR Id EXPI OP_CP      
;	| OP_OP KW_DEFFUN Id IDLIST EXPLISTI OP_CP  
;	| OP_OP KW_IF EXPB EXPLISTI OP_CP     
;	| OP_OP KW_IF EXPB EXPLISTI EXPLISTI OP_CP  
;	| OP_OP OP_PLUS EXPI EXPI OP_CP   
;   | OP_OP OP_MINUS EXPI EXPI OP_CP   
;   | OP_OP OP_MULT EXPI EXPI OP_CP     
;   | OP_OP OP_DIV EXPI EXPI OP_CP
;	| OP_OP Id EXPLISTI OP_CP           
;	| Id                                 
;	| IntegerValue    
 

;EXPB:
;	OP_OP KW_AND EXPB EXPB OP_CP        
;	|OP_OP KW_OR EXPB EXPB OP_CP	      
;	|OP_OP KW_NOT EXPB OP_CP	     
;	|OP_OP KW_EQUAL EXPB EXPB OP_CP      
;	| OP_OP KW_EQUAL EXPI EXPI OP_CP     
;	| BinaryValue

;EXPLISTI:
;	OP_OP KW_CONCAT EXPLISTI EXPLISTI OP_CP 
;	|OP_OP KW_APPEND EXPI EXPLISTI OP_CP
;	|LISTVALUE
;	|

;LISTVALUE:
;	OP_APOS OP_OP VALUES OP_CP
;	|OP_APOS OP_OP OP_CP	 

;VALUES:
;	VALUES IntegerValue 
;	|IntegerValue

;IDLIST:
;	IDLIST Id
;	| Id

;BinaryValue:
;	KW_TRUE 
;	|KW_FALSE 

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
			(let ((ln (lexer (lex line))))
				(if (syntaxController ln)
					(cfgCaller 1 ln 1)
					(cfgCaller 0 ln 1)
				)
			)
		)
		; lexer 'a   tab("	") ve boşluk(" ") lar silinerek, ayrıca aç ve kapa parantezler ayrılarak yollanır.
		; 2. ödevde lexerdan dönenler Syntax controlünden sonra cfgControllera yollanır ve 3. ödevin içeriği uygulanır.
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

;Verilen string bir Binary Değer mi?
(defun isBinaryValue (str)
	(if (equal str "KW_TRUE")
		t
		(if (equal str "KW_FALSE")
			t
			nil
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
	(if(equal str "defvar")(list "KW_DEFVAR")	
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
	(if(equal str "'")(list "OP_APOS")
	(if(equal str "\"")(list "OP_OC")
	(if(equal str "\"")(list "OP_CC")
	(if(equal str ",")(list "OP_COMMA")
	(if(isIdentifier str 0)(list str)
	(if(isNumber str 0)(list str) (list "SYNTAX ERROR !")))))))))))))))))))))))))))))))))
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

;verilen listenin g++ pdf ine göre bir liste olup olmadığını kontrol eder.
(defun isListValue(lst)
	(if (and (equal (car lst) (list "OP_APOS")) (equal (car (cdr lst)) (list "OP_OP")))
		(if (equal (car(last lst)) (list "OP_CP"))
			t
			nil)
		nil 
	)
)

;explisti hesaplamalarında ilk sub_explisti nin hesaplamasını gerçekleştirir.
(defun explistiCalc (lst)
	(if (equal (car lst) (list "OP_CP"))
		nil 	
		(if (equal (car(cdr lst)) (list "OP_CP"))
			(list (parse-integer (car(car lst))))
			(append (list (parse-integer (car(car lst)))) (explistiCalc (cdr lst)))
		)
	)
)

;explisti hesaplamalarında 2. sub_explisti nin hesaplanmasını gerçekleştirir.
(defun explistiCalc2 (lst)
	(defun calc (ls)
		(if (equal (car ls) (list "OP_CP"))
			nil
			(if (equal (car(cdr ls)) (list "OP_CP"))
				(list (parse-integer (car(car ls))))
				(append (list (parse-integer (car(car ls)))) (calc (cdr ls)))
			)
		)
	)
	(if (and (equal (car lst) (list "OP_APOS")) (equal (car (cdr lst)) (list "OP_OP")))
		(calc (cdr(cdr lst)))
		(explistiCalc2 (cdr lst))
	)
)

; lexerdan verilen listeti EXPILISTI ye göre değerlendirir
(defun isEXPLISTI (lst)
	(if (and (and (not(equal (car(cdr lst)) (list "KW_CONCAT"))) (not(equal (car(cdr lst)) (list "KW_APPEND")))) (isListValue lst)) 
		t
		(if (equal (car lst) (list "OP_OP"))
			(let ((lst1 (cdr lst)))
				(if (not(or (equal (car lst1) (list "KW_APPEND")) (equal (car lst1) (list "KW_CONCAT"))))
					nil
					(if (equal (car(last lst1)) (list "OP_CP"))
						(cond 
							( (equal (car lst1) (list "KW_CONCAT")) (if (and (equal (car(cdr lst1)) (list "OP_APOS")) (equal (car(cdr(cdr lst1))) (list "OP_OP")))   
																		(let ((lst2 (cdr(cdr(cdr lst1)))))
																			(append (explistiCalc lst2) (explistiCalc2 lst2))
																		)
																		(list "First Argument is NOT an EXPLISTI")))
							( (equal (car lst1) (list "KW_APPEND")) (if (isNumber (car(car(cdr lst1))) 0) 
																		(append (list(parse-integer (car(car(cdr lst1))))) (explistiCalc2 (cdr(cdr lst1))))
																	(list "First Argument is NOT an EXPI")))
						)
						(list "There is no (OP_CP)")
					)
				)	
			)
			(list "There is no (OP_OP)")
		)
	)		
)

;if statement hesaplamalarında EXPB kısmını değerlendirerek bu hesabı isEXPB de yapar.
(defun ifCalc (ls)
	(defun ifc (lst)
		(if (equal (car lst) (list "OP_CP"))
			nil 	
			(if (equal (car(cdr lst)) (list "OP_CP"))
				(list (car lst))
				(append  (list(car lst)) (ifc (cdr lst)))
			)
		)
	)
	(if (equal (car ls) (list "OP_OP"))
		(isEXPB (append (list(list "OP_OP")) (ifc (cdr ls))(list(list "OP_CP"))))
		nil
	)
)

;if statement larında true durumlarını değerlendirir.
(defun ifCalc2 (ls)
	(defun ifc2 (lst num)
		(if (and (equal (car lst) (list "OP_CP")) (equal num 0))
			nil 	
			(if (and (equal (car(cdr lst)) (list "OP_CP")) (equal num 1))
				(list (car lst))
				(if (equal (car(cdr lst)) (list "OP_CP"))
					(append  (list(car lst)) (ifc2 (cdr lst) 1))
					(append  (list(car lst)) (ifc2 (cdr lst) 0))
				)
			)
		)
	)
	(if (equal (car ls) (list "OP_OP"))
		(isEXPLISTI (append (list(list "OP_OP")) (ifc2 (cdr ls) 0)(list(list "OP_CP"))))
		(ifCalc2 (cdr ls))
	)
)

; lexerdan verilen listeti EXPI ye göre değerlendirir
(defun isEXPI (lst)
	(if (or (isIdentifier (car (car lst)) 0) (isNumber (car(car lst)) 0))
		t
		(if (equal (car lst) (list "OP_OP"))
			(let ((lst1 (cdr lst)))
				(if (and (isIdentifier (car (car lst1)) 0) (equal (car(cdr(cdr lst1))) (list "OP_CP")) )
					(isEXPLISTI (cdr (cdr lst)))
					(if (equal (car(last lst1)) (list "OP_CP"))
						(cond 
							( (equal (car lst1) (list "OP_PLUS")) (+ (parse-integer(car(car (cdr lst1)))) (parse-integer(car(car(cdr(cdr lst1)))))))
							( (equal (car lst1) (list "OP_MINUS")) (- (parse-integer(car(car (cdr lst1)))) (parse-integer(car(car(cdr(cdr lst1)))))))
							( (equal (car lst1) (list "OP_MULT")) (* (parse-integer(car(car (cdr lst1)))) (parse-integer(car(car(cdr(cdr lst1)))))))
							( (equal (car lst1) (list "OP_DIV")) (/ (parse-integer(car(car (cdr lst1)))) (parse-integer(car(car(cdr(cdr lst1)))))))
							( (equal (car lst1) (list "KW_SET")) (if (isIdentifier (car(car(cdr lst1))) 0) (parse-integer(car(car(cdr(cdr lst1))))) (list "There isn't Identifier")))
							( (equal (car lst1) (list "KW_DEFVAR")) (if (isIdentifier (car(car(cdr lst1))) 0) (parse-integer(car(car(cdr(cdr lst1))))) (list "There isn't Identifier")))
							( (equal (car lst1) (list "KW_DEFFUN")) (if (isIdentifier (car(car(cdr lst1))) 0) 0 (list "There isn't Identifier")))
							( (equal (car lst1) (list "KW_IF")) (if (equal (ifCalc (cdr lst1)) (list "TRUE")) (ifCalc2 (cdr(cdr lst1))) 0  ))
						)
						(list "There is no (OP_CP)")
					)
				)	
			)
			(list "There is no (OP_OP)")
		)
	)		
)

; lexerdan verilen listeti EXPB ye göre değerlendirir
(defun isEXPB (lst)
	(if (isBinaryValue (car (car lst)))
		t 
		(if (equal (car lst) (list "OP_OP"))
			(let ((lst1 (cdr lst)))
				(if (equal (car(cdr(cdr lst1))) (list "OP_CP"))
					(if (equal (car lst1) (list "KW_NOT")) (if (equal (car(cdr lst1)) (list "KW_TRUE")) (list "FALSE") 
						(if (equal (car(cdr lst1)) (list "KW_FALSE")) (list "TRUE") (list "NOT a Binary Value !"))))
					(if (equal (car(cdr(cdr(cdr lst1)))) (list "OP_CP"))
						(let ((a (car(cdr lst1))) (b (car (cdr (cdr lst1)))))
							(cond 
								( (equal (car lst1) (list "KW_AND")) (if (and (equal a (list "KW_TRUE")) (equal b (list "KW_TRUE"))) (list "TRUE") 
											(if (and (equal a (list "KW_TRUE")) (equal b (list "KW_FALSE"))) (list "FALSE") 
												(if (and (equal a (list "KW_FALSE")) (equal b (list "KW_TRUE"))) (list "FALSE") 
													(if (and (equal a (list "KW_FALSE")) (equal b (list "KW_FALSE"))) (list "FALSE") (list "Not A Binary Value"))))))
								( (equal (car lst1) (list "KW_OR")) (if (and (equal a (list "KW_TRUE")) (equal b (list "KW_TRUE"))) (list "TRUE")
											(if (and (equal a (list "KW_TRUE")) (equal b (list "KW_FALSE"))) (list "TRUE") 
												(if (and (equal a (list "KW_FALSE")) (equal b (list "KW_TRUE"))) (list "TRUE") 
													(if (and (equal a (list "KW_FALSE")) (equal b (list "KW_FALSE"))) (list "FALSE") (list "Not A Binary Value"))))))
								( (equal (car lst1) (list "KW_EQUAL")) (if (equal a b) (list "TRUE") (list "FALSE")))
							)
						)
						(list "There is no (OP_CP)")
					)
				)	
			)
			(list "There is no (OP_OP)")
		)
	)		
)

;lexer dan dönen değerleri kontrol ederek bir syntax hatası olup olmadığına bakar.
;burdan döndürdüğü değere göre alttaki cfgCaller a gppinterpreter fonksiyonu tarafından
;bir flag yönlendirilir.
(defun syntaxController (lst)
	(if (null lst)
		t
		(if (equal (car lst) (list "SYNTAX ERROR !"))
			nil
			(syntaxController (cdr lst))
		)
	)
)

;WriteSignal 0 ise interpreter için yazacak, 1 ise dosya için ekrana yazacak
;Bunu kullanma nedenim, terminal ekranında daha düzenli görünmesini sağlamak.
;flag ise lexer da syntax sorunu olup, olmaması üzerine tutulmuştur.
(defun cfgCaller (flag lst writeSignal)
	(if (equal writeSignal 1)
		(if (equal flag 1)
			(progn (print "SYNTAX OK.") (print (cfg lst)))
			(progn (print "SYNTAX ERROR !") (print (cfg lst)))
		)
		(if (equal flag 1) ;writeSignal = 0
			(progn (write "SYNTAX OK.") (print (cfg lst)))
			(progn (write "SYNTAX ERROR !") (print (cfg lst)))
		)
	)
)

;cfgCaller tarafından çağrılır ve 3. ödevin operasyon dağılımını sağlar.
(defun cfg (lst)
	(if (or (isBinaryValue (car(car lst))) (isIdentifier (car (car lst)) 0) (isNumber (car(car lst)) 0) (isListValue lst))
		t
		(if (equal (car lst) (list "OP_OP"))
			(let ((op (car(cdr lst)) ))
				(if (or (equal op (list "KW_AND")) (equal op (list "KW_OR")) (equal op (list "KW_NOT")) (equal op (list "KW_EQUAL")) )
					(isEXPB lst)
					(if (or (equal op (list "KW_APPEND")) (equal op (list "KW_CONCAT")))
						(isEXPLISTI lst)
						(if (or (equal op (list "OP_PLUS")) (equal op (list "OP_MINUS")) (equal op (list "OP_MULT")) (equal op (list "OP_DIV")) (equal op (list "KW_SET"))  (equal op (list "KW_DEFVAR"))
							(equal op (list "KW_DEFVAR"))(equal op (list "KW_IF")))
							(isEXPI lst)
							(list "Not An Invalid Operation !!!")
						)
					)
				)
			)
			(list "There is no (OP_OP)")
		)
	)
)

;optional olarak verilen filename e göre, ya direk interpreter olarak çalışır,
;ya da önce dosya okuma ve değerlendirmesi sağlanır, ardından interpreter olarak 
;çalışmaya devam eder. Interpreter a quit değeri girilirse program sonlandırılır.
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
					; 2. ödevde lexerdan dönenler Syntax controlünden sonra cfgControllera yollanır ve 3. ödevin içeriği uygulanır.
					(let ((ln (lexer (lex line))))
						(if (syntaxController ln)
							(cfgCaller 1 ln 0)
							(cfgCaller 0 ln 0)
						)
					)
				)
			)
		)
	))
)

(gppinterpreter (car *args*))
