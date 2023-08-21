#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/*WARNING! The vertices are enumerated starting from 0 to the amount of vertices minus 1.
** Which means the representation is always an integer before that shown in the graphic form.*/

int main() {
    char file_path[100];
    puts("Entre o nome do arquivo com a estensao: ");
    gets(file_path);

    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("Erro ao abrir arquivo\n");
        exit(0);
    }
    int N = 0;
    fscanf(file, "%d", &N); //reading first line

    short **matrix;
    matrix = (short**) malloc(N * sizeof(short*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (short*) malloc(N * sizeof(short));
    }

    int i = 0, j = 0;
    char data = getc(file);
    while (data != EOF) {

        if (data == '1') {
            matrix[i][j] = 1;

            j = (j+1) % N;
            if (j == 0) {
                i++;
            }
        }
        if (data == '0') {
            matrix[i][j] = 0;

            j = (j+1) % N;
            if (j == 0) {
                i++;
            }
        }
        
        data = getc(file);
    }
    fclose(file);
    graph *g = new_graph(N,matrix);

    char op = 0;
    while (op >= 0) {
        puts("\n----------------------------MENU----------------------------");
        puts("[1] Grau Maximo\t\t\t[2] Grau Minimo");
        puts("[3] Sequencia de Graus\t\t[4] Grau de um Vertice");
        puts("[5] Vizinhaca Aberta\t\t[6] Vizinhaca Fechada");
        puts("[7] Adjacencia de Vertices\t[8] Vertices Universais");
        puts("[9] Regularidade do Grafos\t[10] Completude do Grafo");
        puts("[11] Vertices Isolados\t\t[12] Verificar Subgrafo");
        puts("[13] Verificar Passeio\t\t[14] Verificar Caminho");
        puts("[15] Verificar Ciclo\t\t[16] Verificar Trilha");
        puts("[17] Clique\t\t\t[18] Clique Maximal");
        puts("[19] Conjunto Independente\t[20] Complemento do Grafo");
        puts("[21] Mostrar Grafo como Matriz\t[22] Mostrar Grafo como Lista");
        scanf("%d", &op); //precisa de tramento de entrada

        printf("\n");
        switch (op) {
            case 1: {
                printf("Grau maximo: %d\n", max_degree(*g));
                break;
            }
            case 2: {
                printf("Grau minimo: %d\n", min_degree(*g));
                break;
            }
            case 3: {
                v_list *l = degree_sequel(*g);
                printf("Sequencia de graus: ");
                print_vlist(*l);

                destroy_vlist(l);
                break;
            }
            case 4: {
                int id;
                printf("Informe o id do vertice: ");
                scanf("%d", &id);

                printf("\nGrau do vertice %d: %d\n", id, vertex_degree(*g,id));
                break;
            }
            case 5: {
                int id;
                printf("Informe o id do vertice: ");
                scanf("%d", &id);

                v_list *l = open_neighborhood(*g, id);
                printf("Vizinhaca aberta de %d:\n", id);
                print_vlist(*l);
                break;
            }
            case 6: {
                int id;
                printf("Informe o id do vertice: ");
                scanf("%d", &id);

                v_list *l = close_neighborhood(*g, id);
                printf("Vizinhaca fechada de %d:\n", id);
                print_vlist(*l);
                break;
            }
            case 7: {
                int id1;
                printf("Informe o id do 1o vertice: ");
                scanf("%d", &id1);

                int id2;
                printf("Informe o id do 2o vertice: ");
                scanf("%d", &id2);

                printf("\n");
                is_neighbor(*g, id1, id2) ? puts("Verdadeiro") : puts("Falso");
                break;
            }
            case 8: {
                puts("Vertices universais no grafo:");
                v_list *l = universal_vertexes(*g);
                print_vlist(*l);
                
                destroy_vlist(l);
                break;
            }
            case 9: {
                int k = is_regular(*g);
                if (k < 0) {
                    puts("O grafo nao eh regular\n");
                } else {
                    printf ("O grafo tem regularidade k = %d\n", k);
                }
                break;
            }
            case 10: {
                is_complete(*g) ? puts("O Grafo e completo") : puts("O Grafo nao eh completo");
                break;
            }
            case 11: {
                puts("Vertices isolados no grafo:");
                v_list *l = isoleted_vertexes(*g);
                print_vlist(*l);
                
                destroy_vlist(l);
                break;
            }
            case 12: {
                int count = 1;

                int id = 0;
                v_list *ver = new_vlist();
                puts("Entre o id dos vertices no subgrafo:");
                puts("-1 para parar\n");
                do {
                    printf("vertice %d: ", count);
                    scanf("%d", &id);
                    count++;
                } while (add_vertex(ver, id));
                printf("\n");

                count = 1;

                int a, b;
                e_list *edg = new_elist();
                puts("Entre os pontos a e b das arestas no subgrafo:");
                puts("-1 para parar\n");
                do {
                    printf("\naresta %d:\n", count);
                    printf("a: ");
                    scanf("%d", &a);
                    printf("b: ");
                    scanf("%d", &b);
                
                    count++;
                } while (add_edge(edg, a, b));
                printf("\n");

                is_subgraph(*g, *ver, *edg) ? puts("O grafo gerado eh um subgrafo") :
                                              puts("O grafo gerado nao eh subgrafo");
                destroy_vlist(ver);
                destroy_elist(edg);
                break;
            }
            case 13: {
                int count = 1;

                int id = 0;
                v_list *ver = new_vlist();
                puts("Entre o id dos vertices:");
                puts("-1 para parar\n");
                do {
                    printf("vertice %d: ", count);
                    scanf("%d", &id);
                    count++;
                } while (add_vertex(ver, id));
                printf("\n");

                is_passing(*g, *ver) ? puts("A sequencia eh um passeio") :
                                       puts("A sequencia nao eh um passeio");
                destroy_vlist(ver);
                break;
            }
            case 14: {
                int count = 1;

                int id = 0;
                v_list *ver = new_vlist();
                puts("Entre o id dos vertices:");
                puts("-1 para parar\n");
                do {
                    printf("vertice %d: ", count);
                    scanf("%d", &id);
                    count++;
                } while (add_vertex(ver, id));
                printf("\n");

                is_path(*g, *ver) ? puts("A sequencia eh um caminho") :
                                    puts("A sequencia nao eh um caminho");
                destroy_vlist(ver);
                break;
            }
            case 15: {
                int count = 1;

                int id = 0;
                v_list *ver = new_vlist();
                puts("Entre o id dos vertices:");
                puts("-1 para parar\n");
                do {
                    printf("vertice %d: ", count);
                    scanf("%d", &id);
                    count++;
                } while (add_vertex(ver, id));
                printf("\n");

                is_cicle(*g, *ver) ? puts("A sequencia eh um ciclo") :
                                     puts("A sequencia nao eh um ciclo");
                destroy_vlist(ver);
                break;
            }
            case 16: {
                int count = 1;

                int id = 0;
                v_list *ver = new_vlist();
                puts("Entre o id dos vertices:");
                puts("-1 para parar\n");
                do {
                    printf("vertice %d: ", count);
                    scanf("%d", &id);
                    count++;
                } while (add_vertex(ver, id));
                printf("\n");

                is_trail(*g, *ver) ? puts("A sequencia eh um trilha") :
                                     puts("A sequencia nao eh um trilha");
                destroy_vlist(ver);
                break;
            }
            case 17: {
                int count = 1;

                int id = 0;
                v_list *ver = new_vlist();
                puts("Entre o id dos vertices:");
                puts("-1 para parar\n");
                do {
                    printf("vertice %d: ", count);
                    scanf("%d", &id);
                    count++;
                } while (add_vertex(ver, id));
                printf("\n");

                is_clique(*g, *ver) ? puts("A sequencia eh um clique") :
                                      puts("A sequencia nao eh um clique");
                destroy_vlist(ver);
                break;
            }
            case 18: {
                int count = 1;

                int id = 0;
                v_list *ver = new_vlist();
                puts("Entre o id dos vertices:");
                puts("-1 para parar\n");
                do {
                    printf("vertice %d: ", count);
                    scanf("%d", &id);
                    count++;
                } while (add_vertex(ver, id));
                printf("\n");

                is_max_clique(*g, *ver) ? puts("A sequencia eh um clique maximal") :
                                          puts("A sequencia nao eh um clique maximal");
                destroy_vlist(ver);
                break;
            }
            case 19: {
                int count = 1;

                int id = 0;
                v_list *ver = new_vlist();
                puts("Entre o id dos vertices:");
                puts("-1 para parar\n");
                do {
                    printf("vertice %d: ", count);
                    scanf("%d", &id);
                    count++;
                } while (add_vertex(ver, id));
                printf("\n");

                is_independent(*g, *ver) ? puts("A sequencia eh um conjunto independente") :
                                           puts("A sequencia nao eh um conjunto independente");
                destroy_vlist(ver);
                break;
            }
            case 20: {
                graph *comp = complement(*g);
                printf("complemento do grafo:\n\n");
                print_graph1(*comp);
                destroy_graph(comp);
                break;
            }
            case 21: {
                print_graph1(*g);
                break;
            }
            case 22: {
                print_graph2(*g);
                break;
            }
            default: { exit(-1); }
        }
    }
    return 0;
}