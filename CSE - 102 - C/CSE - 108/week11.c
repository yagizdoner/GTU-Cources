int readTable(char filename[], Score table[], int *tableSize){
    int i;
    FILE *ptr_myfile;;
    *tableSize = 0;

    ptr_myfile=fopen(filename,"rb");
    if (!ptr_myfile){
        return -1;
    }
    for ( i=0; ; i++){
        if(fread(&(table[i]),sizeof(Score),1,ptr_myfile) == 0)
            break;

        (*tableSize)++;
    }
    fclose(ptr_myfile);
    return 0;
}

int writeTable(char filename[], Score table[], int tableSize){
    int i;
    FILE *ptr_myfile;;

    ptr_myfile=fopen(filename,"wb");
    if (!ptr_myfile){
        return -1;
    }
    for ( i=0; i<tableSize; i++){
        fwrite(&(table[i]),sizeof(Score),1,ptr_myfile);
    }
    fclose(ptr_myfile);
    return 0;
}

void setRowValues(Score *row, char name[], int score){
    strcpy(row->name, name);
    row->score = score;
}

void setRow(Score *row1, Score row2){
    strcpy(row1->name, row2.name);
    row1->score = row2.score;
}

void swapRows(Score *row1, Score *row2){
    Score tmp;
    setRow(&tmp, *row1);
    setRow(row1, *row2);
    setRow(row2, tmp);
}


void insertRow(Score row, Score table[], int *tableSize){
    int i = 0;
    if(*tableSize < 10){
        setRow(&(table[*tableSize]), row);
        (*tableSize)++;
        for (i = *tableSize-1; i > 0; --i){
            if(table[i-1].score<table[i].score){
                swapRows(&(table[i-1]), &(table[i]));
            }   
        }
    }else{
        if(table[9].score<row.score){
            setRow(&(table[9]), row);
            for (i = *tableSize-1; i > 0; --i){
                if(table[i-1].score<table[i].score){
                    swapRows(&(table[i-1]), &(table[i]));
                }   
            }
        }
    }
}



void insertRowAndSave(char filename[], Score row){
    Score table[10];
    int tableSize = 0;


    readTable(filename, table, &tableSize);

    insertRow(row, table, &tableSize);

    writeTable(filename, table, tableSize);
}




void printTable(Score table[], int tableSize){
    int i = 0;
    for (i = 0; i < tableSize; ++i){
        printf("%s: %d\n",table[i].name, table[i].score);
    }
}


