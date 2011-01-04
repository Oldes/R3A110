REBOL [
	title: "R3 demo extension - tests"
	author: "Richard Smolak"
]

demo-ext: import switch system/version/4 [
	4 [ ;Linux
		%demo-ext.so
	]
	3 [ ;Windows
		%demo-ext.dll
	]
	2 [ ;OSX
		%demo-ext.dylib
	]
]


;commented out types have not yet implemented test case on the C side
types: sort/skip [
	unset! #[unset!]
	none! #[none!]
;	handle!
	logic! #[true]
	integer! 1234
	decimal! 12.34
	percent! 12.34%
	char! #"c"
	pair! 12.34x56.78
	tuple! 1.2.3.4.5.6.7
	time! 17:15:25.123
;	date! 
	word! some-word
;	set-word! 
;	get-word! 
;	lit-word! 
;	refinement! 
;	issue! 
	string! "Hello world! UTF8 chars: ěščřžýáíé"
;	file! 
;	email! 
;	url! 
;	tag! 
;	block! 
;	paren! 
;	path! 
;	set-path! 
;	get-path! 
;	lit-path! 
;	binary! 
;	bitset! 
;	vector! 
;	image! 
;	gob! 
;	object! 
;	module!
] 2

hello-test
print ""
print "Return type tests:"
print "---------------"
foreach [t r] types [
	print [t ":" t: mold/all return-type-test t either t = mold/all get/any 'r ["OK"]["ERROR"]]
]

halt
