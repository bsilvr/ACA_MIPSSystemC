
#include "forwardunit.h"

/**
 * \c Branch module callback function.
 */
void forwardunit::forward_detect()
{
    // Default State
    rs_mux_id2.write(0);
    rt_mux_id2.write(0);
    rs_mux_exe.write(0);
    rt_mux_exe.write(0);
    mux_mem.write(0);


    // EXE/MEM --> EXE (rs)
    if ( rs_exe.read() != 0 && rs_exe.read() == WriteReg_mem.read() && RegWrite_mem.read() == true ){
        rs_mux_exe.write(1);
    }
    // EXE/MEM --> EXE (rt)
    if ( rt_exe.read() != 0 && rt_exe.read() == WriteReg_mem.read() && RegWrite_mem.read() == true && MemRead_exe.read() == false ){
        rt_mux_exe.write(1);
    }
    // EXE/MEM --> ID2 (rs - saltos)
    if ( rs_id2.read() != 0 && rs_id2.read() == WriteReg_mem.read() && RegWrite_mem.read() == true && Branch.read() != 0 ){
        rs_mux_id2.write(1);
    }
    // EXE/MEM --> ID2 (rt - saltos)
    if ( rt_id2.read() != 0 && rt_id2.read() == WriteReg_mem.read() && RegWrite_mem.read() == true && Branch.read() != 0  && MemRead.read() == false ){
        rt_mux_id2.write(1);
    }
    //--------------------------------------------
    // MEM/WB --> EXE (rs)
    if ( rs_exe.read() != 0 && rs_exe.read() == WriteReg_wb.read() && RegWrite_wb.read() == true ){
        rs_mux_exe.write(2);
    }
    // MEM/WB --> EXE (rt)
    if ( rt_exe.read() != 0 && rt_exe.read() == WriteReg_wb.read() && RegWrite_wb.read() == true && MemRead_exe.read() == false ){
        rt_mux_exe.write(2);
    }
    // MEM/WB --> ID2 (rs - saltos)
    if ( rs_id2.read() != 0 && rs_id2.read() == WriteReg_wb.read() && RegWrite_wb.read() == true ){
        rs_mux_id2.write(2);
    }
    // MEM/WB --> ID2 (rt - saltos)
    if ( rt_id2.read() != 0 && rt_id2.read() == WriteReg_wb.read() && RegWrite_wb.read() == true && MemRead.read() == false ){
        rt_mux_id2.write(2);
    }
    // MEM/WB --> EME (lw -> sw)
    if ( rt_mem.read() != 0 && rt_mem.read() == WriteReg_wb.read() && RegWrite_wb.read() == true && MemRead_wb.read() == true && MemWrite_mem.read() == true ){
        mux_mem.write(1);
    }

    fprintf(stderr, "rs_mux_id2: %d\n", (int)rs_mux_id2.read() );
    fprintf(stderr, "rt_mux_id2: %d\n", (int)rt_mux_id2.read() );
    fprintf(stderr, "rs_mux_exe: %d\n", (int)rs_mux_exe.read() );
    fprintf(stderr, "rt_mux_exe: %d\n", (int)rt_mux_exe.read() );
    fprintf(stderr, "\n");
    fprintf(stderr, "rt_mem: %d\n", (int)rt_mem.read() );
    fprintf(stderr, "WriteReg_wb: %d\n", (int)WriteReg_wb.read() );
    fprintf(stderr, "MemRead_wb: %d\n", (int)MemRead_wb.read() );
    fprintf(stderr, "MemWrite_mem: %d\n", (int)MemWrite_mem.read() );
    
    // fprintf(stderr, "WriteReg_exe: %s\n", (int)rt_mux_exe.read() );

}