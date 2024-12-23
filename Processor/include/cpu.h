#ifndef PROCESSOR_CPU_H
#define PROCESSOR_CPU_H

#include "parser.h"
#include "stack.h"

static const size_t DARK_REGISTERS_NUMBER = 4;
static const size_t REGISTERS_NUMBER = 17;
static const size_t RAM_SIZE = 128;
static const size_t WIDTH = 100;
static const size_t HEIGHT = 60;

typedef struct {
  double *Registers;
  double *DarkRegisters;
  double *Ram;
  char *VRam;
  stack Stack;
  stack CallStack;
} CPU;

void processor(const char *const binfile_path);

#endif // PROCESSOR_CPU_H
