#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//shasta exchange headers.
#include "./structure_string/structure_string.h"
#include "./extract_list_of_business_filenames_to_parseable_ram/extract_list_of_business_filenames_to_parseable_ram.h"

//shasta exchange definitions.
#include "./structure_string/structure_string.c"
#include "./extract_list_of_business_filenames_to_parseable_ram/extract_list_of_business_filenames_to_parseable_ram.c"
#include "./extract_list_of_business_attributes_to_parseable_ram/extract_list_of_business_attributes_to_parseable_ram.c"


struct business_name_and_identification {
  unsigned long int identification_number;
  struct string * business_filename;
};

struct business_id_and_per_character_location {
  unsigned long int business_identification_number;
  unsigned short int * per_character_sort_id;
  unsigned short int per_character_sort_id_length;
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
      while(business_file == 0){ business_file = (struct business_name_and_identification *)malloc(list_of_business_records_total * sizeof(struct business_name_and_identification)); } 
      
      struct business_id_and_per_character_location * business_file_sort_information = 0;
      while(business_file_sort_information == 0){ business_file_sort_information = (struct business_id_and_per_character_location *)malloc(list_of_business_records_total * sizeof(struct business_id_and_per_character_location)); } 
      //load initialize memory of businesses
      unsigned short int max_sort_business_name_detected = 0;
      unsigned long int business_identification_number = 0;
    
      //initialize a temporary latch and content storage string.
      char * temporary_latch_and_content_storage_string = 0;
    
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
          
        
          //open business file to define "per character sort id".
          absolute_path_and_filename = 0;
          absolute_path_and_filename_string_length = strlen(root_folder_path_list_of_businesses)+strlen(list_of_business_records[list_of_business_records_index].string_buffer); while(absolute_path_and_filename == 0){ absolute_path_and_filename = (char *)malloc((absolute_path_and_filename_string_length+1) * sizeof(char)); } memset(absolute_path_and_filename, '\0', absolute_path_and_filename_string_length+1); 
          strcat(absolute_path_and_filename, root_folder_path_list_of_businesses);
          strcat(absolute_path_and_filename, list_of_business_records[list_of_business_records_index].string_buffer);
          FILE * business_attribute_file_dot_text = fopen(absolute_path_and_filename, "r");
          printf("\n--------\n");
          if(business_attribute_file_dot_text == NULL)
          {
            printf("\nfailutre\n");
          }
          printf(absolute_path_and_filename);
          printf("\n--------\n");
          free(absolute_path_and_filename);
          
          //find the business sort latch content pair.
          char * business_sort_title = 0;
          unsigned short int latch_content_pair_found = 0;
          while(latch_content_pair_found == 0)
          {
            //determine how long the next latch and content value is.
            short int length_of_next_latch_and_content_line = extract_list_of_business_attributes_to_parseable_ram_step_one_determine_total_characters_of_line(business_attribute_file_dot_text);
              //rewind to starting position of filename.
                //get current position.
                long int current_position = ftell(business_attribute_file_dot_text);
                //do set position to begining of filename.
                fseek(business_attribute_file_dot_text , (current_position-length_of_next_latch_and_content_line), SEEK_SET);
                
           
            //read then copy from storage to temporary string for parse/interpretation.
            temporary_latch_and_content_storage_string = 0;
            while(temporary_latch_and_content_storage_string == 0){ temporary_latch_and_content_storage_string = (char *)malloc((length_of_next_latch_and_content_line+1) * sizeof(char)); } memset(temporary_latch_and_content_storage_string, '\0', (length_of_next_latch_and_content_line+1));
            fread(temporary_latch_and_content_storage_string, 1, (length_of_next_latch_and_content_line), business_attribute_file_dot_text);
         
            
            int compare_return_code = strncmp(temporary_latch_and_content_storage_string, "business_sort_title", 19);
            if(compare_return_code == 0)
            {
              printf("%s\n", temporary_latch_and_content_storage_string);
              
              //isolate the content section of the latch content pair.
              unsigned int start_isolate_index = 20;
              unsigned int end_isolate_index = length_of_next_latch_and_content_line-1;
              unsigned int business_sort_title_length = end_isolate_index - start_isolate_index;
              business_sort_title = 0;
              while(business_sort_title == 0){ business_sort_title = (char *)malloc((business_sort_title_length+1) * sizeof(char)); } memset(business_sort_title, '\0', (business_sort_title_length+1));
              strncat(business_sort_title, temporary_latch_and_content_storage_string+start_isolate_index, business_sort_title_length);
              
              //determine the coresponding "per character id" based upon the "business sort title".
                //initialize per character sort id.
                business_file_sort_information[list_of_business_records_index].per_character_sort_id = 0;
                while(business_file_sort_information[list_of_business_records_index].per_character_sort_id == 0){ business_file_sort_information[list_of_business_records_index].per_character_sort_id = (unsigned short int *)malloc((business_sort_title_length) * sizeof(unsigned short int)); } memset(business_file_sort_information[list_of_business_records_index].per_character_sort_id, '\0', (business_sort_title_length));
                business_file_sort_information[list_of_business_records_index].per_character_sort_id_length = business_sort_title_length;
                
                //define from left to right the corresponding character id.
                unsigned int per_character_id_index = 0;
                while(per_character_id_index < business_sort_title_length)
                {
                  //loop through the character table to determine the character id
                  unsigned short int character_table_index = 0;
                  while(character_table_index < 26)
                  {
                    if(strncmp(character_table+character_table_index, business_sort_title+per_character_id_index, 1) == 0)
                    {
                      business_file_sort_information[list_of_business_records_index].per_character_sort_id[per_character_id_index] = character_table_index;
                      printf("%hu\n", business_file_sort_information[list_of_business_records_index].per_character_sort_id[per_character_id_index]);
                      
                      //end search
                      character_table_index = 26;
                    }else{
                      //next character to compare
                      character_table_index = character_table_index + 1;
                    }
                  }
                  
                  //move on to next character id slot.
                  per_character_id_index = per_character_id_index + 1;
                }
                
                //free(business_sort_title);
              printf("stop search\n");
              
               //read past the delimeter, prepares for the next round.
               char character[1];
               fread(character, 1, 1, business_attribute_file_dot_text);
            
              
              //stop search.
              latch_content_pair_found = 1;
            }
            
            
            free(temporary_latch_and_content_storage_string);
           
           //
          }
          
          //temp end
          //list_of_business_records_index = list_of_business_records_total;
          
        //next business to assign characters number values.
        list_of_business_records_index = list_of_business_records_index + 1;
      }
      
      printf("temp\n");
  
  return output;   
}
