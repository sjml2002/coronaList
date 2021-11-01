#ifndef HASHTABLEARR_H
#define HASHTABLEARR_H

#include <malloc.h>
#include <stdio.h>
#include "./stringLib.h" 

typedef struct InfectedPerson {
	int ID;
	int gender; //0==남자, 1==여자
	int age;
	char region[50]; //지역
} IP;



///// 함수 원형 /////
int IParrSize(IP* ip);
void IPpush(IP* ip, int ID, int gender, int age, char* region);
void IPsearch(IP* ip, int ID);
void IPinit(IP* ip, int start, int end);
IP* tableSizeUP(IP* arr, int size);
IP* tableSizeDown(IP* arr, int size);



///// 함수 작성 /////
int IParrSize(IP* ip) {
	return _msize(ip) / sizeof(IP);
}

void IPinit(IP* ip, int start, int end) {
	while (start < end) {
		ip[start].ID = -1;
		start++;
	}
}

void IPpush(IP* ip, int ID, int gender, int age, char* region) {
	ip->ID = ID; 
	ip->gender = gender;
	ip->age = age;
	ct_strcpy(ip->region, region);
}

void IPsearch(IP* ip, int ID) {
	if (ID == 0) {
		printf("\n---- 확진자 전체 검색 ----\n");
		int size = IParrSize(ip);
		int i = 1;
		while (i < size) {
			printf("ID: %d\n", ip[i].ID);
			printf("gender: %d\n", ip[i].gender);
			printf("age: %d\n", ip[i].age);
			printf("region: %s\n", ip[i].region);
			if (ip[i].ID + 1 != ip[i+1].ID)
				break;
			printf("\n"); 
			i++;
		}
	}
	else {
		//선언이 아예 안된 경우거나 선언이 됐지만 데이터가 들어가지 않은경우 
		if(ip[ID].ID == -1 || ID < 0 || ID >= IParrSize(ip)){
			printf("\n확진자가 존재하지 않습니다.\n");
		}
		else {
			printf("\n---- 확진자 ID: %d 검색 ----\n", ip[ID].ID);
			printf("gender: %d\n", ip[ID].gender);
			printf("age: %d\n", ip[ID].age);
			printf("region: %s\n", ip[ID].region);
		}
	}
	printf("---- 확진자 검색 종료 ----\n\n");
}

IP* tableSizeUP(IP* arr, int size) {
	printf("\n 사이즈 증가 \n");
	free(arr);
	arr = '\0';
	arr = (IP*)malloc(size + (10 * sizeof(IP)));
	IPinit(arr, size, size + 10);
	return arr;
}

IP* tableSizeDown(IP* arr, int size) {
	free(arr);
	arr = '\0';
	arr = (IP*)malloc(size - (10 * sizeof(IP)));
	return arr;
}

#endif

