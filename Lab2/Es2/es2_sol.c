#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#define BUF_SIZE 1024
void copyDirectory (char *srcFile, char *dstFile);
void copyFile (char *srcFile, char *dstFile);
int main (int narg, char *argv[]){
if (narg !=3){
printf ("Wrong inputs, Please specify two inputs\n");
return 1; }
char path1[500];
char path2[500];
strcpy (path1, argv[1]);
strcpy (path2, argv[2]);
copyDirectory(path1, path2);
return 0;}
// Fucntion for Generat // Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat // Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat // Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat // Fucntion for Generating and Copying a File ing and Copying a Fileing and Copying a Fileing and Copying a Fileing and Copying a Fileing and Copying a Fileing and Copying a Fileing and Copying a File ing and Copying a Fileing and Copying a Fileing and Copying a File ing and Copying a Fileing and Copying a Fileing and Copying a Fileing and Copying a Fileing and Copying a Fileing and Copying a File ing and Copying a File
void copyFile (char *srcFile, char *dstFile)
{
int inputFd;
int outputFd;
int openFlags;
char buf[BUF_SIZE];
mode_t filePerms;
ssize_t numRead;
inputFd =open(srcFile, O_RDONLY);
if (inputFd == -1)
{
printf ( "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", "opening file %s", srcFile);
}
openFlags = O_CREAT | O_WRONLY | O_TRUNC;
filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
outputFd = open (dstFile, openFlags, filePerms);
if (outputFd == -1){
Printf ("opening file %s", dstFile); }
while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
printf ("%d", numRead);
if (write(outputFd, buf, numRead) != numRead)
printf ("couldn't write whole buffer""couldn't write whole buffer""couldn't write whole buffer""couldn't write whole buffer""couldn't write whole buffer" "couldn't write whole buffer""couldn't write whole buffer""couldn't write whole buffer" "couldn't write whole buffer""couldn't write whole buffer" "couldn't write whole buffer""couldn't write whole buffer""couldn't write whole buffer""couldn't write whole buffer""couldn't write whole buffer""couldn't write whole buffer" "couldn't write whole buffer""couldn't write whole buffer" "couldn't write whole buffer""couldn't write whole buffer""couldn't write whole buffer");}
if (numRead == -1)
printf("read");
if (close(inputFd) == -1)
printf ("close input");
if (close(outputFd) == -1)
printf ("close output");
}
// Fucntion for Generat // Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat // Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat // Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat// Fucntion for Generat // Fucntion for Generating and Copying a Directory ing and Copying a Directorying and Copying a Directorying and Copying a Directorying and Copying a Directorying and Copying a Directorying and Copying a Directorying and Copying a Directory ing and Copying a Directorying and Copying a Directorying and Copying a Directory ing and Copying a Directorying and Copying a Directorying and Copying a Directorying and Copying a Directorying and Copying a Directory ing and Copying a Directorying and Copying a Directory ing and Copying a Directorying and Copying a Directory
void copyDirectory (char *srcPath, char *dstPath){
char dstPath_new[500];
char srcPath_new[500];
char dstFile[500];
char srcFile[500];
struct dirent *srcDir_f;
DIR *srcDir =opendir (srcPath);
while( srcDir_f=readdir (srcDir) ){
if (strcmp(srcDir_f-> d_named_named_named_named_named_name , ".""."".") != 0){
if (strcmp(srcDir_f-> d_named_named_named_named_named_name , "..""..""..""..") != 0){
if ( srcDir_f-> d_type == DT_DIR ){ strcpy (dstPath_new, dstPath);
strcat (dstPath_new, "/");
strcat (dstPath_new, srcDir_f->d_name);
mkdir (dstPath_new, 0777);
strcpy (srcPath_new, srcPath);
strcat (srcPath_new, "/");
strcat (srcPath_new, srcDir_f->d_name);
copyDirectory(srcPath_new, dstPath_new);}
if ( srcDir_f->d_type == DT_REG ){
strcpy (dstFile, dstPath);
strcat (dstFile, "/");
strcat (dstFile, srcDir_f->d_name);
strcpy (srcFile, srcPath);
strcat (srcFile, "/");
strcat (srcFile, srcDir_f->d_name);
copyFile(srcFile, dstFile );}
}
}
}
closedir (srcDir);
}
