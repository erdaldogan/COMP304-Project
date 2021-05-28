# -*- MakeFile -*-

#target: dependencies
#	action

main: main.o resident.o preference.o dealer.o
	cc obj/main.o obj/resident.o obj/preference.o obj/dealer.o -o main.out

main.o: main.c
	cc -c main.c
	mv main.o obj/

resident.o: resident.c
	cc -c resident.c
	mv resident.o obj/

preference.o: preference.c
	cc -c preference.c
	mv preference.o obj/

dealer.o: dealer.c
	cc -c dealer.c
	mv dealer.o obj/
