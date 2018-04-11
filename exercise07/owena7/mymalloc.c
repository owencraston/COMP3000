/* Memory allocation example
 * COMP3000, Michel Barbeau
 * Version: March 5, 2018
 * Tested on Ubuntu 16.04 (64-bit)
 * Code sources:
 * "A Malloc Tutorial" by Marwan Burelle
 * http://www.inf.udec.cl/~leo/Malloc_tutorial.pdf
 * "Implementing malloc" by Michael Saelee
 * http://moss.cs.iit.edu/cs351/slides/slides-malloc.pdf
 */

#include "mymalloc.h"
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* base address of heap */
void * base = NULL;

/* Searching for a free segment
 */
static t_header find_header(t_header *last, size_t size) {
   t_header b = base; /* start from heap base address */
   /* first fit algorithm */
   while (b && !(b->free && b->size >= size)) {
      *last = b; /* save address of last visited segment */
      b = b->next;
   }
   /* if success, return segment address else NULL */
   return (b);
}

/* Extending the heap
 */
static t_header extend_heap(t_header last , size_t s) {
   void * sb;
   t_header b; /* ptr to header being created */
   b = sbrk(0); /* get current address of break */
   /* increment the break */
   sb = sbrk(header_SIZE + s);
   /* the following verification is in accordance with Linux man pages */
   if (sb == (void *) -1) { 
      /* failure! */
      return (NULL);
   }
   /* success! */
   b->size = s;
   b->next = NULL;
   b->prev = last;
   b->ptr = (char *)b + header_SIZE;
   if (last) {
      last ->next = b;
   }
   b->free = 0;
   return (b); 
}

/* header splitting
 */
void split_header(t_header b, size_t s) {
   t_header new; /* ptr to header being created */
   new = (t_header)( (char *)b->ptr + s ); /* addr of new header */
   new->size = b->size - s - header_SIZE ; /* size of new header */
   new->next = b->next;
   new->prev = b;
   new->free = 1;
   /* In the following, "header_SIZE" is in bytes. Using the type
    * cast "(char *)", the "void *" pointer "p" is converted to a
    * character pointer. Hence, the pointer subtraction is done in 
    * the byte unit. The result is converted as a "t_header" pointer.
    */
   new->ptr = (char *)new + header_SIZE; /* addr of available mem in new header */
   b->size = s; /* update size of old header */
   b->next = new;
   if (new->next) {
      new->next->prev = new;
   }
}

/* Memory allocation function
 * size = number of bytes
 * returns pointer to allocated memory,
 * NULL in case of failure
 */
void * mymalloc(size_t size) {
   t_header b, last;
   size_t s; 
   s = ALIGN(size); /* alignment of size */
   /* not first time */
   if (base) {
      /* find a header */
      last = base;
      b = find_header(&last, s);
      if (b) {
         /* can split? */
         if ((b->size - s) >= (header_SIZE + 8)) {
            split_header(b, s);
         }
         b->free = 0;
      } else {
         /* no fitting header, extend the heap */
         b = extend_heap(last, s);
         if (!b) return (NULL);
      }
   /* first time */
   } else {    
      b = extend_heap(NULL, s);
      if (!b) return (NULL);
      /* set base address of heap */
      base = b;
   }
   return (b->ptr);
} 

// make function to check if adddress is valid
int check_address(void *p) {
    if (base && (p<sbrk(0) && p > base)) {
        return(1);
    } else {
        return(0);
    }
}

/* free function
 */
void myfree(void *p) {
    // set header variable as the base
    t_header b = base;
    // create a boolean variable to check if p is valid
    int check;
    check = 0;
    
    // iterate through the list and check for p
    while (b && (b->next != NULL)) {
        // check for the pointer
        if (b->ptr == p) {
            //set the "boolean" for p to true
            check = 1;
            // break loop
            break;
        }
        // go to the next node and check it
        b = b->next;
        if (b->ptr == p) {
            //set the "boolean" for p to true
            check = 1;
            // break loop
            break;
        }
    }
    // check p
    if (check_address(p) && check) {
        if ((char *)b + header_SIZE + b->size  == sbrk(0)) { 
            // deallocate data segment
            sbrk(-b->size - header_SIZE);
            // set free to true
            b->free = 1;
            // set the prev and next->next values to null
            b->prev->next = NULL;
            b->prev = NULL;
        } else {
            // set free to true
            b->free = 1; 
            // merge headers with nezt
            fusion(b->next);            
            // merge head with prev
            fusion(b->prev);
        }
    }
}

// fusion function to merge heads 
void fusion(t_header header){
    // check if header is available
    if (header->next && header->next->free && header->prev && header->prev->free){ 
        // merge the headers
        header->next = header->next->next;
        // imcrement the sieze
        header->size += header->next->size; 
    }
}