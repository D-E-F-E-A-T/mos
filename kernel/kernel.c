
// int puts(char *s)
// {
// 	char *video = 0xB8000;

// 	int i, j;

// 	for (i = 0, j = 0; s[i]; i++, j += 2)
// 		video[j] = s[i];
// }
#include "drivers/screen.h"

int main()
{
	char msg[] = "\nOooh-oooh\nEverybody′s got something\nThey had to leave behind\nOne regret from yesterday\nThat just seems to grow with time\nThere′s no use looking back or wondering\n(Or wondering)\nHow it could be now or might have been\n(Or might have been)\nAll this I know but still I can′t find ways\nTo let you go\n \nI never had a dream come true\n′Til the day that I found you\nEven though I pretend that I′ve moved on\nYou′ll always be my baby\nI never found the words to say\nYou′re the one I think about each day\nAnd I know no matter where life takes me to\nA part of me will always be with you, yeah\n \nSomewhere in my memory\nI′ve lost all sense of time (ah-ha, ha-ha)\nAnd tommorow can never be\n′Cos yesterday is all that fills my mind\nThere′s no use looking back or wondering\n(Wondering)\nHow it should be now or might have been\n(Or might have been)\nAll this I know but still I can′t find ways\nTo let you go\n \nI never had a dream come true\n′Til the day that I found you\nEven though I pretend that I′ve moved on\nYou′ll always be my baby\nI never found the words to say\nYou′re the one I think about each day\nAnd I know no matter where life takes me to\nA part of me will always be\nYou′ll always be the dream that fills my head\nYes you will, say you will\nYou know you will, oh baby\nYou′ll always be the one I know I′ll never forget\nIt′s no use looking back or wondering\n(Or wondering)\nBecause love is a strange and funny thing\n(And funny thing)\nNo matter how I try and try\nI just can′t say goodbye, no, no, no, no\n \nI never had a dream come true\n′Til the day that I found you\nEven though I pretend that I′ve moved on\nYou′ll always be my baby\n\I never found the words\n(Never found the words to say) to say\nYou′re the one I think about each day (each day)\nAnd I know no matter where life takes me to\nA part of me will always be\nA part of me will always be with you, ooh";

	clear_screen();
	puts(msg);
	
	return 0;
}

