#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
void listContent(char *path, char *relPath);
int main (int narg, char *argv[]) {
printf ("Begin...");
if (narg != 2) {
printf ("Wrong arguments!");
return 1;
}
listContent(argv[1], ".");
printf ("FINISH!");
return EXIT_SUCCESS;
}
void listContent(char *path, char *relPath) {
DIR *dp;
struct dirent *ep;
dp = opendir (path);
char content[500];
content[0] = '\0';
char newPath[500];
char newRelPath[500];
if (dp != NULL) {
printf( "%s:\n", relPath);
while (ep = readdir (dp)) {
if (strcmp(ep-> d_name , ".") != 0) {
if (strcmp(ep->d_name, "..") != 0) {
strcat (content, ep->d_name);
strcat (content, " ");
}
}
}
printf ("%s\n\n", content);
(void) closedir (dp);
dp = opendir (path);
while (ep = readdir (dp)) {
if (strcmp(ep->d_name, ".") != 0) {
if (strcmp(ep->d_name, "..") != 0) {
if (ep->d_type == DT_DIR) {
strcpy(newPath, path);
strcat(newPath, "/");
strcat(newPath, ep->d_name);
strcpy(newRelPath, relPath);
strcat(newRelPath, "/");
strcat(newRelPath, ep->d_name);
listContent(newPath, newRelPath);
}
}
}
}
(void) closedir (dp);
}}