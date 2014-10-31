#include <iostream>
#include <fstream>

using namespace std;

struct Tokens
{
    int token_count;
    string *token_array;

    void Initialize( )
    {
        token_count = 0;
        token_array = new string[0];
    }

    void ResizeTokens(int new_size)
    {
        string *new_list = new string[new_size];

        for(int cntr = 0; cntr < token_count;cntr++)
        {
            new_list[cntr] = token_array[cntr];
        }

        token_array = new_list;
    }

    void AddToken(string token)
    {
        token_array[token_count] = token;
        token_count++;
    }

    void AddTokensFromList(Tokens token_list)
    {
        for(int x = 0;x < token_list.token_count;x++)
        {
            ResizeTokens(token_list.token_count + 1);
            AddToken(token_list.token_array[x]);
        }
    }
};


struct Memory
{
    string mem_name;
    string mem_type;
    bool isConst;
};

struct MemoryList
{

        Memory *memory_list;
        int mem_count;

        void Initialize()
        {
            memory_list = new Memory[0];
            mem_count = 0;
        }

        void ResizeMemory(int newsize)
        {
            Memory *newlist = new Memory[newsize];

            for(int cntr = 0;cntr < mem_count;cntr++)
            {
                 newlist[cntr] = memory_list[cntr];
            }

            memory_list =  newlist;
        }

        void AddMemory(Memory &mem_obj)
        {
           memory_list[mem_count].mem_name = mem_obj.mem_name;
           memory_list[mem_count].mem_type = mem_obj.mem_type;
           memory_list[mem_count].isConst = mem_obj.isConst;
           mem_count++;
        }

        bool RemoveMemory(string mem_name)
        {
            Memory *newlist = new Memory[mem_count - 1];
            bool succes = false;

            for(int cntr = 0;cntr < (mem_count - 1);cntr++)
            {
                if (this->memory_list[cntr].mem_name == mem_name)
                {
                    newlist[cntr].mem_name = memory_list[cntr + 1].mem_name;
                    newlist[cntr].mem_type = memory_list[cntr + 1].mem_type;
                    newlist[cntr].isConst = memory_list[cntr + 1].isConst;
                    cntr++;
                    succes = true;
                }
                else
                {
                    newlist[cntr].mem_name = this->memory_list[cntr].mem_name;
                    newlist[cntr].mem_type = this->memory_list[cntr].mem_type;
                }
            }

            if (!succes)
            {
                return false;
            }

            memory_list = newlist;

            return true;
        }
};

struct Point
{
    string point_name;
};

struct PointList
{
    Point *point_array;
    int point_count;

    void Initialize( )
    {
        point_array = new Point[0];
        point_count = 0;
    }

    void ResizeList(int newsize )
    {
        Point *newlist = new Point[newsize];

        for(int cntr = 0;cntr < point_count;cntr++)
        {
            newlist[cntr] = point_array[cntr];
        }

        point_array = newlist;
    }

    void AddPoint(Point point_name)
    {
        point_array[point_count] = point_name;
        point_count++;
    }
};

struct FunctionList
{
    string *function_names;
    int function_count;

    void Initialize( )
    {
       function_names = new string[0];
       function_count = 0;
    }

    void ResizeFunctions(int newsize)
    {
        string *newlist = new string[newsize];

        for(int cntr = 0;cntr < function_count;cntr++)
        {
            newlist[cntr] = function_names[cntr];
        }

        function_names = newlist;
    }

    void AddFunction(string function_name)
    {
        function_names[function_count] = function_name;
        function_count++;
    }
};

FunctionList func_list;
bool rec_error = false;

int parseIf(ofstream &file_stm,int current_count,Tokens &token_list,MemoryList prev_mem,PointList prev_list)
{
    string cur_action = "";
    int error_count = 0;
    int line_count = 0;
    MemoryList var_list;
    var_list.Initialize();
    Memory def_mem;
    PointList pnt_list;
    pnt_list.Initialize();

    for(register int cntr = 0;cntr < prev_mem.mem_count;cntr++)
    {
        var_list.ResizeMemory(var_list.mem_count + 1);
        var_list.AddMemory(prev_mem.memory_list[cntr]);
    }

    for(register int cntr = 0;cntr < prev_list.point_count;cntr++)
    {
        Point newPoint;
        newPoint.point_name = prev_list.point_array[cntr].point_name;
        pnt_list.ResizeList(pnt_list.point_count + 1);
        pnt_list.AddPoint(newPoint);
    }

    for(register int cntr = current_count;cntr < token_list.token_count;cntr++)
    {
       if (cur_action == "")
       {
           if (token_list.token_array[cntr] == "use")
           {
              cur_action = "use";
           }
           else if (token_list.token_array[cntr] == "_define")
           {
               cur_action = "_define";
           }
           else if (token_list.token_array[cntr] == "mem")
           {
               cur_action = "mem";
           }
           else if (token_list.token_array[cntr] == "mem_")
           {
               cur_action = "mem_";
           }
           else if (token_list.token_array[cntr] == "msg")
           {
               cur_action = "msg";
           }
           else if (token_list.token_array[cntr] == "msg_")
           {
               cur_action = "msg_";
           }
           else if (token_list.token_array[cntr] == "set")
           {
               cur_action = "set";
           }
           else if (token_list.token_array[cntr] == "add")
           {
               cur_action = "add";
           }
           else if (token_list.token_array[cntr] == "sub")
           {
               cur_action = "sub";
           }
           else if (token_list.token_array[cntr] == "mul")
           {
               cur_action = "mul";
           }
           else if (token_list.token_array[cntr] == "div")
           {
               cur_action = "div";
           }
           else if (token_list.token_array[cntr] == "mod")
           {
               cur_action = "mod";
           }
           else if (token_list.token_array[cntr] == "param_clear")
           {
               cur_action = "param_clear";
           }
           else if (token_list.token_array[cntr] == "transfer")
           {
               cur_action = "transfer";
           }
           else if (token_list.token_array[cntr] == "dispach")
           {
               cur_action = "dispach";
           }
           else if (token_list.token_array[cntr] == "point")
           {
               cur_action = "point";
           }
           else if (token_list.token_array[cntr] == "jump")
           {
               cur_action = "jump";
           }
           else if (token_list.token_array[cntr] == "char_get")
           {
               cur_action = "char_get";
           }
           else if (token_list.token_array[cntr] == "close")
           {
               file_stm << endl << "exit(1);";

               cur_action = "end_syntax";
           }
           else if (token_list.token_array[cntr] == "receive")
           {
               cur_action = "receive";
           }
           else if (token_list.token_array[cntr] == "<-")
           {
               if (error_count > 0)
               {
                   rec_error = true;
               }

               file_stm << endl << "}";
               return cntr;
           }
           else if (token_list.token_array[cntr] == "view")
           {
               cur_action = "view";
           }
           else if (token_list.token_array[cntr] == "get")
           {
               cur_action = "get";
           }
           else if (token_list.token_array[cntr] == "push")
           {
               cur_action = "push";
           }
           else if (token_list.token_array[cntr] == "pop")
           {
               cur_action = "pop";
           }
           else if (token_list.token_array[cntr] == "load_file")
           {
               cur_action = "load_file";
           }
           else if (token_list.token_array[cntr] == "param_get")
           {
               cur_action = "param_get";
           }
           else if (token_list.token_array[cntr] == "param_get_")
           {
               cur_action = "param_get_";
           }
           else if (token_list.token_array[cntr] == "cmp")
           {
               cur_action = "cmp";
           }
           else
           {
               bool succes = false;

               for(int cntr0 = 0;cntr0 < func_list.function_count;cntr0++)
               {
                   if (func_list.function_names[cntr0] == token_list.token_array[cntr])
                   {
                        succes = true;
                        break;
                   }
               }

               if (succes)
               {
                   file_stm << endl << token_list.token_array[cntr] << "();";
                   cur_action = "end_syntax";
               }
               else
               {
                    cout << endl << "* Warning : Unknown keyword " << token_list.token_array[cntr] << " *";
               }
           }
       }
       else if (cur_action == "end_syntax")
       {
           if (token_list.token_array[cntr] == ";")
           {
               cur_action = "";
           }
           else
           {
               if (error_count == 0)
               {
                   cout << endl << endl << "Errors Found...";
                   cout << endl << "* Expected end of syntax *" << ++line_count;
               }
               else
               {
                    cout << endl << "* Expected end of syntax *" << ++line_count;
               }

               error_count++;
               cur_action = "";
           }
       }
       else
       {
           if (cur_action == "use")
           {
               ifstream file_stm(token_list.token_array[cntr].c_str());

               if (!file_stm.is_open())
               {
                   if (error_count == 0)
                   {
                     cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Header file not found in use statement ( " << token_list.token_array[cntr].c_str() << " ) *";
                   error_count++;
               }

               cur_action = "end_syntax";
           }
           else if (cur_action == "_define")
           {
               bool succes = true;

               for(int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   cur_action = "_define_value";
                   error_count++;
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "int";
                   def_mem.isConst = true;

                   file_stm << endl << "const int " << def_mem.mem_name << " = ";

                   cur_action = "_define_value";
               }
           }
           else if (cur_action == "_define_value")
           {
                bool succes = true;

                for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                {
                    string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                    if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                    {
                         succes = false;
                         break;
                    }
                }

                if (succes)
                {
                    var_list.ResizeMemory(var_list.mem_count + 1);
                    var_list.AddMemory(def_mem);
                    def_mem.mem_name = def_mem.mem_type = "";
                    def_mem.isConst = false;
                    file_stm << token_list.token_array[cntr] << ";";
                    cur_action = "end_syntax";
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                        cout << endl << "* Illegal value given in constant declaration *";
                    }
                    else
                    {
                        cout << endl << "* Illegal value given in constant declaration *";
                    }

                    error_count++;
                    cur_action = "end_syntax";
                }
           }
           else if (cur_action == "mem")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "mem_comma";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "int";
                   def_mem.isConst = false;

                   file_stm << endl << "int " << def_mem.mem_name << " = ";

                   cur_action = "mem_comma";
               }
           }
           else if (cur_action == "mem_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "mem_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in memory declaration * " + ++line_count;

                   error_count++;
                   cur_action = "mem_value";
               }
           }
           else if (cur_action == "mem_value")
           {
               bool succes = true;

               for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (var_list.memory_list[cntr0].mem_type == "int")
                       {

                       succes = true;
                       goto jmp;

                       }
                       else
                       {
                           goto jmp;
                       }
                   }
               }

                for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                {
                    string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                    if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                    {
                         succes = false;
                         break;
                    }
                }

jmp:
                if (succes)
                {
                    var_list.ResizeMemory(var_list.mem_count + 1);
                    var_list.AddMemory(def_mem);
                    def_mem.mem_name = def_mem.mem_type = "";
                    def_mem.isConst = false;
                    file_stm << token_list.token_array[cntr] << ";";
                    cur_action = "end_syntax";
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                        cout << endl << "* Illegal value given in integer memory declaration *";
                    }
                    else
                    {
                        cout << endl << "* Illegal value given in integer memory declaration *";
                    }

                    error_count++;
                    cur_action = "end_syntax";
                }
           }
           else if (cur_action == "mem_")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "mem__comma";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "string";
                   def_mem.isConst = false;

                   file_stm << endl << "string " << def_mem.mem_name << " = ";

                   cur_action = "mem__comma";
               }
           }
           else if (cur_action == "mem__comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "mem__value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in memory declaration * " + ++line_count;

                   error_count++;
                   cur_action = "mem__value";
               }
           }
           else if (cur_action == "mem__value")
           {
               bool succes = false;

               for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (var_list.memory_list[cntr0].mem_type == "string")
                       {
                        succes = true;
                        goto jmp2;
                       }
                       else
                       {
                           goto jmp2;
                       }
                   }
               }

                if (token_list.token_array[cntr].substr(0,1) == "'")
                {
                    succes = true;
                }

jmp2:
                if (succes)
                {
                    var_list.ResizeMemory(var_list.mem_count + 1);
                    var_list.AddMemory(def_mem);
                    def_mem.mem_name = def_mem.mem_type = "";
                    def_mem.isConst = false;
                    file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "'" << ";";
                    cur_action = "end_syntax";
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                        cout << endl << "* Illegal value given in string memory declaration *";
                    }
                    else
                    {
                        cout << endl << "* Illegal value given in string memory declaration *";
                    }

                    error_count++;
                    cur_action = "end_syntax";
                }
           }
           else if (cur_action == "msg")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "msg";
                   def_mem.isConst = false;
                   var_list.ResizeMemory(var_list.mem_count + 1);
                   var_list.AddMemory(def_mem);
                   def_mem.mem_name = def_mem.mem_type = "";

                   file_stm << endl << "MessageINT " << token_list.token_array[cntr] << ";";

                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "msg_")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "msg_";
                   def_mem.isConst = false;
                   var_list.ResizeMemory(var_list.mem_count + 1);
                   var_list.AddMemory(def_mem);
                   def_mem.mem_name = def_mem.mem_type = "";

                   file_stm << endl << "MessageSTRING " << token_list.token_array[cntr] << ";";

                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "set")
           {
               bool succes = false;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                         def_mem.mem_name = var_list.memory_list[cntr0].mem_name;
                         def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                         succes = true;
                         break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "set_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " = ";

                   cur_action = "set_comma";
               }
           }
           else if (cur_action == "set_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "set_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in SET statement * " << ++line_count;

                   error_count++;
                   cur_action = "set_value";
               }
           }
           else if (cur_action == "set_value")
           {
               if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp03;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp03:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in SET statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (def_mem.mem_type == "string")
               {
                   bool isVar = false;
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                       {
                         isVar = true;
                         succes = true;
                         goto jmp04;
                       }
                   }

                   succes = true;

                   if (token_list.token_array[cntr].substr(0,1) != "'")
                   {
                       succes = false;
                   }

    jmp04:

                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                        if (isVar)
                        {
                            file_stm << token_list.token_array[cntr] << ";";
                        }
                        else
                        {
                            file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "';";
                        }

                        cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected string value in SET statement * " << ++line_count;

                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in SET statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "add")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "add_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " += ";

                   cur_action = "add_comma";
               }
           }
           else if (cur_action == "add_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "add_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in ADD statement * " << ++line_count;

                   error_count++;
                   cur_action = "add_value";
               }
           }
           else if (cur_action == "add_value")
           {
               if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp05;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp05:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in ADD statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (def_mem.mem_type == "string")
               {
                   bool isVar = false;
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                       {
                         isVar = true;
                         succes = true;
                         goto jmp06;
                       }
                   }

                   succes = true;

                   if (token_list.token_array[cntr].substr(0,1) != "'")
                   {
                       succes = false;
                   }

    jmp06:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                        if (isVar)
                        {
                            file_stm << token_list.token_array[cntr] << ";";
                        }
                        else
                        {
                            file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "';";
                        }

                        cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected string value in ADD statement * " << ++line_count;

                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in ADD statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "sub")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "sub_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " -= ";

                   cur_action = "sub_comma";
               }
           }
           else if (cur_action == "sub_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "sub_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in SUB statement * " << ++line_count;

                   error_count++;
                   cur_action = "sub_value";
               }
           }
           else if (cur_action == "sub_value")
           {
               if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp07;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp07:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in SUB statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in SUB statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
          }
          else if (cur_action == "mul")
          {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "mul_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " *= ";

                   cur_action = "mul_comma";
               }
          }
          else if (cur_action == "mul_comma")
          {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "mul_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in MUL statement * " << ++line_count;

                   error_count++;
                   cur_action = "mul_value";
               }
          }
          else if (cur_action == "mul_value")
          {
              if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp08;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp08:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in MUL statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in MUL statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "div")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "div_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " /= ";

                   cur_action = "div_comma";
               }
           }
           else if (cur_action == "div_comma")
           {
                if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "div_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in DIV statement * " << ++line_count;

                   error_count++;
                   cur_action = "div_value";
               }
           }
           else if (cur_action == "div_value")
           {
               if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp09;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp09:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in DIV statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in DIV statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "mod")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "mod_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " = " << token_list.token_array[cntr] << " % ";

                   cur_action = "mod_comma";
               }
           }
           else if (cur_action == "mod_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "mod_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in MOD statement * " << ++line_count;

                   error_count++;
                   cur_action = "mod_value";
               }
           }
           else if (cur_action == "mod_value")
           {
               if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp_mod;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp_mod:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in MOD statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in MOD statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "param_clear")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "msg" || var_list.memory_list[cntr0].mem_name == "msg_"))
                   {
                        succes = true;
                        break;
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << ".ClearParam( );";

                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "transfer")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "msg" || var_list.memory_list[cntr0].mem_type == "msg_"))
                   {
                        def_mem.mem_name = token_list.token_array[cntr];
                        def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                        def_mem.isConst = false;
                        succes = true;
                        break;
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "transfer_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << ".AddParam(";

                   cur_action = "transfer_comma";
               }
           }
           else if (cur_action == "transfer_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "transfer_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in TRANSFER statement * " << ++line_count;

                   error_count++;
                   cur_action = "transfer_value";
               }
           }
           else if (cur_action == "transfer_value")
           {
               if (def_mem.mem_type == "msg")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp10;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp10:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ");";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in transfer statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (def_mem.mem_type == "msg_")
               {
                   bool isVar = false;
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "msg_")
                       {
                         isVar = true;
                         succes = true;
                         goto jmp11;
                       }
                   }

                   succes = true;

                   if (token_list.token_array[cntr].substr(0,1) != "'")
                   {
                       succes = false;
                   }

    jmp11:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                        if (isVar)
                        {
                            file_stm << token_list.token_array[cntr] << ");";
                        }
                        else
                        {
                            file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "');";
                        }

                        cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected string value in transfer statement * " << ++line_count;

                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in transfer statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "dispach")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "msg" || var_list.memory_list[cntr0].mem_type == "msg_"))
                   {
                        succes = true;
                        break;
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << ".Dispach( );";

                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "point")
           {
               bool succes = true;

               for(int cntr0 = 0;cntr0 < pnt_list.point_count;cntr0++)
               {
                   if (pnt_list.point_array[cntr0].point_name == token_list.token_array[cntr])
                   {
                        succes = false;
                        break;
                   }
               }

               if (succes)
               {
                   Point newPoint;
                   newPoint.point_name = token_list.token_array[cntr];
                   pnt_list.ResizeList(pnt_list.point_count + 1);
                   pnt_list.AddPoint(newPoint);

                   file_stm << endl << newPoint.point_name << ":";

                   cur_action = "end_syntax";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The point name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The point name is already defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "jump")
           {
                bool succes = false;

                for (int cntr0 = 0;cntr0 < pnt_list.point_count;cntr0++)
                {
                    if (pnt_list.point_array[cntr0].point_name == token_list.token_array[cntr])
                    {
                       succes = true;
                       break;
                    }
                }

                if (succes)
                {
                    file_stm << endl << "goto " << token_list.token_array[cntr] << ";";

                    cur_action = "end_syntax";
                }
                else
                {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The point name not found *";
                   }
                   else
                   {
                        cout << endl << "* The point name not found *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
                }
           }
           else if (cur_action == "char_get")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                   {
                        def_mem.mem_name = token_list.token_array[cntr];
                        def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                        def_mem.isConst = false;
                        succes = true;
                        break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "char_get_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " = ";

                   cur_action = "char_get_comma";
               }
           }
           else if (cur_action == "char_get_comma")
           {
                if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "char_get_source";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in CHAR_GET statement * " << ++line_count;

                   error_count++;
                   cur_action = "char_get_source";
               }
           }
           else if (cur_action == "char_get_source")
           {
               if (def_mem.mem_type == "string")
               {
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                       {
                         succes = true;
                         break;
                       }
                   }



                    if (succes)
                    {
                        def_mem.mem_name = def_mem.mem_type = "";
                        def_mem.isConst = false;

                        file_stm << token_list.token_array[cntr] << ".substr(";

                        cur_action = "char_get_comma1";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected string value in CHAR_GET statement * " << ++line_count;

                        error_count++;
                        cur_action = "char_get_comma1";
                   }
               }
           }
           else if (cur_action == "char_get_comma1")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "char_get_pos";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in CHAR_GET statement * " << ++line_count;

                   error_count++;
                   cur_action = "char_get_pos";
               }
           }
           else if (cur_action == "char_get_pos")
           {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp12;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp12:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ",1);";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in CHAR_GET statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
            }
            else if (cur_action == "receive")
            {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "string" || var_list.memory_list[cntr0].mem_type == "int"))
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* The string type is not supported in RECEIVE statement *";

                   error_count++;
                   cur_action = "receive_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " = ";

                   cur_action = "receive_comma";
               }
            }
            else if (cur_action == "receive_comma")
            {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "receive_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in RECEIVE statement * " << ++line_count;

                   error_count++;
                   cur_action = "receive_value";
               }
            }
            else if (cur_action == "receive_value")
            {
               if (def_mem.mem_type == "int")
               {
                    bool succes = false;
                    int cntr0;

                    for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
                    {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "msg")
                        {
                            succes = true;
                            break;
                        }
                    }

                    if (!succes)
                    {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected msg int type in RECEIVE statement *";
                        error_count++;
                        cur_action = "end_syntax";
                    }
                    else
                    {
                        def_mem.mem_name = def_mem.mem_type = "";
                        def_mem.isConst = false;

                        file_stm << token_list.token_array[cntr] << ".GetReturn();";
                        cur_action = "end_syntax";
                    }
                }
                else if (def_mem.mem_type == "string")
                {
                    bool succes = false;
                    int cntr0;

                    for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
                    {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "msg_")
                        {
                            succes = true;
                            break;
                        }
                    }

                    if (!succes)
                    {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected msg string type in RECEIVE statement *";
                        error_count++;
                        cur_action = "end_syntax";
                    }
                    else
                    {
                        def_mem.mem_name = def_mem.mem_type = "";
                        def_mem.isConst = false;

                        file_stm << token_list.token_array[cntr] << ".GetReturn();";
                        cur_action = "end_syntax";
                    }
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in RECEIVE statement *";
                    error_count++;
                    cur_action = "end_syntax";
                }

               }
               else if (cur_action == "view")
               {
                  if (token_list.token_array[cntr].substr(0,1) == "'")
                  {
                      file_stm << endl << "cout << '" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "'";
                      cur_action = "view_comma";
                  }
                  else
                  {
                     bool succes = false;

                     for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                     {
                         if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                         {
                             succes = true;
                             goto jump_view;
                         }
                     }

                     succes = true;

                     for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                     {
                         string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                         if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                         {
                             succes = false;
                             break;
                         }
                     }

jump_view:

                     if (succes)
                     {
                        file_stm << endl << "cout << " << token_list.token_array[cntr];
                        cur_action = "view_comma";
                     }
                     else
                     {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Unknown type value in VIEW statement *";
                        error_count++;
                        cur_action = "view_comma";
                     }
                  }
               }
               else if (cur_action == "view_comma")
               {
                   if (token_list.token_array[cntr] == ",")
                   {
                       cur_action = "view_op";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in VIEW statement *";
                        error_count++;
                        cur_action = "view_op";
                   }
               }
               else if (cur_action == "view_op")
               {
                   if (token_list.token_array[cntr] == "0")
                   {
                      file_stm << ";";
                      cur_action = "end_syntax";
                   }
                   else if (token_list.token_array[cntr] == "1")
                   {
                      file_stm << " << endl;";
                      cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected 1 / 0 value in VIEW statement *";
                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "get")
               {
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "int" || var_list.memory_list[cntr0].mem_type == "string"))
                       {
                           succes = true;
                           break;
                       }
                   }

                   if (succes)
                   {
                       file_stm << endl << "cin >> " << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected string / int type value in GET statement *";
                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "push")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp_push;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp_push:
                   if (succes)
                   {
                       file_stm << endl << "stk.push(" <<  token_list.token_array[cntr] << ");";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in PUSH statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "pop")
               {
                    bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                           succes = true;
                           break;
                       }
                   }

                   if (succes)
                   {
                       file_stm << endl << token_list.token_array[cntr] << " = stk.pop();";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected int type value in POP statement *";
                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "load_file")
               {
                  file_stm << endl << "#include '" << token_list.token_array[cntr] << "'";
                  cur_action = "end_syntax";
               }
               else if (cur_action == "param_get")
               {
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                        {
                            succes = true;
                            break;
                        }
                   }

                   if (succes)
                   {
                        file_stm << endl << token_list.token_array[cntr] << " = ";
                        cur_action = "param_get_comma";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in PARAM_GET statement *";
                       error_count++;
                       cur_action = "param_get_comma";
                   }
               }
               else if (cur_action == "param_get_comma")
               {
                     if (token_list.token_array[cntr] == ",")
                     {
                        cur_action = "param_get_source";
                     }
                     else
                     {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET statement *";
                        error_count++;
                        cur_action = "param_get_source";
                     }
               }
               else if (cur_action == "param_get_source")
               {
                    bool succes = false;

                    for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                    {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "msg")
                        {
                            succes = true;
                            break;
                        }
                    }

                    if (succes)
                    {
                        file_stm << token_list.token_array[cntr] << ".GetParamValue(";
                        cur_action = "param_get_comma1";
                    }
                    else
                    {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET statement *";
                        error_count++;
                        cur_action = "param_get_comma1";
                    }
               }
               else if (cur_action == "param_get_comma1")
               {
                     if (token_list.token_array[cntr] == ",")
                     {
                        cur_action = "param_get_value";
                     }
                     else
                     {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET statement *";
                        error_count++;
                        cur_action = "param_get_value";
                     }
               }
               else if (cur_action == "param_get_value")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp_param_get;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp_param_get:
                   if (succes)
                   {
                       file_stm <<  token_list.token_array[cntr] << ");";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in PARAM_GET statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "param_get_")
               {
                    bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                        {
                            succes = true;
                            break;
                        }
                   }

                   if (succes)
                   {
                        file_stm << endl << token_list.token_array[cntr] << " = ";
                        cur_action = "param_get_comma_";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected string type value in PARAM_GET_ statement *";
                       error_count++;
                       cur_action = "param_get_comma_";
                   }
               }
               else if (cur_action == "param_get_comma_")
               {
                    if (token_list.token_array[cntr] == ",")
                     {
                        cur_action = "param_get_source_";
                     }
                     else
                     {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET_ statement *";
                        error_count++;
                        cur_action = "param_get_source_";
                     }
               }
               else if (cur_action == "param_get_source_")
               {
                    bool succes = false;

                    for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                    {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "msg_")
                        {
                            succes = true;
                            break;
                        }
                    }

                    if (succes)
                    {
                        file_stm << token_list.token_array[cntr] << ".GetParamValue(";
                        cur_action = "param_get_comma1_";
                    }
                    else
                    {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET_ statement *";
                        error_count++;
                        cur_action = "param_get_comma1_";
                    }
               }
               else if (cur_action == "param_get_comma1_")
               {
                    if (token_list.token_array[cntr] == ",")
                     {
                        cur_action = "param_get_value_";
                     }
                     else
                     {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET_ statement *";
                        error_count++;
                        cur_action = "param_get_value_";
                     }
               }
               else if (cur_action == "param_get_value_")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp_param_get_;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp_param_get_:
                   if (succes)
                   {
                       file_stm <<  token_list.token_array[cntr] << ");";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in PARAM_GET_ statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "cmp")
               {
                    bool succes = false;

                    for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                    {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "int" || var_list.memory_list[cntr0].mem_type == "string"))
                        {
                            def_mem.mem_name = var_list.memory_list[cntr0].mem_name;
                            def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                            def_mem.isConst = var_list.memory_list[cntr0].isConst;

                            succes = true;
                            break;
                        }
                    }

                    if (succes)
                    {
                        file_stm << endl << "if (" << token_list.token_array[cntr];
                        cur_action = "cmp_op";
                    }
                    else
                    {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int / string type value in cmp statement * " << ++line_count;

                       error_count++;
                       cur_action = "cmp_op";
                    }
               }
               else if (cur_action == "cmp_op")
               {
                    if (token_list.token_array[cntr] == "=" || token_list.token_array[cntr] == "!=" || token_list.token_array[cntr] == "<" || token_list.token_array[cntr] == "<=" || token_list.token_array[cntr] == ">" || token_list.token_array[cntr] == ">=")
                    {
                        file_stm << " " << token_list.token_array[cntr];
                        cur_action = "cmp_val";
                    }
                    else
                    {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected logical operator in cmp statement * " << ++line_count;

                       error_count++;
                       cur_action = "cmp_val";
                    }
               }
               else if (cur_action == "cmp_val")
               {
                    if (def_mem.mem_type == "int")
                    {
                        bool succes = false;
                        int cntr0 = 0;

                        for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                        {
                            if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                            {
                                succes = true;
                                goto jmp_cmp_int;
                            }
                        }

                        succes = true;

                        for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                        {
                            string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                            if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                            {
                                succes = false;
                                break;
                            }
                        }
jmp_cmp_int:
                        if (succes)
                        {
                            def_mem.mem_name = def_mem.mem_type = "";
                            def_mem.isConst = false;

                            file_stm << " " << token_list.token_array[cntr] << ")";
                            cur_action = "cmp_getbrace";
                        }
                        else
                        {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Expected int type value in CMP statement * " << ++line_count;

                            error_count++;
                            cur_action = "cmp_getbrace";
                        }
                    }
                    else if (def_mem.mem_type == "string")
                    {
                        bool isVar = false;
                        bool succes = false;

                        for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                        {
                            if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                            {
                                isVar = true;
                                succes = true;
                                goto jmp_cmp_string;
                            }
                        }

                        succes = true;

                        if (token_list.token_array[cntr].substr(0,1) != "'")
                        {
                            succes = false;
                        }

jmp_cmp_string:

                        if (succes)
                        {
                            def_mem.mem_name = def_mem.mem_type = "";
                            def_mem.isConst = false;

                            if (isVar)
                            {
                                file_stm << token_list.token_array[cntr] << ")";
                            }
                            else
                            {
                                file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "')";
                            }

                            cur_action = "cmp_getbrace";
                        }
                        else
                        {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Expected string value in CMP statement * " << ++line_count;

                            error_count++;
                            cur_action = "cmp_getbrace";
                        }
                    }
                    else
                    {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Unknown type value in CMP statement * " << ++line_count;

                        error_count++;
                        cur_action = "cmp_getbrace";
                    }
               }
               else if (cur_action == "cmp_getbrace")
               {
                    if (token_list.token_array[cntr] == "->")
                    {
                       rec_error = false;
                       file_stm << endl << "{";

                       int res = parseIf(file_stm,cntr + 1,token_list,var_list,pnt_list);

                       if (res == -1)
                       {
                           error_count++;
                       }
                       else
                       {
                           if (rec_error)
                           {
                               error_count++;
                           }

                           cntr = res;
                       }

                       if (error_count > 0)
                       {
                           rec_error = true;
                       }

                       cur_action = "";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected -> after CMP statement *";
                        error_count++;
                        cur_action = "";
                   }
               }
            }
    }

    if (error_count == 0)
    {
        cout << endl << "Errors Found...";
    }

    cout << endl << "* Expected end of function *";

    return -1;
}

int parser_newpos = 0;

int parseFunction(ofstream &file_stm,int current_count,Tokens &token_list,MemoryList prev_mem)
{
    string cur_action = "";
    int error_count = 0;
    int line_count = 0;
    MemoryList var_list;
    var_list.Initialize();
    Memory def_mem;
    PointList pnt_list;
    pnt_list.Initialize();

    for(register int cntr = 0;cntr < prev_mem.mem_count;cntr++)
    {
        var_list.ResizeMemory(var_list.mem_count + 1);
        var_list.AddMemory(prev_mem.memory_list[cntr]);
    }

    for(register int cntr = current_count;cntr < token_list.token_count;cntr++)
    {
       if (cur_action == "")
       {
           if (token_list.token_array[cntr] == "use")
           {
              cur_action = "use";
           }
           else if (token_list.token_array[cntr] == "_define")
           {
               cur_action = "_define";
           }
           else if (token_list.token_array[cntr] == "mem")
           {
               cur_action = "mem";
           }
           else if (token_list.token_array[cntr] == "mem_")
           {
               cur_action = "mem_";
           }
           else if (token_list.token_array[cntr] == "msg")
           {
               cur_action = "msg";
           }
           else if (token_list.token_array[cntr] == "msg_")
           {
               cur_action = "msg_";
           }
           else if (token_list.token_array[cntr] == "set")
           {
               cur_action = "set";
           }
           else if (token_list.token_array[cntr] == "add")
           {
               cur_action = "add";
           }
           else if (token_list.token_array[cntr] == "sub")
           {
               cur_action = "sub";
           }
           else if (token_list.token_array[cntr] == "mul")
           {
               cur_action = "mul";
           }
           else if (token_list.token_array[cntr] == "div")
           {
               cur_action = "div";
           }
           else if (token_list.token_array[cntr] == "mod")
           {
               cur_action = "mod";
           }
           else if (token_list.token_array[cntr] == "param_clear")
           {
               cur_action = "param_clear";
           }
           else if (token_list.token_array[cntr] == "transfer")
           {
               cur_action = "transfer";
           }
           else if (token_list.token_array[cntr] == "dispach")
           {
               cur_action = "dispach";
           }
           else if (token_list.token_array[cntr] == "point")
           {
               cur_action = "point";
           }
           else if (token_list.token_array[cntr] == "jump")
           {
               cur_action = "jump";
           }
           else if (token_list.token_array[cntr] == "char_get")
           {
               cur_action = "char_get";
           }
           else if (token_list.token_array[cntr] == "close")
           {
               file_stm << endl << "exit(1);";

               cur_action = "end_syntax";
           }
           else if (token_list.token_array[cntr] == "receive")
           {
               cur_action = "receive";
           }
           else if (token_list.token_array[cntr] == "<-")
           {
               if (error_count > 0)
               {
                   rec_error = true;
               }

               file_stm << endl << "}";
               parser_newpos = cntr;
               return 0;
           }
           else if (token_list.token_array[cntr] == "view")
           {
               cur_action = "view";
           }
           else if (token_list.token_array[cntr] == "get")
           {
               cur_action = "get";
           }
           else if (token_list.token_array[cntr] == "push")
           {
               cur_action = "push";
           }
           else if (token_list.token_array[cntr] == "pop")
           {
               cur_action = "pop";
           }
           else if (token_list.token_array[cntr] == "load_file")
           {
               cur_action = "load_file";
           }
           else if (token_list.token_array[cntr] == "param_get")
           {
               cur_action = "param_get";
           }
           else if (token_list.token_array[cntr] == "param_get_")
           {
               cur_action = "param_get_";
           }
           else if (token_list.token_array[cntr] == "cmp")
           {
               cur_action = "cmp";
           }
           else
           {
               bool succes = false;

               for(int cntr0 = 0;cntr0 < func_list.function_count;cntr0++)
               {
                   if (func_list.function_names[cntr0] == token_list.token_array[cntr])
                   {
                        succes = true;
                        break;
                   }
               }

               if (succes)
               {
                   file_stm << endl << token_list.token_array[cntr] << "();";
                   cur_action = "end_syntax";
               }
               else
               {
                    cout << endl << "* Warning : Unknown keyword " << token_list.token_array[cntr] << " *";
               }
           }
       }
       else if (cur_action == "end_syntax")
       {
           if (token_list.token_array[cntr] == ";")
           {
               cur_action = "";
           }
           else
           {
               if (error_count == 0)
               {
                   cout << endl << endl << "Errors Found...";
                   cout << endl << "* Expected end of syntax *" << ++line_count;
               }
               else
               {
                    cout << endl << "* Expected end of syntax *" << ++line_count;
               }

               error_count++;
               cur_action = "";
           }
       }
       else
       {
           if (cur_action == "use")
           {
               ifstream file_stm(token_list.token_array[cntr].c_str());

               if (!file_stm.is_open())
               {
                   if (error_count == 0)
                   {
                     cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Header file not found in use statement ( " << token_list.token_array[cntr].c_str() << " ) *";
                   error_count++;
               }

               cur_action = "end_syntax";
           }
           else if (cur_action == "_define")
           {
               bool succes = true;

               for(int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   cur_action = "_define_value";
                   error_count++;
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "int";
                   def_mem.isConst = true;

                   file_stm << endl << "const int " << def_mem.mem_name << " = ";

                   cur_action = "_define_value";
               }
           }
           else if (cur_action == "_define_value")
           {
                bool succes = true;

                for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                {
                    string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                    if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                    {
                         succes = false;
                         break;
                    }
                }

                if (succes)
                {
                    var_list.ResizeMemory(var_list.mem_count + 1);
                    var_list.AddMemory(def_mem);
                    def_mem.mem_name = def_mem.mem_type = "";
                    def_mem.isConst = false;
                    file_stm << token_list.token_array[cntr] << ";";
                    cur_action = "end_syntax";
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                        cout << endl << "* Illegal value given in constant declaration *";
                    }
                    else
                    {
                        cout << endl << "* Illegal value given in constant declaration *";
                    }

                    error_count++;
                    cur_action = "end_syntax";
                }
           }
           else if (cur_action == "mem")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "mem_comma";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "int";
                   def_mem.isConst = false;

                   file_stm << endl << "int " << def_mem.mem_name << " = ";

                   cur_action = "mem_comma";
               }
           }
           else if (cur_action == "mem_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "mem_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in memory declaration * " + ++line_count;

                   error_count++;
                   cur_action = "mem_value";
               }
           }
           else if (cur_action == "mem_value")
           {
               bool succes = true;

               for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (var_list.memory_list[cntr0].mem_type == "int")
                       {

                       succes = true;
                       goto jmp;

                       }
                       else
                       {
                           goto jmp;
                       }
                   }
               }

                for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                {
                    string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                    if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                    {
                         succes = false;
                         break;
                    }
                }

jmp:
                if (succes)
                {
                    var_list.ResizeMemory(var_list.mem_count + 1);
                    var_list.AddMemory(def_mem);
                    def_mem.mem_name = def_mem.mem_type = "";
                    def_mem.isConst = false;
                    file_stm << token_list.token_array[cntr] << ";";
                    cur_action = "end_syntax";
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                        cout << endl << "* Illegal value given in integer memory declaration *";
                    }
                    else
                    {
                        cout << endl << "* Illegal value given in integer memory declaration *";
                    }

                    error_count++;
                    cur_action = "end_syntax";
                }
           }
           else if (cur_action == "mem_")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "mem__comma";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "string";
                   def_mem.isConst = false;

                   file_stm << endl << "string " << def_mem.mem_name << " = ";

                   cur_action = "mem__comma";
               }
           }
           else if (cur_action == "mem__comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "mem__value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in memory declaration * " + ++line_count;

                   error_count++;
                   cur_action = "mem__value";
               }
           }
           else if (cur_action == "mem__value")
           {
               bool succes = false;

               for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (var_list.memory_list[cntr0].mem_type == "string")
                       {
                        succes = true;
                        goto jmp2;
                       }
                       else
                       {
                           goto jmp2;
                       }
                   }
               }

                if (token_list.token_array[cntr].substr(0,1) == "'")
                {
                    succes = true;
                }

jmp2:
                if (succes)
                {
                    var_list.ResizeMemory(var_list.mem_count + 1);
                    var_list.AddMemory(def_mem);
                    def_mem.mem_name = def_mem.mem_type = "";
                    def_mem.isConst = false;
                    file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "'" << ";";
                    cur_action = "end_syntax";
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                        cout << endl << "* Illegal value given in string memory declaration *";
                    }
                    else
                    {
                        cout << endl << "* Illegal value given in string memory declaration *";
                    }

                    error_count++;
                    cur_action = "end_syntax";
                }
           }
           else if (cur_action == "msg")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "msg";
                   def_mem.isConst = false;
                   var_list.ResizeMemory(var_list.mem_count + 1);
                   var_list.AddMemory(def_mem);
                   def_mem.mem_name = def_mem.mem_type = "";

                   file_stm << endl << "MessageINT " << token_list.token_array[cntr] << ";";

                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "msg_")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "msg_";
                   def_mem.isConst = false;
                   var_list.ResizeMemory(var_list.mem_count + 1);
                   var_list.AddMemory(def_mem);
                   def_mem.mem_name = def_mem.mem_type = "";

                   file_stm << endl << "MessageSTRING " << token_list.token_array[cntr] << ";";

                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "set")
           {
               bool succes = false;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                         def_mem.mem_name = var_list.memory_list[cntr0].mem_name;
                         def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                         succes = true;
                         break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "set_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " = ";

                   cur_action = "set_comma";
               }
           }
           else if (cur_action == "set_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "set_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in SET statement * " << ++line_count;

                   error_count++;
                   cur_action = "set_value";
               }
           }
           else if (cur_action == "set_value")
           {
               if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp03;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp03:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in SET statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (def_mem.mem_type == "string")
               {
                   bool isVar = false;
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                       {
                         isVar = true;
                         succes = true;
                         goto jmp04;
                       }
                   }

                   succes = true;

                   if (token_list.token_array[cntr].substr(0,1) != "'")
                   {
                       succes = false;
                   }

    jmp04:

                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                        if (isVar)
                        {
                            file_stm << token_list.token_array[cntr] << ";";
                        }
                        else
                        {
                            file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "';";
                        }

                        cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected string value in SET statement * " << ++line_count;

                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in SET statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "add")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "add_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " += ";

                   cur_action = "add_comma";
               }
           }
           else if (cur_action == "add_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "add_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in ADD statement * " << ++line_count;

                   error_count++;
                   cur_action = "add_value";
               }
           }
           else if (cur_action == "add_value")
           {
               if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp05;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp05:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in ADD statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (def_mem.mem_type == "string")
               {
                   bool isVar = false;
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                       {
                         isVar = true;
                         succes = true;
                         goto jmp06;
                       }
                   }

                   succes = true;

                   if (token_list.token_array[cntr].substr(0,1) != "'")
                   {
                       succes = false;
                   }

    jmp06:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                        if (isVar)
                        {
                            file_stm << token_list.token_array[cntr] << ";";
                        }
                        else
                        {
                            file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "';";
                        }

                        cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected string value in ADD statement * " << ++line_count;

                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in ADD statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "sub")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "sub_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " -= ";

                   cur_action = "sub_comma";
               }
           }
           else if (cur_action == "sub_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "sub_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in SUB statement * " << ++line_count;

                   error_count++;
                   cur_action = "sub_value";
               }
           }
           else if (cur_action == "sub_value")
           {
               if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp07;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp07:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in SUB statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in SUB statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
          }
          else if (cur_action == "mul")
          {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "mul_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " *= ";

                   cur_action = "mul_comma";
               }
          }
          else if (cur_action == "mul_comma")
          {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "mul_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in MUL statement * " << ++line_count;

                   error_count++;
                   cur_action = "mul_value";
               }
          }
          else if (cur_action == "mul_value")
          {
              if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp08;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp08:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in MUL statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in MUL statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "div")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "div_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " /= ";

                   cur_action = "div_comma";
               }
           }
           else if (cur_action == "div_comma")
           {
                if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "div_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in DIV statement * " << ++line_count;

                   error_count++;
                   cur_action = "div_value";
               }
           }
           else if (cur_action == "div_value")
           {
               if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp09;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp09:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in DIV statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in DIV statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "mod")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "mod_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " = " << token_list.token_array[cntr] << " % ";

                   cur_action = "mod_comma";
               }
           }
           else if (cur_action == "mod_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "mod_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in MOD statement * " << ++line_count;

                   error_count++;
                   cur_action = "mod_value";
               }
           }
           else if (cur_action == "mod_value")
           {
               if (def_mem.mem_type == "int")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp_mod;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp_mod:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in MOD statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in MOD statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "param_clear")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "msg" || var_list.memory_list[cntr0].mem_name == "msg_"))
                   {
                        succes = true;
                        break;
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << ".ClearParam( );";

                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "transfer")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "msg" || var_list.memory_list[cntr0].mem_type == "msg_"))
                   {
                        def_mem.mem_name = token_list.token_array[cntr];
                        def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                        def_mem.isConst = false;
                        succes = true;
                        break;
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "transfer_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << ".AddParam(";

                   cur_action = "transfer_comma";
               }
           }
           else if (cur_action == "transfer_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "transfer_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in TRANSFER statement * " << ++line_count;

                   error_count++;
                   cur_action = "transfer_value";
               }
           }
           else if (cur_action == "transfer_value")
           {
               if (def_mem.mem_type == "msg")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp10;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp10:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ");";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in transfer statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (def_mem.mem_type == "msg_")
               {
                   bool isVar = false;
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "msg_")
                       {
                         isVar = true;
                         succes = true;
                         goto jmp11;
                       }
                   }

                   succes = true;

                   if (token_list.token_array[cntr].substr(0,1) != "'")
                   {
                       succes = false;
                   }

    jmp11:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                        if (isVar)
                        {
                            file_stm << token_list.token_array[cntr] << ");";
                        }
                        else
                        {
                            file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "');";
                        }

                        cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected string value in transfer statement * " << ++line_count;

                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else
               {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in transfer statement * " << ++line_count;

                    error_count++;
                    cur_action = "end_syntax";
               }
           }
           else if (cur_action == "dispach")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "msg" || var_list.memory_list[cntr0].mem_type == "msg_"))
                   {
                        succes = true;
                        break;
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << ".Dispach( );";

                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "point")
           {
               bool succes = true;

               for(int cntr0 = 0;cntr0 < pnt_list.point_count;cntr0++)
               {
                   if (pnt_list.point_array[cntr0].point_name == token_list.token_array[cntr])
                   {
                        succes = false;
                        break;
                   }
               }

               if (succes)
               {
                   Point newPoint;
                   newPoint.point_name = token_list.token_array[cntr];
                   pnt_list.ResizeList(pnt_list.point_count + 1);
                   pnt_list.AddPoint(newPoint);

                   file_stm << endl << newPoint.point_name << ":";

                   cur_action = "end_syntax";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The point name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The point name is already defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "jump")
           {
                bool succes = false;

                for (int cntr0 = 0;cntr0 < pnt_list.point_count;cntr0++)
                {
                    if (pnt_list.point_array[cntr0].point_name == token_list.token_array[cntr])
                    {
                       succes = true;
                       break;
                    }
                }

                if (succes)
                {
                    file_stm << endl << "goto " << token_list.token_array[cntr] << ";";

                    cur_action = "end_syntax";
                }
                else
                {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The point name not found *";
                   }
                   else
                   {
                        cout << endl << "* The point name not found *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
                }
           }
           else if (cur_action == "char_get")
           {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                   {
                        def_mem.mem_name = token_list.token_array[cntr];
                        def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                        def_mem.isConst = false;
                        succes = true;
                        break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is not defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is not defined *";
                   }

                   error_count++;
                   cur_action = "char_get_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " = ";

                   cur_action = "char_get_comma";
               }
           }
           else if (cur_action == "char_get_comma")
           {
                if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "char_get_source";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in CHAR_GET statement * " << ++line_count;

                   error_count++;
                   cur_action = "char_get_source";
               }
           }
           else if (cur_action == "char_get_source")
           {
               if (def_mem.mem_type == "string")
               {
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                       {
                         succes = true;
                         break;
                       }
                   }



                    if (succes)
                    {
                        def_mem.mem_name = def_mem.mem_type = "";
                        def_mem.isConst = false;

                        file_stm << token_list.token_array[cntr] << ".substr(";

                        cur_action = "char_get_comma1";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected string value in CHAR_GET statement * " << ++line_count;

                        error_count++;
                        cur_action = "char_get_comma1";
                   }
               }
           }
           else if (cur_action == "char_get_comma1")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "char_get_pos";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in CHAR_GET statement * " << ++line_count;

                   error_count++;
                   cur_action = "char_get_pos";
               }
           }
           else if (cur_action == "char_get_pos")
           {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp12;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp12:
                   if (succes)
                   {
                       def_mem.mem_name = def_mem.mem_type = "";
                       def_mem.isConst = false;

                       file_stm << token_list.token_array[cntr] << ",1);";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in CHAR_GET statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
            }
            else if (cur_action == "receive")
            {
               bool succes = false;
               int cntr0;

               for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "string" || var_list.memory_list[cntr0].mem_type == "int"))
                   {
                       if (!var_list.memory_list[cntr0].isConst)
                       {
                           def_mem.mem_name = token_list.token_array[cntr];
                           def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                           def_mem.isConst = false;
                           succes = true;
                           break;
                       }
                       else
                       {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Constant value cannot be changed * " << ++line_count;
                            error_count++;
                            succes = false;
                            break;
                       }
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* The string type is not supported in RECEIVE statement *";

                   error_count++;
                   cur_action = "receive_comma";
               }
               else
               {
                   file_stm << endl << token_list.token_array[cntr] << " = ";

                   cur_action = "receive_comma";
               }
            }
            else if (cur_action == "receive_comma")
            {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "receive_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in RECEIVE statement * " << ++line_count;

                   error_count++;
                   cur_action = "receive_value";
               }
            }
            else if (cur_action == "receive_value")
            {
               if (def_mem.mem_type == "int")
               {
                    bool succes = false;
                    int cntr0;

                    for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
                    {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "msg")
                        {
                            succes = true;
                            break;
                        }
                    }

                    if (!succes)
                    {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected msg int type in RECEIVE statement *";
                        error_count++;
                        cur_action = "end_syntax";
                    }
                    else
                    {
                        def_mem.mem_name = def_mem.mem_type = "";
                        def_mem.isConst = false;

                        file_stm << token_list.token_array[cntr] << ".GetReturn();";
                        cur_action = "end_syntax";
                    }
                }
                else if (def_mem.mem_type == "string")
                {
                    bool succes = false;
                    int cntr0;

                    for (cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
                    {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "msg_")
                        {
                            succes = true;
                            break;
                        }
                    }

                    if (!succes)
                    {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected msg string type in RECEIVE statement *";
                        error_count++;
                        cur_action = "end_syntax";
                    }
                    else
                    {
                        def_mem.mem_name = def_mem.mem_type = "";
                        def_mem.isConst = false;

                        file_stm << token_list.token_array[cntr] << ".GetReturn();";
                        cur_action = "end_syntax";
                    }
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                    }

                    cout << endl << "* Unknown type value in RECEIVE statement *";
                    error_count++;
                    cur_action = "end_syntax";
                }

               }
               else if (cur_action == "view")
               {
                  if (token_list.token_array[cntr].substr(0,1) == "'")
                  {
                      file_stm << endl << "cout << '" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "'";
                      cur_action = "view_comma";
                  }
                  else
                  {
                     bool succes = false;

                     for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                     {
                         if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                         {
                             succes = true;
                             goto jump_view;
                         }
                     }

                     succes = true;

                     for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                     {
                         string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                         if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                         {
                             succes = false;
                             break;
                         }
                     }

jump_view:

                     if (succes)
                     {
                        file_stm << endl << "cout << " << token_list.token_array[cntr];
                        cur_action = "view_comma";
                     }
                     else
                     {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Unknown type value in VIEW statement *";
                        error_count++;
                        cur_action = "view_comma";
                     }
                  }
               }
               else if (cur_action == "view_comma")
               {
                   if (token_list.token_array[cntr] == ",")
                   {
                       cur_action = "view_op";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in VIEW statement *";
                        error_count++;
                        cur_action = "view_op";
                   }
               }
               else if (cur_action == "view_op")
               {
                   if (token_list.token_array[cntr] == "0")
                   {
                      file_stm << ";";
                      cur_action = "end_syntax";
                   }
                   else if (token_list.token_array[cntr] == "1")
                   {
                      file_stm << " << endl;";
                      cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected 1 / 0 value in VIEW statement *";
                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "get")
               {
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "int" || var_list.memory_list[cntr0].mem_type == "string"))
                       {
                           succes = true;
                           break;
                       }
                   }

                   if (succes)
                   {
                       file_stm << endl << "cin >> " << token_list.token_array[cntr] << ";";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected string / int type value in GET statement *";
                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "push")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp_push;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp_push:
                   if (succes)
                   {
                       file_stm << endl << "stk.push(" <<  token_list.token_array[cntr] << ");";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in PUSH statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "pop")
               {
                    bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                           succes = true;
                           break;
                       }
                   }

                   if (succes)
                   {
                       file_stm << endl << token_list.token_array[cntr] << " = stk.pop();";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected int type value in POP statement *";
                        error_count++;
                        cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "load_file")
               {
                  file_stm << endl << "#include '" << token_list.token_array[cntr] << "'";
                  cur_action = "end_syntax";
               }
               else if (cur_action == "param_get")
               {
                   bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                        {
                            succes = true;
                            break;
                        }
                   }

                   if (succes)
                   {
                        file_stm << endl << token_list.token_array[cntr] << " = ";
                        cur_action = "param_get_comma";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in PARAM_GET statement *";
                       error_count++;
                       cur_action = "param_get_comma";
                   }
               }
               else if (cur_action == "param_get_comma")
               {
                     if (token_list.token_array[cntr] == ",")
                     {
                        cur_action = "param_get_source";
                     }
                     else
                     {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET statement *";
                        error_count++;
                        cur_action = "param_get_source";
                     }
               }
               else if (cur_action == "param_get_source")
               {
                    bool succes = false;

                    for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                    {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "msg")
                        {
                            succes = true;
                            break;
                        }
                    }

                    if (succes)
                    {
                        file_stm << token_list.token_array[cntr] << ".GetParamValue(";
                        cur_action = "param_get_comma1";
                    }
                    else
                    {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET statement *";
                        error_count++;
                        cur_action = "param_get_comma1";
                    }
               }
               else if (cur_action == "param_get_comma1")
               {
                     if (token_list.token_array[cntr] == ",")
                     {
                        cur_action = "param_get_value";
                     }
                     else
                     {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET statement *";
                        error_count++;
                        cur_action = "param_get_value";
                     }
               }
               else if (cur_action == "param_get_value")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp_param_get;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp_param_get:
                   if (succes)
                   {
                       file_stm <<  token_list.token_array[cntr] << ");";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in PARAM_GET statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "param_get_")
               {
                    bool succes = false;

                   for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                        {
                            succes = true;
                            break;
                        }
                   }

                   if (succes)
                   {
                        file_stm << endl << token_list.token_array[cntr] << " = ";
                        cur_action = "param_get_comma_";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected string type value in PARAM_GET_ statement *";
                       error_count++;
                       cur_action = "param_get_comma_";
                   }
               }
               else if (cur_action == "param_get_comma_")
               {
                    if (token_list.token_array[cntr] == ",")
                     {
                        cur_action = "param_get_source_";
                     }
                     else
                     {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET_ statement *";
                        error_count++;
                        cur_action = "param_get_source_";
                     }
               }
               else if (cur_action == "param_get_source_")
               {
                    bool succes = false;

                    for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                    {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "msg_")
                        {
                            succes = true;
                            break;
                        }
                    }

                    if (succes)
                    {
                        file_stm << token_list.token_array[cntr] << ".GetParamValue(";
                        cur_action = "param_get_comma1_";
                    }
                    else
                    {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET_ statement *";
                        error_count++;
                        cur_action = "param_get_comma1_";
                    }
               }
               else if (cur_action == "param_get_comma1_")
               {
                    if (token_list.token_array[cntr] == ",")
                     {
                        cur_action = "param_get_value_";
                     }
                     else
                     {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected comma in PARAM_GET_ statement *";
                        error_count++;
                        cur_action = "param_get_value_";
                     }
               }
               else if (cur_action == "param_get_value_")
               {
                   bool succes = false;
                   int cntr0 = 0;

                   for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                   {
                       if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                       {
                          succes = true;
                          goto jmp_param_get_;
                       }
                   }

                   succes = true;

                   for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                   {
                       string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                       if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                       {
                           succes = false;
                           break;
                       }
                   }
jmp_param_get_:
                   if (succes)
                   {
                       file_stm <<  token_list.token_array[cntr] << ");";
                       cur_action = "end_syntax";
                   }
                   else
                   {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int type value in PARAM_GET_ statement * " << ++line_count;

                       error_count++;
                       cur_action = "end_syntax";
                   }
               }
               else if (cur_action == "cmp")
               {
                    bool succes = false;

                    for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                    {
                        if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && (var_list.memory_list[cntr0].mem_type == "int" || var_list.memory_list[cntr0].mem_type == "string"))
                        {
                            def_mem.mem_name = var_list.memory_list[cntr0].mem_name;
                            def_mem.mem_type = var_list.memory_list[cntr0].mem_type;
                            def_mem.isConst = var_list.memory_list[cntr0].isConst;

                            succes = true;
                            break;
                        }
                    }

                    if (succes)
                    {
                        file_stm << endl << "if (" << token_list.token_array[cntr];
                        cur_action = "cmp_op";
                    }
                    else
                    {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected int / string type value in cmp statement * " << ++line_count;

                       error_count++;
                       cur_action = "cmp_op";
                    }
               }
               else if (cur_action == "cmp_op")
               {
                    if (token_list.token_array[cntr] == "=" || token_list.token_array[cntr] == "!=" || token_list.token_array[cntr] == "<" || token_list.token_array[cntr] == "<=" || token_list.token_array[cntr] == ">" || token_list.token_array[cntr] == ">=")
                    {
                        file_stm << " " << token_list.token_array[cntr];
                        cur_action = "cmp_val";
                    }
                    else
                    {
                       if (error_count == 0)
                       {
                            cout << endl << endl << "Errors Found...";
                       }

                       cout << endl << "* Expected logical operator in cmp statement * " << ++line_count;

                       error_count++;
                       cur_action = "cmp_val";
                    }
               }
               else if (cur_action == "cmp_val")
               {
                    if (def_mem.mem_type == "int")
                    {
                        bool succes = false;
                        int cntr0 = 0;

                        for(cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                        {
                            if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "int")
                            {
                                succes = true;
                                goto jmp_cmp_int;
                            }
                        }

                        succes = true;

                        for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                        {
                            string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                            if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                            {
                                succes = false;
                                break;
                            }
                        }
jmp_cmp_int:
                        if (succes)
                        {
                            def_mem.mem_name = def_mem.mem_type = "";
                            def_mem.isConst = false;

                            file_stm << " " << token_list.token_array[cntr] << ")";
                            cur_action = "cmp_getbrace";
                        }
                        else
                        {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Expected int type value in CMP statement * " << ++line_count;

                            error_count++;
                            cur_action = "cmp_getbrace";
                        }
                    }
                    else if (def_mem.mem_type == "string")
                    {
                        bool isVar = false;
                        bool succes = false;

                        for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
                        {
                            if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr] && var_list.memory_list[cntr0].mem_type == "string")
                            {
                                isVar = true;
                                succes = true;
                                goto jmp_cmp_string;
                            }
                        }

                        succes = true;

                        if (token_list.token_array[cntr].substr(0,1) != "'")
                        {
                            succes = false;
                        }

jmp_cmp_string:

                        if (succes)
                        {
                            def_mem.mem_name = def_mem.mem_type = "";
                            def_mem.isConst = false;

                            if (isVar)
                            {
                                file_stm << token_list.token_array[cntr] << ")";
                            }
                            else
                            {
                                file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "')";
                            }

                            cur_action = "cmp_getbrace";
                        }
                        else
                        {
                            if (error_count == 0)
                            {
                                cout << endl << endl << "Errors Found...";
                            }

                            cout << endl << "* Expected string value in CMP statement * " << ++line_count;

                            error_count++;
                            cur_action = "cmp_getbrace";
                        }
                    }
                    else
                    {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Unknown type value in CMP statement * " << ++line_count;

                        error_count++;
                        cur_action = "cmp_getbrace";
                    }
               }
               else if (cur_action == "cmp_getbrace")
               {
                    if (token_list.token_array[cntr] == "->")
                    {
                       rec_error = false;
                       file_stm << endl << "{";

                       int res = parseIf(file_stm,cntr + 1,token_list,var_list,pnt_list);

                       if (res == -1)
                       {
                           error_count++;
                       }
                       else
                       {
                           if (rec_error)
                           {
                               error_count++;
                           }

                           cntr = res;
                       }

                       if (error_count > 0)
                       {
                           rec_error = true;
                       }

                       cur_action = "";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected -> after CMP statement *";
                        error_count++;
                        cur_action = "";
                   }
               }
            }
    }

    if (error_count == 0)
    {
        cout << endl << "Errors Found...";
    }

    cout << endl << "* Expected end of function *";

    return -1;
}

bool parseTokens(Tokens &token_list)
{
   string cur_action = "";
   int error_count = 0;
   int line_count = 0;
   ofstream file_stm;
   MemoryList var_list;
   var_list.Initialize();
   Memory def_mem;
   PointList pnt_list;
   pnt_list.Initialize();
   func_list.Initialize();

   file_stm.open("F:\\Code.cpp");  // For now generate in F Drive.

   file_stm << "#include<iostream>" << endl << "#include<conio.h>" << endl << "#include<Assembly++.hpp>" << endl << endl << "using namespace std;" << endl << endl; // Generate include statements.

   for(register int cntr = 0;cntr < token_list.token_count;cntr++)
   {
       if (cur_action == "")
       {
           if (token_list.token_array[cntr] == "use")
           {
              cur_action = "use";
           }
           else if (token_list.token_array[cntr] == "_define")
           {
               cur_action = "_define";
           }
           else if (token_list.token_array[cntr] == "mem")
           {
               cur_action = "mem";
           }
           else if (token_list.token_array[cntr] == "mem_")
           {
               cur_action = "mem_";
           }
           else if (token_list.token_array[cntr] == "msg")
           {
               cur_action = "msg";
           }
           else if (token_list.token_array[cntr] == "msg_")
           {
               cur_action = "msg_";
           }
           else if (token_list.token_array[cntr] == "define")
           {
               cur_action = "define_getname";
           }
           else
           {
               cout << endl << "* Warning : Unknown keyword " << token_list.token_array[cntr] << " *";
           }
       }
       else if (cur_action == "end_syntax")
       {
           if (token_list.token_array[cntr] == ";")
           {
               cur_action = "";
           }
           else
           {
               if (error_count == 0)
               {
                   cout << endl << endl << "Errors Found...";
                   cout << endl << "* Expected end of syntax *" << ++line_count;
               }
               else
               {
                    cout << endl << "* Expected end of syntax *" << ++line_count;
               }

               error_count++;
               cur_action = "";
           }
       }
       else
       {
           if (cur_action == "use")
           {
               ifstream file_stm(token_list.token_array[cntr].c_str());

               if (!file_stm.is_open())
               {
                   if (error_count == 0)
                   {
                     cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Header file not found in use statement ( " << token_list.token_array[cntr].c_str() << " ) *";
                   error_count++;
               }

               cur_action = "end_syntax";
           }
           else if (cur_action == "_define")
           {
               bool succes = true;

               for(int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   cur_action = "_define_value";
                   error_count++;
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "int";
                   def_mem.isConst = true;

                   file_stm << endl << "const int " << def_mem.mem_name << " = ";

                   cur_action = "_define_value";
               }
           }
           else if (cur_action == "_define_value")
           {
                bool succes = true;

                for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                {
                    string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                    if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                    {
                         succes = false;
                         break;
                    }
                }

                if (succes)
                {
                    var_list.ResizeMemory(var_list.mem_count + 1);
                    var_list.AddMemory(def_mem);
                    def_mem.mem_name = def_mem.mem_type = "";
                    def_mem.isConst = false;
                    file_stm << token_list.token_array[cntr] << ";";
                    cur_action = "end_syntax";
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                        cout << endl << "* Illegal value given in constant declaration *";
                    }
                    else
                    {
                        cout << endl << "* Illegal value given in constant declaration *";
                    }

                    error_count++;
                    cur_action = "end_syntax";
                }
           }
           else if (cur_action == "mem")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "mem_comma";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "int";
                   def_mem.isConst = false;

                   file_stm << endl << "int " << def_mem.mem_name << " = ";

                   cur_action = "mem_comma";
               }
           }
           else if (cur_action == "mem_comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "mem_value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in memory declaration * " + ++line_count;

                   error_count++;
                   cur_action = "mem_value";
               }
           }
           else if (cur_action == "mem_value")
           {
               bool succes = true;

               for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (var_list.memory_list[cntr0].mem_type == "int")
                       {

                       succes = true;
                       goto jmp;

                       }
                       else
                       {
                           goto jmp;
                       }
                   }
               }

                for(int cntr0 = 0;cntr0 < token_list.token_array[cntr].length();cntr0++)
                {
                    string sub_ch = token_list.token_array[cntr].substr(cntr0,1);

                    if (!(sub_ch == "0" || sub_ch == "1" || sub_ch == "2" || sub_ch == "3" || sub_ch == "4" || sub_ch == "5" || sub_ch == "6" || sub_ch == "7" || sub_ch == "8" || sub_ch == "9" ))
                    {
                         succes = false;
                         break;
                    }
                }

jmp:
                if (succes)
                {
                    var_list.ResizeMemory(var_list.mem_count + 1);
                    var_list.AddMemory(def_mem);
                    def_mem.mem_name = def_mem.mem_type = "";
                    def_mem.isConst = false;
                    file_stm << token_list.token_array[cntr] << ";";
                    cur_action = "end_syntax";
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                        cout << endl << "* Illegal value given in integer memory declaration *";
                    }
                    else
                    {
                        cout << endl << "* Illegal value given in integer memory declaration *";
                    }

                    error_count++;
                    cur_action = "end_syntax";
                }
           }
           else if (cur_action == "mem_")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }

               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "mem__comma";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "string";
                   def_mem.isConst = false;

                   file_stm << endl << "string " << def_mem.mem_name << " = ";

                   cur_action = "mem__comma";
               }
           }
           else if (cur_action == "mem__comma")
           {
               if (token_list.token_array[cntr] == ",")
               {
                   cur_action = "mem__value";
               }
               else
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                   }

                   cout << endl << "* Expected comma operator in memory declaration * " + ++line_count;

                   error_count++;
                   cur_action = "mem__value";
               }
           }
           else if (cur_action == "mem__value")
           {
               bool succes = false;

               for(int cntr0 = 0;cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       if (var_list.memory_list[cntr0].mem_type == "string")
                       {
                        succes = true;
                        goto jmp2;
                       }
                       else
                       {
                           goto jmp2;
                       }
                   }
               }

                if (token_list.token_array[cntr].substr(0,1) == "'")
                {
                    succes = true;
                }

jmp2:
                if (succes)
                {
                    var_list.ResizeMemory(var_list.mem_count + 1);
                    var_list.AddMemory(def_mem);
                    def_mem.mem_name = def_mem.mem_type = "";
                    def_mem.isConst = false;
                    file_stm << "'" << token_list.token_array[cntr].substr(1,token_list.token_array[cntr].length() - 1) << "'" << ";";
                    cur_action = "end_syntax";
                }
                else
                {
                    if (error_count == 0)
                    {
                        cout << endl << endl << "Errors Found...";
                        cout << endl << "* Illegal value given in string memory declaration *";
                    }
                    else
                    {
                        cout << endl << "* Illegal value given in string memory declaration *";
                    }

                    error_count++;
                    cur_action = "end_syntax";
                }
           }
           else if (cur_action == "msg")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "msg";
                   def_mem.isConst = false;
                   var_list.ResizeMemory(var_list.mem_count + 1);
                   var_list.AddMemory(def_mem);
                   def_mem.mem_name = def_mem.mem_type = "";

                   file_stm << endl << "MessageINT " << token_list.token_array[cntr] << ";";

                   cur_action = "end_syntax";
               }
           }
           else if (cur_action == "msg_")
           {
               bool succes = true;

               for (int cntr0 = 0; cntr0 < var_list.mem_count;cntr0++)
               {
                   if (var_list.memory_list[cntr0].mem_name == token_list.token_array[cntr])
                   {
                       succes = false;
                       break;
                   }
               }


               if (!succes)
               {
                   if (error_count == 0)
                   {
                       cout << endl << endl << "Errors Found...";
                       cout << endl << "* The memory name is already defined *";
                   }
                   else
                   {
                        cout << endl << "* The memory name is already defined *";
                   }

                   error_count++;
                   cur_action = "end_syntax";
               }
               else
               {
                   def_mem.mem_name = token_list.token_array[cntr];
                   def_mem.mem_type = "msg_";
                   def_mem.isConst = false;
                   var_list.ResizeMemory(var_list.mem_count + 1);
                   var_list.AddMemory(def_mem);
                   def_mem.mem_name = def_mem.mem_type = "";

                   file_stm << endl << "MessageSTRING " << token_list.token_array[cntr] << ";";

                   cur_action = "end_syntax";
               }
           }
               else if (cur_action == "define_getname")
               {
                   bool succes = true;

                   for(int cntr0 = 0;cntr0 < func_list.function_count;cntr0++)
                   {
                       if (func_list.function_names[cntr0] == token_list.token_array[cntr])
                       {
                           succes = false;
                           break;
                       }
                   }

                   if (succes)
                   {
                       func_list.ResizeFunctions(func_list.function_count + 1);
                       func_list.AddFunction(token_list.token_array[cntr]);

                       file_stm << endl << "void " << token_list.token_array[cntr] << "( )";
                       cur_action = "define_getbrace";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Function name already exists in DEFINE statement *";
                        error_count++;
                        cur_action = "define_getbrace";
                   }
               }
               else if (cur_action == "define_getbrace")
               {
                   if (token_list.token_array[cntr] == "->")
                   {
                       rec_error = false;
                       file_stm << endl << "{";

                       int res = parseFunction(file_stm,cntr + 1,token_list,var_list);

                       if (res == -1)
                       {
                           error_count++;
                       }
                       else
                       {
                           if (rec_error)
                           {
                               error_count++;
                           }

                           cntr = parser_newpos;
                           parser_newpos = 0;
                       }

                       cur_action = "";
                   }
                   else
                   {
                        if (error_count == 0)
                        {
                            cout << endl << endl << "Errors Found...";
                        }

                        cout << endl << "* Expected -> after DEFINE statement *";
                        error_count++;
                        cur_action = "";
                   }
               }
            }
        }

    file_stm.close( );

   /* for(int x= 0;x < var_list.mem_count;x++)
    {
        cout << endl << var_list.memory_list[x].mem_name;
    } */

    if (error_count > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool scanTokens(Tokens &token_list,ifstream &inp_file)
{
    string cur_line;
    int error_count = 0;

    while (getline(inp_file,cur_line))
    {
        string cur_token;
        bool isString = false;
        bool isUse = false;
        bool isComment = false;

        for(int cntr = 0;cntr < cur_line.length();cntr++)
        {
            string cur_char = cur_line.substr(cntr,1);

            if (!isString && !isComment)
            {

            if (cur_char == " ")
            {
                if (!isUse)
                {

                if (cur_token != "")
                {
                    token_list.ResizeTokens(token_list.token_count + 1);
                    token_list.AddToken(cur_token);
                    cur_token = "";
                }

                }
            }
            else if (cur_char == ";")
            {
                if (!isUse)
                {


                if (cur_token != "")
                {
                    token_list.ResizeTokens(token_list.token_count + 2);
                    token_list.AddToken(cur_token);
                    token_list.AddToken(";");
                    cur_token = "";
                }
                else
                {
                    token_list.ResizeTokens(token_list.token_count + 1);
                    token_list.AddToken(";");
                    cur_token = "";
                }

                }
                else
                {
                    ifstream file_stm(cur_token.c_str());

                    if (file_stm.is_open())
                    {
                        Tokens tok_list;

                        tok_list.Initialize();

                        if (scanTokens(tok_list,file_stm))
                        {
                          /*  for (int x = 0;x < tok_list.token_count;x++)
                            {
                                cout << endl << tok_list.token_array[x];
                            } */

                            token_list.AddTokensFromList(tok_list);
                        }
                        else
                        {
                            error_count++;
                        }
                    }
                    else
                    {
                         if (error_count == 0)
                         {
                             cout << endl << endl << "Errors Found...";
                         }

                         cout << endl << "* Header file not found in use statement ( " << cur_token.c_str() << " ) *";
                         error_count++;
                    }

                    isUse = false;
                    cur_token = "";
                }
            }
            else if (cur_char == "'")
            {
                if (cur_token != "")
                {
                    token_list.ResizeTokens(token_list.token_count + 1);
                    token_list.AddToken(cur_token);
                }

                cur_token = "'";       // String identifier.
                isString = true;
            }
            else if (cur_char == "?")
            {
                if (cur_token != "")
                {
                    token_list.ResizeTokens(token_list.token_count + 1);
                    token_list.AddToken(cur_token);
                }

                cur_token = "";
                isComment = true;
            }
            else
            {
                    cur_token += cur_char;

                    if (cur_token == "use")
                    {
                        isUse = true;
                        cur_token = "";
                    }
            }

           }
           else if (isComment)
           {
               if (cur_char == "?")
               {
                   isComment = false;
               }
           }
           else
           {
               if (cur_char == "'")
               {
                   token_list.ResizeTokens(token_list.token_count + 1);
                   token_list.AddToken(cur_token);
                   isString = false;
                   cur_token = "";
               }
               else
               {
                   cur_token += cur_char;
               }
           }
        }

        if (isString)
        {
             if (error_count == 0)
             {
                cout << endl << endl << "Errors Found...";
             }

            cout << endl << "Non-Terminating String Literal.";
            error_count++;
        }
        else if (isComment)
        {
            if (error_count == 0)
             {
                cout << endl << endl << "Errors Found...";
             }

            cout << endl << "Non-Terminating Comment Section.";
            error_count++;
        }

        if (cur_token != "")
        {
            token_list.ResizeTokens(token_list.token_count + 1);
            token_list.AddToken(cur_token);
        }
    }

    if (error_count > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}



int main()
{
    string file_name;

    cout << "Assembly++ Compiler : [Version - 1.0.0]" << endl << endl;
    cout << "Enter Source : ";
    cin >> file_name;

    ifstream inp_file(file_name.c_str());

    if (inp_file.is_open())
    {
        Tokens token_list;

        token_list.Initialize();

        if (scanTokens(token_list,inp_file))
        {
          /*  for (int  x= 0;x < token_list.token_count;x++)
            {
                cout << endl << token_list.token_array[x];
            } */

            // Parse Tokens and Generate Code
            if (parseTokens(token_list))
            {
                 cout << endl << endl << "Compile Succesfull...";
            }
            else
            {
                cout << endl << endl << "Compile Failed...";
            }
        }
        else
        {
            cout << endl << endl << "Compile Failed...";
        }
    }
    else
    {
        cout << endl << "File Not Found!!";
    }

    return 0;
}
