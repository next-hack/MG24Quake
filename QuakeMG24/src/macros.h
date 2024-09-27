/***************************************************************************//**
 * @file macros.h
 * @brief 
 *
 * @version 1.0.0
 ******************************************************************************/
#ifndef SRC_MACROS_H_
#define SRC_MACROS_H_
#ifdef __cplusplus
extern "C" {
#endif
#define CATEXP(a, b)                    a ## b
#define CAT(a, b)                       CATEXP(a, b)
#define CAT3(a,b,c)                     CAT3EXP(a, b, c)
#define CAT3EXP(a,b,c)                  a ## b ## c

#ifdef __cplusplus
}
#endif
#endif /* SRC_MACROS_H_ */
