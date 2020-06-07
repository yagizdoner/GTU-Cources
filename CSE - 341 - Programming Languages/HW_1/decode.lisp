; *********************************************
; *  341 Programming Languages                *
; *  Fall 2019                                *
; *  Author: Yağız Döner                      *
; *  Number: 141044062                        *
; *********************************************

;; utility functions 
(load "include.lisp") ;; "c2i and "i2c"


(defun read-as-list (filename)
	; Reads a file containing one word per line and returns a list of words (each word is in turn a list of characters)."
	(with-open-file (stream filename)
	(loop for line = (read-line stream nil nil)		
		while line
		collect (word-to-int(coerce line 'list))))
)

;; -----------------------------------------------------
;; HELPERS
;; *** PLACE YOUR HELPER FUNCTIONS BELOW ***

;converts characters to integer numbers
(defun word-to-int (word)
	(if (not(eq word nil))
	(cons (c2i(car word)) (word-to-int (cdr word))))
)

;converts integer numbers to characters
(defun int-to-word (word)
	(if (not(eq word nil))
	(cons (i2c(car word)) (int-to-word (cdr word))))
)

;shuffle the list, Shuffled list is used for mapping.
(defun list-shuffler-recursive (input-list &optional accumulator)
  "Shuffle a list using tail call recursion."
  (if (eq input-list nil)
      accumulator
      (progn
	(rotatef (car input-list) 
		 (nth (random (length input-list)) input-list))
	(list-shuffler-recursive (cdr input-list) 
				 (append accumulator (list (car input-list))))))
)

;creating alphabet and chipperAlphabet mapping
(defun createMap ()
	(setf mainAlphabet '(#\a #\b #\c #\d #\e #\f #\g #\h #\i #\j 
		#\k #\l #\m #\n #\o #\p #\q #\r #\s #\t #\u #\v #\w #\x #\y #\z))
	(setf mainAlp '(#\a #\b #\c #\d #\e #\f #\g #\h #\i #\j 
		#\k #\l #\m #\n #\o #\p #\q #\r #\s #\t #\u #\v #\w #\x #\y #\z))

	;;Sifrenin olusturulmasi
	(list-shuffler-recursive mainAlphabet)
	;;Sifrenin gercek alfabeye map etmesi
	(setf mapAlphabet (make-hash-table :test 'equal))
	(loop for k from 0 to 25
		do(setf (gethash (nth k mainAlp) mapAlphabet) (nth k mainAlphabet))
	)
	mapAlphabet
)	

;if docoded word is in the list, function returns decoded word. Else, return nil
(defun match (cipherAlphabet encodedWord)
	(setf decodedWord (converter cipherAlphabet encodedWord))
	(setf found (spell-checker-1 decodedWord))
	(if (not(equal found nil))
		(setf decodedWord nil))
	decodedWord
)			 

;convert the given word according to given map
(defun converter (mapAlphabet encodedWord)
	(if (not(eq encodedWord nil))
	(cons (gethash (car encodedWord) mapAlphabet ) (converter mapAlphabet (cdr encodedWord))))
)

;read function for spell-check-1
(defun read-dict-for-spe1 (filename)
	(setf dict (make-hash-table :test #'equal))
	(defun add (word)
		(setf (gethash word dict) t))
	(with-open-file (stream filename)
        (do ((line (read-line stream) (read-line stream nil 'eof)))
            ((eq line 'eof))
        (add line)))
	dict
)

(defun spell-checker-0 (word)
	(setf isThere nil)
	(setf words (read-as-list "dictionary1.txt"))
    (loop for w in words
		do(if (equal w (word-to-int word))
			(setf isThere T)
		)
	)
	isThere
)

(defun spell-checker-1 (word)
	(setf dictionary (make-hash-table :test #'equal))
	;read-dict-for-spe1 is helper function. Given above.
	(setf dictionary (read-dict-for-spe1 "dictionary2.txt"))
	(setf isThere (gethash word dictionary))
	isThere
)



;; -----------------------------------------------------
;; DECODE FUNCTIONS

(defun Gen-Decoder-A (paragraph)
	(setf exit t)
	(loop while (eq exit t)
		do
			(setf alphabet (createMap))
			(setf decodedWord (match alphabet paragraph))
			(if (not(eq decodedWord nil))
				(setf exit nil))
			)
	decodedWord	
	
)

(defun Gen-Decoder-B-0 (paragraph)
  	;you should implement this function
)

(defun Gen-Decoder-B-1 (paragraph)
  	;you should implement this function
)

(defun Code-Breaker (document decoder)
	(setf plainText '())
	(setf doc (read-as-list document))
	(loop for i from 0 to (- (list-length doc) 1)
			 do(setf decodedWord (decoder (nth doc i)))
			 (setf plainText (cons plainText decodedWord)))
	plainText
)

;; -----------------------------------------------------
;; Test code...

(defun test_on_test_data ()
	(print "....................................................")
	(print "Testing ....")
	(print "....................................................")
	(print "Firstly, Test of spell-checker-0")
	;spell-checker-0 take most time. So, these examples are on dictionary1.txt
	(print "dictionary is in dictionary1.txt ->") ;(Expected : T)
	(write (spell-checker-0 '(#\d #\i #\c #\t #\i #\o #\n #\a #\r #\y)))
	(print "test is in dictionary1.txt ->" (spell-checker-0 '(#\t #\e #\s #\t))) ;(Expected : T)
	(write (spell-checker-0 '(#\t #\e #\s #\t)))
	(print "abc is in dictionary1.txt ->") ;(Expected : NIL)
	(write (spell-checker-0 '(#\a #\b #\c)))
	(print "....................................................")
	(print "Secondly, Test of spell-checker-1")
	;spell-checker-1 is faster. So, these examples are on dictionary2.txt
	(print "rotator is in dictionary2.txt ->") ;(Expected : T)
	(write (spell-checker-1 "rotator"))
	(print "statute is in dictionary2.txt ->") ;(Expected : T)
	(write (spell-checker-1 "statute"))
	(print "klmnt is in dictionary2.txt ->") ;(Expected : NIL)
	(write (spell-checker-1 "klmnt"))
	(print "....................................................")

	(print "Testing of Gen-Decoder-A")
	(print "dictionary is encoding -->  ")
	(write (Gen-Decoder-A '(#\d #\i #\c #\t #\i #\o #\n #\a #\r #\y)))
	(print "programming is encoding -->  ")
	(write (Gen-Decoder-A '(#\p #\r #\o #\g #\r #\a #\m #\m #\i #\n #\g)))
)

;; test code...
(test_on_test_data)