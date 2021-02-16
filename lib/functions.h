#ifndef _FUNCTIONS_H_
# define _FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*  Find factorial value  */
double fact(double x);

/*  Find double factorial value  */
double dfact(double x);

/*  Compare two char arrays with diferent allocation size  */
int compstr(const char *str1, const char *str2);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*  not _COMMANDS_H_  */
