#ifndef _LOG_H_
#define _LOG_H_
#include <iostream>

#define LOG_LEVEL(x) _level_ = x;

enum TLogType {OFF, FATAL, ERROR, WARN, INFO, TRACE, ALL};

static int _level_ = ALL;

std::string LOG(TLogType type)
{
   std::string os;

   // Checks the log level for filtering
   if(_level_ == OFF)
   {
      std::cout.setstate(std::ios_base::failbit);
   }
   else if(_level_ == ALL)
   {
      std::cout.clear();
   }
   else if(_level_ == FATAL)
   {
      if(type == FATAL)
         std::cout.clear();
      else
         std::cout.setstate(std::ios_base::failbit);
   }
   else if(_level_ == ERROR)
   {
      if((type == FATAL)||(type == ERROR))
         std::cout.clear();
      else
         std::cout.setstate(std::ios_base::failbit);
   }
   else if(_level_ == WARN)
   {
      if((type >= FATAL)&&(type <= WARN))
         std::cout.clear();
      else
         std::cout.setstate(std::ios_base::failbit);
   }
   else if(_level_ == INFO)
   {
      if((type >= FATAL)&&(type <= INFO))
         std::cout.clear();
      else
         std::cout.setstate(std::ios_base::failbit);
   }
   else if(_level_ == TRACE)
   {
      if((type >= FATAL)&&(type <= TRACE))
         std::cout.clear();
      else
         std::cout.setstate(std::ios_base::failbit);
   }

   switch (type)
   {                 
      case FATAL:
         os.append("\033[31m"); //Red
         os.append("[FATAL]: ");
      break;    
      case ERROR:
         os.append("\033[35m"); //Purple
         os.append("[ERROR]: ");
      break;    
      case WARN:
         os.append("\033[33m"); //Yellow
         os.append("[WARN]: ");
      break;    
      case INFO:
         os.append("\033[39m"); //White 
         os.append("[INFO]: ");
      break;    
      case TRACE:
         os.append("\033[36m"); //Light Blue
         os.append("[TRACE]: ");
      break;
      default:
      break;
   }

   return os;
}
#endif
