#include <stdio.h>
#include "./include/hashTableArr.h"
#include "./include/stringLib.h"

void tmpScan(int* gender, int *age, char region[50]) {
	printf("확진자의 정보를 입력해주세요.\n");
	printf("gender: ");
	scanf("%d", gender);
	getchar(); //입력버퍼 비우기
	printf("age: ");
	scanf("%d", age);
	getchar(); //입력버퍼 비우기 
	printf("region: ");
	scanf("%s", region);
	getchar(); //입력버퍼 비우기
}

int main(int argc, char** argv) {
	IP* IPtable = (IP*)malloc(2 * sizeof(IP));
	int gender;
	int age;
	char region[50];
	
	int index = 1;
	while (index < 5) {
		printf("%d: ", index);
		tmpScan(&gender, &age, region);
		//확진자를 추가할려는데
		//배열에 데이터가 꽉찼다면
		//배열의 크기를 늘림
		if (index >= IParrSize(IPtable)) {
			tableSizeUP(IPtable, _msize(IPtable));
		}
		IPpush(&IPtable[index], index, gender, age, region);
		IPsearch(IPtable, index);
		index++;
	}
	IPsearch(IPtable, -1); //전체 검색 
	
	return 0;
}
