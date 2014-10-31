#include<iostream>
#include<typeinfo>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<math.h>

using namespace std;

#ifndef ASSEMBLY++_HPP_INCLUDED

#define ASSEMBLY++_HPP_INCLUDED


class MessageINT
{
  public:

      int *param_list;
      int param_count;
      int msg_name;
      int msg_return;

      MessageINT()
      {
         ClearParam();
      }

      void ClearParam()
      {
          param_list = new int[0];
          param_count = 0;
          msg_name = 0;
          msg_return = 0;
      }

      void AddParam(int param_val)
      {
            if (msg_name != 0)
            {
                ResizeList(param_count + 1);
                param_list[param_count] = param_val;
                param_count++;
            }
            else
            {
                msg_name = param_val;
            }
      }

      int GetParam(int param_id)
      {
         if (param_id >= 0 && param_id < param_count)
         {
            return param_list[param_id];
         }
      }

      void Dispach()
      {
            if (msg_name == 11)
            {
                system("cls");
                msg_return = 1;
            }
            else if (msg_name == 121)
            {
                system("pause");
                msg_return = 1;
            }
            else if (msg_name == 4)
            {
                exit(1);
            }
            else if (msg_name == 16)
            {
                if (param_list[1] == 1)
                {
                    cout << endl << param_list[0] << endl;
                    msg_return = 1;
                }
                else if (param_list[1] == 0)
                {
                    cout << endl << param_list[0] << endl;
                    msg_return = 1;
                }
                else
                {
                    msg_return = 0;
                }
            }
            else if (msg_name == 5)
            {
                param_list = new int[0];
                msg_name = 0;
            }
            else if (msg_name == 25)
            {
                msg_return = (int) sin((int) param_list[1]);
            }
            else if (msg_name == 6)
            {
                msg_return = (int) cos((int) param_list[1]);
            }
            else if (msg_name == 36)
            {
                msg_return = (int) tan((int) param_list[1]);
            }
            else if (msg_name == 7)
            {
                msg_return = (int) sqrt((int) param_list[1]);
            }
            else if (msg_name == 49)
            {
                msg_return = param_list[1] & param_list[2];
            }
            else if (msg_name == 8)
            {
                msg_return = param_list[1] | param_list[2];
            }
            else if (msg_name == 64)
            {
                msg_return = param_list[1] << param_list[2];
            }
            else if (msg_name == 9)
            {
                msg_return = param_list[1] >> param_list[2];
            }
            else if (msg_name == 81)
            {
                msg_return = param_list[2] << param_list[1];
            }
            else if (msg_name == 10)
            {
                msg_return = param_list[2] >> param_list[1];
            }
            else if (msg_name == 100)
            {
                msg_return = ~(param_list[1]);
            }
            else if (msg_name == 12)
            {
                Sleep(param_list[1]);
                msg_return = 1;
            }
      }

      int GetReturn()
      {
          return msg_return;
      }

  private:
      void ResizeList(int newsize)
      {
         int* newlist = new int[newsize];

         for(int cntr = 0;cntr < param_count;cntr++)
         {
             newlist[cntr] = param_list[cntr];
         }

         param_list = newlist;
      }
};

class MessageSTRING
{
  public:

      string *param_list;
      int param_count;
      string msg_name;
      int msg_return;

      MessageSTRING()
      {
         ClearParam();
      }

      void ClearParam()
      {
          param_list = new string[0];
          param_count = 0;
          msg_name = "";
          msg_return = 0;
      }

      void AddParam(string param_val)
      {
            if (msg_name != "")
            {
                ResizeList(param_count + 1);
                param_list[param_count] = param_val;
                param_count++;
            }
            else
            {
                msg_name = param_val;
            }
      }

      string GetParam(int param_id)
      {
         if (param_id >= 0 && param_id < param_count)
         {
            return param_list[param_id];
         }
      }

      void Dispach()
      {
            if (msg_name == "0x1a")
            {
                msg_return = param_list[1].length();
            }
            else if (msg_name == "0x1b")
            {
                FILE *file_inst = fopen(param_list[1].c_str(),"w");

                if (file_inst)
                {
                    fprintf(file_inst,"%s",param_list[2].c_str());
                    fclose(file_inst);

                    msg_return = 1;
                }
                else
                {
                    msg_return = 0;
                }
            }
            else if (msg_name == "0x1c")
            {
                FILE *file_inst = fopen(param_list[1].c_str(),"r");
                msg_return = file_inst->_file;
            }
            else if (msg_name == "0x1d")
            {
                if (param_list[2].c_str() == "NEW_LINE")
                {
                    cout << param_list[1] << endl;
                    msg_return = 1;
                }
                else if (param_list[2].c_str() == "SAME_LINE")
                {
                     cout << param_list[1];
                     msg_return = 1;
                }
                else
                {
                    msg_return = 0;
                }
            }
      }

      int GetReturn()
      {
          return msg_return;
      }

  private:
      void ResizeList(int newsize)
      {
         string* newlist = new string[newsize];

         for(int cntr = 0;cntr < param_count;cntr++)
         {
             newlist[cntr] = param_list[cntr];
         }

         param_list = newlist;
      }
};

class Stack
{
   public:
       Stack()
       {
           elem_array = new int;
           base = (int) elem_array;
       }

       void push(int val)
       {
           *elem_array = val;
           elem_array++;
       }

       int pop()
       {
           if (elem_array == (int *) base)
           {
              return NULL;
           }
           else
           {
               elem_array--;
               return *elem_array;
               *elem_array = 0;
           }
       }

   private:
       int *elem_array;
       int base;
};

Stack stk;

#endif // ASSEMBLY++_HPP_INCLUDED
