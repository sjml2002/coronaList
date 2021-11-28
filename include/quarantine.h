#ifndef QUARANTINE_H
#define QUARANTINE_H

#include <malloc.h>
#include <stdio.h>
#include "./stringLib.h" 

typedef struct Quarantine {
	int ID;
	int vaccination; //0:미접종, 1:1차, 2:2차 후 14일 미경과, 3: 접종완료
	char vaccineName[20]; //백신 이름 
	struct Quarantine* nextQT;
} QT;



///// 함수 원형 /////
int QTlinkedListSize(QT* qt);
void QTpush(QT* qt, char* vaccineName, int vaccination);
void QTsearchView(QT* qt, int IPID);
int QTremove(QT* qt, int QID);
void QTremoveAll(QT* qt);


///// 함수 작성 /////
int QTlinkedListSize(QT* qt) {
	int size = 0;
	while(qt->nextQT != '\0') {
		qt = qt->nextQT;
		size++;
	}
	return size;
}

//밀접접촉자 추가 
void QTpush(QT* qt, char* vaccineName, int vaccination) {
	QT* tmp = qt; 
	if (vaccineName[0] == 'h') { //head init
		qt->ID = -1;
	}
	else { //정상 push
		int prevID = 0;
		while (tmp->nextQT != '\0') { //링크드 리스트의 맨 끝까지 이동
			prevID = tmp->ID;
			tmp = tmp->nextQT;
		}
		//값 할당 
		tmp->ID = prevID + 1;
		tmp->vaccination = vaccination;
		ct_strcpy(tmp->vaccineName, vaccineName);
	}
	//새로운 노드 메모리 할당 및 nextQT를 nullptr로 초기화
	QT* newNode = (QT*)malloc(sizeof(QT)); 
	newNode->nextQT = '\0';
	//현재 nextQT 값 할당
	tmp->nextQT = newNode;
}

//밀접접촉자 전체 검색 
void QTsearchView(QT* qt, int IPID) {
	const char* vacStr[4] = {
		"미접종", "1차접종", "2차접종 후 14일 미경과", "접종완료"
	};
	printf("\n---- 확진자ID: %d의 밀접접촉자 전체 검색 ----\n", IPID);
	while (qt->nextQT != 0) {
		if(qt->ID != -1) {
			printf("QID: %d\n", qt->ID);
			printf("백신이름: %s , %s\n", qt->vaccineName, vacStr[qt->vaccination]);
			printf("\n");
		}
		qt = qt->nextQT;
	}
	printf("---- 밀접접촉자 검색 종료 ----\n\n");
}

//밀접접촉자 1명 삭제
int QTremove(QT* qt, int QID) {
	QT* prevQT = qt; //이전 QT포인터 임시 저장
	qt = qt->nextQT; 
	while (qt->nextQT != 0) { 
		if (qt->ID == QID) {
			prevQT->nextQT = qt->nextQT;
			qt->nextQT = 0;
			free(qt);
			qt = 0;
			return 1;
		}
		prevQT = qt;
		qt = qt->nextQT;
	}
	return 0;
}

//밀접접촉자 전체 삭제 
void QTremoveAll(QT* qt) {
	if(qt->nextQT != 0) {
		QTremoveAll(qt->nextQT);
		qt->nextQT = 0;
	}
	free(qt);
	qt = 0;
}

#endif

