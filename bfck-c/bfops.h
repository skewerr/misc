#ifndef _BF_OPS_H
#define _BF_OPS_H

#include <stdint.h>

/* will be defined in the main unit */
extern FILE *fstream;

extern long  	*loop_arr;
extern size_t	loop_iter;
extern size_t	loop_cnt;

extern uint8_t	*cell_arr;
extern uint8_t	*curr_pnt;
extern size_t 	cell_cnt;

extern char  	out_str[512];
extern size_t	out_iter;

void interpret(const char);
void init_arrays(void);
void free_arrays(void);

void inc_cell(void);
void dec_cell(void);
void inc_pntr(void);
void dec_pntr(void);
void start_loop(void);
void end_loop(void);
void print_char(void);
void read_char(void);

#endif /* _BF_OPS_H */
