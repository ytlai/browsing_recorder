/*
@author Yuting Lai
#(c)2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define TOTAL_PAGES_NUM 3
#define MAX_LINKS 100

#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BOLDWHITE   "\033[1m\033[37m"


/* hash table  */

typedef struct page_links{

	int data;
	struct hlist_node pnode;
		

}page_links;


//doubly link list to record the traverse of the page

typedef struct page_t{
	
	int data;
	struct list_head my_tlist;

}page_t;


enum {
	visit,prev,next,end

};

void traverse_plink(struct hlist_head *hl){
	

	page_links *pl;
	printf(GREEN "Next link options:\n" RESET);
 	hlist_for_each_entry(pl,hl,pnode){
		printf("page %d \n", pl->data);
	}

}


int add_page_t(page_t *head, page_t *pall, int i,int data){


	struct list_head mylist;
	
	INIT_LIST_HEAD(&mylist);	
	page_t new_page_t={data,mylist};
	
	pall[i] = new_page_t;

	
	list_add_tail(&(pall[i].my_tlist), &(head->my_tlist));
	

	show_page_t(&head->my_tlist,i);
	return 1;
	  	
}

int show_page_t(struct list_head *head, int i){

	page_t *pos;
	int j=0;	
	printf(YELLOW "Page Traverse : " RESET);
	list_for_each_entry(pos,head,my_tlist){
			
	 	printf("%d",pos->data);
		if ((j++)==i) break;
		printf(", ");
	}
	printf("\n");	
	  return 1;	
}

int replace_page_t(page_t entry){
	
	list_del(&entry.my_tlist);	
	
	return 1;

}
int input_handler(char input[10],int *op){

	char act[6];
	char spage[4];
	int i,space=0,base,flag=1,errcode,_act,_page;

	

	for(i=0;i<strlen(input);i++){
		

		if(input[i]=='\0'||input[i]=='\n') break;
		if(input[i]==' ') ++space;
		else {
			if (space<1) act[i]=input[i];
		
			else {
				if (flag){
					base=i;
					flag=0;				
				}
				spage[i-base]=input[i];

			}		
		}
		
	}

	if (space==0)
		base=i;
	act[base-space] = '\0';
	

	errcode=0;
	if(!strcmp(act,"visit")) _act=0;
	else if (!strcmp(act,"prev")) _act=1;
	else if (!strcmp(act,"next")) _act=2;
	else if (!strcmp(act,"end")) _act=3;
	else{
		if(strstr(act,"visit")||strstr(act,"prev")||strstr(act,"next")) errcode=1;
		else errcode=2;		
	}
	
	if(strlen(spage)){
		spage[i-base] = '\0';
		_page=atoi(spage);
	}
		
	else
		if(!strcmp(act,"visit")) errcode=3;
	
	
	op[0]=_act;
	op[1]=_page;
	
	return errcode;
	

}

