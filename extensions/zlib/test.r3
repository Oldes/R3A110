REBOL [
    Title: "Zlib"
]

import %zlib-rxt.dll

;bin-test #{78DAF348CDC9C90700058C01F5}
;bin-test next #{78DAF348CDC9C90700058C01F5}
;bin-test to-binary "hello"
;ask ""

probe zlib-compress to-binary "hello" 9

probe data: #{78DAF348CDC9C90700058C01F5}

probe length? data
probe to-string zlib-decompress data

probe data: insert data #{000000}
probe length? data
probe to-string zlib-decompress data



ask ""