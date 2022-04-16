void client_routine_stage_one(char temporary_receive_buffer[], const unsigned int receive_string_max_size, const int client_socket_filedescriptor, char * receive_buffer_associated_to_the_respective_client, char * whole_message_transmitted_flag, unsigned short int * the_current_stage_the_client_connection_is_active_in)
{
  //zero temporary receive buffer.
  //expecting to receive the nature of the request.
  unsigned short int temporary_receive_buffer_index = 0;
  while(temporary_receive_buffer_index < receive_string_max_size)
  {
    temporary_receive_buffer[temporary_receive_buffer_index] = '\0';
         
    //next character slot.
    temporary_receive_buffer_index = temporary_receive_buffer_index + 1;
  }
               
  //do receive operation.
  int total_received = recv(client_socket_filedescriptor, temporary_receive_buffer, receive_string_max_size, 0);
  if(total_received == -1)
  {
    //error occurrd durinf received.
    printf("error: %s\n", strerror(errno));
                
                
  }else if(total_received == 0){
    //do nothing when in stage zero and received no message.
                
                
  }else if(total_received > 0)
  {
    //the client partial or full message has been received.
    //do append
    strncat(receive_buffer_associated_to_the_respective_client, temporary_receive_buffer, total_received);
      
    //get current string length of recieve buffer.
    unsigned short int current_string_length = strlen(receive_buffer_associated_to_the_respective_client);
              
                
    //determine if stage zero can motion to stage one.
    //this is determined by string matching for stop sequence.
    if(current_string_length > 40)
    {
      unsigned short int consecutive_matches = 0;
      unsigned int whole_message_transmitted_flag_index = 0;
      unsigned int stop_sequence_detected = 0;
      unsigned int stop_sequence_detected_index = current_string_length - 40;
      while(stop_sequence_detected_index < current_string_length)
      {
        int match_detected = strncmp(receive_buffer_associated_to_the_respective_client+stop_sequence_detected_index, whole_message_transmitted_flag+whole_message_transmitted_flag_index, 1);
        if(match_detected != 0)
        {
          //stop comparing (purpose: to prevent known what would hve been loss).
          stop_sequence_detected_index = current_string_length;
                     
        }else if(match_detected == 0)
        {
          consecutive_matches = consecutive_matches + 1;
                     
          //next character to check for matching stop sequence.
          whole_message_transmitted_flag_index = whole_message_transmitted_flag_index + 1;
          stop_sequence_detected_index = stop_sequence_detected_index + 1;
        }
      }
                   
      //determine if the "whole message transmitted flag was transmitted".
      if(consecutive_matches == 40)
      {
        //whole message of the client' response has been received
        //switch to stage one.
        *the_current_stage_the_client_connection_is_active_in = 1;
      }
    }
  }
}


