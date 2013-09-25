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
        &array->angles[0],
        &array->angles[1],
        &array->angles[2],
        &array->angles[3],
        &array->angles[4],
        &array->angles[5],
        &array->angles[6],
        &array->angles[7],
        &array->angles[8],
        &array->angles[9],
        &array->angles[10],
        &array->angles[11],
        &array->angles[12],
        &array->angles[13],
        &array->angles[14],
        &array->angles[15],
        &array->angles[16],
        &array->angles[17],
        &array->angles[18],
        &array->angles[19],
        &array->angles[20],
        &array->angles[21],
        &array->angles[22],
        &array->angles[23],
        &array->angles[24],
        &array->angles[25],
        &array->angles[26],
        &array->angles[27],
        &array->angles[28],
        &array->angles[29],
        &array->angles[30],
        &array->angles[31],
        &array->angles[32],
        &array->angles[33],
        &array->angles[34],
        &array->angles[35],
        &array->angles[36],
        &array->angles[37],
        &array->angles[38],
        &array->angles[39]);

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

int sendFileTrajectory(char *s){
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

  ach_channel_t balance_cmd_chan;
  balance_cmd_t ladder_mode;
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


  sendFileTrajectory(s);

  fflush(stdout);

}
