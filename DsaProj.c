#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
struct node{
    struct node *lchild;
    char nam_e[200];
    int emp_id;
    char phn_no[100];
    char locate[200];
    int salry;
    struct node *rchild;
};
struct node *newNode(int item,const char *name,const char *location,int salary,const char *phone_number){
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->emp_id = item;
    strcpy(newnode->nam_e, name);
    strcpy(newnode->locate, location);
    newnode->salry=salary;
    strcpy(newnode->phn_no, phone_number);
    newnode->lchild = NULL;
    newnode->rchild = NULL;
    return newnode;
}
struct node *insertBST(struct node *root, int item, const char *name, const char *location,int salary,const char *phone_number) {
    struct node *current;
    struct node *parent;
    if (root == NULL) {
        return newNode(item, name, location,salary, phone_number);
    } else {
        current = root;
        parent = NULL;
        while(1) {
            parent = current;
            if (item < parent->emp_id) {
                current = current->lchild;
                if (current == NULL) {
                    parent->lchild = newNode(item, name, location,salary, phone_number);
                    return root;
                }
            } else {
                current = current->rchild;
                if (current == NULL) {
                    parent->rchild = newNode(item, name, location,salary, phone_number);
                    return root;
                }
            }
        }
    }
}
void displayBST(struct node *root) {
    if (root != NULL) {
        displayBST(root->lchild);
        printf("Employee ID: %d\n", root->emp_id);
        printf("Employee Name: %s\n", root->nam_e);       
        printf("Employee Location: %s\n", root->locate);
        printf("Employee Phone Number:%s\n", root->phn_no);
        printf("Annual Income: %d\n",12*root->salry);
        printf("----------------------------");
        displayBST(root->rchild);
    }
}
bool searchBST(struct node *root, int item){
    if(root==NULL){
        return false;
    } else if(root->emp_id==item){
        
        return true;
    } else if(item<root->emp_id){
        return searchBST(root->lchild, item);
    } else {
        return searchBST(root->rchild,item);
    }
}
struct node *inordersucc(struct node *ptr) {
    struct node *curr = ptr;
    while (curr && curr->lchild != NULL)
        curr = curr->lchild;
    return curr;
}
struct node *deleteBST(struct node *root, int item){
    struct node *temp;
    if(root==NULL){
        return root;
    } else if(item<root->emp_id){
        root->lchild = deleteBST(root->lchild, item);
    } else if(item>root->emp_id){
        root->rchild = deleteBST(root->rchild, item);
    } else {
        if(root->rchild && root->lchild==NULL){
            root=NULL;
            free(root);
        } else if(root->rchild==NULL){
            temp=root;
            root=root->lchild;
            free(temp);
        } else if(root->lchild==NULL){
            temp=root;
            root=root->rchild;
            free(temp);
        } else {
            struct node *ptr1 = inordersucc(root->rchild);
            root->emp_id = ptr1->emp_id;
            root->rchild = deleteBST(root->rchild, ptr1->emp_id);
        }
    }
    return root;
}
void isalphaornot(char *name,char *choice ){
    int checkalpha,i,lengthname;
    checkalpha=0;
    printf("Enter %s: ",choice);
    getchar();
    gets(name);
    name[strcspn(name, "\n")] = '\0'; // Remove trailing newline
    while(1){
        lengthname=strlen(name);
        if(checkalpha==lengthname){
            checkalpha=0;
            break;
        }                           
        for(i=0;i<lengthname;i++){
            if(!isalpha(name[i])){
                printf("Enter valid %s:",choice);
                gets(name);
                checkalpha=0;
                break;
            }else{
                checkalpha++;                             
            }
        }
    }             
}
int main(){
    printf("Operations on BST\n");
    int empid,salary,ch,length,i,checkdigit;
    char phone_number[100];
    char name[100];
    char location[100];
    struct node *root = NULL;
    do {
        printf("1.Create an Employee Details\n2.DISPLAY the Employee Details\n3.Deletion of an Employee\n4.Search an Employee\n5.Exit\n");
        printf("Enter a choice:");
        scanf("%d", &ch);
        switch(ch) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d",&empid);
                isalphaornot(name,"Name");
                printf("Enter monthly Salary:");
                scanf("%d", &salary);
                isalphaornot(location,"Location");
                printf("Enter Phone No.:");
                gets(phone_number);
                phone_number[strcspn(phone_number, "\n")] = '\0'; // Remove trailing newline
                checkdigit=0;
                while(1){
                    length=strlen(phone_number);
                    if(checkdigit==length){
                        root = insertBST(root,empid,name,location,salary,phone_number);
                        break;
                    }
                    if(length==10){
                        for(i=0;i<length;i++){
                            if(!isdigit(phone_number[i])){
                                checkdigit=0;
                                printf("Enter valid Phone number:");
                                gets(phone_number);
                                break;
                            }else{                            
                            checkdigit++;
                            }
                        }
                    }else{
                        checkdigit=0;
                        printf("Enter valid Phone number:");
                        gets(phone_number);
                        phone_number[strcspn(phone_number, "\n")] = '\0';
                    }
                }
                break;
            case 2:
                printf("\nEmployees Details are:\n");
                displayBST(root);
                printf("\n");
                break;
            case 3:
                printf("Enter Employee ID to be deleted:");
                scanf("%d", &empid);
                root = deleteBST(root, empid);
                break;
            case 4:
                printf("Enter Employee ID to be searched:");
                scanf("%d", &empid);
                if(searchBST(root, empid)){
                    printf("Found\n");
                } else {
                    printf("Not Found\n");
                }
                break;
            case 5:
                printf("Exit\n");
                break;
            default:
                printf("Invalid Choice\n");
        }
    } while(ch!=5);
    return 0;
}