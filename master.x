/**********************************************************************\
* file - master.x                                                      *
* V-1.0_1                                                              *
* Header file RPC for master.c .                                       *
*                                                                      *
*                                                                      *
*                                                                      *
*                                                                      *
*                                                                      *
\**********************************************************************/

program MASTERPROG {
  version MASTERVERS {
    int HOSTS_GETNUMBCPU(void)    = 1;
    int HOSTS_GETNUMBRUN(void)    = 2;
    int HOSTS_RUNRTASK(string)    = 3;
  } = 1;
} = 0x30090949;
