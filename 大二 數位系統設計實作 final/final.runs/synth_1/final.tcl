# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
create_project -in_memory -part xc7a35tcsg324-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir C:/Users/yuchin/Desktop/final/final.cache/wt [current_project]
set_property parent.project_path C:/Users/yuchin/Desktop/final/final.xpr [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_MEMORY} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property ip_output_repo c:/Users/yuchin/Desktop/final/final.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
add_files C:/Users/yuchin/Desktop/OS/Desktop/a004.coe
add_files C:/Users/yuchin/Desktop/OS/Desktop/fire.coe
add_files C:/Users/yuchin/Documents/MATLAB/a004.coe
add_files C:/Users/yuchin/Documents/MATLAB/fire.coe
read_verilog -library xil_defaultlib {
  C:/Users/yuchin/Desktop/final/final.srcs/sources_1/new/SyncGeneration.v
  C:/Users/yuchin/Desktop/final/final.srcs/sources_1/new/final.v
}
read_ip -quiet C:/Users/yuchin/Desktop/final/final.srcs/sources_1/ip/ROM1/ROM1.xci
set_property used_in_implementation false [get_files -all c:/Users/yuchin/Desktop/final/final.srcs/sources_1/ip/ROM1/ROM1_ooc.xdc]

read_ip -quiet C:/Users/yuchin/Desktop/final/final.srcs/sources_1/ip/dcm_25M/dcm_25M.xci
set_property used_in_implementation false [get_files -all c:/Users/yuchin/Desktop/final/final.srcs/sources_1/ip/dcm_25M/dcm_25M_board.xdc]
set_property used_in_implementation false [get_files -all c:/Users/yuchin/Desktop/final/final.srcs/sources_1/ip/dcm_25M/dcm_25M.xdc]
set_property used_in_implementation false [get_files -all c:/Users/yuchin/Desktop/final/final.srcs/sources_1/ip/dcm_25M/dcm_25M_ooc.xdc]

read_ip -quiet C:/Users/yuchin/Desktop/final/final.srcs/sources_1/ip/ROM2/ROM2.xci
set_property used_in_implementation false [get_files -all c:/Users/yuchin/Desktop/final/final.srcs/sources_1/ip/ROM2/ROM2_ooc.xdc]

# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc C:/Users/yuchin/Desktop/final/final.srcs/constrs_1/new/final.xdc
set_property used_in_implementation false [get_files C:/Users/yuchin/Desktop/final/final.srcs/constrs_1/new/final.xdc]

set_param ips.enableIPCacheLiteLoad 1
close [open __synthesis_is_running__ w]

synth_design -top final -part xc7a35tcsg324-1


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef final.dcp
create_report "synth_1_synth_report_utilization_0" "report_utilization -file final_utilization_synth.rpt -pb final_utilization_synth.pb"
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]
