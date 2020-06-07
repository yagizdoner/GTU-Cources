/* CSE - 108  WEEK - 1 */

int readInt()

{
	int intValue;
	scanf("%d", &intValue);
	return(intValue);
}

double readDouble()

{
	double doubleValue;
	scanf("%lf", &doubleValue);
	return(doubleValue);
}

char readChar()

{
	char charValue;
	scanf(" %c", &charValue);
	return(charValue);
}

double calculateBMI(int height, double weight)

{
	double BMI, m_height;

	m_height = height / 100.0;

	BMI = weight / (m_height * m_height);

	return(BMI);
}

void printPersonalInfo(int id, char name, int height, double weight)

{
	double BMI;

	BMI = calculateBMI(height, weight);

	printf("Id:%d\n", id);
	printf("Name:%c\n", name);
	printf("Height:%dcm\n", height);
	printf("Weight:%.2fkg\n", weight);
	printf("BMI:%.2f\n", BMI);
}

void getAndPrintPersonalInfo()

{
	int id, height;
	double weight;
	char name;

	id = readInt();
	name = readChar();
	height = readInt();
	weight = readDouble();

	printPersonalInfo(id, name, height, weight);
}

double getInfoAndCalculateBMI()

{
	int height;
	double weight, BMI;

	printf("Enter Your Height to be Integer (CM) : ");
	scanf("%d", &height);
	printf("Enter Your Weight to be a Double (KG) : ");
	scanf("%lf", &weight);

	BMI = calculateBMI(height, weight);

	return(BMI);
}
