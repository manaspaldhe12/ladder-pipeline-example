//#include <ach.h>
#include <stdio.h>
#include <iostream>
#include <Ladder.h>
#include <hubo.h>
int main (){

  LadderPlanner input_params;
  ach_channel_t ladder_plannerInitChan;
  size_t fs;

  ach_status_t r = ach_open(&ladder_plannerInitChan,  LADDER_PLANNERINITCHAN , NULL);
  r = ach_get( &ladder_plannerInitChan, &input_params, sizeof(input_params), &fs, NULL, ACH_O_LAST );

  std::cout<<  ach_result_to_string(r) << std::endl;


  printf("rung width is %f \n", input_params.rung_width);
  printf("rung length is %f \n", input_params.rung_length);

  printf("rung spacing is %f \n", input_params.rung_spacing);
  printf("rung 1st spacing is %f \n", input_params.first_rung_spacing);

  printf("rail height is %f \n", input_params.rail_height);
  printf("rail radius is %f \n", input_params.rail_radius);

  printf("inclination is %f \n", input_params.inclination);
  printf("number_of_stairs is %d \n", input_params.number_of_stairs);

  return 0;
}
