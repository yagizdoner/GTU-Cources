
int isLowercase(char ch) {
	return (ch >= 'a' && ch <= 'z');
}


int isUppercase(char ch) {
	return (ch >= 'A' && ch <= 'Z');
}


int isLetter(char ch) {
	return (isLowercase(ch) || isUppercase(ch));
}


char uppercase(char lowercase) {
	if (!isLetter(lowercase))
		return 0;
	else if(!isLowercase(lowercase))
		return lowercase;
	else /* uppercase */
		return lowercase + 'A' - 'a';
}

void hist(char str[], int hist[ALPHABET]) {
	int i,ind;
	for (i = 0; i < ALPHABET; ++i)
		hist[i] = 0;

	while(*str) {
		ind = uppercase(*str++);
		if(!ind)
			hist[ALPHABET-1]++;
		else
			hist[ind-'A']++;
	}
}
