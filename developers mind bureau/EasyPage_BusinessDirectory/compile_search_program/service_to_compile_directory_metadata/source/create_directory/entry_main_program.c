#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//shasta exchange headers.
#include "./structure_string/structure_string.h"
#include "./extract_list_of_business_filenames_to_parseable_ram/extract_list_of_business_filenames_to_parseable_ram.h"

//shasta exchange definitions.
#include "./structure_string/structure_string.c"
#include "./extract_list_of_business_filenames_to_parseable_ram/extract_list_of_business_filenames_to_parseable_ram.c"

struct business_name_and_identification {
  unsigned long int identification_number;
  struct string * business_name;
};

struct business_id_and_per_character_location {
  unsigned long int identification_number;
  unsigned short int * per_character_sort_id;
};

int main()
{
  int output = 0;
 
  //get list of business filenames.
  char * absolute_file_path_directory_list_of_businesses = "/var/www/business_directory_content/list_of_businesses/list_of_businesses.text";
  FILE * list_of_businesses_dot_text = fopen(absolute_file_path_directory_list_of_businesses, "r");
  
    //determine total delemiters. (to estimate exact memory requirements, and ensuing knowable progress as opposed to coninutous work without knowing progress)
    unsigned long int list_of_business_records_total = extract_list_of_business_filenames_to_parseable_ram_step_one_determine_total_delmiters(list_of_businesses_dot_text);
  
    //expect to extract as many "filenames of businesses" as there are delemiters detected.
      //rewind the proverbial tape.
      fseek(list_of_businesses_dot_text, 0, SEEK_SET);
      
      //allocate strings to store the filenames of businesses.
      struct string * list_of_business_records = 0;
      while(list_of_business_records == 0){ list_of_business_records = (struct string *)malloc(list_of_business_records_total * sizeof(struct string)); }
   
      //for each business filename, store that file name into the list of business records.
      unsigned long int list_of_business_records_index = 0;
      while(list_of_business_records_index < list_of_business_records_total)
      {
        //determine how long the next filename of business is.
        short int length_of_next_filename_of_business = extract_list_of_business_filenames_to_parseable_ram_step_two_dash_a_determine_length_of_next_business_name(list_of_businesses_dot_text);
          //rewind to starting position of filename.
            //get current position.
            long int current_position = ftell(list_of_businesses_dot_text);
            //do set position to begining of filename.
            fseek(list_of_businesses_dot_text , (current_position-length_of_next_filename_of_business), SEEK_SET);
        
          //copy read filename from storage to business file name(list of business records by index).
            //allocate space.
            list_of_business_records[list_of_business_records_index].string_buffer = 0;
            while(list_of_business_records[list_of_business_records_index].string_buffer == 0){ list_of_business_records[list_of_business_records_index].string_buffer = (char *)malloc((length_of_next_filename_of_business+1) * sizeof(char)); }
            memset(list_of_business_records[list_of_business_records_index].string_buffer, '\0', (length_of_next_filename_of_business+1));
            list_of_business_records[list_of_business_records_index].string_buffer_memory_size = (length_of_next_filename_of_business+1);
            
            //read then copy from storage to list.
            fread(list_of_business_records[list_of_business_records_index].string_buffer, 1, (length_of_next_filename_of_business-1), list_of_businesses_dot_text);
         
            printf("%s\n", list_of_business_records[list_of_business_records_index].string_buffer);
          
            //read past the delimeter, prepares for the next round.
            char character[1];
            fread(character, 1, 1, list_of_businesses_dot_text);
              
          
        //next extract next record.
        list_of_business_records_index = list_of_business_records_index + 1;
      }
      
      fclose(list_of_businesses_dot_text);
   
   
  /* 
  //sort business names from a to z.
    //get list of the business names.
    char * root_folder_path_list_of_businesses = "/var/www/business_directory_content/list_of_businesses/";
    char * absolute_path_and_filename = 0;
    
    struct business_name_and_identification * list_of_unsorted_business_names = 0;
    while(list_of_unsorted_business_names == 0){ list_of_unsorted_business_names = (struct business_name_and_identification *)malloc(list_of_business_records_total * sizeof(struct business_name_and_identification)); }
    
    unsigned long int business_identification_number = 0;
    unsigned long int list_of_business_records_index = 0;
    while(list_of_business_records_index < list_of_business_records_total)
    {
        printf("%d\n", list_of_business_records[list_of_business_records_index].string_buffer_memory_size);
      //open business file, 
        //determined string length of absolute path abd file name.
        //unsigned int absolute_path_and_filename_string_string_length = strlen(root_folder_path_list_of_businesses)+list_of_business_records[list_of_business_records_index].string_buffer_memory_size;
        /*absolute_path_and_filename = 0;
        while(absolute_path_and_filename == 0){ absolute_path_and_filename = (char *)malloc(absolute_path_and_filename_string_string_length * sizeof(char)); }
        strcat(absolute_path_and_filename, root_folder_path_list_of_businesses);
        strcat(absolute_path_and_filename , list_of_business_records[list_of_business_records_index].string_buffer);
        printf("%s\n", absolute_path_and_filename);
        
        
      //cleanup
      free(absolute_path_and_filename);
      
      //next business
      list_of_business_records_index = list_of_business_records_index + 1;
    }
    
    //do sort
      //allocate the assocated sorting id.
      
      


  int a = 0;
  a = a + 1;
  */
  return output;   
}
