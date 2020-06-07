void addIlce(nufus *nuf, char* line) {
	sscanf(line,"%s %s %d",nuf->ilceler[nuf->count].isim,nuf->ilceler[nuf->count].il,&nuf->ilceler[nuf->count].nufus);
	++nuf->count;
}


void swapIlce(ilce *i1, ilce *i2) {
	ilce temp;
	memcpy(&temp,i1,sizeof(ilce));
	memcpy(i1,i2,sizeof(ilce));
	memcpy(i2,&temp,sizeof(ilce));
}

int comp(ilce i1,ilce i2, sortby sort, order ord) {
	int cmp;
	switch(sort) {
		case NUFUS:
			cmp = ord == ASC ? i1.nufus < i2.nufus : i1.nufus > i2.nufus;
			break;
		case IL:
			cmp = strcmp(i1.il,i2.il);
			if(cmp != 0) {
				cmp = ord == ASC ? cmp < 0 : cmp > 0;
				break;
			} /* continue to sort by isim for same ils */
		case ISIM:
		default:
			cmp = strcmp(i1.isim,i2.isim);
			if(cmp != 0) {
				cmp = strcmp(i1.il,i2.il);
			} /* continue to sort by isim for same ils */
			cmp = ord == ASC ? cmp < 0 : cmp > 0;
			break;
	}
	return cmp;
}

void printSorted(nufus nuf, sortby sort, order ord) {
	int i,j,k,cmp;
	for (i = 0; i < nuf.count; ++i) {
		k = i;
		for (j = i+1; j < nuf.count; ++j) {
			cmp = comp(nuf.ilceler[j],nuf.ilceler[k],sort, ord);
			if(cmp)
				k = j;
		}
		swapIlce(&nuf.ilceler[i],&nuf.ilceler[k]);
	}
	printNufus(nuf);
}

int getIlNufus(nufus nuf, char* il) {
	int i,ilnufus = 0;
	for (i = 0; i < nuf.count; ++i)
		if(strcmp(nuf.ilceler[i].il, il) == 0)
			ilnufus += nuf.ilceler[i].nufus;
	return ilnufus;
}

char* mostCrowdedCity(nufus nuf, iller* sehirler) {
	int i, nufus, maxNufus = -999;
	char* mostFragmented = 0;
	for (i = 0; i < ILSAYISI; ++i) {
		nufus = getIlNufus(nuf,sehirler->isim[i]);
		if(maxNufus < nufus) {
			maxNufus = nufus;
			mostFragmented = sehirler->isim[i];
		}
	}
	return mostFragmented;
}

char* mostFragmentedCity(nufus nuf, iller* sehirler) {
	int i,j, ilceSayisi, maxIlceSayisi = -999;
	char* mostFragmented = 0;
	for (i = 0; i < ILSAYISI; ++i) {
		ilceSayisi = 0;
		for (j = 0; j < nuf.count; ++j) {
			if(strcmp(sehirler->isim[i],nuf.ilceler[j].il) == 0) {
				++ilceSayisi;
				if(maxIlceSayisi < ilceSayisi) {
					maxIlceSayisi = ilceSayisi;
					mostFragmented = sehirler->isim[i];
				}
			}
		}
	}
	return mostFragmented;
}


void constructIller(nufus nuf, iller *sehirler) {
	int i,j, ind = 0;
	for (i = 0; i < nuf.count; ++i) {
		for(j = 0; j < ILSAYISI; ++j) {
			if(strcmp(nuf.ilceler[i].il,sehirler->isim[j]) == 0) {
				break;
			}
		}
		if(j == ILSAYISI) /* not found */
			strcpy(sehirler->isim[ind++], nuf.ilceler[i].il);
	}
}
