#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(char * input) {

int res = 0;
int i = 0;
while(input[i] != '\0') {
res = 31 * res + input[i];
i++;
}
return res;
}


int main(int argc, char **argv) {

char * c = malloc(sizeof(char)*20000);

strcpy(c, "https://mosfarr.ru/%d0%bf%d1%80%d1%8f%d0%bc%d0%b0%d1%8f-%d1%82%d1%80%d0%b0%d0%bd%d1%81%d0%bb%d1%8f%d1%86%d0%b8%d1%8f-%d1%87%d0%b8%d0%bf-%d0%bc%d0%be%d1%81%d0%ba%d0%b2%d1%8b-22-23-02-2020/");

int h = 0;

h = hash(c);

printf("%s\n",c);
printf("%d\n",h);


}
