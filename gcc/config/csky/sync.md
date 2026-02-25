
(define_c_enum "unspec" [
  UNSPEC_MEMORY_BARRIER
])

(define_expand "memory_barrier"
  [(set (match_dup 0)
	 (unspec:BLK [(match_dup 0)] UNSPEC_MEMORY_BARRIER))]
  "CSKY_ISA_FEATURE(mb)"
  {
    operands[0] = gen_rtx_MEM (BLKmode, gen_rtx_SCRATCH (Pmode));
    MEM_VOLATILE_P (operands[0]) = 1;
  }
)

(define_insn "*memory_barrier"
  [(set (match_operand:BLK 0 "" "")
	 (unspec:BLK [(match_dup 0)] UNSPEC_MEMORY_BARRIER))]
  "CSKY_ISA_FEATURE(mb)"
  {
	 return "sync";
  }
  [(set_attr "length" "4")]
)
