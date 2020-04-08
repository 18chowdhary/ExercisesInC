#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gmodule.h>

void print_pair(const char* key, const int value) {
  g_print("%s: %d\n", key, value);
}

int main(int argc, char** argv) {
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    FILE* fp = fopen("pride.txt", "rb");
    char* buffer = malloc(1000*sizeof(char*));

    if (!fp) {
      exit(1);
    }
    while (fscanf(fp, "%s", buffer) != EOF) {
      if (g_hash_table_lookup(hash, buffer)) {
        printf("Updating an old value\n");
        g_hash_table_insert(hash, g_strdup(buffer), g_hash_table_lookup(hash, buffer) + 1);
      }
      else {
        printf("Inserting a new value\n");
        g_hash_table_insert(hash, g_strdup(buffer), GINT_TO_POINTER(1));
      }
    }


    g_hash_table_foreach(hash, (GHFunc)print_pair, NULL);

    // GList* list = NULL;
    // list = g_list_append(list, "Hello world!");
    // printf("The first item is '%s'\n", (char *) g_list_first(list)->data);
    // return 0;
}
