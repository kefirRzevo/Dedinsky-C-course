#include <stdio.h>
#include <stdlib.h>
#include "include/queue.h"


int main() 
{
   queue q = {};
   queue_ctor(&q);
   int num = 41, step = 2, k = 0;
   for(int i = 0; i < num; i++)
      push_head(&q, i);
      queue_dump(&q);
   while(q.size > 1)
   {
      for(int j = 0; j < q.size; j+=step)
      {
         pop_tail(&q, &k);
         q.size--;
      }
      queue_dump(&q);
   }
   queue_dump(&q);
   printf("%d\n", k);
   return 0;
}