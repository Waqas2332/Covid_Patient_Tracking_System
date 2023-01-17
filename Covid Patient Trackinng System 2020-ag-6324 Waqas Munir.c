#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Structure For Patient Information
struct Patient{
	char name[15],phone[15],city[15],date[15],status[10],hospital_name[100];
	int age;
} p[100];
//  Global Variables
int num_patients,medicine_history;

// Add new patient Record
void addPatient(){
	int patient_status;
	FILE *fptr = fopen("Patient.txt","w+");
	if(fptr == NULL){
		printf("\nError in Opening File");
		exit(1);
	}
	printf("\nEnter Patient's Name = ");
	scanf("%s",p[num_patients].name);
	printf("\nEnter Patient's Age = ");
	scanf("%d",&p[num_patients].age);
	printf("\nEnter Patient's Phone Number = ");
	scanf("%s",p[num_patients].phone);
	printf("\nEnter City of Patient = ");
	scanf("%s",p[num_patients].city);
		
	printf("\nEnter status of Patient == \n1 for Active\n2 for Cured\n3 for Dead : ");
	scanf("%d",&patient_status);

	if(patient_status == 1){
		strcpy(p[num_patients].status,"Active");
	}
	else if(patient_status == 2){
		strcpy(p[num_patients].status,"Cured");
	}
	else if(patient_status == 3){
		strcpy(p[num_patients].status,"Dead");
	}
	else{
		printf("\nInvalid Status");
	}
	printf("Enter Hospital Name in which patient is admitted (End it with dot (.) ) : ");
	scanf("%s",p[num_patients].hospital_name);
	num_patients++;
	fwrite(p,sizeof(struct Patient),num_patients,fptr);
	fclose(fptr);
}
// Reading Patients Info
void readPatients(){
	FILE *fptr = fopen("Patient.txt","r");
	if(fptr == NULL){
		printf("Error in opening file");
		exit(1);	
	}
	num_patients = fread(p,sizeof(struct Patient),100,fptr);
	fclose(fptr);
}

//Editing Patient info
void editPatient(){
	int update = 0;
	char search_name[15],updated_info[15];
	int updated_age,patient_status;
	int options;
	printf("\nEnter Patient's Name which info you want to be edited : ");
	scanf("%s",search_name);
	for(int i = 0;i < num_patients;i++){
		if(strcmp(p[i].name,search_name)==0){
			update = 1;
			printf("\nEnter 1 for Editing Name\n2 for Age\n3 for City\n4 For Phone Number\n5 for Editing Hospital Name\n6 For Editing Patient's Status : ");
			scanf("%d",&options);
			if(options == 1){
				printf("\nEnter New Name : ");
				scanf("%s",p[i].name);
			}
			else if(options == 2){
				printf("\nEnter New Age : ");
				scanf("%d",p[i].age);
				
			}
			else if(options == 3){
				printf("\nEnter New City : ");
				scanf("%s",p[i].city);
				
			}
			else if(options == 4){
				printf("\nEnter New Phone Number : ");
				scanf("%s",p[i].phone);
				
			
			}
			else if(options == 5){
			if(strcmp(p[i].status,"Dead")==0){
				printf("Can't Change the hospital name of dead patient");
}
			else{
					printf("\nEnter New Hospital Name (end it with dot (.)");
				scanf("%s",p[i].hospital_name);
			
			}
			}
			else if(options == 6){
			if(strcmp(p[i].status,"Dead")==0){
				printf("\nPatient is Dead.Status can't be changed");
				exit(1);
			}
			else{
				printf("\nEnter status of Patient == \n1 for Active\n2 for Cured\n3 for Dead : ");
	scanf("%d",&patient_status);
	if(patient_status == 1){
		strcpy(p[i].status,"Active");
	}
	else if(patient_status == 2){
		strcpy(p[i].status,"Cured");
	}
	else if(patient_status == 3){
		strcpy(p[i].status,"Dead");
	}
	else{
		printf("\nInvalid Status");
	}
			}
			}
			else{
				printf("\nInvalid Option");
			}		
		}		
		
	}
	if(update == 0){
	printf("Can't Find Record Against Given Name");
	exit(1);
	}
	FILE *fptr = fopen("Patient.txt","w+");
	if(fptr == NULL){
		printf("\nError in Opening File");
		exit(1);
	}
	fwrite(p,sizeof(struct Patient),num_patients,fptr);
	fclose(fptr);
	
}


//Search Single Patient
void searchPatient(){
	int options,id;	
	printf("\nEnter 1 for Searching By ID\nEnter 2 For Searching By Name : ");
	scanf("%d",&options);
	if(options == 1){
		printf("\nEnter ID between 0-%d : ",num_patients-1);
		scanf("%d",&id);
		printf("\nPatient's Name : %s",p[id].name);
		printf("\nPatient's Age : %d",p[id].age);
		printf("\nPatient's Phone Number : %s",p[id].phone);
		printf("\nPatient's City : %s",p[id].city);
		printf("\nPatient's Status : %s",p[id].status);
		printf("\nPatient's Hospital Name : %s",p[id].hospital_name);
	}
	else if(options == 2){
		char name[15];
		printf("\nEnter Name of Patient : ");
		scanf("%s",name);
		for(int i = 0;i < num_patients;i++){
			if(strcmp(p[i].name,name)==0){
			printf("\nPatient's Name : %s",p[i].name);
			printf("\nPatient's Age : %d",p[i].age);
			printf("\nPatient's Phone Number : %s",p[i].phone);
			printf("\nPatient's City : %s",p[i].city);
			printf("\nPatient's Status : %s",p[i].status);
			printf("\nPatient's Hospital : %s",p[i].hospital_name);
			}	
		}
	}
	else{
		printf("\nInvalid Option");
		exit(0);
	}
}

//Structure for Medicine History
struct Medicine{
	char name[15],medicine_names[100],time_date[50];
} m[100];

//Adding Medicine History of patient
void addMedicine(){
	time_t t;
	char name[15];
	int add = 0,status = 0;
	FILE *fptr = fopen("Medicine.txt","w+");
	if(fptr == NULL){
		printf("\nError in Opening File");
		exit(1);
	}
	printf("\nEnter Patient's Name = ");
	scanf("%s",name);
	for(int i = 0; i < num_patients; i++){
		if(strcmp(p[i].name,name)==0){
			add = 1;
			if(strcmp(p[i].status,"Active")==0){
			status = 1;
			break;
			}
		}
	}
	if(add == 0){
		printf("\nPatient Doesn't Exist");
		exit(0);
	}
	else if(status == 0){
		printf("\nPatient is not addmitted in any hospital");
		exit(0);
	}
	else{
		strcpy(m[medicine_history].name,name);
		printf("\nEnter Medicine Name for patient : ");
		scanf("%s",m[medicine_history].medicine_names);
		time(&t);
		strcpy(m[medicine_history].time_date,ctime(&t));
		medicine_history++;	
	}
	fwrite(m,sizeof(struct Medicine),medicine_history,fptr);
	fclose(fptr);
}
//Reading Data from Medicine History
void readMedicine(){
	FILE *fp = fopen("Medicine.txt","r+");
	if(fp == NULL){
		printf("Error in opening file");
		exit(0);	
	}
	medicine_history=fread(m,sizeof(struct Medicine),100,fp);
	fclose(fp);
	
}
//Searching Medicine History of one patient
void searchMedicine(){
	char name[15];	
	int update = 0,i=0;
	printf("\nEnter Patient's Name for Searching his/her Medicine Details : ");
	scanf("%s",name);
	printf("\nRecord of Medicine of %s is : ",name);
	for(int i = 0;i < medicine_history;i++){
		if(strcmp(m[i].name,name)== 0){
			update = 1;
			printf("\nMedicine Given : 	%s",m[i].medicine_names);
			printf("\nTime at which Medicine is Given : %s",m[i].time_date);
		}
	}
	if(update == 0){
		printf("\nSorry, There is no record for %s",name);
	}

}
//Editing Medicine Details
void editMedicine(){
	time_t t;
	int update = 0;
	char search_name[15];
	int options;
	printf("\nEnter Patient's Name whose medicine details has to be edited : ");
	scanf("%s",search_name);
	for(int i = 0;i < medicine_history;i++){
	if(strcmp(m[i].name,search_name)==0){
	update = 1;
	printf("\nEnter 1 for Editing Name\n2 for Medicine Names : \n");
	scanf("%d",&options);
	if(options == 1){
		printf("\nEnter New Name : ");
		scanf("%s",m[i].name);
	}
	else if(options == 2){
		printf("\nEnter New Medicine Names : ");
		scanf("%s",m[i].medicine_names);
		time(&t);
		strcpy(m[i].time_date,ctime(&t));
	}
	else{
		printf("\nInvalid Option");
	}		
	}			
	}
	if(update == 0){
	printf("Can't Find Record Against Given Name");
	exit(0);
	}
	FILE *fptr = fopen("Medicine.txt","w+");
	if(fptr == NULL){
		printf("\nError in Opening File");
		exit(0);
	}
	fwrite(m,sizeof(struct Medicine),medicine_history,fptr);
	fclose(fptr);
}
//Generate Report By area
void generateCity(){
	int count = 0,active=0,cured=0,dead=0;
	char city[15];
	printf("\nEnter City which Report You want to be generated : ");
	scanf("%s",city);
	for(int i = 0;i < num_patients;i++){
		if(strcmp(p[i].city,city)==0){
			count++;
			if(strcmp(p[i].status,"Active")==0){
			active++;
		}
		else if(strcmp(p[i].status,"Cured")==0){
			cured++;
		}
		else if(strcmp(p[i].status,"Dead")==0){
			dead++;
		}
		}		
	}
	printf("\nNumber of Patients in %s is %d",city,count);
	printf("\nTotal Number of Patients that are under Rehab : %d",active);
	printf("\nTotal Number of Patients that have been Successfully cured : %d",cured);
	printf("\nTotal Number of Patients that have been passed away due to COVID : %d",dead);
}
//Generate Report By Hospital
void generateHospital(){
	int count = 0,active=0,cured=0,dead=0;
	char hospital[100];
	printf("\nEnter Hospital Name which Report You want to be generated : ");
	scanf("%s",hospital);
	for(int i = 0;i < num_patients;i++){
		if(strcmp(p[i].hospital_name,hospital)==0){
			count++;
			if(strcmp(p[i].status,"Active")==0){
			active++;
		}
		else if(strcmp(p[i].status,"Cured")==0){
			cured++;
		}
		else if(strcmp(p[i].status,"Dead")==0){
			dead++;
		}
		}
		
	}
	printf("\nNumber of Patients in %s is %d",hospital,count);
	printf("\nTotal Number of Patients that are under Rehab : %d",active);
	printf("\nTotal Number of Patients that have been Successfully cured : %d",cured);
	printf("\nTotal Number of Patients that have been passed away due to COVID : %d",dead);
}
int main(){
	readPatients();
	readMedicine();
	int options,choice;
	printf("\nEnter 1 for Patient's Record\nEnter 2 for Medicine History\nEnter 3 for Generating Report : ");
	scanf("%d",&choice);
	if(choice == 1){
		printf("\nEnter 1 for Adding New Patient\nEnter 2 for Editing Patient's Info\nEnter 3 for Searching Patient's Info : ");
		scanf("%d",&options);
		if(options == 1){
			addPatient();	
		}
		else if(options == 2){
			editPatient();	
		}
		else if(options == 3){
			searchPatient();
		}
	}
	else if(choice == 2){
		printf("\nEnter 1 for Adding New Medicine Details\nEnter 2 for Editing Medicine Details\nEnter 3 for Searching any Patient's Medicine History : ");
		scanf("%d",&options);
		if(options == 1){
			addMedicine();	
		}
		else if(options == 2){
				editMedicine();
		}
		else if(options == 3){
			searchMedicine();
		}
	}
	else if(choice == 3){
		printf("\nEnter 1 for Generating Report By Area :\nEnter 2 for Generating Report By Hospital : ");
		scanf("%d",&options);
		if(options == 1){
			generateCity();
		}
		else if(options == 2){
			generateHospital();
		}		
	}
}
