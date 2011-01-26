REBOL [
    Title: "Zlib"
]

switch/default system/version/4 [
	3 [ import %zlib-rxt.dll]
][	do make error! "Zlib extension is not done yet for your OS!"]
