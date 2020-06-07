char* interleave(char str1[], char str2[], char res[]) {
	int i=0;
	char *s1 = str1, *s2 = str2;
	while(*s1 || *s2) {
		if(!(*s1) && *s2) {
			/* if str1 has ended and str2 has not, continue until str2 ends */
			while((res[i++] = *s2++));
		} else if(!(*s2) && *s1) {
			/* if str2 has ended and str1 has not, continue until str1 ends */
			while((res[i++] = *s1++));
		} else {
			/* either strings has not ended */
			if(i%2) /* alternate the string */
				res[i++] = *s2++;
			else
				res[i++] = *s1++;
		}
	}
	res[i]='\0';
	return res;
}
