
int extract_list_of_business_filenames_to_parseable_ram(struct string * list_of_business_records, unsigned long int * list_of_business_records_total)
{
  int output = -1;
  
  //have a list of filenames representing business names at tbe ready.
  char * absolute_file_path_directory_list_of_businesses = "/var/www/business_directory_content/list_of_businesses/list_of_businesses.text";
  FILE * list_of_businesses_dot_text = fopen(absolute_file_path_directory_list_of_businesses, "r");
  
  long int total_characters = 0;
  if(list_of_businesses_dot_text != NULL)
  {
    fseek(list_of_businesses_dot_text, 0, SEEK_END);
    total_characters = ftell(list_of_businesses_dot_text);
    fseek(list_of_businesses_dot_text, 0, SEEK_SET);
   
    //determine total new lines. ";" is the delimter.
    char character[2] = "\0\0";
    unsigned long int total_delimeters = 0;
    unsigned long int list_of_businesses_dot_text_index = 0;
    while(list_of_businesses_dot_text_index < total_characters)
    {
     fread(character, 1, 1, list_of_businesses_dot_text);
     int character_matches = strncmp(character, ";", 1);
     if(character_matches == 0)
     {
       total_delimeters = total_delimeters + 1;
     }
    
      //next character within index.
      list_of_businesses_dot_text_index = list_of_businesses_dot_text_index + 1;
    }
    
    //define total businesses within list.
    *list_of_business_records_total = total_delimeters;
    
    //extract as many lines as their are delimeters detected.
      //rewind the proverbial tape.
      fseek(list_of_businesses_dot_text, 0, SEEK_SET);
      
      //allocate as many string structures as their are total delemiters
      while(list_of_business_records == 0){ list_of_business_records = (struct string *)malloc(total_delimeters * sizeof(struct string)); }
    
      //for each business filename, store that file name into the list of business records.
      unsigned int start_of_business_filename = 0;
      unsigned int end_of_business_filename = 0;
      unsigned int list_of_business_records_index = 0;
      list_of_businesses_dot_text_index = 0;
      while(list_of_business_records_index < total_delimeters)
      {
        //keep reading until end of file or delmiter found.
        unsigned short int keep_reading_character = 1;
        while(keep_reading_character == 1)
        {
          fread(character, 1, 1, list_of_businesses_dot_text);
          int character_matches = strncmp(character, ";", 1);
          if(character_matches == 0)
          {
            //extract filename
            char * business_filename = 0;
            unsigned int filename_length = end_of_business_filename - start_of_business_filename;
            while(business_filename == 0){ business_filename = (char *)malloc((filename_length+1) * sizeof(char)); }
            memset(business_filename, '\0', (filename_length+1));
            fseek(list_of_businesses_dot_text, start_of_business_filename, SEEK_SET);
            fread(business_filename, 1, filename_length, list_of_businesses_dot_text);
         
            //store filename to be used later.
              //allocate.
              list_of_business_records[list_of_business_records_index].string_buffer = 0;
              while(list_of_business_records[list_of_business_records_index].string_buffer == 0){ list_of_business_records[list_of_business_records_index].string_buffer = (char *)malloc((filename_length+1) * sizeof(char)); }
              memset(list_of_business_records[list_of_business_records_index].string_buffer, '\0', (filename_length+1));
              list_of_business_records[list_of_business_records_index].string_buffer_memory_size = (filename_length+1);
             
              //store
              strcat(list_of_business_records[list_of_business_records_index].string_buffer, business_filename);
              printf("%s\n", list_of_business_records[list_of_business_records_index].string_buffer);
            //next segment
              //start past delimeter.
              end_of_business_filename = end_of_business_filename + 2;
              start_of_business_filename = end_of_business_filename;
              
              //read past the delimeter.
              fread(character, 1, 2, list_of_businesses_dot_text);
              
              //break out of parse by character loop.
              keep_reading_character = 0;
              
              //delete,free temporary variables.
              free(business_filename);
              
          }else if(character_matches != 0)
          {
            //next character in search of ";" delimeter.
            end_of_business_filename = end_of_business_filename + 1;
            
          }
        }
        
        //next line
        list_of_business_records_index = list_of_business_records_index + 1;
      }
    fclose(list_of_businesses_dot_text);
   
   output = 1;
    
  }else if(list_of_businesses_dot_text == NULL)
  {
    output = -2;
  }
  
  return output;
}
