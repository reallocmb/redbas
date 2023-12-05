#include"redbas/redbas.h"
#include<string.h>
#include<stdio.h>

typedef struct {
    char name[250];
    uint32_t age;
} Person;

void person_print(Person *person)
{
    printf("Person:\n");
    printf("\t%-10s%s\n", "Name", person->name);
    printf("\t%-10s%d\n", "Age", person->age);
}

int main(void)
{
    Person person = { "Matthias", 22 };

    RedbasDB *db = redbas_db_open("database.rdb", sizeof(person));
    printf("Items: %d\n", redbas_db_items(db));

#if 1
    uint32_t i;
    for (i = 0; i < 10; i++)
    {
        strcpy(person.name + 2, "Matthias");
        person.name[1] = i % 10 + 0x30;
        person.name[0] = i / 10 + 0x30;
        person.age = i;
        redbas_db_store(db, &person, sizeof(person));
        /*
        person_print(&person);
        */
    }

    printf("Items: %d\n", redbas_db_items(db));

#else
    /* print every person */
    uint32_t i;
    for (i = 0; i < redbas_db_items(db); i++)
    {
        redbas_db_restore_cursor_set(db, i);
        redbas_db_restore(db, &person, sizeof(person));
        /*
        person_print(&person);
        */
    }
#endif

    redbas_db_close(db);

    return 0;
}
