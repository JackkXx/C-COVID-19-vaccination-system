#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define Max 100	
struct date{
	int year; //接种年份 
	int month;  //接种月份 
	int day;  //接种当日 
	char address[20];  //接种地址 
	int status;  //标识是否已接种 
}; 
struct covid{
	char name[10]; //姓名 
	char idCard[18];  //身份证号 
	char tel[11];  //电话号码 
	char address[20];  //地址 
	struct date first;  //第一针 
	struct date second;  //第二针 
};

typedef struct medical{
	int amount;  //已录入信息的总人数
    struct covid cov[Max]; 
}Medical;
 
void insert(Medical *index, int total);
void menu();
void seek(Medical *index);
void del(Medical *index);
void alter(Medical *index); 
void without(Medical *index);
void already(Medical *index);
void swap(int *p1, int *p2, int len); 
int judge(char idCard[], Medical *index);


void menu(){
	printf("-----------------欢迎来到新冠疫苗管理系统----------------\n\n");
	printf("               1.录入接种人信息\n");
	printf("               2.查找接种人信息\n");
	printf("               3.显示已经接种疫苗的人信息\n");
	printf("               4.显示未接种疫苗的人信息\n");
	printf("               5.修改接种人信息\n");
	printf("               6.删除接种人信息\n");
	printf("               0.退出系统\n\n");
	printf("----------------------------------------------------------\n\n");
	
}

/*
 录入接种人信息 
*/
void insert(Medical *index, int total){
	int i;
	int sit = index->amount;
	char confirm;
	char idCard[18];
	for(i = 1; i <= total; i++){
		printf("\n\n----------第%d个接种人信息-------------\n",i);
		printf("接种人姓名：");
		scanf("%s",index->cov[sit].name);
		while(1){
			printf("接种人身份证号：");
			fflush(stdin);
			scanf("%s",idCard); 
			if(judge(idCard, index)){
				printf("身份证已存在，请重新输入! \n");
			}else{
				strcpy(index->cov[sit].idCard,idCard);
				break;
			}
			
		}
		
		printf("接种人电话：");
		scanf("%s",index->cov[sit].tel);
		printf("接种人居住地址：");
		scanf("%s",index->cov[sit].address);
		printf("接种人是否接种了第一针(y/n)：");
		fflush(stdin); 
		scanf("%c",&confirm);
		if(confirm == 'y' || confirm == 'Y'){
			index->cov[sit].first.status = 1;
			printf("请输入接种时间（年、月、日），空格隔开输入：");
			scanf("%d%d%d",&index->cov[sit].first.year,&index->cov[sit].first.month,&index->cov[sit].first.day);
			printf("接种地址：");
			scanf("%s",index->cov[sit].first.address);
		}else{
			index->cov[sit].first.status = 0;
			index->cov[sit].second.status = 0;
			index->amount++;
			sit++;
			printf("第%d个接种人信息录入成功...\n",i);
			continue;
		}
		printf("接种人是否接种了第二针(y/n)：");
		fflush(stdin);  //刷新stain缓冲区 
		scanf("%c",&confirm);
		if(confirm == 'y' || confirm == 'Y'){
			index->cov[sit].second.status = 1;
			printf("请输入接种时间（年、月、日），空格隔开输入：");
			scanf("%d%d%d",&index->cov[sit].second.year,&index->cov[sit].second.month,&index->cov[sit].second.day);
			printf("接种地址：");
			fflush(stdin);
			gets(index->cov[sit].second.address);
		}else{
			index->cov[sit].second.status = 0;
		}
		printf("第%d个接种人信息录入成功...\n",i);
		index->amount++;
		sit++;
	}
	system("pause");
}

/*
 查找接种人信息 
*/
void seek(Medical *index){
	char name[10];
	printf("请输入接种人姓名：");
	scanf("%s",name);
	int i;
	for(i = 0; i < index->amount; i++){
		if(!strcmp(index->cov[i].name,name)){
			printf("接种人身份证号：%s\n",index->cov[i].idCard);
			printf("接种人电话号码：%s\n",index->cov[i].tel);
			printf("接种人地址：%s\n",index->cov[i].address);
			if(index->cov[i].first.status){
				printf("第一针疫苗受钟情况：已受种\n");
				printf("接种时间：%d年 %d月 %d日\n",index->cov[i].first.year,index->cov[i].first.month,index->cov[i].first.day);
				printf("接种地址：%s\n\n",index->cov[i].first.address); 
				if(index->cov[i].second.status){
					printf("第二针疫苗受钟情况：已受种\n");
					printf("接种时间：%d年 %d月 %d日\n",index->cov[i].first.year,index->cov[i].first.month,index->cov[i].first.day);
					printf("接种地址：%s\n\n",index->cov[i].second.address);
				}
				
				else
				printf("第二针疫苗受钟情况：未受种\n");
			}
            else{
            	printf("第一针疫苗受钟情况：未受种\n");
            	printf("第二针疫苗受钟情况：未受种\n");
			}
			break; 
		}
	} 
	if(i == index->amount)
	printf("未找到受种人信息.....\n");
}

/*
 删除接种人信息 
*/ 
void del(Medical *index){
	char name[10];
	printf("删除对应接种人的姓名：");
	scanf("%s",name);
	int i, sit, flag = 0;
	for(i = 0; i < index->amount; i++){
		if(!strcmp(index->cov[i].name,name)){
			sit = i;
			while(sit <= index->amount){
				index->cov[sit] = index->cov[sit+1];
				sit++;
			}
			index->amount--;
			flag = 1;
			break;
		}
	}
	if(flag){
		printf("删除成功!\n");
	}else{
		printf("删除失败！未找到该受种者信息.......\n");
	}
}

/*
 修改接种人信息 
*/
void alter(Medical *index){
	char name[10];
	char confirm;
	printf("请接种人的姓名：");
	scanf("%s",name);
	int i;
	for(i = 0; i < index->amount; i++){
		if(!strcmp(index->cov[i].name,name)){
		    printf("接种人姓名：");
			scanf("%s",index->cov[i].name);
			printf("接种人身份证号：");
			scanf("%s",index->cov[i].idCard); 
			printf("接种人电话：");
			scanf("%s",index->cov[i].tel);
			printf("接种人居住地址：");
			scanf("%s",index->cov[i].address);
			printf("接种人是否接种了第一针(y/n)：");
			fflush(stdin); 
			scanf("%c",&confirm);
			if(confirm == 'y' || confirm == 'Y'){
				index->cov[i].first.status = 1;
				printf("请输入接种时间（年、月、日），空格隔开输入：");
				scanf("%d%d%d",&index->cov[i].first.year,&index->cov[i].first.month,&index->cov[i].first.day);
				printf("接种地址：");
				scanf("%s",index->cov[i].first.address);
			}else{
				index->cov[i].first.status = 0;
				index->cov[i].second.status = 0;
				continue;
			}
			printf("接种人是否接种了第二针(y/n)：");
			fflush(stdin);  //刷新stain缓冲区 
			scanf("%c",&confirm);
			if(confirm == 'y' || confirm == 'Y'){
				index->cov[i].second.status = 1;
				printf("请输入接种时间（年、月、日），空格隔开输入：");
				scanf("%d%d%d",&index->cov[i].second.year,&index->cov[i].second.month,&index->cov[i].second.day);
				printf("接种地址：");
				fflush(stdin);
				gets(index->cov[i].second.address);
			}else{
				index->cov[i].second.status = 0;
			}
			printf("接种人信息修改成功...\n");
			break;
		}
	} 
	if(i == index->amount){
		printf("未找到受种者信息...\n\n");
	}
	system("pause");
}

/*
 显示所有未接种疫苗的人信息 
*/ 
void without(Medical *index){
	int i, flag = 0;
	printf("姓名\t身份证号\t电话\t居住地址\t接种情况\n");
	for(i = 0; i < index->amount; i++){
		if(index->cov[i].first.status == 0 && index->cov[i].second.status == 0){
			printf("%s\t%s\t\t%s\t\t%s\t两针都未接种\n",index->cov[i].name,index->cov[i].idCard,index->cov[i].tel,index->cov[i].address);
			flag = 1;
		}
	}
	if(!flag){
		printf("\n暂时没有未受种疫苗的人......\n"); 
	}
}


void swap(int *p1, int *p2, int len){
	int i, j;
	for(i = 0, j = 0 ; i < len; i++, j++){
		p1[i] = p1[i] ^ p2[j];
		p2[j] = p1[i] ^ p2[j];
		p1[i] = p1[i] ^ p2[j];
	}
}
/*
 显示所有已经接种疫苗的人 
*/ 
void already(Medical *index){
	int i, n, p, k, amount1 = 0, amount2 = 0;
	
	//统计第一针和第二针已经接种的人数 
	for(i = 0; i < index->amount; i++){
		if(index->cov[i].first.status){
			amount1++;
		}
		if(index->cov[i].second.status){
			amount2++;
		}	
	}
	
	if(amount1 == 0){
		printf("\n-------------------已经接种第一针的人----------------------\n"); 
		printf("\n  >> >> 没有接种第一针的人.......\n\n");
		return;
	}
	
	int deal[amount1][4], sit = 0;
	for(i = 0; i < index->amount; i++){
		if(index->cov[i].first.status){
			deal[sit][0] = i;
			deal[sit][1] = index->cov[i].first.year;
			deal[sit][2] = index->cov[i].first.month;
			deal[sit][3] = index->cov[i].first.day;
			sit++;
		}			
	}
	
	for(i = 0; i < amount1; i++){
		for(n = i + 1; n < amount1; n++){
			if(deal[i][1] > deal[n][1]){
				swap(deal[i],deal[n],4);
			}
			if(deal[i][1] == deal[n][1]){
				if(deal[i][2] > deal[n][2]){
					swap(deal[i],deal[n],4);
				}
				if(deal[i][2] == deal[n][2]){
					if(deal[i][3] > deal[n][3]){
						swap(deal[i],deal[n],4);
					} 
				}
			}
		}
	}
	printf("-------------------已经接种第一针的人----------------------\n"); 
	printf("姓名\t身份证号\t电话\t居住地址\t接种时间\n");
	for(i = 0; i < amount1; i++){
		n = deal[i][0];
		printf("%s\t%s\t\t%s\t\t%s\t%d年%d月%d日\n",index->cov[n].name,index->cov[n].idCard,index->cov[n].tel,index->cov[n].address,
		deal[i][1],deal[i][2],deal[i][3]);
		
	}
	
	if(amount2 == 0){
		printf("\n-------------------已经接种第二针的人----------------------\n"); 
		printf("\n  >> >> 没有接种第二针的人.......\n\n");
		return;
	}
	
	int deal2[amount2][4];
	sit = 0;
	for(i = 0; i < index->amount; i++){
		if(index->cov[i].second.status){
			deal2[sit][0] = i;
			deal2[sit][1] = index->cov[i].second.year;
			deal2[sit][2] = index->cov[i].second.month;
			deal2[sit][3] = index->cov[i].second.day;
			sit++;
		}
				
	}
	
	for(i = 0; i < amount2; i++){
		for(n = i + 1; n < amount2; n++){
			if(deal2[i][1] > deal2[n][1]){
				swap(deal2[i], deal2[n], 4);
			}
			if(deal2[i][1] == deal2[n][1]){
				if(deal2[i][2] > deal2[n][2]){
					swap(deal2[i],deal2[n],4);
				}
				if(deal2[i][2] == deal2[n][2]){
					if(deal2[i][3] > deal2[n][3]){
						swap(deal2[i],deal2[n],4);
					} 
				}
			}
		}
	}
	printf("\n-------------------已经接种第二针的人----------------------\n"); 
	printf("姓名\t身份证号\t电话\t居住地址\t接种时间\n");
	for(i = 0; i < amount2; i++){
		n = deal2[i][0];
		printf("%s\t%s\t\t%s\t\t%s\t%d年%d月%d日\n",index->cov[n].name,index->cov[n].idCard,index->cov[n].tel,index->cov[n].address,
		deal2[i][1],deal2[i][2],deal2[i][3]);
		
	}
	
} 

/*
	判断输入的身份证号是否重复
	如果重复，返回1；否则，返回0 
*/ 
int judge(char idCard[], Medical *index){
	int i;
	for(i = 0; i < index->amount; i++){
		if(!strcmp(index->cov[i].idCard,idCard)){
			return 1;
		}
	}
	return 0;
} 

int main(){
	Medical index;
	index.amount = 0; 
	while(1){
		int choose,total;
		menu();
		printf("请输入你的选择：");
		scanf("%d",&choose);
		switch(choose){
			case 1:
			    printf("请输入录入的人数：");
				scanf("%d",&total); 
				insert(&index,total);
				break;
			case 2:
			    if(index.amount == 0){
			    	printf("   >> 当前接种人信息为空......\n");
				}else{ 
					seek(&index);
				}
				printf("\n");
				system("pause");
				break;
			case 3:
				if(index.amount == 0){
			    	printf("   >> 当前接种人信息为空......\n");
				}else{ 
					already(&index);
				}
				printf("\n");
				system("pause");
				break;
			case 4:
				if(index.amount == 0){
			    	printf("   >> 当前接种人信息为空......\n");
				}else{ 
					without(&index);
				}
				printf("\n");
				system("pause");
				break;		
			case 5:
				alter(&index);
				break;
			case 6:
				if(index.amount == 0){
			    	printf("   >> 当前接种人信息为空......\n");
				}else{ 
					del(&index);
				}	
				system("pause");
				break; 
			case 0:
                 printf("欢迎下次使用！\n");
                 exit(0);	
		}
		system("cls");  //清屏 
	}
	
	return 0;
} 
