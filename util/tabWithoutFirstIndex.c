void tabWithoutFirstIndex(char *tab){
	int lenght = sizeof(tab)-1;
	char *tabWFI = malloc(lenght);
	
	for (i = 0 ; compteur < lenght ; compteur++)
	{
		tabWFI[i] = tab[i+1];
	}
}