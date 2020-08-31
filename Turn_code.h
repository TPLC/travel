#ifndef _Turn_code_h_
  #define _Turn_cose_h_
  
  void F_turn_L(void);
  void F_turn_R(void);
  void B_turn_L(void);
  void B_turn_R(void);
  void F_turn_B_L(void);
  void F_turn_B_R(void);
  void B_turn_F_L(void);
  void B_turn_F_R(void);

  void F_up_stage(void);
  void B_up_stage(int,int,int);
  void F_down(void);
  void B_down(void);

  void F_bridge(void);
  void B_bridge(void);


  void F_cycle_sp(int,int,int);
  void changqiao(int,int);
  void changqiao_sp(int,int);
  void F_cycle(int,int,int);
  void B_turn_F_L_SLOW(void);
  void B_turn_F_R_SLOW(void);
  void F_turn_B_L_SLOW(void);
  void F_turn_B_R_SLOW(void);
  
 

#endif