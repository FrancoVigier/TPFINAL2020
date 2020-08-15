#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

struct _GNodo *** inicializar_HASH();
int codigo_ascii(char a);
int hasheo_uno(char* palabra);
int hasheo_dos(char* palabra);
void hash_inserto(struct _GNodo*** hash, char* alias, GList lista, GList intervaloLista);
Conjunto hash_busco(struct _GNodo*** hash, char* alias);
void hash_elimino(struct _GNodo*** hash, char* alias);
struct _GNodo*** ingresar_conjunto(struct _GNodo*** hasheo, Conjunto pal);
struct _GNodo*** eliminar_conjunto(struct _GNodo*** hasheo, Conjunto pal);
void free_table(struct _GNodo*** table);
#endif // HASH_H_INCLUDED
