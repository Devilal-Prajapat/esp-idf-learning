#include <stdio.h>
#include <string.h>
#include "esp_log.h"

#define TAG "APP"

struct Person{
    char firstname[32];
    char lastname[32];
    int age;
};

// void updateInfo(struct Person person)
// {
//     strcpy(person.firstname,"Devilal");
//     strcpy(person.lastname,"Prajapat");
//     person.age = 32;
// }

void updateInfo(struct Person *person)
{
    strcpy(person->firstname,"Devilal");
    strcpy(person->lastname,"Prajapat");
    person->age = 32;
}

void app_main(void)
{
    ESP_LOGI(TAG,"Person INFO");
    struct Person person;
    // strcpy(person.firstname,"Devilal");
    // strcpy(person.lastname,"Prajapat");
    // person.age = 32;
    updateInfo(&person);
    printf("firstname: %s\nlastname: %s\nage: %d\r\n",person.firstname, person.lastname, person.age);  
}