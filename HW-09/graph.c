#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

/* This is a testing file just to be able to compile the 
 * examples of binary files to convert graph from txt->bin
 * and bin -> txt
 */

// - function -----------------------------------------------------------------
graph_t* allocate_graph(void) 
{
   graph_t *temp = (graph_t *) malloc(sizeof(graph_t));
   temp -> capacity = 128;
   temp -> edge_count = 0;
   edge *temp_e = (edge *) malloc(temp -> capacity * sizeof(edge));
   temp ->edge = temp_e;

   return temp;

}

// - function -----------------------------------------------------------------
void free_graph(graph_t **graph)
{
   free((*graph) -> edge);
   free((*graph)); //mozna chyba s cap
}

// - function -----------------------------------------------------------------
void load_txt(const char *fname, graph_t *graph)
{
   FILE *f = fopen(fname, "r");
   int from=0, to=0, cost=0;
   while (fscanf(f, "%d %d %d", &from, &to, &cost)==3){
      edge *edg = graph -> edge + graph -> edge_count;
      if (from < 0 || to < 0 || cost < 0){
         exit(100);
      }
      edg -> from = from;
      edg -> to = to;
      edg -> cost = cost;
      edg ++;
      graph -> edge_count++;
      if (graph -> edge_count == graph -> capacity){
         graph -> capacity = graph -> capacity * 2;
			edge * edg_new = realloc(graph -> edge, graph -> capacity * sizeof(edge));
         edg = edg_new;
         graph -> edge = edg;
         
      }

   }
   fclose(f);
}

// - function -----------------------------------------------------------------
void load_bin(const char *fname, graph_t *graph)
{
   FILE *f = fopen(fname, "rb");
   while(!feof(f)) {
      edge *edg = graph->edge + graph->edge_count;
      if(graph->edge_count < graph->capacity) {
		   if(fread(edg, sizeof(edge), 1, f) != 1){
            break;
         }
         graph->edge_count++ ;
			edg++;

		} else {
         graph -> capacity = graph -> capacity * 2;
			edge * edg_new = realloc(graph -> edge, graph -> capacity * sizeof(edge));
         edg = edg_new;
         graph -> edge = edg;
		}
   }
   fclose(f);
}

// - function -----------------------------------------------------------------
void save_txt(const graph_t * const graph, const char *fname)
{
   FILE *f = fopen(fname, "w");

      edge *edg = graph -> edge;
   	for (int i = 0; i < (graph -> edge_count); i++, edg++) {
		   fprintf(f, "%d %d %d\n", edg -> from, edg -> to, edg -> cost);
         // fputc(edg -> from,f);
         // fputc(' ',f);
         // fputc(edg -> to,f);
         // fputc(' ',f);
         // fputc(edg -> cost,f);
         // fputc('\n',f);


      }
   fclose(f);
}

// - function -----------------------------------------------------------------
void save_bin(const graph_t * const graph, const char *fname)
{
   printf("%d", graph -> edge_count);
   FILE *f = fopen(fname, "wb");
	edge *edg = graph->edge;
   	for (int i = 0; i < (graph->edge_count); i++, edg++) {
		fwrite(&edg -> from, sizeof(edg -> from), 1, f);
		fwrite(&edg -> to, sizeof(edg -> to), 1, f);
		fwrite(&edg -> cost, sizeof(edg -> cost), 1, f);
	}
   fclose(f);
   }
