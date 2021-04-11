
#ifndef __UTILITIES_H__
#define __UTILITIES_H__

/*************************** MACROS ****************************/


#define TEST(condition, func_name) ((1) == (condition))? \
                                    printf("%s:\t\x1b[32m SUCCESS \x1b[0m | Line: %d\n", #func_name, __LINE__) : \
                                    printf("%s:\t\x1b[31m FAILURE \x1b[0m | Line: %d\n", #func_name, __LINE__)
  

#ifndef NDEBUG
    #include <stdio.h>
    #include <errno.h>
    #define ERR_PRINT() perror("errno"); fprintf(stderr, "Error in %s file, in line: %d\n", __FILE__ , __LINE__) 
#else
    #define ERR_PRINT() 
#endif





#endif /* __UTILITIES_H__ */
