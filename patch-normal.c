#include <stdio.h>
#include <stdlib.h>

// Patches falloutw.exe to fix a null pointer bug

int main(void) {
  printf("[+] Opening falloutw.exe to be patched\n");
  FILE* gameFile = fopen("falloutw.exe", "r+");

  unsigned int caveOffset = 0xA9B9;
  char patchFunction[]  = //
    "\x90\x90\x90\x90\x90\x90\x90\x90\x8B\x5E\x04\x8B\x16"
    "\x83\xF8\x00\x74\x05\xE8\xC0\xD8\x00\x00\xE9\x0F\xDA"
    "\x00\x00\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
    "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
    "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
  fseek(gameFile, caveOffset, SEEK_SET);
  fwrite(&patchFunction, sizeof(patchFunction)-1, 1, gameFile);

  int hookOffset = 0x183DF;
  char hookFunction[] = //
    "\xE9\xDD\x25\xFF\xFF\x90\x90\x90\x90\x90";
  fseek(gameFile, hookOffset, SEEK_SET);
  fwrite(&hookFunction, sizeof(hookFunction)-1, 1, gameFile);

  fclose(gameFile);
  printf("[+] Game patched");

  return 0;
}
