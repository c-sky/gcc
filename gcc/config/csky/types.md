;; Instruction Classification for CSKY for GNU compiler.

;; TYPE attribute is used to classify instructions for use in scheduling.

(define_attr "type"
  "unknown,\
  alu,\
  alu_ix,\
  addsub, caddsub,\
  div,\
  mul,\
  zext, sext, ins, sexth,\
  load, store, loadr, loadi,\
  lslr,\
  cmp,\
  branch, branch_jmp, cbranch,\
  call, call_jsr"
  (const_string "alu"))
