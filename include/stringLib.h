#ifndef __STRINGLIB_H
#define __STRINGLIB_H

//함수 원형 
void ct_strcpy (char* dest, char* src);

//함수 작성 
void ct_strcpy (char* dest, char* src) { //문자열 길이 구하기 
	while (*src) {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

#endif

