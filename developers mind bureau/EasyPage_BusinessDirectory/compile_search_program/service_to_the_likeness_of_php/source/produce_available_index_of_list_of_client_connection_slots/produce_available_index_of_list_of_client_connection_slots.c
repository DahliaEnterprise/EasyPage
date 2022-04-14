
unsigned short int produce_available_index_of_list_of_client_connection_slots(unsigned short int * list_of_flags_indicating_active_clients, unsigned short int size_of_concurrent_connections)
{
  unsigned short int output = 0;
  
  unsigned short int index = 0;
  while(index < size_of_concurrent_connections)
  {
   if(list_of_flags_indicating_active_clients[index] == 0)
   { 
    output = index;
    
    //stop searching
    index = size_of_concurrent_connections;
    
   }else{
    //next slot to check
    index = index + 1;
    
   }
  }

  return output;
}
