Part1

int readInt(){
    int ret = 0;
    scanf("%d", &ret);
    return ret;
}
double readDouble(){
    double ret = 0;
    scanf("%lf", &ret);
    return ret;
}
char readChar(){
    char ret;
    scanf(" %c", &ret);
    return ret;
}


Part2

/**************************** part 1 *****************************/
int readInt(){
    int ret = 0;
    scanf("%d", &ret);
    return ret;
}
double readDouble(){
    double ret = 0;
    scanf("%lf", &ret);
    return ret;
}
/**************************** part 2 *****************************/
double calculateBMI(int height, double weight){
    double BMI = 0;
    double heightM = 0;
    heightM = height/100.0;
    BMI = weight/(heightM*heightM);
    return BMI;
}
double getInfoAndCalculateBMI(){
    int height;
    double weight;
    height = readInt();
    weight = readDouble();
    return calculateBMI(height, weight);
}


Part3

/**************************** part 1 *****************************/
int readInt(){
    int ret = 0;
    scanf("%d", &ret);
    return ret;
}
double readDouble(){
    double ret = 0;
    scanf("%lf", &ret);
    return ret;
}
char readChar(){
    char ret;
    scanf(" %c", &ret);
    return ret;
}

/**************************** part 2 *****************************/
double calculateBMI(int height, double weight){
    double BMI = 0;
    double heightM = 0;
    heightM = height/100.0;
    BMI = weight/(heightM*heightM);
    return BMI;
}

/**************************** part 3 *****************************/
void printPersonalInfo(int id, char name, int height, double weight){
    printf("Id:%d\n", id);
    printf("Name:%c\n", name);
    printf("Height:%dcm\n", height);
    printf("Weight:%.2fkg\n", weight);
    printf("BMI:%.2f\n", calculateBMI(height, weight));
}

void getAndPrintPersonalInfo(){
    int id;
    char name;
    int height;
    double weight;
    id = readInt();
    name = readChar();
    height = readInt();
    weight = readDouble();
    printPersonalInfo(id, name, height, weight);
}
