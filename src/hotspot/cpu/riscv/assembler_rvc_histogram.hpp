//
// Created by Xiaolin Zheng on 2022/2/9.
//

#ifndef OPENJDK_RISCV_PORT_ASSEMBLER_RVC_HISTOGRAM_HPP
#define OPENJDK_RISCV_PORT_ASSEMBLER_RVC_HISTOGRAM_HPP

#include "utilities/ostream.hpp"

struct RVCCalculator {
public:
  enum Inst {
    // 00
    c_addi4spn,
    c_fld,
    c_lw,
    c_ld,
    c_fsd,
    c_sw,
    c_sd,
    // 01
    c_nop,
    c_addi,
    c_addiw,
    c_li,
    c_addi16sp,
    c_lui,
    c_srli,
    c_srai,
    c_andi,
    c_sub,
    c_xor,
    c_or,
    c_and,
    c_subw,
    c_addw,
    c_j,
    c_beqz,
    c_bnez,
    // 10
    c_slli,
    c_fldsp,
    c_lwsp,
    c_ldsp,
    c_jr,
    c_mv,
    c_ebreak,
    c_jalr,
    c_add,
    c_fsdsp,
    c_swsp,
    c_sdsp,  // the last rvc inst
    final_rvc,



    add = final_rvc,sub,subw,andr,orr,xorr,addw,lw,ld,fld,sd,sw,fsd,beq,bne,jal,jalr,ebreak,
    li /* multi insts... */,addi,addiw,and_imm12,slli,srai,srli,lui,

    final

  };
  static const char *names[final+1];
  static unsigned long times[final+1];

  static void atomic_add_one(Inst inst, bool scratch);
  static void total_atomic_add_one(bool scratch);

  static void print();

private:
  template<typename T, typename... T1>
  static uint64_t family_inst_count(T member, T1... members) {
    return times[member] + family_inst_count(members...);
  }
  template<typename T>
  static uint64_t family_inst_count(T member) {
    return times[member];
  }
  static void print_two_compressions(Inst c_inst, Inst normal_inst, bool pesudo = false);
  static void print_three_compressions(Inst c_inst1, Inst c_inst2, Inst normal_inst, bool pesudo = false);
  static void print_six_compressions(Inst c_inst1, Inst c_inst2, Inst c_inst3, Inst c_inst4, Inst c_inst5, Inst normal_inst);
  static void split();
  // helper
  static void print_header(stringStream &ss, Inst normal_inst);
  static void print_col1(stringStream &ss, Inst c_inst, int c_inst_num, int total);
  static void print_col2(stringStream &ss, Inst normal_inst, int normal_inst_num, int total);
  static void print_col2_empty(stringStream &ss);
  static void print_col3(stringStream &ss, int total, bool pesudo = false);
  static void print_col3_empty(stringStream &ss, bool sp = true);
};




#endif //OPENJDK_RISCV_PORT_ASSEMBLER_RVC_HISTOGRAM_HPP
