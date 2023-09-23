#include<eenheid.h>
#include<redbas.c>

typedef struct {
    char *name;
    int age;
} Person;

__EENHEID_INIT__

Person p;
RedbasDB *db = redbas_db_open("db_path", sizeof(p));

TEST(redbas_db_open())
{
    eenheid_assert(db != NULL);
    eenheid_assert_int32(sizeof(p), db->size);
    eenheid_assert_int32(0, db->items);
    TEST_END
}

TEST(redbas_db_store())
{
    redbas_db_store(db, &p, sizeof(p));
    eenheid_assert_int32(1, db->items);
    TEST_END
}

TEST(redbas_db_items())
{
    uint32_t items = redbas_db_items(db);
    eenheid_assert_int32(1, items);
    TEST_END
}

__EENHEID_END__
