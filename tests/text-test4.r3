REBOL []

do %gfx-pre.r3


g_win: make gob! [size: 600x500]
g_bkg: make gob! [size: 600x500 color: white]
g_txt: make gob! [size: 600x500 text: []]

caret-obj: make object! [
	caret: 
	highlight-start:
	highlight-end: none
]

to-text [
	"Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
	newline newline
	"Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
	newline newline
	"Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
	newline newline
	"Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
	caret caret-obj
] g_txt/text



append g_win g_bkg
append g_bkg g_txt


window: view/options g_win [
	title: "TEXT test"
	offset: 'center
	handler: [
		name: 'my-handler
		priority: 100
		handler: func [event] [
			switch event/type [
				close [
					unhandle-events self ; Remove this handler from the global list.
					unview event/window
					quit
				]
				move [
					show g_win ;<- this is here so we can test speed of the text redraw
				]
				down [
					
					otc:  offset-to-caret g_txt event/offset
					;note: caret-to-offset crashes if you does not click on text! 
					cto:  caret-to-offset g_txt otc otc/1						
					otc2: offset-to-caret g_txt cto

					caret-obj/caret: reduce [otc2 otc2/1]
					show g_win
				]
				alt-down [
				]
				key [
				]
			]
			none
		]
	]
]
