#include <stdio.h>
#include "./include/hashTableArr.h"
#include "./include/stringLib.h"

void dataScan(int* gender, int *age, char region[50]) {
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
	IPinit(IPtable, 0, 2);
	char order;
	int IPpushIndex = 1;

	printf("[주문] 0: 프로그램 종료, 1: 확진자 추가, 2: 확진자 검색\n");
	while (1) {
		printf("[주문]: ");
		scanf("%c", &order);
		getchar(); //입력버퍼 비우기
		if (order == '0') { //프로그램 종료
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		else if (order == '1') {  // 데이터 추가
			int gender;
			int age;
			char region[50];
			
			dataScan(&gender, &age, region);
			//확진자를 추가할려는데
			//배열에 데이터가 꽉찼다면
			//배열의 크기를 늘림
			if (IPpushIndex >= IParrSize(IPtable)) {
				printf("%d\n", IParrSize(IPtable));
				tableSizeUP(IPtable, _msize(IPtable));
			}
			IPpush(&IPtable[IPpushIndex], IPpushIndex, gender, age, region);
			IPpushIndex++;			
		}
		else if (order == '2') { // 데이터 검색
			int searchIndex;
			printf("검색할 ID를 입력해주세요. (0 입력시 전체 검색이 됩니다.)\n");
			printf("ID: ");
			scanf("%d", &searchIndex);
			getchar(); //입력버퍼 지우기
			IPsearch(IPtable, searchIndex);
		}
		else {
			printf("다시 입력해주세요.\n");
		}
	}
	
	return 0;
}
