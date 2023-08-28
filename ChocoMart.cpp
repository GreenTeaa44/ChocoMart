#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

struct data{
	char ID[101];
	char brand[101];
	int weight;
	char type[101];
	float price;	
	int height;
	
	struct data* left;
	struct data* right;
};

struct data* create(char ID[],char brand[],int weight,char type[],float price){
	struct data* curr = (struct data*)malloc(sizeof(data));
	strcpy(curr->ID,ID);
	strcpy(curr->brand,brand);
	curr->weight = weight;
	strcpy(curr->type,type);
	curr->price=price;
	
	curr->left=curr->right=NULL;
	curr->height=1;
	
	
	return curr;
}

int max(int a,int b){
	if(a>b) return a;
	return b;
}

int getHeight(struct data* temp){
	if(temp==NULL){
		return 0;
	}
	else{
		return getHeight(temp->left) - getHeight(temp->right);
	}
}

data* rightRotate(data* temp){
	data* x = temp->left;
	data* y = x->right;
	
	x->right = temp;
	temp->left = y;
	
	temp->height = max(getHeight(temp->left),getHeight(temp->right))+1;
	x->height = max(getHeight(x->left),getHeight(x->right))+1; 
	
	return x;
}

data* leftRotate(data* temp){
	data* x = temp->right;
	data* y = x->left;
	
	x->left = temp;
	temp->right = y;
	
	temp->height = max(getHeight(temp->left),getHeight(temp->right))+1;
	x->height = max(getHeight(x->left),getHeight(x->right))+1; 
	
	return x;
}

struct data* insert(struct data* root,char ID[],char brand[],int weight,char type[],float price){
	if(root==NULL){
		return create(ID,brand,weight,type,price);
	}
	if(strcmp(ID,root->ID)<0){
		root->left = insert(root->left,ID,brand,weight,type,price);
	}
	else{
		root->right= insert(root->left,ID,brand,weight,type,price);
	}
	if(root==NULL){
		return root;
	}
	
	root->height = max(getHeight(root->left),getHeight(root->right))+1;
	
	int balance = getHeight(root);
	
	if(balance>1 && strcmp(ID,root->left->ID)<0){
		return rightRotate(root);
	}
	if(balance>1 && strcmp(ID,root->left->ID)>0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if(balance>1 && strcmp(ID,root->right->ID)<0){
		return leftRotate(root);
	}
	if(balance>1 && strcmp(ID,root->right->ID)>0){
		root->left = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

void viewInOrder(data* temp){
	if(temp!=NULL){
		viewInOrder(temp->left);
		printf("|  %-7s|  %-8s   |   %-4d    |   %-6s   |  $%-10.2f  |\n"
		,temp->ID,temp->brand,temp->weight,temp->type,temp->price);
		viewInOrder(temp->right);
	}
}

void viewPreOrder(data* temp){
	if(temp!=NULL){
		printf("|  %-7s|  %-8s   |   %-4d    |   %-6s   |  $%-10.2f  |\n"
		,temp->ID,temp->brand,temp->weight,temp->type,temp->price);
		viewPreOrder(temp->left);
		viewPreOrder(temp->right);
	}
}

void viewPostOrder(data* temp){
	if(temp!=NULL){
		viewPostOrder(temp->left);
		viewPostOrder(temp->right);
		printf("|  %-7s|  %-8s   |   %-4d    |   %-6s   |  $%-10.2f  |\n"
		,temp->ID,temp->brand,temp->weight,temp->type,temp->price);
	}
}

data *search(data* root, char ID[]){
	if(root==NULL){
		return NULL;
	}
	if(strcmp(ID,root->ID)==0){
		return root;
	}
	if(strcmp(ID,root->ID)==0){
		search(root->left,ID);
	}
	else{
		search(root->right,ID);	
	}
}

data* remove(data* root, char ID[]){
	if(root==NULL){
		return NULL;
	}
	if(strcmp(ID,root->ID)<0){
		root->left=remove(root->right,ID);
	}
	else if(strcmp(ID,root->ID)>0){
		root->right=remove(root->right,ID);
	}
	else{
		if(root->left==NULL && root->right==NULL){
			free(root);
			root=NULL;
		}
		else if(root->left!=NULL && root->right==NULL){
			data *temp= root->left;
			*root = *temp;
			free(temp);
			temp=NULL;
		}
		else if(root->left==NULL && root->right!=NULL){
			data*temp = root->left;
			while(temp->right!=NULL){
				temp=temp->right;
			}
			strcpy(root->brand,temp->brand);
			strcpy(root->ID,temp->ID);
			strcpy(root->type,temp->type);
			root->height=temp->height;
			root->weight=temp->weight;
			
			root->left = remove(root->left,temp->ID);
		}
	}
	if(root==NULL){
		return root;
	}
	
	root->height = max(getHeight(root->left),getHeight(root->right))+1;
	
	int balance = getHeight(root);
	
	if(balance>1 && strcmp(ID,root->left->ID)<0){
		return rightRotate(root);
	}
	if(balance>1 && strcmp(ID,root->left->ID)>0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if(balance>1 && strcmp(ID,root->right->ID)<0){
		return leftRotate(root);
	}
	if(balance>1 && strcmp(ID,root->right->ID)>0){
		root->left = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
	
}

int main(){
	data* root = NULL;
	int opt;
	mainmenu:
//		system("cls");
	do{
		printf("=========================\n");
		printf("||     Choco Mart      ||\n");
		printf("=========================");
		printf("\n  1. Add Choclate\n");
		printf("  2. View All Chocolate\n");
		printf("  3. Remove Chocolate\n");
		printf("  4. Exit\n");
		scanf("%d",&opt);
	}while(opt<1||opt>4);
	
	char name[21];
	int berat;
	char tipe[21];
	float price;
	char ans;
	
	switch(opt){
		case 1:{
			do{
				printf("\nInput Chocolate Brand [3-30 char]: ");
				scanf(" %[^\n]",&name);
			}while(strlen(name)<3||strlen(name)>30);
			
			do{
				printf("\nInput Chocolate Weight [>10]: ");
				scanf("%d",&berat);
			}while(berat<10 );
			
			do{
				printf("\nInput Chocolate Type [White | Milk | Dark | Cocoa | Ruby] : ");
				scanf("%s",&tipe);
			}while(strcmp(tipe,"White")!=0 && strcmp(tipe,"Milk")!=0 && strcmp(tipe,"Dark")!=0 && strcmp(tipe,"Cocoa")!=0 && strcmp(tipe,"Ruby")!=0);
			
			char tempID[21];
			if(strcmp(tipe,"White")==0){
				strcpy(tempID,"WHI");
			}
			if(strcmp(tipe,"Milk")==0){
				strcpy(tempID,"MIL");
			}
			if(strcmp(tipe,"Dark")==0){
				strcpy(tempID,"DAR");
			}
			if(strcmp(tipe,"Cocoa")==0){
				strcpy(tempID,"COC");
			}
			if(strcmp(tipe,"Ruby")==0){
				strcpy(tempID,"RUB");
			}
			
			do{
				printf("\nInput Chocolate price [$1.0 - 5000.0] : ");
				scanf(" %f",&price);
			}while(price<1 || price>5000);
			
			do{
				printf("Are you sure want to add? [Y / N]: ");
				scanf(" %c",&ans);
			}while(ans == 'Y' && ans == 'N');
			
			char num[4];
			sprintf(num,"%d%d%d",rand()%9,rand()%4,rand()%7);
			strcat(tempID,num);
			
			printf("Chocolate with ID %s has been inputed",tempID);
			
			root = insert(root,tempID,name,berat,tipe,price);
			
			printf("\nPress enter to continue...\n");
			getch();goto mainmenu;
			break;
		}
		
		case 2:{
//			system("cls");
				if(root==NULL){
					printf("No Data");
					getch();goto mainmenu;
				}
				
				char conf[5];
				do{
				printf("Choose Order [Pre / In / Post] : ");
				scanf("%s",&conf);	
				}while(strcmp(conf,"Pre")!=0 && strcmp(conf,"In")!= 0 && strcmp(conf,"Post")!=0);
				
				if(strcmp(conf,"Pre")==0){
					viewPreOrder(root);
					printf("\nPress enter to continue...");
					getch();goto mainmenu;
				}
				else if(strcmp(conf,"In")==0){
					viewInOrder(root);
					printf("\nPress enter to continue...\n");
					getch();goto mainmenu;
				}
				else if(strcmp(conf,"Post")==0){
					viewPostOrder(root);
					printf("\nPress enter to continue...\n");
					getch();goto mainmenu;
				}
			break;
		}
		
		case 3:{
//			system("cls");
			if(root==NULL){
				printf("No Data");
				getch();
				goto mainmenu;
			}
			if(root!=NULL){
				char del[21];
				viewInOrder(root);
				printf("Input ID to Remove : ");
				scanf(" %[^\n]",del);
				
				struct data* temp = search(root,del);
				
				if(temp==NULL){
					printf("\nID not found");
					getch();goto mainmenu;
				}
				else{
					printf("\nChocolate with ID %s removed!",temp->ID);
					printf("\nPress Enter to Continue\n");
					root = remove(root,del);
					getch();
					goto mainmenu;
				}
			}
			break;
		}
		
		case 4:{
			
			break;
		}
	}
	
	return 0;
}
