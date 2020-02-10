#ifndef VM_MOD_CTL_H
#define VM_MOD_CTL_H

#include "../common.h"

#define CBIT_INSTMASK 0
#define CBIT_HALTED   1
#define CBIT_ABORTED  2

#define NUM_CBITS 3

class mod_ctl {
    private:
    vm_logger &logger;

    void set_instmask_enabled(bool state);
    void ft_enter();

    public:
    //FIXME make this private
    regval_t reg[NUM_SREGS];
    bool cbits[NUM_CBITS];

    mod_ctl(vm_logger &logger);
    void dump_registers();
    regval_t get_inst();
    uinst_t get_uinst();
    void clock_outputs(uinst_t ui, bus_state &s);
    void clock_inputs(uinst_t ui, bus_state &s);
};

#endif