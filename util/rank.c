#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_LEN 4096

int main(int ac, char *av[]) {
	FILE *fp;
	char buf[BUF_LEN+64], *s, *word, *num;
	int i, isfile;
	
	// check args
	if(ac != 1 && ac != 2) {
		fprintf(stderr, "Usage: %s filename\n", av[0]);
		return 1;
	}
	
	// open stream
	if(ac == 2) {
		fp = fopen(av[1], "rb");
		if(fp == NULL) {
			fprintf(stderr, "Cannot open file: %s\n", av[1]);
			return 2;
		}
		isfile = 1;
	} else {
		fp = stdin;
	}
	
	printf("rank      num word\n");
	printf("---- -------- -------\n");
	for(i=1;;i++) {
		if(fgets(buf, BUF_LEN, fp) == NULL) break;
		for(s=buf,word=num=NULL; *s; s++) {
			if(*s == '\t' || *s == ' ') {
				*s = 0;
				num = buf;
				word = s+1;
				break;
			}
		}
		if(word && num) {
			printf("%4d %8s %s", i, num, word);
		}
	}
	printf("---- -------- -------\n");
	
	// close file
	if(isfile) fclose(fp);
	
	return 0;
}
