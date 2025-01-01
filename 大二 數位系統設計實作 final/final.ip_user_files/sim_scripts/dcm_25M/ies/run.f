-makelib ies_lib/xil_defaultlib -sv \
  "D:/Vivado/2018.3/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
  "D:/Vivado/2018.3/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib ies_lib/xpm \
  "D:/Vivado/2018.3/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../../final.srcs/sources_1/ip/dcm_25M/dcm_25M_clk_wiz.v" \
  "../../../../final.srcs/sources_1/ip/dcm_25M/dcm_25M.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  glbl.v
-endlib

