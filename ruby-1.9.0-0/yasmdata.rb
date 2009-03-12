# -*-ruby-*-
#

class VM
  class InstructionSequence
    class Instruction
      InsnID2NO = {
        :nop => 0,
        :getlocal => 1,
        :setlocal => 2,
        :getspecial => 3,
        :setspecial => 4,
        :getdynamic => 5,
        :setdynamic => 6,
        :getinstancevariable => 7,
        :setinstancevariable => 8,
        :getclassvariable => 9,
        :setclassvariable => 10,
        :getconstant => 11,
        :setconstant => 12,
        :getglobal => 13,
        :setglobal => 14,
        :putnil => 15,
        :putself => 16,
        :putobject => 17,
        :putstring => 18,
        :concatstrings => 19,
        :tostring => 20,
        :toregexp => 21,
        :newarray => 22,
        :duparray => 23,
        :expandarray => 24,
        :concatarray => 25,
        :splatarray => 26,
        :checkincludearray => 27,
        :newhash => 28,
        :newrange => 29,
        :pop => 30,
        :dup => 31,
        :dupn => 32,
        :swap => 33,
        :reput => 34,
        :topn => 35,
        :setn => 36,
        :emptstack => 37,
        :definemethod => 38,
        :alias => 39,
        :undef => 40,
        :defined => 41,
        :postexe => 42,
        :trace => 43,
        :defineclass => 44,
        :send => 45,
        :invokesuper => 46,
        :invokeblock => 47,
        :leave => 48,
        :finish => 49,
        :throw => 50,
        :jump => 51,
        :branchif => 52,
        :branchunless => 53,
        :getinlinecache => 54,
        :onceinlinecache => 55,
        :setinlinecache => 56,
        :opt_case_dispatch => 57,
        :opt_checkenv => 58,
        :opt_plus => 59,
        :opt_minus => 60,
        :opt_mult => 61,
        :opt_div => 62,
        :opt_mod => 63,
        :opt_eq => 64,
        :opt_neq => 65,
        :opt_lt => 66,
        :opt_le => 67,
        :opt_gt => 68,
        :opt_ge => 69,
        :opt_ltlt => 70,
        :opt_aref => 71,
        :opt_aset => 72,
        :opt_length => 73,
        :opt_succ => 74,
        :opt_not => 75,
        :opt_regexpmatch1 => 76,
        :opt_regexpmatch2 => 77,
        :opt_call_c_function => 78,
        :bitblt => 79,
        :answer => 80,

      }
      
      def self.id2insn_no id
        if InsnID2NO.has_key? id
          InsnID2NO[id]
        end
      end
    end
  end
end


