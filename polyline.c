#include <stdlib.h>
#include <stdio.h>

typedef struct {
  struct {
    double x, y;
  } point;
  void *next;  
  void *prev; 
} segment_t;

typedef struct {
  segment_t *first; 
  segment_t *last; 
} poly_t; 

// create a new segment
segment_t *segment_new(double x, double y) {
  segment_t *s;
  s = malloc(sizeof(segment_t));
  s->point.x = x;
  s->point.y = y;
  
  return s;
}

// create a new polygon with the first segment
poly_t *poly_new(double x, double y) {
  poly_t *p ;
  segment_t *s;
  p = malloc(sizeof(poly_t)); 
  s = malloc(sizeof(segment_t));
  s->point.x = x;
  s->point.y = y;
  p->first = s;
  p->last = s;

  return p;
}

// add a segment at the end of a polygon created
void poly_add(poly_t *poly, segment_t *seg) {
  seg->prev = poly->last;
  poly->last->next = seg;
  poly->last = seg;
} 

// add a segment everywhere you want of a polygon
void poly_insert_at(poly_t *poly, segment_t *seg, size_t pos) {

// count the number of elements of the polygon
  int counter = 0;
  segment_t *a; 
  a = poly->first;
  do{
    a = a->next;
    counter++; 
  } while (a != NULL);
  printf("\nNumero di elementi del poligono prima dell'aggiunta: %d\n\n", counter); // print the number of elements

// if we want to put in the first position
  if (pos == 0) {
    seg->next = poly->first; 
    poly->first->prev = seg;
    poly->first = seg;
  }

// if we want to put in the middle of the list
  if (pos < counter && pos != 0){ 
    segment_t *s;
    s = poly->first;
    int i = 1;
    while (i != pos){
      s = s->next;
      i++;
    } 
    segment_t *s2 = s->next;
    s->next = seg;
    seg->prev = s;
    seg->next = s2;
    s2->prev = seg;
  }

// if we want to put in the last position
  if (pos == counter) {
    seg->prev = poly->last;
    poly->last->next = seg;
    poly->last = seg;
  }
  
}

// free all the element of the polygon choosed
void poly_free(poly_t *poly) {
  segment_t *s1, *s2;
  s1 = poly->first;
  do {
    s2 = s1->next;
    //printf("%f\n", s1->point.x);
    free(s1);
    s1 = s2;
  } while (s1 != NULL);
}

int main(int argc, char const *argv[]) {
  size_t i;
  segment_t *seg;
  double x[10] = {1, 3, 8, 2, 6, 4, 10, 5, 5, 1};
  double y[10] = {6, 2, 1, 2, 8, 8, 3, 1, 5, 7};
  poly_t *poly = poly_new(0, 0);
  for (i = 0; i < 10; i++) {
    segment_t *s = segment_new(x[i], y[i]);
    poly_add(poly, s);
  }

  printf("\nStampo la lista dal primo valore all'ultimo:\n\n" );
  seg = poly->first;
  for ( i = 0; i < 11; i++)
  {
    printf("%5zu:  {%2d, %2d}\n", i, (int)seg->point.x, (int)seg->point.y );
    seg = seg->next;
  }

  printf("\nStampo la lista dall'ultimo valore al primo:\n\n");
  seg = poly->last;
  for (size_t i = 0; i < 11; i++)
  {
  // If i print "10 - i" the segments of the list remain whith the same numbers
  // If i print "i" the numbers will be inverted
    printf("%5zu:  {%2d, %2d}\n", (10 - i), (int)seg->point.x, (int)seg->point.y );
    seg = seg->prev;
  }

  poly_free(poly);

  
  // This part of the cose is to verify that the fuction poly_insert_at works correctly
  // pos = 5 it means that the number will be put at the position numbered as five, then at the sixth position
  // not at the fifth position 
  poly_t *polygon_test = poly_new( 0, 0);
  segment_t *seg_test = segment_new ( 89, 89);
  segment_t *seg_test1 = segment_new ( 1, 1);
  segment_t *seg_test2 = segment_new ( 2, 2);
  segment_t *seg_test3 = segment_new ( 3, 3);
  segment_t *seg_test4 = segment_new ( 4, 4);
  segment_t *seg_test5 = segment_new ( 5, 5);
  poly_add( polygon_test, seg_test1);
  poly_add( polygon_test, seg_test2);
  poly_add( polygon_test, seg_test3);
  poly_add( polygon_test, seg_test4);
  poly_add( polygon_test, seg_test5);
  poly_insert_at (polygon_test, seg_test, 3);
  seg = polygon_test->first;
  for (size_t i = 0; i < 100; i++) { 
    printf("%5zu:  {%2d, %2d}\n", i, (int)seg->point.x, (int)seg->point.y );
    if ( seg->next != NULL ){
      seg = seg->next;
    } else
    {
      break;
    }
  }
  printf("\nCarlo Morganti\nMatricola: 215606\n\n");
  poly_free(polygon_test);
  
  // Commento da parte di Vittorio
  printf("%f\n", polygon_test->first->point.x);
  return 0;
	
}
