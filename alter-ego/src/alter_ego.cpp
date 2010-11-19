/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "imago_c.h"

#define HELP(exe_name) do { printHelp(exe_name); return 0; } while(0)
#define CALL(func) do { if (!func) { fprintf(stderr, "%s\n", imagoGetLastError()); return 2; } } while(0)

void printHelp( const char *exe_name )
{
   fprintf(stderr, "Usage: %s [Options] <infile.png>\n\n"
      "Common usage examples:\n\n"
      "%s -q my-image.png\n"
      "%s my-image.png -o 1.mol -p recognized_molecules\n\n"
      "Options:\n"
      "    -o <outfile.mol>  If not mentioned molecule will be stored in <infile.mol>\n" 
      "    -h                Display this message\n"
      "    -b                Set binarization level (must be between 0 and 255)\n"
      "    -g                Do Gauss bluring\n"
      "    -q                Quiet mode - do not display log & enable -y\n"
      "    -p <directory>    Directory prefix for output file\n"
      "    -y                Yes - always try another settings if recognition failed\n"
      "    -n                No - do not try another settings if recognition failed\n", exe_name, exe_name, exe_name);
}

void formPrettyExeName( char *full )
{
   int n = strlen(full), i;

   for (i = n - 1; i >= 0; i--)
      if (full[i] == '\\' || full[i] == '/')
         break;

   if (i != 0)
   {
      i += 1;

      for (int j = 0; j < n - i; j++)
         full[j] = full[i + j];

      full[n - i] = 0;
   }
}

int main( int argc, char **argv )
{
   int bin_level = -1;
   char *in_file_name = 0, *out_file_name = 0, *out_directory_prefix = 0;
   bool no_output = false, standard_output = false, always_yes = false, ask = true;

   formPrettyExeName(argv[0]);

   qword id = imagoAllocSessionId();
   imagoSetSessionId(id);

   //Check & parse command-line parameters

   if (argc < 2)
   {
      HELP(argv[0]);
      imagoReleaseSessionId(id);
      return 0;
   }

   for (int i = 1; i < argc; i++)
   {
      char *str = argv[i];

      if (strcmp(str, "-g") == 0)
      {
         CALL(imagoSetFilter("blur"));
      }
      else if (strcmp(str, "-b") == 0)
      {
         if (++i == argc)
         {
            fprintf(stderr, "expected number after -b\n");
            imagoReleaseSessionId(id);
            return 1;
         }

         if (sscanf(argv[i], "%i", &bin_level) != 1 || bin_level < 0 || bin_level > 255)
         {
            fprintf(stderr, "%s is not valid binarization level", argv[i]);
            imagoReleaseSessionId(id);
            return 1;
         }

         CALL(imagoSetBinarizationLevel(bin_level));
      }
      else if (strcmp(str, "-y") == 0)
      {
         ask = false;
         always_yes = true;
      }
      else if (strcmp(str, "-h") == 0)
      {
         HELP(argv[0]);
      }
      else if (strcmp(str, "-q") == 0)
      {
         ask = false;
         always_yes = true;
         CALL(imagoDisableLog());
      }
      else if (strcmp(str, "-n") == 0)
      {
         ask = false;
         always_yes = false;
      }
      else if (strcmp(str, "-o") == 0)
      {
         if (++i == argc)
         {
            fprintf(stderr, "expected file name after -o\n");
            imagoReleaseSessionId(id);
            return 1;
         }

         out_file_name = argv[i];

         if (strcmp(out_file_name, "-") == 0)
            standard_output = true;
      }
      else if (strcmp(str, "-p") == 0)
      {
         if (++i == argc)
         {
            fprintf(stderr, "expected directory path after -p\n");
            imagoReleaseSessionId(id);
            return 1;
         }

         out_directory_prefix = argv[i];
      }
      else
      {
         in_file_name = argv[i];
         int n = strlen(in_file_name);

         if (in_file_name[n - 4] != '.')
            //if (strcmp(in_file_name + n - 4, ".png") != 0)
         {
            fprintf(stderr, "%s is unexpected file (not *.png)\n", in_file_name);
            imagoReleaseSessionId(id);
            return 1;
         }
      }
   }

   if (out_file_name == 0)
      no_output = true;

   if (in_file_name == 0)
   {
      fprintf(stderr, "no input file\n");
      imagoReleaseSessionId(id);
      return 1;
   }

   CALL(imagoLoadPngImageFromFile(in_file_name));

   int n = strlen(in_file_name), slash_delim = -1;

   for (int i = n - 1; i >= 0; i--)
   {
      if (in_file_name[i] == '\\' || in_file_name[i] == '/')
      {
         slash_delim = i;
         break;
      }
   }

   strcpy(in_file_name, in_file_name + slash_delim + 1);

   int cur_config = 0, configs_count = imagoGetConfigsCount();

   //Process data

   while (true)
   {
      int res = imagoRecognize();

      if (!res) //No result achieved
      {
         fprintf(stderr, "%s\n", imagoGetLastError());
         if (!ask) //Do not ask - '-y' or '-n' is set
         {
            if (always_yes)
            {
               if (cur_config == configs_count)
                  break;

               CALL(imagoSetConfigNumber(cur_config));
               cur_config++;
               continue;
            }
            else //Everything is not fine but work is finished
            {
               imagoReleaseSessionId(id);
               return 2;
            }
         }
         else //Ask if user wants to continue recognition 
         {
            char c;

            fprintf(stderr, "Imago could not recognize an image."
               "Try another settings? (Current config - #%i) [Y\\n]\n", cur_config);
            scanf("%c", &c);

            if (c == 'N' || c == 'n')
               return 2;
            else
            {
               CALL(imagoSetConfigNumber(cur_config));
               cur_config++;
               continue;
            }
         }
      }
      else //Everything is fine
      {
         break;
      }
   }

   //Write result in infile.mol
   if (no_output)
   {
      int n = strlen(in_file_name), k;

      k = n - 4;

      out_file_name = new char[n + 1];
      strcpy(out_file_name, in_file_name);
      strcpy(out_file_name + k + 1, "mol");
   }

   //Save molecule in file 
   if (!standard_output)
   {
      int n1 = strlen(out_file_name), n2;

      if (out_directory_prefix != 0)
         n2 = strlen(out_directory_prefix);
      else
         n2 = 0;

      char *output_name = new char[n1 + n2 + 2];

      if (out_directory_prefix != 0)
      {
         strcpy(output_name, out_directory_prefix);
         strcat(output_name, "/");
         strcat(output_name, out_file_name);
      }
      else
         strcpy(output_name, out_file_name);

      CALL(imagoSaveMolToFile(output_name));

      if (no_output)
         delete out_file_name;

      delete output_name;
   }
   else
   {
      int size;
      char *buf;

      CALL(imagoSaveMolToBuffer(&buf, &size));

      puts(buf);
   }

   imagoReleaseSessionId(id);

   return 0;
}
