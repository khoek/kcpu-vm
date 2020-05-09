#include <cstdio>
#include <sys/types.h>

#include "src/spec/hw.hpp"
#include "src/spec/ucode.hpp"
#include "src/spec/ucode.hpp"

bool check_cond_onlytrue(bool cond, const char *desc, bool do_nl = true) {
    if(cond) {
        printf("%s%s", desc, do_nl ? "\n" : "");
    }

    return cond;
}

bool check_cond(bool cond, const char *desc, bool do_nl = true) {
    if(cond) {
        printf("1   %s", desc);
    } else {
        printf("0   %s", desc);
    }
    printf(do_nl ? "\n" : "");

    return cond;
}

bool check_option(uinst_t ui, uinst_t mask, uinst_t bit, const char *desc, bool do_nl = true) {
    return check_cond_onlytrue((ui & mask) == bit, desc, do_nl);
}

bool do_check_bit(bool inv, uinst_t ui, uinst_t bit, const char *desc) {
    return check_cond((!!(ui & bit)) != inv, desc);
}

bool check_nbit(uinst_t ui, uinst_t bit, const char *desc) {
    return do_check_bit(false, ui, bit, desc);
}

bool check_ibit(uinst_t ui, uinst_t bit, const char *desc) {
    return do_check_bit(true, ui, bit, desc);
}

void gap() {
    printf("\n");
}

void diasm(regval_t ir, uinst_t ui) {
    regval_t i = ir >> 6;

    printf("disasm: %04X(%04X:%01X:%01X) " UINST_FMT "\n\n", ir, i, INST_GET_IU1(ir), INST_GET_IU2(ir), ui);

    // FIXME This is super old now

    // GCTRL
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_FT_NONE,         "FT_NONE");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_FT_ENTER,        "FT_ENTER");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_FT_MAYBEEXIT,    "FT_MAYBEEXIT");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_FT_EXIT,         "FT_EXIT");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JM_YES,          "JM_YES");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JM_P_RIP_BUSB_O, "JM_P_RIP_BUSB_O");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JM_HALT,         "JM_HALT");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JM_ABRT,         "JM_ABRT");

    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JCOND_CARRY,     "JM_CARRY");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JCOND_N_ZERO,    "JM_N_ZERO");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JCOND_SIGN,      "JM_SIGN");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JCOND_N_OVFLW,   "JM_N_OVFLW");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JM_INVERTCOND | GCTRL_JCOND_CARRY,     "JM_INV_CARRY");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JM_INVERTCOND | GCTRL_JCOND_N_ZERO,    "JM_INV_N_ZERO");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JM_INVERTCOND | GCTRL_JCOND_SIGN,      "JM_INV_SIGN");
    check_option(ui, MASK_GCTRL_FTJM, GCTRL_JM_INVERTCOND | GCTRL_JCOND_N_OVFLW,   "JM_INV_N_OVFLW");

    // check_option(ui, MASK_GCTRL_FTJM, ACTION_CTRL_NONE,       "ACTION_NONE");
    // check_option(ui, MASK_GCTRL_FTJM, ACTION_GCTRL_RFG_BUSB_I, "ACTION_RFG_BUSB_I");
    // check_option(ui, MASK_GCTRL_FTJM, ACTION_RCTRL_RSP_INC,    "ACTION_RSP_INC");
    // check_option(ui, MASK_GCTRL_FTJM, ACTION_RCTRL_RSP_DEC,    "ACTION_RSP_DEC");

    gap();

    // RCTRL
    check_option(ui, MASK_RCTRL_IU1, RCTRL_IU1_BUSA_I, "IU1 BUSA IN ", false);
    check_option(ui, MASK_RCTRL_IU1, RCTRL_IU1_BUSA_O, "IU1 BUSA OUT", false);
    check_option(ui, MASK_RCTRL_IU1, RCTRL_IU1_BUSB_I, "IU1 BUSB IN ", false);
    check_option(ui, MASK_RCTRL_IU1, RCTRL_IU1_BUSB_O, "IU1 BUSB OUT", false);
    if(RCTRL_IU_IS_EN(RCTRL_DECODE_IU1(ui))) {
        printf(": %s\n", kcpu::PREG_NAMES[INST_GET_IU1(ir)]);
    } else {
        printf("IU1 DISABLE\n");
    }

    check_option(ui, MASK_RCTRL_IU2, RCTRL_IU2_BUSA_I, "IU2 BUSA IN ", false);
    check_option(ui, MASK_RCTRL_IU2, RCTRL_IU2_BUSA_O, "IU2 BUSA OUT", false);
    check_option(ui, MASK_RCTRL_IU2, RCTRL_IU2_BUSB_I, "IU2 BUSB IN ", false);
    check_option(ui, MASK_RCTRL_IU2, RCTRL_IU2_BUSB_O, "IU2 BUSB OUT", false);
    if(RCTRL_IU_IS_EN(RCTRL_DECODE_IU2(ui))) {
        printf(": %s\n", kcpu::PREG_NAMES[INST_GET_IU2(ir)]);
    } else {
        printf("IU2 DISABLE\n");
    }

    gap();

    // MCTRL
    // check_nbit(ui, MCTRL_USE_PREFIX_FAR, "USE FAR");
    // check_nbit(ui, MCTRL_PREFIX_STORE  , "PRFX STORE");
    // check_ibit(ui, MCTRL_N_MAIN_OUT    , "MAIN OUT");
    // check_nbit(ui, MCTRL_MAIN_STORE    , "MAIN STORE");
    // check_nbit(ui, MCTRL_FIDD_STORE    , "FIDD STORE");
    // check_ibit(ui, MCTRL_N_FIDD_OUT    , "FIDD OUT");
    // check_nbit(ui, MCTRL_BUSMODE_WRITE , "BM_W");
    // check_nbit(ui, MCTRL_BUSMODE_X     , "BM_X");

    gap();

    // MCTRL BUSMODE
    uint match = 0;
    match += check_option(ui, MASK_MCTRL_BUSMODE, MCTRL_BUSMODE_CONH, "BUSMODE_CONH");
    match += check_option(ui, MASK_MCTRL_BUSMODE, MCTRL_BUSMODE_CONW_BUSM, "BUSMODE_CONW_BUSM");
    match += check_option(ui, MASK_MCTRL_BUSMODE, MCTRL_BUSMODE_CONW_BUSB, "BUSMODE_CONW_BUSB");
    match += check_option(ui, MASK_MCTRL_BUSMODE, MCTRL_BUSMODE_CONW_BUSB_MAYBEFLIP, "BUSMODEW_BUSB_MAYBEFLIP");
    check_cond_onlytrue(match != 1, "XX  INVALID BUSMODE");

    gap();

    uint anom_max = 0;
    for(uint j = UCODE_END; j < sizeof(uinst_t) * 8; j++) {
        if(ui & (((uint64_t) 1) << j)) {
            anom_max = j;
        }
    }

    if(anom_max) {
        for(uint j = UCODE_END; j <= anom_max; j++) {
            check_cond(ui & (((uint64_t) 1) << j), "EXTRANEOUS BIT");
        }
    }
}

int main() {
    diasm(0x0000, 0x120C00);
}