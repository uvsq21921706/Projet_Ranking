
partie1 : PG
	./PG.exe 
		
PG : main1.o 
	gcc -o PG.exe main1.o -Wall

main1.o : page_rank.o main_page_rank.c 
	gcc main_page_rank.c  -c -o main1.o -Wall
	
page_rank.o : page_rank.h 
	gcc page_rank.c -c -o page_rank.o -Wall
	
clean : 
	rm *.o
	rm -f PG.exe
	rm -f PG 