short int extract_list_of_business_attributes_to_parseable_ram_step_one_determine_total_characters_of_line(FILE * business_attribute_file_dot_text)
{
  short int output = -1;
  
  char * character = 0;  while(character == 0){ character = (char *)malloc(2 * sizeof(char)); }  memset(character, '\0', 2);
  
  //keep reading until end of file or delmiter found.
  short int length = 0;
  unsigned short int keep_reading_character = 1;
  while(keep_reading_character == 1)
  {
    character[0] = '\0';
    fread(character, 1, 1, business_attribute_file_dot_text);
    int character_matches = strncmp(character, ";", 1);
    if(character_matches == 0)
    {
      length = length + 1;
      keep_reading_character = 0;
      output = length;
    }else{
      length = length + 1;
    }
  }
  
  free(character);
  
  return output;
}
