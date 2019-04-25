#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "md5.h"

const int PASS_LEN=20;        // Maximum any password will be
const int HASH_LEN=33;        // Length of MD5 hash strings

int file_length(char *filename)
{
	struct stat info;
	if (stat(filename, &info) == -1) return -1;
	else return info.st_size;
	
}

// Given a hash and a plaintext guess, return 1 if
// the hash of the guess matches the given hash.
// That is, return 1 if the guess is correct.
int tryguess(char *hash, char *guess)
{
    // Hash the guess using MD5
    void *check =  md5(guess, file_length(guess));
    // Compare the two hashes
    if (check == hash) {free(check); return 1;} 
    // Free any malloc'd memory
    else {free(check); return 0;}
}

// Read in the dictionary file and return the array of strings
// and store the length of the array in size.
// This function is responsible for opening the dictionary file,
// reading from it, building the data structure, and closing the
// file.
char **read_dictionary(char *filename, int *size)
{
    int len = file_length(filename);
    printf("check two:  %d\n", len);
    char * contents = malloc(sizeof(char) * len);
    printf("check three\n");
    FILE * f = NULL;
    printf("check four\n");
    f = fopen(filename, "r");
    printf("check five\n");
    if (!f)
    {
        printf("Can't open for reading\n");
        exit(1);
        
    }
    
    fread(contents, 1, len, f);
    fclose(f);
    
    int passcount;
    printf("check six\n");
    for (int k = 0; k < len; k++)
    {
        if (contents[k] == '\n') 
        {
            contents[k] = '\0';
            passcount++;
        }
        
    }
    
    char **dictionary = malloc(passcount * sizeof(char *)); 
    printf("check seven\n");
    dictionary[0] = contents;
    int j = 1;
    
    for (int i = 0; i < len; i++)
    {
        if (contents[i] == '\n') 
        {
            dictionary[j] = &contents[i+1];
            j++;
        }    
    }
    
    *size = len;
   printf("check eight\n"); 
    return dictionary;
        
}
  
    
int main(int argc, char *argv[])
{
    printf("check one\n");
    
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // Read the dictionary file into an array of strings.
    int hlen = file_length(argv[1]);
    int dlen = file_length(argv[2]);
    
    printf("dlen: %d hlen: %d\n", dlen, hlen);
    
    char **dict = read_dictionary(argv[2], &dlen);
    
    // Open the hash file for reading.
    
    FILE *e = fopen(argv[1], "r");
    if (!e)
    {
        printf("Can't open for reading\n");
        exit(1);
        
    }
    
    FILE *f = fopen(argv[2], "r");
    if (!f)
    {
        printf("Can't open for reading\n");
        exit(1);
        
    }
    printf("check nine\n"); 
    //char *hash = malloc(file_length(*f));
    char *hashfile;
    char *passfile;
    
    //fread(hashfile, 1, len, f);
    //fclose(f);
    
    char *hashwrite;
    char *passwrite;
    
    
    // For each hash, try every entry in the dictionary.
    printf("check ten\n"); 
    while (fgets(passwrite, PASS_LEN, f)!= NULL)
    {
        printf("loop check\n");
        
        while (fgets(hashwrite, HASH_LEN, e)!= NULL)
        {
            if (tryguess(hashfile, passfile) == 1) printf("%s , %s", hashfile, passfile);
        }
        
        // Print the matching dictionary entry.
    }
    printf("check eleven\n"); 
    // Need two nested loops.
}
