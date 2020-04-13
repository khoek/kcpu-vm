#include <sstream>
#include "kcpu.hpp"
#include "../spec/inst.hpp"
#include "../codegen/disassembler.hpp"

namespace kcpu {

vm::vm(vm_logger l) : total_clocks(0), logger(l), ctl(logger), reg(logger), mem(logger), alu(logger), io(logger) { }

uint32_t vm::get_total_clocks() {
    return total_clocks;
}

vm::STATE vm::get_state() {
    if(ctl.cbits[CBIT_HALTED]) {
        return ctl.cbits[CBIT_ABORTED] ? STATE_ABORTED : STATE_HALTED;
    }

    return STATE_RUNNING;
}

void vm::dump_registers() {
    logger.logf("---------------------\n");
    ctl.dump_registers();
    mem.dump_registers();
    reg.dump_registers();
    alu.dump_registers();
    logger.logf("\n");
}

vm::STATE vm::ustep() {
    total_clocks++;

    if(ctl.cbits[CBIT_HALTED]) {
        throw vm_error("cpu already halted!");
    }

    // This must be called before `ctl.get_uinst()`, as it sets up the value of the uinst latch.
    ctl.offclock_pulse(io.get_io_done());

    regval_t i = ctl.get_inst();
    uinst_t ui = ctl.get_uinst();
    if(logger.dump_bus) logger.logf("IP/UC @ I/UI: 0x%04X/0x%04X @ 0x%04X/0x%04lX\n", ctl.reg[REG_IP], ctl.reg[REG_UC], i, ui);

    if(!ui) {
        throw vm_error("executing undefined microcode instruction!");
    }

    if(logger.dump_registers) {
        dump_registers();
    }

    bus_state state(logger);

    io.clock_outputs(ui, state);
    ctl.clock_outputs(ui, state);
    alu.clock_outputs(ui, state);
    // `mod_reg` must appear after `mod_ctl` and before `mod_mem`
    // FIXME hand over the high four RCTRL registers to GCTRL, for a better model
    // of the real situation.
    reg.clock_outputs(i, ui, !ctl.cbits[CBIT_INSTMASK] && (ctl.reg[REG_UC] == 0x0), state);
    mem.clock_outputs(ui, state);

    mem.clock_connects(ui, state);

    state.freeze();

    alu.clock_inputs(ui, state);
    mem.clock_inputs(ui, state);
    reg.clock_inputs(i, ui, state);
    ctl.clock_inputs(ui, state);
    io.clock_inputs(ui, state);

    return get_state();
}

void vm::disassemble_current() {
    regval_t ip = ctl.reg[REG_IP] - ((ctl.cbits[CBIT_INSTMASK] ? 0 : 1) * (INST_GET_LOADDATA(ctl.reg[REG_IR]) ? 4 : 2));
    codegen::bound_instruction b = codegen::disassemble_peek(ip, mem.get_bank(false));

    std::stringstream ss;
    ss << "(0x" << std::hex << std::uppercase << ip << ")  " << codegen::pretty_print(b) << std::endl;

    logger.logf("---------------------\n");
    logger.logf(ss.str().c_str());
    if(!logger.dump_registers) {
        dump_registers();
    }
}

vm::STATE vm::step() {
    if(logger.disassemble && !ctl.cbits[CBIT_INSTMASK]) {
        disassemble_current();
    }

    if(ctl.cbits[CBIT_HALTED]) {
        throw vm_error("cpu already halted!");
    }

    do {
        ustep();
    } while(ctl.reg[REG_UC] && !ctl.cbits[CBIT_HALTED]);

    return get_state();
}

vm::STATE vm::run(std::optional<uint32_t> max_clocks) {
    uint32_t then = total_clocks;

    while(!ctl.cbits[CBIT_HALTED]) {
        if(max_clocks && *max_clocks < (total_clocks - then)) {
            return vm::STATE_TIMEOUT;
        }

        step();
    }

    return get_state();
}

vm::STATE vm::run() {
    return run(std::nullopt);
}

void vm::resume() {
    if(get_state() != STATE_ABORTED) {
        throw vm_error("cannot resume, cpu not aborted");
    }

    ctl.cbits[CBIT_HALTED ] = false;
    ctl.cbits[CBIT_ABORTED] = false;
}

}