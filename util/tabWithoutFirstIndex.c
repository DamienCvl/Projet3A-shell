char *tabWithoutFirstIndex(int length, char *tab[]){
	length--;
	char *tabWFI = malloc(sizeof(char) * length);
	for (int i = 0; i < length; i++) {
		tabWFI[i] = tab[i + 1];
	}
	return tabWFI;
}
