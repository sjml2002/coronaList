#include <stdio.h>
#include "./include/infected.h"
#include "./include/stringLib.h"
#include "./include/quarantine.h" 

//확진자 추가시 확진자 정보 입력 함수 
void IPscan(int* gender, int *age, char region[50]) {
	printf("확진자의 정보를 입력해주세요.\n");
	printf("gender (0:남자, 1:여자): ");
	scanf("%d", gender);
	getchar(); //입력버퍼 비우기
	printf("age: ");
	scanf("%d", age);
	getchar(); //입력버퍼 비우기 
	printf("region: ");
	scanf("%[^\n]s", region); //공백 입력 가능 
	getchar(); //입력버퍼 비우기
}

//밀접접촉자 추가시 밀접접촉자 정보 입력 함수
int QTscan(IP* ip, int* IPID, char* vaccineName, int* vaccination) {
	printf("밀접접촉자의 정보를 입력해주세요.\n");
	//확진자ID 입력
	int tmpIPID;
	printf("확진자ID: ");
	scanf("%d", &tmpIPID);
	getchar();
	if (IPsearch(ip, tmpIPID)) { //확진자가 존재한다면 
		*IPID = tmpIPID;
	}
	else {
		printf("확진자가 존재하지 않습니다. 다시 입력해주십시오.\n");
		return 0;
	}
	printf("백신 접종 여부 (0: 미접종, 1: 1차접종, 2: 2차접종 후 14일 미경과, 3: 접종완료): ");
	scanf("%d", vaccination);
	getchar(); //입력버퍼 비우기
	if (*vaccination != 0) {
		printf("백신 이름: ");
		scanf("%s", vaccineName);
		getchar(); //입력버퍼 비우기 
	}
	return 1;
} 

///// 메인 함수 ///// 
int main(int argc, char** argv) {
	IP* IPtable = (IP*)malloc(2 * sizeof(IP));
	IPinit(IPtable, 0, 2);
	char order;
	int IPpushIndex = 1;
	int descriptionView = 0;
	FILE *files;

	while (1) {
		if (descriptionView == 0) {
			printf("\nㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
			printf("[주문] 0: 프로그램 종료\n"); 
			printf("       1: 확진자 추가, 2: 확진자 검색, 3: 확진자 삭제\n");
			printf("       4: 밀접접촉자 추가, 5: 밀접접촉자 검색, 6: 밀접접촉자 삭제\n");
			printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
		}
		printf("\n[주문]: ");
		scanf("%c", &order);
		getchar(); //입력버퍼 비우기
		if (order == '0') { //프로그램 종료
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		else if (order == '1') {  // 확진자 추가
			int gender;
			int age;
			char region[50];
			int usr_cmd = -1;
			
			printf("외부 텍스트 파일에서 불러오시겠습니까? (1 입력시 불러오기 진행)");
			scanf("%d", &usr_cmd);
			getchar(); //입력 버퍼 제거 
			
			if(usr_cmd == 1){
				files = fopen("input.txt", "r"); //입력용 파일 읽기모드로 부르기 
				while( !feof(files) ){
					fscanf(files, "%d\t%d\t%s\n", &gender, &age, &region);
					//확진자를 추가할려는데
					//배열의 크기가 부족하면 sizeup 
					if (IPpushIndex >= IParrSize(IPtable)) {
						IPtable = tableSizeUP(IPtable, IParrSize(IPtable));
						printf("사이즈업\n");
					}
					IPpush(&IPtable[IPpushIndex], IPpushIndex, gender, age, region);
					IPpushIndex++;       
				}	
				fclose(files);
				printf("불러오기 완료\n");
			} else {
				IPscan(&gender, &age, region);
				//확진자를 추가할려는데
				//배열의 크기가 부족하면 sizeup 
				if (IPpushIndex >= IParrSize(IPtable)) {
					IPtable = tableSizeUP(IPtable, IParrSize(IPtable));
					printf("사이즈업\n");
				}
				IPpush(&IPtable[IPpushIndex], IPpushIndex, gender, age, region);
				IPpushIndex++;
			}
			
		}
		else if (order == '2') { // 확진자 검색
			int searchIndex;
			printf("검색할 ID를 입력해주세요. (0 입력시 전체 검색, -1 입력시 전체 명단 내보내기): ");
			scanf("%d", &searchIndex);
			getchar(); //입력버퍼 지우기
			IPsearchView(IPtable, searchIndex, files);
		}
		else if (order == '3') {
			int IPID;
			printf("삭제할 확진자의 ID: ");
			scanf("%d", &IPID);
			getchar();
			if (IPsearch(IPtable, IPID)) {
				IPremove(IPtable, IPID);
				//IPpushIndex--;
				printf("확진자 삭제 완료\n");
			}
			else
				printf("확진자가 존재하지 않습니다. 다시 입력해주십시오.\n");
		}
		else if (order == '4') { //밀접접촉자 추가
			int IPID; //어느 확진자의 밀접접촉자인지 
			char vaccineName[20] = "없음";
			int vaccination;
			int scanRes = QTscan(IPtable, &IPID, vaccineName, &vaccination);
			if (scanRes) {
				//링크드리스트는 추가할때마다 하나씩 사이즈를 늘려감
				QTpush(IPtable[IPID].qurantineList, vaccineName, vaccination);
			}
		}
		else if (order == '5') { //밀접접촉자 검색
			//밀접접촉자는 전체 검색으로 구현
			int inputID;
			printf("밀접접촉자를 검색하려는 확진자ID 입력: ");
			scanf("%d", &inputID);
			getchar();
			if (IPsearch(IPtable, inputID)) { //확진자가 존재한다면 
				QTsearchView(IPtable[inputID].qurantineList, inputID);
			}
			else {
				printf("확진자가 존재하지 않습니다. 다시 입력해주십시오.\n");
			}
		}
		else if (order == '6') { //밀접접촉자 삭제 
			int IPID;
			int QID;
			printf("확진자ID: ");
			scanf("%d", &IPID);
			getchar();
			if (IPsearch(IPtable, IPID)) {
				printf("밀접접촉자ID: ");
				scanf("%d", &QID);
				getchar();
				if (QTremove(IPtable[IPID].qurantineList, QID))
					printf("밀접접촉자 삭제가 완료되었습니다.\n");
				else
					printf("밀접접촉자가 존재하지 않습니다.\n");
			}
			else
				printf("확진자가 존재하지 않습니다. 다시 입력해주십시오.\n");
		}
		else { 
			printf("다시 입력해주세요.\n");
		}
		
		if (descriptionView == 4)
			descriptionView = 0;
		else
			descriptionView++;
	}
	
	return 0;
}
