#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
  int space;
  int starting_add;
  struct node* next;
}node;


node *alist,*flist;
int space;
int starting_add;


 void traverse_alist()
{
     node *temp;
     temp = alist;
     printf("allocated list\n");
     while(temp!=NULL)
     {
         printf("starting address: %d space: %d\n",temp->starting_add,temp->space);
         temp = temp->next;
     }
}


void traverse_flist()
{
     node *temp;
     temp = flist;
     printf("free list\n");
     while(temp!=NULL)
     {
         printf("starting address: %d space: %d\n",temp->starting_add,temp->space);
         temp = temp->next;
     }
}


void free_fun(node* nptr)
      {
          free(nptr);
      }

node* malloc_fun()
    {
          node *nptr;
          nptr = (node*)malloc(sizeof(node));
          nptr->space = space;
          nptr->starting_add = starting_add;
          nptr->next=NULL;
          return nptr;
    }


 void free_up(node* nptr)
{
         node *prev,*temp;

         int done=0,sum;
         prev = NULL;
         temp = flist;

          while(temp!=NULL && done==0)
          {
             if(temp->starting_add > nptr->starting_add) //find appropriate location to insert in alloc list
             {
                done=1;
             }
             else
             {

                 prev=temp;
                 temp = temp->next;

             }
          }

          if(done==1)  //if found in list
          {

                    sum = nptr->starting_add + nptr->space;
                    if(sum==temp->starting_add)                    //merge with right node
                    {
                         temp->starting_add = nptr->starting_add;
                         temp->space += nptr->space;
                         free_fun(nptr);
                         if(prev!=NULL)
                         {
                             sum=prev->starting_add+prev->space;  // merge with left node
                             if(sum==temp->starting_add)
                             {
                                 prev->space+=temp->space;
                                 node* t=temp;
                                 prev->next=t->next;
                                 t->next=NULL;
                                 free_fun(t);
                             }
                         }
                    }
                    else
                    {
                       if(prev!=NULL)  // last node case
                       {
                           sum = prev->starting_add + prev->space;
                           if(sum==nptr->starting_add)
                           {
                              prev->space += nptr->space;
                              free_fun(nptr);
                           }
                           else
                           {
                              prev->next = nptr;
                              nptr->next = temp;
                           }

                       }                // first node case
                       else
                       {
                            nptr->next = temp;
                            flist = nptr;

                       }

                    }
          }
          else
          {

               if(prev==NULL)
               { nptr->next = temp; flist = nptr;}
               else
               {
                   sum = prev->starting_add + prev->space;
                   if(sum==nptr->starting_add)
                   {
                      prev->space += nptr->space;
                      free_fun(nptr);
                   }
                   else
                   {
                      prev->next = nptr;
                      nptr->next = temp;
                   }
               }

          }

}

void to_allocate(node* nptr)
{
     node* temp,* prev;
     temp = alist;
     prev=NULL;

     while(temp!=NULL && nptr->starting_add > temp->starting_add)
     {
        prev=temp;
        temp = temp->next;
     }

     if(prev==NULL)
     {
        nptr->next = alist;
        alist = nptr;
     }
     else
     {
          prev->next = nptr;
          nptr->next = temp;
     }

}

node* NextFit(node* ptr)
{
    node *temp,*prev,*nptr;
    temp = flist;
    prev = NULL;
    int done=0;

    while(temp!=NULL && temp!=ptr)
    {
        prev=temp;
        temp = temp->next;
    }

    if(temp==NULL)
    {
        temp = flist;
    }


    while(temp!=NULL && done==0)
    {
        if(temp->space < space)
        {
           prev=temp;
           temp = temp->next;
        }
        else
        {
          done=1;
          if(temp->space > space)
          {

             starting_add = temp->starting_add;
             nptr = malloc_fun();
             to_allocate(nptr);
             temp->space -= space;
             temp->starting_add += space;
             ptr = temp;
          }
          else
          {
              if(prev!=NULL)
              {
                 prev->next = temp->next;
                 ptr = prev;
              }
              else
              {
                  flist = flist->next;
                  ptr = flist;
              }
              to_allocate(temp);
          }

        }
    }

    if(done==0)
    { printf("NOT ENOUGH SPACE\n"); ptr = flist;}
    else{ printf("allocated successfully\n");}
    return ptr;
}

void FirstFit()
{
    node *temp,*prev,*nptr;
    temp = flist;
    prev = NULL;
    int done=0;

    while(temp!=NULL && done==0)
    {
           if(temp->space < space)
           {
               prev=temp;
               temp = temp->next;
           }
           else
           {
              done=1;
              if(temp->space > space)
              {
                 starting_add = temp->starting_add;
                 nptr = malloc_fun();
                 to_allocate(nptr);
                 temp->space -=space;
                 temp->starting_add += space;
              }
              else
              {
                  if(prev!=NULL)
                  {
                     prev->next = temp->next;
                  }
                  else
                  {
                      flist = flist->next;
                  }
                  to_allocate(temp);
              }

           }
        }

        if(done==0)
        { printf("NOT ENOUGH SPACE\n");}
        else
        { printf("allocated successfully\n");}


 }

 void BestFit()
	{
	   	node *temp,*prev,*nptr,*t;
        temp = flist;
        prev = NULL;
        t=NULL;

		int diff,max,done;
        max=100;
        done=0;

		while(temp!=NULL && done==0)
		{
            if(temp->space < space)
            {
               prev=temp;
               temp = temp->next;
            }
            else
            {

              if(temp->space > space)
              {
                 diff = temp->space - space;
                 if(diff<max){ max=diff; t=temp; }
                 prev = temp;
                 temp = temp->next;
              }
              else
              {
                  done=1;
                  if(prev!=NULL)
                  {
                     prev->next = temp->next;
                  }
                  else
                  {
                      flist = flist->next;
                  }
                  to_allocate(temp);
              }

           }

		}

        if(done==0)
        {
               if(t==NULL)
               { printf("NOT ENOUGH SPACE\n"); }
               else
               {
                     starting_add = t->starting_add;
                     nptr = malloc_fun();
                     to_allocate(nptr);
                     t->space -= space;
                     t->starting_add += space;
                     printf("allocated successfully\n");
               }
        }


      }



void main()
{
   node *nptr,*ptr;
   flist = NULL;
   alist = NULL;
   space = 100;
   starting_add=0;
   nptr = malloc_fun();
   nptr->next = flist;
   flist = nptr;
   ptr = flist;

   int choice,i,t,done;



   t=1;

   while(t)
   {
       printf("\n<==================CPL ASSIGNMENT-3==================>\n");
	 printf("ENTER YOUR CHOICE:\n\n=====================================================>\n1:ADD MEMORY\n2:FOR FREEING UP THE SPACE\n3:TRAVERSE ALLOCATED LIST\n4:TRAVERSE FREE LIST\n=====================================================>\n\n");
         scanf("%d",&choice);
         if(choice==1)
         {
             int k;

                printf("ENTER THE MEMORY YOU WANT TO ALLOCATE\n");
                scanf("%d",&space);

		printf("1:FIRST_FIT\n2:BEST_FIT\n3:NEXT_FIT");
                scanf("%d",&k);

                switch(k)
                {

                   case 1: FirstFit();
                           break;

                   case 2: BestFit();
	                       break;

                   case 3: ptr = NextFit(ptr);

			               break;
                }

	 }
         else
         {
                    if(choice==2)
                    {
		        int done;
		        done=0;
		        node *prev;
		        prev=NULL;

		        nptr = alist;
		        printf("ENTER THE STARTING ADDRESS OF THE VARIABLE THAT YOU WANT TO FREE\n");
		        scanf("%d",&starting_add);


		        while(nptr!=NULL && done==0)
		        {
		            if(nptr->starting_add==starting_add)
		            {
		                done=1;
		            }
		            else
		            {
		              prev = nptr;
		              nptr = nptr->next;
		            }
		        }

		        if(done==0)
		            {
				printf("no such node exist\n");
			    }

		        else
		            {
				   if(prev!=NULL)
				   {
				        prev->next = nptr->next;
				   }
				   else
				   {
					alist = alist->next;
				   }

                                   nptr->next = NULL;
				   free_up(nptr);
		            }
                  }
                  else
                  {
                     if(choice==3){ traverse_alist();}
                     else
                     { traverse_flist();}

                  }

	 }

         printf("want to continue press 1 else 0\n");
         scanf("%d",&t);

    }
   }

