# -*- MakeFile -*-

OUT_DIR = obj/


#target: dependencies
#	action

$(shell mkdir -p obj)

main: main.o resident.o preference.o dealer.o
	cc obj/main.o obj/resident.o obj/preference.o obj/dealer.o -o main.out

main.o: main.c
	cc -c main.c
	mv main.o $(OUT_DIR)

resident.o: resident.c
	cc -c resident.c
	mv resident.o $(OUT_DIR)

preference.o: preference.c
	cc -c preference.c
	mv preference.o $(OUT_DIR)

dealer.o: dealer.c
	cc -c dealer.c
	mv dealer.o $(OUT_DIR)
