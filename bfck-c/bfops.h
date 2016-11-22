#ifndef _BF_OPS_H
#define _BF_OPS_H

/* will be defined in the main unit */
extern FILE *fstream;

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
