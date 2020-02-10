#ifndef VM_KCPU_H
#define VM_KCPU_H

#include "common.h"
#include "mod/ctl.h"
#include "mod/reg.h"
#include "mod/mem.h"
#include "mod/alu.h"

class kcpu {
    private:
    uint32_t total_clocks;
    vm_logger logger;

    public:
    enum STATE {
        STATE_RUNNING,
        STATE_HALTED,
        STATE_ABORTED,
    };

    mod_ctl ctl;
    mod_reg reg;
    mod_mem mem;
    mod_alu alu;
  
    kcpu();
    kcpu(vm_logger logger);
    uint32_t get_total_clocks();
    STATE get_state();

    STATE ustep();
    STATE step();
    STATE run();
    void resume();
};

#endif
