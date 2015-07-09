/*
@author Yuting Lai
(c)2015
*/
#include "browsing.h" 

// all pages and associated links

struct hlist_head *hlink[TOTAL_PAGES_NUM];

HLIST_HEAD(A);
HLIST_HEAD(B);
HLIST_HEAD(C);
	
struct hlist_node hA1;
struct hlist_node hA2;
struct hlist_node hA3;
struct hlist_node hB1;
struct hlist_node hB2;
struct hlist_node hC1;


page_links pA1;
page_links pA2;
page_links pA3;
page_links pB1;
page_links pB2;
page_links pC1;


//implement hash table to store url links in each page

void pages_db_init(){
	


	pA1.data=0;
	pA1.pnode=hA1;
	pA2.data=1;
        pA2.pnode=hA2;
	pA3.data=2;
        pA3.pnode=hA3;
	pB1.data=0;
        pB1.pnode=hB1;
	pB2.data=2;
        pB2.pnode=hB2;
	pC1.data=0;
        pC1.pnode=hC1;
	

	INIT_HLIST_NODE(&pA1.pnode);
	INIT_HLIST_NODE(&pA2.pnode);
	INIT_HLIST_NODE(&pA3.pnode);
	INIT_HLIST_NODE(&pB1.pnode);
	INIT_HLIST_NODE(&pB2.pnode);
	INIT_HLIST_NODE(&pC1.pnode);
	
	hlist_add_head(&pA1.pnode,&A);
	hlist_add_head(&pB1.pnode,&B);
	hlist_add_head(&pC1.pnode,&C);
	
	hlist_add_after(&pA1.pnode,&pA2.pnode);	
	hlist_add_after(&pA2.pnode,&pA3.pnode);	
	hlist_add_after(&pB1.pnode,&pB2.pnode);	


	hlink[0] = &A;
	hlink[1] = &B;
	hlink[2] = &C;

	

}





int main(void){

	

	pages_db_init();
	
	

	struct list_head p0list = LIST_HEAD_INIT(p0list);
	INIT_LIST_HEAD(&p0list);	
	page_t p0={0,p0list};

	//allocate dlinklist
	page_t pall[MAX_LINKS];
	//page_t *pall= (page_t*)malloc(sizeof(page_t));
	pall[0] = p0;
	//printf("data is %d\n",pall[0].data);

	char input[6];
	int operation[2];
	int errcode;
	int stop = 0;
	int seq=0, real_len=0,j=0;	

	printf(BOLDWHITE "****Simple web page browsing history recoder***.\n" RESET "Action: \n " );
	printf("visit: Visit new page. Start with \"visit 0\" \n " );
	printf("prev: Visit previous record based on current page.\n ");
	printf("next: Visit next record based on current page.\n ");
	printf("end: Exit the program.\n");
	printf("Input action: ");
	
	while(!stop){
		
		
		fgets(input,9,stdin);

		
		errcode = input_handler(input,operation);
		
			
	
	
		if (!errcode){
			switch(operation[0]){
				
							
			case visit:
				//pall=realloc(pall,++seq);
				
				++seq;
				if(real_len>seq){
					for (j=seq;j<=real_len;j++)	
						replace_page_t(pall[j]);
				}
			
				add_page_t(&pall[0],pall,seq,operation[1]);
				real_len=seq;
				traverse_plink(hlink[operation[1]]);
				break;
			case prev:
			
				if (!seq){
					printf(RED "This is the first record\n" RESET);
					break;
				}					
				traverse_plink(hlink[pall[--seq].data]);
				show_page_t(&pall[0].my_tlist,seq);
				
				break;
			case next:
				if (seq==real_len){
					printf(RED "This is the last record\n" RESET);						
					break;
				}
				traverse_plink(hlink[pall[++seq].data]);
				show_page_t(&pall[0].my_tlist,seq);
				break;	
			case end:
				stop=1;
				break;
			
			

			default:
				printf("Todo sth\n");
				break;		
		
			}
		}
		else if (errcode==1)
			printf(CYAN"Use space between action and page. ex: visit 0\n" RESET);
		else if (errcode==2)
			printf(CYAN"Invalid action.\n" RESET);
		else if (errcode==3)
			printf(CYAN"page is need to complete visit action.\n" RESET);
		
		if(!stop)
			printf(BOLDWHITE "Input action: " RESET);
		else
			printf(YELLOW "Bye~\n" RESET);
		fflush(stdin);

		

	}		
	

	return 0;
}
