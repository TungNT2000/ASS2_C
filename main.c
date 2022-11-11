#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define FILENAME "log.txt"
#define MAXLENGTHFILE 5000
char fileStr[MAXLENGTHFILE];
// log_obj
int fileToStr(char* str);
char log_storage[30][250];
char log_set_storage[15][250];
char log_status_storage[15][250];
int log_storage_length;
int log_set_storage_length;
int log_status_storage_length;
int getnchr(char* s, char c, int n){
    int i = 0;
    while(*(s + i)){
        if (*(s + i) == c){
            --n;
            if(!n) return i;
        }
        i++;
    }
    return -1;
}
int stridexof(char *s,char *c){
    char *tmp, *result;
    tmp=s;
    result = strstr(tmp,c);
    if(result!=NULL){
        int i =strlen(s)-strlen(result);
        tmp=NULL;
        result=NULL;
        return i;
    }
    tmp=NULL;
    result=NULL;

    return -1;
}
void cut_log(char *str){
    int i =0;
    char *p;
    for(p=strtok(str,"\n");p!=NULL;p=strtok(NULL,"\n")){
            strcpy(log_storage[i],p);
          //  printf("%d\n%s\n\n",i,log_storage[i]);
            i++;
    }
    log_storage_length=i;
}
// check set log
void check_set_log(){
    int k=0;
    int j=0;
    for(int i=0;i<log_storage_length;i++){
        if(strstr(log_storage[i],"\"cmd\":\"set\"")!=NULL){
            strcpy(log_set_storage[k],log_storage[i]);
            printf("\t%s\n",log_set_storage[k]);
            k++;
        }
        else{
                strcpy(log_status_storage[j],log_storage[i]);
                 //printf("%d--%s\n",j,log_status_storage[j]);
                 j++;
                }
    }
    log_set_storage_length=k;
    log_status_storage_length=j;
    printf("\tSo ban tin da gui di la: %d\n",log_set_storage_length);
}
// cnt log from device
void cut_data(char *log, char *data, char end, char *res){
    char *tmp;
    int index;
    tmp=strstr(log,data);
    index=getnchr(tmp,end,1);//strtok
    strncpy(res,tmp+1,index-1);
    res[index-1]='\0';
   // printf("%s\n",res);
    tmp=NULL;

}
void cnt_log(){
    char device[20];
    printf("\tNhap di chi nwk cua thiet bi: ");
    gets(device);
    strlwr(device);
    int cnt=0;
    printf("\tban tin gui di tu device %s la:\n",device);
    if(strlen(device)==4){
    for(int i=0;i<log_set_storage_length;i++){
        if(strstr(log_set_storage[i],device)!=NULL){
           printf("\t%s\n",log_set_storage[i]);
           cnt++;
            }
        }
    }
    printf("\tSo ban tin gui di la:%d \n",cnt);
}
// switch nwk address
struct nw_address{
    char name[5];
    char end_point[1];
};
/*int struct_cmp(struct nw_address nw1, struct nw_address nw2){
    if(strcmp(nw1.name, nw2.name) != 0) {
        return 0;
    }
    if(strcmp(nw1.end_point, nw2.end_point) != 0) {
        return 0;
    }
    return 1;
}
void struct_cpy(struct nw_address nw1, struct nw_address nw2){
    strcpy(nw1.name,nw2.name);
    strcpy(nw1.end_point,nw2.end_point);
}
void push_data(struct nw_address arr[],struct nw_address data, int last){
    if(last==0) {
        struct_cpy(arr[0]==data);
        k++
        return;
    }
    for(int i=0;i<last;i++){
        if(struct_cmp(arr[last-1],data)) return;
    }
    struct_cpy(arr[last],data);
}
int check_data(struct nw_address arr[],struct nw_address data, int last){
    for(int i=0;i<last;i++){
        if(struct_cmp(arr[i],data)) return 0;
    }
    return 1;
}*/
void switch_adaress(){
    char data[20];
    char tmp[10];
    char strData[200];
    int idx;
    struct nw_address sw_nwk[log_set_storage_length];
    int k=0;
      for(int i=0;i<log_set_storage_length;i++){
            struct nw_address t={"",""};
            cut_data(log_set_storage[i],"\"data",']',data);
            if(strstr(strData,data)==NULL||k==0){
                cut_data(data,"-",':',t.name);//??
                strncpy(t.end_point,data+strlen(data)-2,1);
                t.end_point[1] = '\0'; //.....
               // printf("%s\n",t.end_point);
               // struct_cpy(sw_nwk[k],t);
                //strcat(strData,data);
                //printf("%s\n%s\n",data,strData);
                printf("\ttb thu %d co dia chi la :NWK - %s, ENDPOINT - %s\n",k+1,t.name,t.end_point);
                 strcat(strData,data);//???
                  k++;
            }
    }
}
// parse time
struct obj_time{
    int year,month,day,hours,min;
    float sec;
};

struct obj_time pares_time(char *str_time){ //yyyy-MM-ddhh:mm:ss.sss
    struct obj_time obj;
    char *p;
    int tmp;
    p=strtok(str_time,"-");
    obj.year=atoi(p);
    p=strtok(NULL,"-");
    obj.month=atoi(p);
    p=strtok(NULL,":");
    tmp=atoi(p);
    obj.day=tmp/100;
    obj.hours=tmp%100;
    p=strtok(NULL,":");
    obj.min=atoi(p);
    p=strtok(NULL,".");
    tmp=atoi(p);
    p=strtok(NULL,"]");
    obj.sec=tmp*1000+atoi(p);
   // printf("%s----\n",p);
   //printf("%d-%d-%d-%d-%d-%f\n",obj.month,obj.year,obj.hours,obj.day,obj.min,obj.sec);
    return obj;

}
unsigned long subtimer(struct obj_time obj1,struct obj_time obj2){
   // printf("%d-%d-%d-%d-%d-%f\n",obj1.year,obj1.month,obj1.hours,obj1.day,obj1.min,obj1.sec);
   // printf("%d-%d-%d-%d-%d-%f\n",obj2.year,obj2.month,obj2.hours,obj2.day,obj2.min,obj2.sec);
    return abs((obj1.sec-obj2.sec)+((obj1.min-obj2.min)*60+(obj1.hours-obj2.hours)*60*60)*1000);
}
//
// check reqid
struct m_pair{
    int a,b;
};
struct m_pair suc_log_id[20];
int suc_log_id_length;
void check_reqid(){
    char stt_reqid[20][100];
    char req[20];
   // printf("%d\n",log_status_storage_length);
    for(int i=0;i<log_status_storage_length;i++){
           // printf("%s\n",log_status_storage[i]);
        cut_data(log_status_storage[i],"\"reqid",'}',req);
       // printf("%s\n",req);
       // strcat(stt_reqid,req);
       //strcat(stt_reqid,req); // dùng-> chỉ chạy đến 7?
       strcpy(stt_reqid[i],req);
      // printf("%s\n",stt_reqid[i]);
    }
    int cnt=0;
    for(int i=0;i<log_set_storage_length;i++){
         cut_data(log_set_storage[i],"\"reqid",'}',req);
       //   printf("%s\n",req);
       //  printf("%s\n",stt_reqid[i]);
        for(int j=0;j<log_status_storage_length;j++)
        {
            if(strcmp(req,stt_reqid[j])==0) {
              // printf("%s-%s\n",req,stt_reqid[j]);
               suc_log_id[cnt].a=i; suc_log_id[cnt].b=j;
              // printf("%d-%d\n",suc_log_id[cnt].a,suc_log_id[cnt].b);
                cnt++;
                break;
            }
        }
    }
     printf("\tSo ban tin bi loi la: %d\n",log_status_storage_length-cnt);
     suc_log_id_length=cnt;
}
//// time delay;
void time_delay(){
    char str_time1[50],str_time2[50];
    struct obj_time ob1,ob2;
    unsigned long delay_time[suc_log_id_length],max=0,sub=0;
    for (int i=0;i<suc_log_id_length;i++){
            //cut_data(log_set_storage[i],"][",']',str_time1);
            //cut_data(log_status_storage[i],"][",']',str_time2);
            strncpy(str_time1,log_set_storage[suc_log_id[i].a]+7,22);
            str_time1[22]='\0';
            strncpy(str_time2,log_status_storage[suc_log_id[i].b]+7,22);
            str_time1[22]='\0';
            ob1=pares_time(str_time1);
            ob2=pares_time(str_time2);
            delay_time[i]=subtimer(ob1,ob2);
           // printf("%lu\n",delay_time[i]);
    }
    max=delay_time[0];
    sub=delay_time[0];
    for (int i=1;i<suc_log_id_length;i++){
        if(delay_time[i]>max) max=delay_time[i];
        sub+=delay_time[i];
    }
    printf("\tDo tre lon nhat la: %lu\n",max);
    printf("\tdo tr trung binh la: %lu\n",sub/suc_log_id_length);

}
int main(){
     char str[MAXLENGTHFILE];
     fileToStr(str);
     cut_log(str);
     printf("1,\n");
     check_set_log();
     printf("2,\n");
     cnt_log();
     printf("3,\n");
    switch_adaress();
     printf("4,\n");
     check_reqid();
      printf("5,6,\n");
     time_delay();
    return 0;
}

int fileToStr(char* str){
    int status;
    FILE *fp = NULL;
    fp=fopen(FILENAME,"r");
    if(fp==NULL){
        printf("File does not exit\n");
    return -1;
    }
    status = fread(str,MAXLENGTHFILE,1,fp);
    fclose(fp);
    fp=NULL;
    return status;
}
