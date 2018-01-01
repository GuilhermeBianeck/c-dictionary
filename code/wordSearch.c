#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
   struct node *children[26];
   int lastWord;
};

struct node* createTrieNode(void){
    struct node *Node=(struct node*)malloc(sizeof(struct node));
    Node->lastWord=0;
    int i;
    for(i=0;i<26;i++){
      Node->children[i]=NULL;
    }
    return Node;
}


void insert(struct node * trie, char *word , int j){

    struct node *tempNode=trie;
    int i=0,idx;

    while(word[i]){
      idx=tolower(word[i])-'a';
      if(tempNode->children[idx] == NULL ){
        tempNode->children[idx]=createTrieNode();
      }
      tempNode=tempNode->children[idx];
      ++(i);
    }

    tempNode->lastWord=j;
}

int search(struct node *trie, char *word){

    struct node *tempNode=trie;
    if(trie==NULL || word==NULL) return 0;

    int i=0,idx;

    while(word[i]){
        idx=tolower(word[i])-'a';
        if(tempNode->children[idx] != NULL ){
           tempNode=tempNode->children[idx];
        }else{
           return 0;
        }
        ++i;
    }

    if(tempNode!=NULL && tempNode->lastWord>0) return tempNode->lastWord;
    else return -1;
}

FILE * insertMeaning(FILE *fp, char *meanings){
    char ch; int i=0;
    ch=fgetc(fp);
    while(ch!='\n'&&ch!=EOF){
        if(i<299){
            meanings[i++]=ch;
            //printf("%c",ch);
        }
        ch=fgetc(fp);
    }
    //printf("\n");
    meanings[i]='\0';
    return fp;
}

void getMeaning(char *word, int idx, char **meanings){
    printf("%s\n",meanings[idx]);

   ;
}

void dictionary(struct node *trie, char **meanings){
  char *word=(char*)malloc(26*sizeof(char));

   while(1){
        printf("Plz enter a word: ");
        scanf("%[^\n]s",word);
        getchar();
        int idx = search(trie,word);
        if(idx>0){
           printf("Meaning: ");
           getMeaning(word,idx-1, meanings);
        }else{
           printf("Sorry word not found\n");
        }
   }
}

int main(){

      struct node *trie=createTrieNode();

      FILE *fp;
      FILE *fp1;
      int i=0,j=0;
      fp = fopen("../FILESYSTEM/words.csv", "r");
      fp1 = fopen("../FILESYSTEM/meanings.csv", "r");

      char word[26];
      char **meanings=(char **)malloc(54556*sizeof(char*));

      char ch = fgetc(fp);

      for(i=0;i<54556;i++){
         meanings[i]=(char*)malloc(300*sizeof(char));
         fp1=insertMeaning(fp1,meanings[i]);
      }

      i=0; j=0;

      while (ch != EOF){

           if(ch!='\n'){
             word[i++]=ch;
           }else{
             word[i]='\0';
             i=0; ++j;
             insert(trie,word,j);
           }
           ch = fgetc(fp);
      }

      fclose(fp);
      fclose(fp1);

      dictionary(trie, meanings);
      return 0;

}

