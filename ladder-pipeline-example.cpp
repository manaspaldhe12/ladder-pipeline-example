//#include <ach.h>
#include <stdio.h>
#include <iostream>
#include <Ladder.h>
#include <hubo.h>
#include <balance-daemon.h>

int main (){

  LadderPlanner input_params;
  ach_channel_t ladder_plannerInitChan;
  size_t fs;

  ach_status_t r = ach_open(&ladder_plannerInitChan,  LADDER_PLANNERINITCHAN , NULL);
  std::cout << "parms ach_open result: " << ach_result_to_string(r) << "\n";
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

  ach_channel_t ladder_chan;
  zmp_traj_t currentTraj;
  memset( &currentTraj, 0, sizeof(currentTraj) );
  currentTraj.count=2000;
  for (int i=0; i<2000; i++){
	for (int joint=0; joint<HUBO_JOINT_COUNT; joint++){
		currentTraj.traj[i].angles[joint]=0;
		if (joint==LEB){
			currentTraj.traj[i].angles[LEB]=i/2000;
		}
	}
  }

  ach_channel_t balance_cmd_chan;
  balance_cmd_t ladder_mode;
  memset( &ladder_mode, 0, sizeof(ladder_mode) );
  ladder_mode.cmd_request= BAL_LADDER_CLIMBING;
  
  r = ach_open(&balance_cmd_chan, BALANCE_CMD_CHAN, NULL );
  if( r != ACH_OK )
      fprintf( stderr, "Problem with channel %s: %s (%d)\n",
              BALANCE_CMD_CHAN, ach_result_to_string(r), (int)r );
  std::cout << "balance cmd ach_open result: " << ach_result_to_string(r) << "\n";

  r = ach_put(&balance_cmd_chan, &ladder_mode, sizeof(ladder_mode));
  std::cout << "balance cmd ach_put result: " << ach_result_to_string(r) << "\n";
  
  r = ach_open(&ladder_chan, HUBO_CHAN_LADDER_TRAJ_NAME, NULL );
  if( r != ACH_OK )
      fprintf( stderr, "Problem with channel %s: %s (%d)\n",
              HUBO_CHAN_LADDER_TRAJ_NAME, ach_result_to_string(r), (int)r );
  std::cout << "cm ach_open result: " << ach_result_to_string(r) << "\n";


  r = ach_put(&ladder_chan, &currentTraj, sizeof(currentTraj));
  std::cout << "cm ach_put result: " << ach_result_to_string(r) << "\n";
  return 0;
}
