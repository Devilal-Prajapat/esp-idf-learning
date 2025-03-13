#include <stdio.h>
#include <string.h>
#include "esp_log.h"

#define TAG "APP"

typedef struct _Person{
    char firstname[32];
    char lastname[32];
    int age;
}Person;

// void updateInfo(struct Person person)
// {
//     strcpy(person.firstname,"Devilal");
//     strcpy(person.lastname,"Prajapat");
//     person.age = 32;
// }

void PrintPersonInfo(char *buffer)
{
    printf(buffer);
}

/*
 * function Pointer declaration: void (*printinfo)(char *) 
 */ 

void updateInfo(Person *person, void(*printinfo)(char *buff))
{
    strcpy(person->firstname,"Devilal");
    strcpy(person->lastname,"Prajapat");
    person->age = 32;
    char * buf = (char *)malloc(100 + sizeof(Person));
    sprintf(buf,"firstname: %s\nlastname: %s\nage: %d\r\n",person->firstname, person->lastname, person->age);
    printinfo(buf);
    free((void *)buf);
}

void app_main(void)
{
    ESP_LOGI(TAG,"Person INFO");
    Person person;
    // strcpy(person.firstname,"Devilal");
    // strcpy(person.lastname,"Prajapat");
    // person.age = 32;
    updateInfo(&person,PrintPersonInfo);
    // printf("firstname: %s\nlastname: %s\nage: %d\r\n",person.firstname, person.lastname, person.age);  
} 