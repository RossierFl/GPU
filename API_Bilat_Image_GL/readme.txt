0.0.1
cedric.bilat@he-arc.ch


Linux (gcc, intel)

	Compilation	:	required	.h
	Linkage		:	required	.so (shared lib)  .a (static lib)
	runtime		:	required	.so

Windows (vidual, intel)

	Compilation	:	required	.h, 
	Linkage		:	required	.lib (shared lib and static lib)
	runtime		:	required	.dll

Windows (mingw)
	
	Compilation	:	required	.h
	Linkage		:	required	.dll.a 
	runtime		:	required	.dll	(TODO same .dll as visual intel?)

Note

	(N1)	Ainsi pas de folder linux dans LIB pour les shared lib,mais il peut y en avoir pour des static lib
	
	(n2)	MinGW fonctionne sous windows mais avec politique gcc linux

TODO: freeglut lib, pas name juste : recompiler
TODO: Bilat_