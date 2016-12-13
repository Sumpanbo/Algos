#include <string.h>
#include <stdio.h>

/* Each element in the array to be sorted is of type ELEM_TYPE. 
** If not defined, set ELEM_TYPE to int.
*/
#ifndef ELEM_TYPE
#define ELEM_TYPE int
#endif
#ifndef KEY_TYPE
#define KEY_TYPE int
#endif

typedef ELEM_TYPE elem_t;
typedef KEY_TYPE key_t;

/* Max array is bounded by the size of ar_size_t. 
** Can be changed here if needed. 
*/
typedef unsigned long ar_size_t;  

/* Left Child Index
   Right Child Index
*/
inline static ar_size_t LCI(ar_size_t ix) {return 2*ix;}
inline static ar_size_t RCI(ar_size_t ix) {return 2*ix+1;}

/* Swap the elements at postition ix1 and ix2 in the array ar[]
     For ix1 and ix2, position 1 refers to the first element while for ar,
     position 0 is the first element. This has be compensated for.
     Each element is of size sizeof(elem_t).
*/   
static void swap_elem(elem_t ar[], ar_size_t ix1, ar_size_t ix2)
{
  elem_t temp;
  memcpy(&temp, &ar[ix1-1], sizeof(elem_t));
  memcpy(&ar[ix1-1], &ar[ix2-1], sizeof(elem_t));
  memcpy(&ar[ix2-1], &temp, sizeof(elem_t));
}

/* Convert the sub-tree at ar[node_ix] into a max-heap 
**   Assumes the root node's children, ar[2*node_ix] and ar[2*node_ix+1], 
**     are already max-heaps.
*/
static void heapify_max(elem_t ar[], ar_size_t node_ix, ar_size_t num_elem)
{
  key_t node_key, l_key, r_key;
  ar_size_t next_ix = node_ix;

  /* repeat until we reach the leaves */
  while (next_ix <= num_elem/2) {
    /* to be abstracted later - right now the array consist of keys only */
    node_key = (key_t) ar[next_ix-1];
    l_key = (key_t) ar[2*next_ix-1];

    if (LCI(next_ix) < num_elem) { /* make sure there is a right child */
      r_key = (key_t) ar[2*next_ix];
    }

    /* find the greater of the two children and swap it with the node, if
       node is smaller than the biggest child. Next loop iteration, do the
       same on the swapped child 
    */
    /* Also handle the special case of a node with only a left child */    

    if ((LCI(next_ix) == num_elem) || (l_key > r_key) && (node_key < l_key)) {
      /* swap node and left child */
      swap_elem(ar, next_ix, LCI(next_ix));
      next_ix = LCI(next_ix);
    } else if ((r_key > l_key) && (node_key < r_key)) {
      /* swap node and right child */
      swap_elem(ar, next_ix, RCI(next_ix)); 
      next_ix = RCI(next_ix);
    } else {
      /* no need to swap? Then we are done. Exit the loop */
      break;
    }
  } 
}

static void build_max_heap(elem_t ar[], ar_size_t num_elem)
{
  for (ar_size_t i=num_elem/2; i>0; i--) 
  {
    heapify_max(ar, i, num_elem);
  }
}

void heapsort_max(elem_t ar[], ar_size_t num_elem)
{
  build_max_heap(ar, num_elem);

  for (ar_size_t i=num_elem; i>1; i--)
  {
    /* swap the first element with the last, remove the last, then fixup
       the heap again. */
    swap_elem(ar, 1, i);
    heapify_max(ar, 1, i-1);
  }
  

}

/* quick and dirty test code, to be removed later */
int main(int argc, char *argv[]) 
{
  int ar[] = {3, 4, 7, 9, 1, -2, 11, 100, 0};
  heapsort_max(ar, (sizeof(ar)/sizeof(int)));
  for (int i=0; i<sizeof(ar)/sizeof(int); i++)
  {
    printf("%d: %d\n", i, ar[i]);
  }
}


