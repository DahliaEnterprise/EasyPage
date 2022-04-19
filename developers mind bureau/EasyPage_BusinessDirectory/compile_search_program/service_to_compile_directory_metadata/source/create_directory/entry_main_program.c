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
  struct string * business_filename;
};

struct business_id_and_per_character_location {
  unsigned long int business_identification_number;
  unsigned short int * per_character_sort_id;
  //unsigned short int * flag_character_slot_as_space; //this can be replaced using max detected string length.
  
};

int main()
{
  int output = 0;
 
  //define root path folder to not yet compiled content.
  char * root_folder_path_list_of_businesses = "/var/www/business_directory_content/list_of_businesses/";
  char * absolute_path_and_filename = 0;
  unsigned short int absolute_path_and_filename_string_length = 0;
 
  //get list of business filenames.
  absolute_path_and_filename_string_length = strlen(root_folder_path_list_of_businesses)+23;
  while(absolute_path_and_filename == 0){ absolute_path_and_filename = (char *)malloc((absolute_path_and_filename_string_length+1) * sizeof(char)); } 
  memset(absolute_path_and_filename, '\0', absolute_path_and_filename_string_length+1); 
  strcat(absolute_path_and_filename, root_folder_path_list_of_businesses);
  strcat(absolute_path_and_filename, "list_of_businesses.text");
  FILE * list_of_businesses_dot_text = fopen(absolute_path_and_filename, "r");
  free(absolute_path_and_filename);
  
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
         
         
            //read past the delimeter, prepares for the next round.
            char character[1];
            fread(character, 1, 1, list_of_businesses_dot_text);
              
          
        //next extract next record.
        list_of_business_records_index = list_of_business_records_index + 1;
      }
      
      fclose(list_of_businesses_dot_text);
      
  //sort business names from a to z.
    //initialize and define memory of business names to sort.
      //allocate memory for business sort names.
      struct business_name_and_identification * business_file = 0;
      while(business_file == 0){ business_file = (struct business_name_and_identification *)malloc(list_of_business_records_total * sizeof(struct business_name_and_identification)); } memset(business_file, '\0', list_of_business_records_total);
      
      struct business_id_and_per_character_location * business_file_sort_information = 0;
      while(business_file_sort_information == 0){ business_file_sort_information = (struct business_id_and_per_character_location *)malloc(list_of_business_records_total * sizeof(struct business_id_and_per_character_location)); } memset(business_file_sort_information, '\0', list_of_business_records_total);
      
      //load initialize memory of businesses
      unsigned short int max_search_business_name_detected = 0;
      unsigned long int business_identification_number = 0;
    
      char * character_table =  "abcdefghijklmnopqrstuvwxyz";
      //parse each character within the business name and assign it a number value per character.
      list_of_business_records_index = 0;
      while(list_of_business_records_index < list_of_business_records_total)
      {
        //define identification number.
        business_file[list_of_business_records_index].identification_number = business_identification_number;
        
        //allocate and define business filename.
        business_file[list_of_business_records_index].business_filename = 0;
        while(business_file[list_of_business_records_index].business_filename == 0){ business_file[list_of_business_records_index].business_filename = (struct string *)malloc(sizeof(struct string)); } memset(business_file[list_of_business_records_index].business_filename, '\0', sizeof(struct string));
       
        business_file[list_of_business_records_index].business_filename->string_buffer = 0;
        while(business_file[list_of_business_records_index].business_filename->string_buffer == 0){ business_file[list_of_business_records_index].business_filename->string_buffer = (char *)malloc((strlen(list_of_business_records[list_of_business_records_index].string_buffer)+1) * sizeof(char)); } memset( business_file[list_of_business_records_index].business_filename->string_buffer , '\0', strlen(list_of_business_records[list_of_business_records_index].string_buffer)+1);
        list_of_business_records[list_of_business_records_index].string_buffer_memory_size = (strlen(list_of_business_records[list_of_business_records_index].string_buffer)+1);
        
        //allocate and define sort information.
          //define business id to associate information.
          business_file_sort_information[list_of_business_records_index].business_identification_number = business_identification_number;
          
          //initialize per character sort id.
          business_file_sort_information[list_of_business_records_index].per_character_sort_id = 0;
          while(business_file_sort_information[list_of_business_records_index].per_character_sort_id == 0){ business_file_sort_information[list_of_business_records_index].per_character_sort_id = (unsigned short int *)malloc(strlen(list_of_business_records[list_of_business_records_index].string_buffer) * sizeof(unsigned short int)); } memset(business_file_sort_information[list_of_business_records_index].per_character_sort_id, '\0', strlen(list_of_business_records[list_of_business_records_index].string_buffer));
        
          //open business file to define "per character sort id".
          absolute_path_and_filename = 0;
          absolute_path_and_filename_string_length = strlen(root_folder_path_list_of_businesses)+strlen(list_of_business_records[list_of_business_records_index].string_buffer);
          while(absolute_path_and_filename == 0){ absolute_path_and_filename = (char *)malloc((absolute_path_and_filename_string_length+1) * sizeof(char)); } 
          memset(absolute_path_and_filename, '\0', absolute_path_and_filename_string_length+1); 
          strcat(absolute_path_and_filename, root_folder_path_list_of_businesses);
          strcat(absolute_path_and_filename, list_of_business_records[list_of_business_records_index].string_buffer);
          //FILE * list_of_businesses_dot_text = fopen(absolute_path_and_filename, "r");
          printf("new: %s\n", absolute_path_and_filename);
          
        
        //next business to assign characters number values.
        list_of_business_records_index = list_of_business_records_index + 1;
      }
  
  return output;   
}
