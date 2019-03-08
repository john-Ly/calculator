mode: exe

;;;;;;;;  compile flags
; flag: -Wall, -O3, -pg, -g
flag: -Wall, -O3, -g

; link phase
; link: m, pthread, stdc++
link: stdc++

; extral header file path(dir)
; inc: /usr/local/opt/jdk/include

; extral lib file path(dir)
; lib: /usr/local/opt/jdk/lib

;;;;;;;; tmp director for object files(just erase it when droping)
; int: objs/$(target)
int: objs

;;;;;;;; target binary
out: main

src: error.cpp, lexer.cpp, parser.cpp, table.cpp, main.cpp