# -*-Makefile-*-
#----------------------------------------------------------------------------
#       Make Workspace
#
# $Id$
#
# This file was generated by MPC.  Any changes made directly to
# this file will be lost the next time it is generated.
#
# MPC Command:
# /home/dds/OvernightTests/overnight/ospli/tags/OSPL_V6_8_2-RC2/ubuntu1204-64/x86_64.linux-release-notest-inner/build/bin/mwc.pl -features ospl_os_host_linux=1 -features ospl_os_linux=1 -features ospl_64_bit=1 -value_template lib_modifier= -include /home/dds/INSTALLED_FOR_DDS/TAO211_0-RedHat-EL62-gcc446-inline-64bit-120927-head/bin/MakeProjectCreator/config -include /home/dds/INSTALLED_FOR_DDS/TAO211_0-RedHat-EL62-gcc446-inline-64bit-120927-head/bin/MakeProjectCreator/config/TAO -features x86_64_linux=1 -features ospl_arch_x86_64=1 -type make -features isocpp2_cxx11=1 HDE/x86_64.linux/examples/examples.mwc
#
#----------------------------------------------------------------------------


all: ccpp_pingpong_types ccpp_pingpong_ping ccpp_pingpong_pong

clean depend generated realclean check-syntax $(CUSTOM_TARGETS):
	@$(MAKE) -f Makefile.ccpp_pingpong_types $(@)
	@$(MAKE) -f Makefile.ccpp_pingpong_ping $(@)
	@$(MAKE) -f Makefile.ccpp_pingpong_pong $(@)

.PHONY: ccpp_pingpong_types
ccpp_pingpong_types:
	@$(MAKE) -f Makefile.ccpp_pingpong_types all

.PHONY: ccpp_pingpong_ping
ccpp_pingpong_ping: ccpp_pingpong_types
	@$(MAKE) -f Makefile.ccpp_pingpong_ping all

.PHONY: ccpp_pingpong_pong
ccpp_pingpong_pong: ccpp_pingpong_types
	@$(MAKE) -f Makefile.ccpp_pingpong_pong all

project_name_list:
	@echo ccpp_pingpong_ping
	@echo ccpp_pingpong_pong
	@echo ccpp_pingpong_types
