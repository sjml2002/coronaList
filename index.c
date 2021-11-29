#include <stdio.h>
#include "./include/infected.h"
#include "./include/stringLib.h"
#include "./include/quarantine.h" 

//Ȯ���� �߰��� Ȯ���� ���� �Է� �Լ� 
void IPscan(int* gender, int *age, char region[50]) {
	printf("Ȯ������ ������ �Է����ּ���.\n");
	printf("gender (0:����, 1:����): ");
	scanf("%d", gender);
	getchar(); //�Է¹��� ����
	printf("age: ");
	scanf("%d", age);
	getchar(); //�Է¹��� ���� 
	printf("region: ");
	scanf("%[^\n]s", region); //���� �Է� ���� 
	getchar(); //�Է¹��� ����
}

//���������� �߰��� ���������� ���� �Է� �Լ�
int QTscan(IP* ip, int* IPID, char* vaccineName, int* vaccination) {
	printf("������������ ������ �Է����ּ���.\n");
	//Ȯ����ID �Է�
	int tmpIPID;
	printf("Ȯ����ID: ");
	scanf("%d", &tmpIPID);
	getchar();
	if (IPsearch(ip, tmpIPID)) { //Ȯ���ڰ� �����Ѵٸ� 
		*IPID = tmpIPID;
	}
	else {
		printf("Ȯ���ڰ� �������� �ʽ��ϴ�. �ٽ� �Է����ֽʽÿ�.\n");
		return 0;
	}
	printf("��� ���� ���� (0: ������, 1: 1������, 2: 2������ �� 14�� �̰��, 3: �����Ϸ�): ");
	scanf("%d", vaccination);
	getchar(); //�Է¹��� ����
	if (*vaccination != 0) {
		printf("��� �̸�: ");
		scanf("%s", vaccineName);
		getchar(); //�Է¹��� ���� 
	}
	return 1;
} 

///// ���� �Լ� ///// 
int main(int argc, char** argv) {
	IP* IPtable = (IP*)malloc(2 * sizeof(IP));
	IPinit(IPtable, 0, 2);
	char order;
	int IPpushIndex = 1;
	int descriptionView = 0;
	FILE *files;

	while (1) {
		if (descriptionView == 0) {
			printf("\n�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
			printf("[�ֹ�] 0: ���α׷� ����\n"); 
			printf("       1: Ȯ���� �߰�, 2: Ȯ���� �˻�, 3: Ȯ���� ����\n");
			printf("       4: ���������� �߰�, 5: ���������� �˻�, 6: ���������� ����\n");
			printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
		}
		printf("\n[�ֹ�]: ");
		scanf("%c", &order);
		getchar(); //�Է¹��� ����
		if (order == '0') { //���α׷� ����
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		else if (order == '1') {  // Ȯ���� �߰�
			int gender;
			int age;
			char region[50];
			int usr_cmd = -1;
			
			printf("�ܺ� �ؽ�Ʈ ���Ͽ��� �ҷ����ðڽ��ϱ�? (1 �Է½� �ҷ����� ����)");
			scanf("%d", &usr_cmd);
			getchar(); //�Է� ���� ���� 
			
			if(usr_cmd == 1){
				files = fopen("input.txt", "r"); //�Է¿� ���� �б���� �θ���
				int c = fgetc(files);
				if (c == EOF) {
					//file is empty
					printf("������ ����ֽ��ϴ�.\n");
				}
				else {
					ungetc(c, files);
					while(!feof(files)){
						fscanf(files, "%d\t%d\t%s\n", &gender, &age, &region);
						//feof�� ����������(files)�� ���� �����ѵ� �ѹ� �� �����
						//���� ���ۿ� �ִ� ���� fscanf�� �� 
						//if (feof(files)) break;
						//Ȯ���ڸ� �߰��ҷ��µ�
						//�迭�� ũ�Ⱑ �����ϸ� sizeup 
						if (IPpushIndex >= IParrSize(IPtable)) {
							IPtable = tableSizeUP(IPtable, IParrSize(IPtable));
							printf("�������\n");
						}
						IPpush(&IPtable[IPpushIndex], IPpushIndex, gender, age, region);
						IPpushIndex++;       
					}	
					fclose(files);
					printf("�ҷ����� �Ϸ�\n");
				}
			} else {
				IPscan(&gender, &age, region);
				//Ȯ���ڸ� �߰��ҷ��µ�
				//�迭�� ũ�Ⱑ �����ϸ� sizeup 
				if (IPpushIndex >= IParrSize(IPtable)) {
					IPtable = tableSizeUP(IPtable, IParrSize(IPtable));
					printf("�������\n");
				}
				IPpush(&IPtable[IPpushIndex], IPpushIndex, gender, age, region);
				IPpushIndex++;
			}
			
		}
		else if (order == '2') { // Ȯ���� �˻�
			int searchIndex;
			printf("�˻��� ID�� �Է����ּ���. (0 �Է½� ��ü �˻�, -1 �Է½� ��ü ��� ��������): ");
			scanf("%d", &searchIndex);
			getchar(); //�Է¹��� �����
			IPsearchView(IPtable, searchIndex, files);
		}
		else if (order == '3') {
			int IPID;
			printf("������ Ȯ������ ID: ");
			scanf("%d", &IPID);
			getchar();
			if (IPsearch(IPtable, IPID)) {
				IPremove(IPtable, IPID);
				//IPpushIndex--;
				printf("Ȯ���� ���� �Ϸ�\n");
			}
			else
				printf("Ȯ���ڰ� �������� �ʽ��ϴ�. �ٽ� �Է����ֽʽÿ�.\n");
		}
		else if (order == '4') { //���������� �߰�
			int IPID; //��� Ȯ������ �������������� 
			char vaccineName[20] = "����";
			int vaccination;
			int scanRes = QTscan(IPtable, &IPID, vaccineName, &vaccination);
			if (scanRes) {
				//��ũ�帮��Ʈ�� �߰��Ҷ����� �ϳ��� ����� �÷���
				QTpush(IPtable[IPID].qurantineList, vaccineName, vaccination);
			}
		}
		else if (order == '5') { //���������� �˻�
			//���������ڴ� ��ü �˻����� ����
			int inputID;
			printf("���������ڸ� �˻��Ϸ��� Ȯ����ID �Է�: ");
			scanf("%d", &inputID);
			getchar();
			if (IPsearch(IPtable, inputID)) { //Ȯ���ڰ� �����Ѵٸ� 
				QTsearchView(IPtable[inputID].qurantineList, inputID);
			}
			else {
				printf("Ȯ���ڰ� �������� �ʽ��ϴ�. �ٽ� �Է����ֽʽÿ�.\n");
			}
		}
		else if (order == '6') { //���������� ���� 
			int IPID;
			int QID;
			printf("Ȯ����ID: ");
			scanf("%d", &IPID);
			getchar();
			if (IPsearch(IPtable, IPID)) {
				printf("����������ID: ");
				scanf("%d", &QID);
				getchar();
				if (QTremove(IPtable[IPID].qurantineList, QID))
					printf("���������� ������ �Ϸ�Ǿ����ϴ�.\n");
				else
					printf("���������ڰ� �������� �ʽ��ϴ�.\n");
			}
			else
				printf("Ȯ���ڰ� �������� �ʽ��ϴ�. �ٽ� �Է����ֽʽÿ�.\n");
		}
		else { 
			printf("�ٽ� �Է����ּ���.\n");
		}
		
		if (descriptionView == 4)
			descriptionView = 0;
		else
			descriptionView++;
	}
	
	return 0;
}

