/******************************************************************************

1. усложним структуру адресной книги:
ФИО
телефон
адрес  
    Город
    Улица
    Дом

char[80]        char[10]    char[20]    char[20]    uint16_t    итого 132 байта
Иванов И.И.     123456      Минск       Советская   10
Петров П.П.     111111      Орша        Советская   1
Васильев В.В.   777777      Минск       Победы      10

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct Coords {
    char city[20];
    char street[20];
    uint16_t number;
} Coords;

struct Person;

typedef struct Person {
    char name[80];
    char phone[10];
    Coords address;
    Person* next;
} Person;

Person *people = NULL;      // список всех абонентов

// = {
//     {"Иванов И.И.", "123456", {"Минск", "Советская", 10}},
//     {"Петров П.П.", "111111", {"Орша", "Советская", 1}},
//     {"Васильев В.В.", "777777", {"Минск", "Победы", 10}}
// };

void addPerson(Person* head, char* name, char* phone, char* city, char* street, uint16_t number) 
{
    Coords *coords = (Coords*)malloc(sizeof(Coords));
    strcpy(coords->city, city);
    strcpy(coords->street, street);
    coords->number = number;
    Person *newPerson = (Person*)malloc(sizeof(Person));
    strcpy(newPerson->name, name);
    strcpy(newPerson->phone, phone);
    newPerson->address = *coords;
    newPerson->next = NULL;
    if (head != NULL) 
    {
        newPerson->next = people;
    }
    people = newPerson;
}

// PERSON1             PERSON2             PERSON3
//     next > PERSON2      next > PERSON3      next > NULL

void ShowPerson(Person *person){
    printf("%s\t%s\t%s\t%s\t%d\n", person->name, person->phone, person->address.city, person->address.street, person->address.number);
}

void ShowPersons() 
{
    if (people == NULL)
        return;
    Person *person = people;
    do {
        ShowPerson(person);
        person = person->next;
    } while (person != NULL);
}

void FindPerson(const char* personName) {
    Person *person = people;
    int count = 1;
    do {
        char *name = person->name;
        int found = 1;
        
        for(int i=0; i<sizeof(personName); i++){
            if(personName[i]!=name[i]){
                found = 0;
                break;
            }
        }
        
        if(found){
            printf("Found %d - ", count);
            ShowPerson(person);
        }
        
        person = person->next;
        count ++;
    } while (person != NULL);
}

int main()
{
    addPerson(people, "Иванов И.И.", "123456", "Минск", "Советская", 10);
    addPerson(people, "Петров П.П.", "111111", "Орша", "Советская", 1);
    addPerson(people, "Васильев В.В.", "777777", "Минск", "Победы", 10);
    ShowPersons();
    FindPerson("Петров П.П.");
    return 0;
}


