#include "cachelab.h"
#include <stdio.h>
#include <getopt.h>
#include <math.h>
#include <stdlib.h>

#define BIT_LENGTH 64

typedef struct {
	short int visual;

	int s;
	int b;
	long long S;
	int E;
	long long B;

	int hit;
	int evict;
	int miss;

} simulatorProperty;

typedef struct {
	short int valid;
	unsigned long long tag;
	char* blocks;
	int recentUsed;
} cacheLine;

typedef struct {
	cacheLine* lines;
} cacheSet;

typedef struct {
	cacheSet* sets;
} cache;

cache initialize(simulatorProperty property) {
	//initializing new cache
	cache tmp;
	tmp.sets = (cacheSet *) malloc(sizeof(cacheSet) * property.S);
	for(int i = 0; i < property.S; i++){ 
		//initializing new set
		cacheSet tmpSet;
		tmpSet.lines = (cacheLine *) malloc(sizeof(cacheLine) * property.E);
		for(int j = 0; j < property.E; j++){
			//initializing new line
			cacheLine tmpLine;
			tmpLine.valid = 0;
			tmpLine.tag = 0;
			tmpLine.blocks = (char *) malloc(sizeof(char) * property.B);
			tmpLine.recentUsed = 0;
			tmpSet.lines[j] = tmpLine;	//new line on lines[j]
		}
		tmp.sets[i] = tmpSet;	//new set on sets[i]
	}
	return tmp;
}

simulatorProperty resetCounter(simulatorProperty property) {
	property.hit = 0;
	property.miss = 0;
	property.evict = 0;
	return property;
}

simulatorProperty accessLine(cacheSet current, unsigned long long tag, simulatorProperty property){
	int found = 0;
	int empty = -1;
	int max = 0;
	for(int i = 0; i < property.E; i++){
		if(current.lines[i].valid == 1){
			current.lines[i].recentUsed += 1;
			if(current.lines[i].tag == tag){
				found = 1;
				current.lines[i].recentUsed = 0;
			}
			if(current.lines[i].recentUsed > current.lines[max].recentUsed){
				max = i;
			}
		}
		else {
			empty = i;
		}
	}
	if(found){
		property.hit++;
		if(property.visual)	printf(" hit");
		return property;
	}
	else {
		property.miss++;
		if(property.visual)	printf(" miss");
		if(empty < 0){
			property.evict++;
			if(property.visual)	printf(" eviction");
			current.lines[max].recentUsed = 0;
			current.lines[max].tag = tag;
		}
		else {
			current.lines[empty].tag = tag;
			current.lines[empty].valid = 1;
			current.lines[empty].recentUsed = 0;
		}
		return property;
	}

}//accessing line

simulatorProperty access(cache current, unsigned long long address, simulatorProperty property){
	unsigned long long set;
	unsigned long long tag;
	tag = address >> (property.s + property.b);
	set = address << (BIT_LENGTH - property.s - property.b);
	set = set >> (BIT_LENGTH - property.s);
	cacheSet currentSet = current.sets[set];
	return accessLine(currentSet, tag, property);
}//search appropriate set to search.


int main(int argc, char** argv)
{
	simulatorProperty property;
	cache myCache;
	char* trace;
	char input;

	FILE* trace_input;
	char instructionType;
	unsigned long long address;
	int size;

	property.visual = 0;

	while((input = getopt(argc, argv, "s:E:b:t:vh")) != -1){
		switch(input){
			case 's':
				property.s = atoi(optarg);
				property.S = pow(2.0, property.s);
				break;
			case 'E':
				property.E = atoi(optarg);
				break;
			case 'b':
				property.b = atoi(optarg);
				property.B = pow(2.0, property.b);
				break;
			case 'v':
				property.visual = 1;
				break;
			case 't':
				trace = optarg;
				break;
			case 'h':
				exit(0);
			default:
				exit(-1);
		}
	}
	
	myCache = initialize(property);
	property = resetCounter(property);

	trace_input = fopen(trace, "r");
	if(trace_input != NULL){
		while(fscanf(trace_input, " %c %llx, %d", &instructionType, &address, &size) == 3){
			switch(instructionType){
				case 'L':
				case 'S':
					if(property.visual) printf("%c %llx,%d", instructionType, address, size);
					property = access(myCache, address, property);
					if(property.visual) printf("\n");
					break;
				case 'M':
					if(property.visual) printf("%c %llx,%d", instructionType, address, size);
					property = access(myCache, address, property);
					property = access(myCache, address, property);
					if(property.visual) printf("\n");
					break;
				case 'I':
				default:
					break;
			}
		}
	}

	printSummary(property.hit, property.miss, property.evict);
	
    return 0;
}
