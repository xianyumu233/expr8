#include <stdio.h>
#include <string.h>
struct data {
	int count;    //冲突计数
	int free;    //空闲标志
	int key;    //记录的key值
	char value[30];    //key值对应的内容
};

//初始化结构 d[] 用一个data数组来模拟总体结构

void init(struct data d[], int n) {
	int i;
	for(i=0; i<n; i++) {
		d[i].count=0;
		d[i].free=1;
		d[i].key=0;
		strcpy(d[i].value,"");
	}
}

//将结构打印出来

void print(struct data d[],int n) {
	int i;
	printf("count,free,key,value\n");
	for(i=0; i<n; i++) {
		printf("  %-4d %-4d %-4d %-5s\n",d[i].count,d[i].free,d[i].key,d[i].value);
	}
}

//添加记录
void add(struct data d[], int key,char value[]) {
	int flag = 1;
	int addr = hash(key);
	d[addr].count += 1;    //冲突计数加1
	while(flag) {
		if(d[addr].free == 1) {
			d[addr].free=0;
			d[addr].key=key;
			strcpy(d[addr].value,value);
			printf("----------Add Sucess!-------");
			flag=0;
		} else {
			flag = 1;
			addr += 1;
			if(addr >= 20) {
				printf("---out of space!---\n");
				return;
			}
		}
	}
}

//hash函数，通过key计算出地址
int hash(int key) {
	return key % 50;
}

//通过key值查找对应的记录
int findByKey(struct data d[],int key) {
	int addr = hash(key);
	int count = d[addr].count;
	if(count == 0) {
		printf("-------No Record!-------");
		return 0;
	} else {
		int flag = 1;
		while(flag) {
			if(d[addr].free == 1) {
				flag = 1;//Next position
				addr += 1;
				if(addr >= 20) {
					printf("-------No Record!-------");
					return 0;
				}
			} else {
				int key1 = d[addr].key;
				if(key == key1) {
					flag = 0;//find success
					return addr;
				} else {
					if(hash(key) == hash(key1)) {
						count -= 1;
						if(count == 0) {
							printf("-------No Record!-------");
							return 0;
						} else {
							flag=1;//find next position
							addr += 1;
							if(addr >= 20) {
								printf("-------No Record!-------");
								return 0;
							}
						}
					} else {
						flag=1;//find next position
						addr += 1;
						if(addr >= 20) {
							printf("-------No Record!-------");
							return 0;
						}
					}
				}//end if(key == key')
			}//end if(d[addr].free==1)
		}//end while(flag)
	}//end if(count == 0)
}

//通过key删除记录
int deleteByKey(struct data d[], int key) {
	int rs,addr;
	rs = findByKey(d, key);
	addr = hash(key);
	if(rs > 0) {
		d[rs].free = 1;
		d[addr].count -= 1;
		return rs;
	} else {
		printf("-------No Record!------");
		return -1;
	}
}

//程序主界面
void start() {
	printf("------------Please choice-----------\n");
	printf("A---Add a new record\n");
	printf("F---find the record by key\n");
	printf("D---Delete the record by key\n");
	printf("S---Show the records\n");
	printf("E---Exit this\n");
}
//添加一条记录
void addRecord(struct data d[]) {
	int key;
	char value[30];
	printf("Please input the key and the value!\n");
	scanf("%d,%s",&key,&value);

	printf("Your input:key=%d,value=%s\n",key,value);
	getchar();//read the "enter"
	add(d,key,value);
	printf("\n");
}

//查找记录
void find(struct data d[]) {
	int addr,key;
	printf("Please input the key:\n");
	scanf("%d",&key);
	getchar();
	addr = findByKey(d,key);
	if(addr > 0) {
		printf("Find Success! the key=%d,the value=%s\n",d[addr].key,d[addr].value);
	} else {
		//printf("Find %c,%d\n",o,addr);
	}
	printf("\n");
}

//删除记录
void delete(struct data d[]) {
	int key,rs;
	printf("Please input the key:\n");
	scanf("%d",&key);
	getchar();
	rs = deleteByKey(d,key);
	if(rs > 0) {
		printf("Delete Sucess!the key is:%d\n",d[rs].key);
	} else {
		printf("Delete Failure!\n");
	}
}

int main(void) {
	char o;
	int addr,key;
	struct data d[20];
	init(d,20);
	do {
		start();
		scanf("%c",&o);
		getchar();

		if(o == 'A' || o == 'a') {
			addRecord(d);
		} else if(o == 'F' || o == 'f') {
			find(d);
		} else if(o == 'D' || o == 'd') {
			delete(d);
		} else if(o == 'E' || o == 'e') {
			return 0;
		} else if(o == 'S' || o == 's') {
			print(d,20);
		} else {
			printf("Error! Please input again!\n");
		}
	} while(!(o == 'E' || o == 'e'));
}
