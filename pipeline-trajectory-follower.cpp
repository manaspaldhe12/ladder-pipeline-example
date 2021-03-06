//#include <ach.h>
#include <iostream>
#include <Ladderach.h>
#include <hubo.h>
#include <balance-daemon.h>
#include <hubo-zmp.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

 
ach_channel_t ladder_plannerInitChan; //,adder_plannerInitChan;
balance_cmd_t ladder_mode;
ach_channel_t ladder_chan;
ach_channel_t balance_cmd_chan;
ach_channel_t params_chan;

void obtainPlannerParams(){
  LadderPlanner input_params;
  size_t fs;
  int r;

  r = ach_get( &ladder_plannerInitChan, &input_params, sizeof(input_params), &fs, NULL, ACH_O_LAST );

  //std::cout<<  ach_result_to_string(r) << std::endl;

  printf("rung width is %f \n", input_params.rung_width);
  printf("rung length is %f \n", input_params.rung_length);

  printf("rung spacing is %f \n", input_params.rung_spacing);
  printf("rung 1st spacing is %f \n", input_params.first_rung_spacing);

  printf("rail height is %f \n", input_params.rail_height);
  printf("rail radius is %f \n", input_params.rail_radius);

  printf("inclination is %f \n", input_params.inclination);
  printf("number_of_stairs is %d \n", input_params.number_of_stairs);
}

int  getArg(char* s, zmp_traj_element_t *array) {

sscanf(s, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
        &array->angles[RHY],
        &array->angles[RHR],
        &array->angles[RHP],
        &array->angles[RKN],
        &array->angles[RAP],
        &array->angles[RAR],
        &array->angles[LHY],
        &array->angles[LHR],
        &array->angles[LHP],
        &array->angles[LKN],
        &array->angles[LAP],
        &array->angles[LAR],
        &array->angles[RSP],
        &array->angles[RSR],
        &array->angles[RSY],
        &array->angles[REB],
        &array->angles[RWY],
        &array->angles[RWR],
        &array->angles[RWP],
        &array->angles[LSP],
        &array->angles[LSR],
        &array->angles[LSY],
        &array->angles[LEB],
        &array->angles[LWY],
        &array->angles[LWR],
        &array->angles[LWP],
        &array->angles[NKY],
        &array->angles[NK1],
        &array->angles[NK2],
        &array->angles[WST],
        &array->angles[RF1],
        &array->angles[RF2],
        &array->angles[RF3],
        &array->angles[RF4],
        &array->angles[RF5],
        &array->angles[LF1],
        &array->angles[LF2],
        &array->angles[LF3],
        &array->angles[LF4],
        &array->angles[LF5]);

        return 0;
}




void sendTestTrajectory(){
  int r;
  zmp_traj_t currentTraj;
  memset( &currentTraj, 0, sizeof(currentTraj) );
  currentTraj.count=20000;
  for (int i=0; i<2000; i++){
	for (int joint=0; joint<HUBO_JOINT_COUNT; joint++){
		currentTraj.traj[i].angles[joint]=0;
		if (joint==LEB){
			currentTraj.traj[i].angles[LEB]=((float)(i))/2000;
		}
	}
  }

  memset( &ladder_mode, 0, sizeof(ladder_mode) );
  ladder_mode.cmd_request=BAL_LADDER_CLIMBING;
 
  r = ach_put(&balance_cmd_chan, &ladder_mode, sizeof(ladder_mode));
  //std::cout << "balance cmd ach_put result: " << ach_result_to_string(r) << "\n";
  
  r = ach_put(&ladder_chan, &currentTraj, sizeof(currentTraj));
  //std::cout << "cm ach_put result: " << ach_result_to_string(r) << "\n";
 
}

void sendPlannedTrajectory(){
  ach_channel_t ladder_chan;
  zmp_traj_t currentTraj;
  memset( &currentTraj, 0, sizeof(currentTraj) );
  currentTraj.count=20000;
  for (int i=0; i<2000; i++){
	for (int joint=0; joint<HUBO_JOINT_COUNT; joint++){
		currentTraj.traj[i].angles[joint]=0;
		if (joint==LEB){
			currentTraj.traj[i].angles[LEB]=((float)(i))/2000;
		}
	}
  }

  ach_channel_t balance_cmd_chan;
  balance_cmd_t ladder_mode;
  memset( &ladder_mode, 0, sizeof(ladder_mode) );
  ladder_mode.cmd_request=BAL_LADDER_CLIMBING;
 
  int r = ach_put(&balance_cmd_chan, &ladder_mode, sizeof(ladder_mode));
  //std::cout << "balance cmd ach_put result: " << ach_result_to_string(r) << "\n";
  
  r = ach_put(&ladder_chan, &currentTraj, sizeof(currentTraj));
  //std::cout << "cm ach_put result: " << ach_result_to_string(r) << "\n";
 
}

int sendFileTrajectory(char *s, bool compliance_flag, bool pause_flag){
  ach_channel_t ladder_chan;
  zmp_traj_t currentTraj;
  memset( &currentTraj, 0, sizeof(currentTraj) );
  currentTraj.count=20000;
  //char *s = "left_elbow.txt";
  char str[1000];
  FILE *fp;               // file pointer
  fp = fopen(s,"r");
  if(!fp) {
  	printf("No Trajectory File!!!\n");
        return 1;  // exit if not file
  }

  printf("trajectory is %s \n", s);
 
  TrajectoryFollowerParams_t traj_params;
  memset(&traj_params, 0, sizeof(traj_params));
  traj_params.compliance_flag=compliance_flag;
  traj_params.pause_flag=pause_flag;
 
  int counter=0;
  while(fgets(str,sizeof(str),fp) != NULL) {
 	 int len = strlen(str)-1;
         if(str[len] == '\n') {
        	 str[len] = 0;
         }
	 //printf("%d \n", counter);
   	 //printf("%s \n" ,str); 
	 //printf("\n");
	
 	 getArg(str, &currentTraj.traj[counter]);
	 //for (int j=0; j<40; j++){
 	 //	printf("%f, ",currentTraj.traj[counter].angles[j]);
	 //}
	 //printf("\n");
	 counter++;
  }

  memset( &ladder_mode, 0, sizeof(ladder_mode) );
  ladder_mode.cmd_request=BAL_LADDER_CLIMBING;

  ach_status_t r = ach_open(&balance_cmd_chan, BALANCE_CMD_CHAN, NULL );
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
  std::cout << "ladder ach_put result: " << ach_result_to_string(r) << "\n";

  r = ach_open(&params_chan, HUBO_CHAN_TRAJECTORY_PARAMS, NULL );
  if( r != ACH_OK )
      fprintf( stderr, "Problem with channel %s: %s (%d)\n",
              HUBO_CHAN_TRAJECTORY_PARAMS, ach_result_to_string(r), (int)r );
  std::cout << "params_chan ach_open result: " << ach_result_to_string(r) << "\n";

  r = ach_put(&params_chan, &traj_params, sizeof(traj_params));
  std::cout << "params_chan ach_put result: " << ach_result_to_string(r) << "\n";
  return 0;


}


int main (int argc, char **argv){

  int i=1;
  char *s = "left_elbow.txt";
  while(argc > i) {
       if(strcmp(argv[i], "-n") == 0) {
                        if( argc > (i+1)) {
                                s = argv[i+1];
                                printf("Trejectory file changed\n");
                        }
                        else {
                                printf("ERROR: File name not changed\n");
                        }
       }
       i++;
   }
  

  ach_status_t r = ach_open(&ladder_plannerInitChan,  LADDER_PLANNERINITCHAN , NULL); 
  std::cout << "parms ach_open result: " << ach_result_to_string(r) << "\n";

  r = ach_open(&balance_cmd_chan, BALANCE_CMD_CHAN, NULL );
  if( r != ACH_OK )
      fprintf( stderr, "Problem with channel %s: %s (%d)\n",
              BALANCE_CMD_CHAN, ach_result_to_string(r), (int)r );
  std::cout << "balance cmd ach_open result: " << ach_result_to_string(r) << "\n";

  r = ach_open(&ladder_chan, HUBO_CHAN_LADDER_TRAJ_NAME, NULL );
  if( r != ACH_OK )
      fprintf( stderr, "Problem with channel %s: %s (%d)\n",
              HUBO_CHAN_LADDER_TRAJ_NAME, ach_result_to_string(r), (int)r );
  std::cout << "cm ach_open result: " << ach_result_to_string(r) << "\n";

  r = ach_open(&params_chan, HUBO_CHAN_TRAJECTORY_PARAMS, NULL );
  if( r != ACH_OK )
      fprintf( stderr, "Problem with channel %s: %s (%d)\n",
              HUBO_CHAN_TRAJECTORY_PARAMS, ach_result_to_string(r), (int)r );
  std::cout << "params_chan ach_open result: " << ach_result_to_string(r) << "\n";

  sendFileTrajectory(s, true, false);

  fflush(stdout);

}
