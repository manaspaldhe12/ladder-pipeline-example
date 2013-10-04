//#include <ach.h>
#include <stdio.h>
#include <iostream>
#include <Ladderach.h>
#include <hubo.h>
#include <balance-daemon.h>
#include <hubo-zmp.h>

int main (){

  CorrectionParams input_params;
  ach_channel_t correction_plannerInitChan;
  size_t fs;

  ach_status_t r = ach_open(&correction_plannerInitChan,  CORRECTION_PLANNERINITCHAN , NULL);
  std::cout << "parms ach_open result: " << ach_result_to_string(r) << "\n";
  r = ach_get( &correction_plannerInitChan, &input_params, sizeof(input_params), &fs, NULL, ACH_O_LAST );

  std::cout<<  ach_result_to_string(r) << std::endl;

  printf("left hand x %d \n", input_params.left_hand_x);
  printf("left hand y %d \n", input_params.left_hand_y);
  return 0;
}
