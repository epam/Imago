
#include "list.h"
#include "array.h"
#include "exception.h"
#include "queue.h"
#include "../imago/image.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

#include <stdio.h>

int int_compare( const int &in1, const int &in2 )
{
   int a = in1, b = in2;

   if (a < b)
      return -1;

   if (a > b)
      return 1;

   if (a == b)
      return 0;

   return 2;
}

void TestQueue( void )
{
   try
   {
      Queue<int> Q;

      for (int i = 0; i < 10; i++)
         Q.put(i);

      while (!Q.isEmpty())
      {
         int a = Q.get();
         printf("%i\n", a);
      }
   }
   catch ( Exception &e )
   {
      puts(e.what());
   }

/*
   printf("\n");

   for (int i = 0; i < 10; i++)
   {
      int &a = Q.put();
      a = rand() % 50;
   }

   while (!Q.isEmpty())
   {
      int &a = Q.get();
      printf("%i\n", a);
      Q.del();
   }*/
}

#include <list>
#include <time.h>

using namespace std;

struct TestStruct
{
   TestStruct()
   {
      puts("constructor");
   }

   ~TestStruct()
   {
      puts("destructor");
   }
   void f()
   {
      int asd = 0;
   }
};

void TestList( void )
{
   try
   {
      int n = 10;
      List<int> l1, l2;
      list<int> l3;
      
      /*
      for (int i = 0; i < n; i++)
         l1[l1.pushBack()] = i;

      /*
      int j;
      list_for_each(l1, j)
      {
         if (l1[j] % 2 == 0)
            l1.del(j, true);
      }

      /*
      l1.delBack();
      l1.delFront();
      l1.delFront();
      
      for (int i = 0; i < n; i++)
      {
         int b = rand() % 50;
         l1[l1.findPlace(b, int_compare)] = b;
      }

      l1.clear();

      for (int i = 0; i < n; i++)
         l1[l1.pushBack()] = i;

      /*
      l1.delBack();
      l1.delBack();

      l1.delFront();
      l1.delFront();*/
      
      int c = l1.pushBack();
      l1[c] = -1;

      for (int i = 0; i < n; i++)
      {
         int a = l1.pushBack();
         l1[a] = i;
         int b = l1.pushBack();
         l1[b] = i + 1;

         int j = l1.tail();
         j = l1.prev(j);
         j = l1.prev(j);
         l1.del(j, true);
         j = l1.next(j);
         l1.del(j, true);

         int h = l1.getBack();
         printf("%i", h);
      }

      list_for_each(l1, i)
         printf("%i\n", l1[i]);
/*

      list_for_each(l1)
      {
         int a = l1.get();
         printf("%i\n", a);
      }
      printf("\n");

      
    /*  double t1 = clock();
      for (int i = 0; i < n; i++)
      {
         int &a = l1.pushBack();
         a = i;
      }
      t1 = (clock() - t1) / CLOCKS_PER_SEC;

      double t2 = clock();
      for (int i = 0; i < n; i++)
         l3.push_back(i);
      t2 = (clock() - t2) / CLOCKS_PER_SEC;

      printf("Mine:%lf\nTheirs:%lf", t1, t2);

      l1.delBack();
      l1.delFront();

      list_for_each(l1)
      {
         int &i = l1.get();

         if (i == 3)
         {
            int &a = l1.push(true);
            a = -1;
         }
         
         if (i == 8)
         {
            int &a = l1.push(false);
            a = -2;
         }
      }

      
      int &a1 = l1.pushFront();
      a1 = 28;

      int &a2 = l1.pushFront();
      a2 = 24;

      int &a3 = l1.pushBack();
      a3 = 21;
      
      list_for_each(l1)
      {
         int a = l1.get();
         printf("%i\n", a);
      }

      printf("\n");

      l1.delBack();
      l1.delBack();
      l1.delBack();

      list_for_each(l1)
      {
         int a = l1.get();
         printf("%i\n", a);
      }

      printf("\n");

      l1.delFront();
      l1.delFront();
      l1.delFront();

      list_for_each(l1)
      {
         int a = l1.get();
         printf("%i\n", a);
      }*/

      /*
      for (int i = 0; i < 10; i++)
      {
         int b = rand() % n;
         int &a = l1.findPlace(b, int_compare);
         a = b;
      }

      list_for_each(l1)
      {
         int a = l1.get();
         printf("%i\n", a);
         l1.del(true);
      }*/

      int b;
   }
   catch ( Exception &e )
   {
      puts(e.what());
   }
}

void TestArray( void )
{
   int n = 25, maximum, max_ind;
   Array<int> int_array;

   int_array.resize(n);

   for (int i = 0; i < n; i++)
      int_array[i] = rand() % n;

   maximum = int_array.max();
   maximum = int_array.max(max_ind);
   int a_mean = int_array.arithMean();
   double b_mean = int_array.harmonicMean();

//   int_array.sort(int_compare);
   int c_mean = int_array.interMean();
}

void main( void )
{
//   TestQueue();
//   TestArray();
   TestList();

   _CrtDumpMemoryLeaks();
}
