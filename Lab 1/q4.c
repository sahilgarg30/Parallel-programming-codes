#include <stdio.h>
#include <string.h>
void main(){
	FILE *fopen(), *fa;
	int temp,ca, words=0, j=0, i=0;
	fa = fopen("in.txt","r"); 
	ca = getc(fa) ;
	char word[30][30];
	while ( ca != EOF ){
		if(ca == '\n' || ca == ' '){
			word[j++][i] = '\0';
			words += 1;
			i=0;
		}
		else
			word[j][i++] = ca;
		ca = getc(fa);
	}
	fclose(fa);
	char uniq[j][30];
	i = 0;
	int l, k=0;
	while(i<j){
		for(l=0;l<k;l++){
			if(strcmp(uniq[l],word[i]) == 0)
				break;
			else
				continue;
		}
		if(l == k)
			strcpy(uniq[k++],word[i]);
		i++;
	}	
	i=0;
	int freq[k];	
	for(l=0;l<k;l++)
	freq[l] = 0;
	for(i=0;i<j;i++){
		for(l=0;l<k;l++){
			if(strcmp(uniq[l],word[i]) == 0)
				freq[l]++;
		}	
	}
	int freq2[k];
	for(l=0;l<k;l++)
		freq2[l] = freq[l];
	for(i=0;i<k;i++){
		for(l=i;l<k-i-1;l++){
			if(freq[l] > freq[l+1]){
				temp = freq[l];
				freq[l] = freq[l+1];
				freq[l+1] = temp;
			}
		}
	}
	for(l=k-1;l>=0;l--){
		for(i=0;i<k;i++){	
			if(freq[l] == freq2[i]){
				printf("%s : %d\n",uniq[i],freq2[i]);
				freq2[i] = -99;
				break;
			}		
		}
	}
}

